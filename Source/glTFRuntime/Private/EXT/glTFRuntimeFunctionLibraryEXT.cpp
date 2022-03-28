#include "EXT/glTFRuntimeFunctionLibraryEXT.h"
#include <functional>
#include "glTFRuntimeAssetActor.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceDynamic.h"

UStaticMesh* UglTFRuntimeFunctionLibraryEXT::glTFLoadStaticMesh(UglTFRuntimeAsset* Asset, int32 MeshIndex, FglTFRuntimeStaticMeshConfig& StaticMeshConfig)
{ 
	FMatrix Transform = FMatrix::Identity;
	std::function<void(TArray<int32>)> GetMatrix;
	
	GetMatrix = [Asset, &Transform, &GetMatrix, MeshIndex](TArray<int32> NodeIndices) {
		for( const int32 ChildIndex : NodeIndices ) {
			FglTFRuntimeNode Child;
			if (!Asset->GetNode(ChildIndex, Child)) {
				return;
			}
			Transform = Child.Transform.ToMatrixWithScale() * Transform;
			if (Child.MeshIndex == MeshIndex) {
				break;
			}
			GetMatrix(Child.ChildrenIndices);
		}
	};
	
	TArray<FglTFRuntimeScene> Scenes = Asset->GetScenes();
	for (const FglTFRuntimeScene& Scene : Scenes) {
		GetMatrix(Scene.RootNodesIndices);
	}

	StaticMeshConfig.LoadStaticMeshTransform = Transform * StaticMeshConfig.LoadStaticMeshTransform;
	return Asset->LoadStaticMesh(MeshIndex, StaticMeshConfig);
}

bool UglTFRuntimeFunctionLibraryEXT::IsglTFMaterialInstance(UMaterialInstance* MaterialInstance)
{
	return true;
}

UMaterialInstance* UglTFRuntimeFunctionLibraryEXT::BuildMaterialVariant(
	AglTFRuntimeAssetActor* Owner,
	UMaterialInstance* Origin, 
	EglTFRuntimeMaterialType newMaterilaType)
{
	UMaterialInterface* UberMaterial;
	if (newMaterilaType == EglTFRuntimeMaterialType::Opaque) {
		UberMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/glTFRuntime/M_glTFRuntimeBase"));
	}
	else if( newMaterilaType == EglTFRuntimeMaterialType::Translucent ) {
		UberMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/glTFRuntime/M_glTFRuntimeTranslucent_Inst"));
	}
	else if( newMaterilaType == EglTFRuntimeMaterialType::TwoSided ){
		UberMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/glTFRuntime/M_glTFRuntimeTwoSided_Inst"));
	}
	else if( newMaterilaType == EglTFRuntimeMaterialType::TwoSidedTranslucent ) {
		UberMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/glTFRuntime/M_glTFRuntimeTwoSidedTranslucent_Inst"));
	}
	else {
		return nullptr;
	}
	UMaterialInstanceDynamic* Material = UMaterialInstanceDynamic::Create(UberMaterial, UberMaterial);
	const FString materialName = *UEnum::GetValueAsName(newMaterilaType).ToString();
	Material->Rename(*FString::Printf(TEXT("glTFRuntime_Modifier_%s"), *materialName));
	Material->CopyParameterOverrides(Origin);
	return Material;
}
