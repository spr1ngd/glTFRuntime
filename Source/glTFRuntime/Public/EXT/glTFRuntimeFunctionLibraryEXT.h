#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "glTFRuntimeAsset.h"
#include "glTFRuntimeFunctionLibraryEXT.generated.h"

// author : spr1ngd
// desc   : glTFRuntime Plugin api extension 

UCLASS(Category="glTFRuntimeEXT")
class GLTFRUNTIME_API UglTFRuntimeFunctionLibraryEXT : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "glTFRuntimeEXT", meta= (DisplayName = "gltf Load Static Mesh from gltF Asset"))
	static UStaticMesh* glTFLoadStaticMesh(UglTFRuntimeAsset* Asset, int32 MeshIndex, FglTFRuntimeStaticMeshConfig& StaticMeshConfig);
	
	static bool IsglTFMaterialInstance(UMaterialInstance* MaterialInstance);
	
	static UMaterialInstance* BuildMaterialVariant(class AglTFRuntimeAssetActor* Owner, UMaterialInstance* Origin, EglTFRuntimeMaterialType newMaterilaType);
};
