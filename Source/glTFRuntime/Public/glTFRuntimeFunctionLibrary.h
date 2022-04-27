// Copyright 2020, Roberto De Ioris.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "glTFRuntimeAsset.h"
#include "glTFRuntimeWriter.h"
#include "glTFRuntimeFunctionLibrary.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FglTFRuntimeHttpResponse, UglTFRuntimeAsset*, Asset);

/**
 * 
 */
UCLASS()
class GLTFRUNTIME_API UglTFRuntimeFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(DisplayName="glTF Load Asset from Filename", AutoCreateRefTerm = "LoaderConfig"), Category="glTFRuntime")
	static UglTFRuntimeAsset* glTFLoadAssetFromFilename(const FString& Filename, const bool bPathRelativeToContent, const FglTFRuntimeConfig& LoaderConfig);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "glTF Load Asset from String", AutoCreateRefTerm = "LoaderConfig"), Category = "glTFRuntime")
	static UglTFRuntimeAsset* glTFLoadAssetFromString(const FString& JsonData, const FglTFRuntimeConfig& LoaderConfig);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "glTF Load Asset from Url", AutoCreateRefTerm = "LoaderConfig, Headers"), Category = "glTFRuntime")
	static void glTFLoadAssetFromUrl(const FString& Url, TMap<FString, FString>& Headers, FglTFRuntimeHttpResponse Completed, const FglTFRuntimeConfig& LoaderConfig);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "glTF Load Asset from Data", AutoCreateRefTerm = "LoaderConfig"), Category = "glTFRuntime")
	static UglTFRuntimeAsset* glTFLoadAssetFromData(const TArray<uint8>& Data, const FglTFRuntimeConfig& LoaderConfig);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", DisplayName = "glTF Save SkeletalMesh in File", AutoCreateRefTerm = "Animations, WriterConfig"), Category = "glTFRuntime")
	static bool glTFSaveSkeletalMeshToFile(UObject* WorldContextObject, USkeletalMesh* SkeletalMesh, const int32 LOD, const FString& Filename, const TArray<UAnimSequence*>& Animations, const FglTFRuntimeWriterConfig& WriterConfig);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", DisplayName = "glTF Save SkeletalMeshComponent in File", AutoCreateRefTerm = "Animations, WriterConfig"), Category = "glTFRuntime")
	static bool glTFSaveSkeletalMeshComponentToFile(UObject* WorldContextObject, USkeletalMeshComponent* SkeletalMeshComponent, const int32 LOD, const FString& Filename, const TArray<UAnimSequence*>& Animations, const FglTFRuntimeWriterConfig& WriterConfig);
};
