#pragma once
#include "CoreMinimal.h"
#include "glTFLoaderConfigEXT.generated.h"

UCLASS(meta=(THINGAPI="*"))
class GLTFRUNTIME_API UglTFLoaderConfigEXT : public UObject 
{
	GENERATED_BODY()
public:

	UPROPERTY()
	bool bBuildSimpleCollision = false;
};
