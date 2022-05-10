#pragma once
#include "glTFRuntimeAssetActor.h"
#include "glTFRuntimeAssetActorAsync.h"
#include "glTFRuntimeAssetActorEXT.generated.h"

// author : spr1ngd
// desc   : add animation apis for AglTFRuntimeAssetActor

UCLASS(Blueprintable, BlueprintType, meta=(THINGAPI="*"))
class GLTFRUNTIME_API AglTFRuntimeAssetActorEXT : public AglTFRuntimeAssetActorAsync
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void Play(FString animationName, float playSpeedRate = 1.0f);
	UFUNCTION(BlueprintCallable)
	void Pause(FString animationName);
	UFUNCTION(BlueprintCallable)
	void Stop(FString animationName);
	UFUNCTION(BlueprintCallable)
	void Resume(FString animationName);
	// TODO: 需要ILWrapper导出支持
	// UFUNCTION(BlueprintCallable)
	TArray<FString> GetAnimationNames();
};
