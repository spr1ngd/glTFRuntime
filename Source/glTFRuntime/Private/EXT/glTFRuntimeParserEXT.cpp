#include "EXT/glTFRuntimeParserEXT.h"

FglTFRuntimeParserEXT::FglTFRuntimeParserEXT(TSharedRef<FJsonObject> JsonObject, const FMatrix& InSceneBasis, float InSceneScale)
	: FglTFRuntimeParser(JsonObject, InSceneBasis, InSceneScale)
{
	const FString BaseUrl = "/Game/Shared/Materials/glTF/Materials/";
	const FString Prefix = "M_Base_"; 

	const FString OpaqueMaterialName = *FString::Printf(TEXT("%s%s"), *Prefix, L"Opaque");
	UMaterialInterface* OpaqueMaterial = LoadObject<UMaterialInterface>(nullptr, *FString::Printf(TEXT("%s%s.%s"), *BaseUrl, *OpaqueMaterialName, *OpaqueMaterialName));
	if (OpaqueMaterial)
	{
		MetallicRoughnessMaterialsMap.Add(EglTFRuntimeMaterialType::Opaque, OpaqueMaterial);
	}

	const FString TranslucentMaterialName = *FString::Printf(TEXT("%s%s"), *Prefix, L"Translucent");
	UMaterialInterface* TranslucentMaterial = LoadObject<UMaterialInterface>(nullptr, *FString::Printf(TEXT("%s%s.%s"), *BaseUrl, *TranslucentMaterialName, *TranslucentMaterialName));
	if (OpaqueMaterial)
	{
		MetallicRoughnessMaterialsMap.Add(EglTFRuntimeMaterialType::Translucent, TranslucentMaterial);
	}

	const FString TwoSidedMaterialName = *FString::Printf(TEXT("%s%s"), *Prefix, L"TwoSided");
	UMaterialInterface* TwoSidedMaterial = LoadObject<UMaterialInterface>(nullptr, *FString::Printf(TEXT("%s%s.%s"), *BaseUrl, *TwoSidedMaterialName, *TwoSidedMaterialName));
	if (TwoSidedMaterial)
	{
		MetallicRoughnessMaterialsMap.Add(EglTFRuntimeMaterialType::TwoSided, TwoSidedMaterial);
	}

	const FString TwoSidedTranslucentMaterialName = *FString::Printf(TEXT("%s%s"), *Prefix, L"TwoSided_Translucent");
	UMaterialInterface* TwoSidedTranslucentMaterial = LoadObject<UMaterialInterface>(nullptr, *FString::Printf(TEXT("%s%s.%s"), *BaseUrl, *TwoSidedTranslucentMaterialName, *TwoSidedTranslucentMaterialName));
	if (TwoSidedTranslucentMaterial)
	{
		MetallicRoughnessMaterialsMap.Add(EglTFRuntimeMaterialType::TwoSidedTranslucent, TwoSidedTranslucentMaterial);
	}

	const FString MaskedMaterialName = *FString::Printf(TEXT("%s%s"), *Prefix, L"Masked");
	UMaterialInterface* MaskedMaterial = LoadObject<UMaterialInterface>(nullptr, *FString::Printf(TEXT("%s%s.%s"), *BaseUrl, *MaskedMaterialName, *MaskedMaterialName));
	if (TwoSidedTranslucentMaterial)
	{
		MetallicRoughnessMaterialsMap.Add(EglTFRuntimeMaterialType::Masked, MaskedMaterial);
	}
	
	const FString TwoSidedMaskedMaterialName = *FString::Printf(TEXT("%s%s"), *Prefix, L"TwoSided_Masked");
	UMaterialInterface* TwoSidedMaskedMaterial = LoadObject<UMaterialInterface>(nullptr, *FString::Printf(TEXT("%s%s.%s"), *BaseUrl, *TwoSidedMaskedMaterialName, *TwoSidedMaskedMaterialName));
	if (TwoSidedMaskedMaterial)
	{
		MetallicRoughnessMaterialsMap.Add(EglTFRuntimeMaterialType::TwoSidedMasked, TwoSidedMaskedMaterial);
	}

	// do not support SpecularGlossiness Material.
	// KHR_materials_pbrSpecularGlossiness
	UMaterialInterface* SGOpaqueMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/glTFRuntime/M_glTFRuntime_SG_Base"));
	if (SGOpaqueMaterial)
	{
		SpecularGlossinessMaterialsMap.Add(EglTFRuntimeMaterialType::Opaque, SGOpaqueMaterial);
	}
	
	UMaterialInterface* SGTranslucentMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/glTFRuntime/M_glTFRuntime_SG_Translucent_Inst"));
	if (SGTranslucentMaterial)
	{
		SpecularGlossinessMaterialsMap.Add(EglTFRuntimeMaterialType::Translucent, SGTranslucentMaterial);
	}
	
	UMaterialInterface* SGTwoSidedMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/glTFRuntime/M_glTFRuntime_SG_TwoSided_Inst"));
	if (SGTwoSidedMaterial)
	{
		SpecularGlossinessMaterialsMap.Add(EglTFRuntimeMaterialType::TwoSided, SGTwoSidedMaterial);
	}
	
	UMaterialInterface* SGTwoSidedTranslucentMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/glTFRuntime/M_glTFRuntime_SG_TwoSidedTranslucent_Inst"));
	if (SGTwoSidedTranslucentMaterial)
	{
		SpecularGlossinessMaterialsMap.Add(EglTFRuntimeMaterialType::TwoSidedTranslucent, SGTwoSidedTranslucentMaterial);
	}
}