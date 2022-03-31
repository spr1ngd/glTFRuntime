#include "EXT/glTFRuntimeAssetActorEXT.h"

void AglTFRuntimeAssetActorEXT::Play(FString animationName , float playSpeedRate)
{
	if( !DiscoveredCurveAnimationsNames.Contains(animationName) ) {
		UE_LOG(LogTemp,Log, TEXT("%s does not exist."), *animationName);
		return;
	}

	for (TPair<USceneComponent*, UglTFRuntimeAnimationCurve*>& Pair : CurveBasedAnimations) {
		TMap<FString, UglTFRuntimeAnimationCurve*> WantedCurveAnimationsMap = DiscoveredCurveAnimations[Pair.Key];
		if( WantedCurveAnimationsMap.Contains(animationName) ) {
			Pair.Value = WantedCurveAnimationsMap[animationName];
			CurveBasedAnimationsTimeTracker[Pair.Key] = 0;
		}
		if(!CurveBasedAnimationsTimeTrackerFactor.Contains(Pair.Key)) {
			CurveBasedAnimationsTimeTrackerFactor.Add(Pair.Key, 1.0f);
		}
		CurveBasedAnimationsTimeTrackerFactor[Pair.Key] = playSpeedRate;
	}
}

void AglTFRuntimeAssetActorEXT::Pause(FString animationName)
{
	if( !DiscoveredCurveAnimationsNames.Contains(animationName) ) {
		UE_LOG(LogTemp,Log, TEXT("%s does not exist."), *animationName);
		return;
	}

	for (TPair<USceneComponent*, UglTFRuntimeAnimationCurve*>& Pair : CurveBasedAnimations) {
		TMap<FString, UglTFRuntimeAnimationCurve*> WantedCurveAnimationsMap = DiscoveredCurveAnimations[Pair.Key];
		if( WantedCurveAnimationsMap.Contains(animationName) ) {
			Pair.Value = nullptr;
		}
		else {
			UE_LOG(LogTemp, Log, TEXT("%s is not playing."));
		}
	}
}

void AglTFRuntimeAssetActorEXT::Stop(FString animationName)
{
	if( !DiscoveredCurveAnimationsNames.Contains(animationName) ) {
		UE_LOG(LogTemp,Log, TEXT("%s does not exist."), *animationName);
		return;
	}

	for (TPair<USceneComponent*, UglTFRuntimeAnimationCurve*>& Pair : CurveBasedAnimations) {
		TMap<FString, UglTFRuntimeAnimationCurve*> WantedCurveAnimationsMap = DiscoveredCurveAnimations[Pair.Key];
		if(WantedCurveAnimationsMap.Contains(animationName)){
			if(!CurveBasedAnimationsTimeTrackerFactor.Contains(Pair.Key)) {
				CurveBasedAnimationsTimeTrackerFactor.Add(Pair.Key, 1.0f);
			}
			CurveBasedAnimationsTimeTrackerFactor[Pair.Key] = 0.0f;
		}
		else {
			UE_LOG(LogTemp, Log, TEXT("%s is not playing."));
		}
	}
}

void AglTFRuntimeAssetActorEXT::Resume(FString animationName)
{
	if( !DiscoveredCurveAnimationsNames.Contains(animationName) ) {
		UE_LOG(LogTemp,Log, TEXT("%s does not exist."), *animationName);
		return;
	}

	for (TPair<USceneComponent*, UglTFRuntimeAnimationCurve*>& Pair : CurveBasedAnimations) {
		TMap<FString, UglTFRuntimeAnimationCurve*> WantedCurveAnimationsMap = DiscoveredCurveAnimations[Pair.Key];
		if(WantedCurveAnimationsMap.Contains(animationName)){
			if(CurveBasedAnimationsTimeTrackerFactor.Contains(Pair.Key)) {
				CurveBasedAnimationsTimeTrackerFactor[Pair.Key] = 1.0f;
			}
		}
		else {
			UE_LOG(LogTemp, Log, TEXT("%s is not playing."));
		}
	}
}

TArray<FString> AglTFRuntimeAssetActorEXT::GetAnimationNames()
{
	TArray<FString> result;
	for( FString animName : DiscoveredCurveAnimationsNames ) {
		result.Push(animName);
	}
	return result;
}
