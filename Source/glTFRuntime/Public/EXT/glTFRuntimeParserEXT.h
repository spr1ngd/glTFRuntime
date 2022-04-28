#pragma once
#include "glTFRuntimeParser.h"

class GLTFRUNTIME_API FglTFRuntimeParserEXT : public FglTFRuntimeParser, public TSharedFromThis<FglTFRuntimeParserEXT>
{
public:
	FglTFRuntimeParserEXT(TSharedRef<FJsonObject> JsonObject, const FMatrix& InSceneBasis, float InSceneScale);
};