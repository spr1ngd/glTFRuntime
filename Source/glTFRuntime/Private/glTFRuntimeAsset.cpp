// Copyright 2020 Roberto De Ioris.


#include "glTFRuntimeAsset.h"

bool UglTFRuntimeAsset::LoadFromFilename(const FString Filename)
{
	// asset already loaded ?
	if (Parser)
		return false;

	Parser = FglTFRuntimeParser::FromFilename(Filename);
	if (!Parser)
		return false;

	return true;
}

TArray<FglTFRuntimeScene> UglTFRuntimeAsset::GetScenes()
{
	if (!Parser)
	{
		UE_LOG(LogTemp, Error, TEXT("No glTF Asset loaded."));
		return TArray<FglTFRuntimeScene>();
	}

	TArray<FglTFRuntimeScene> Scenes;
	if (!Parser->LoadScenes(Scenes))
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to retrieve Scenes from glTF Asset."));
		return TArray<FglTFRuntimeScene>();
	}
	return Scenes;
}

bool UglTFRuntimeAsset::GetNode(int32 Index, FglTFRuntimeNode& Node)
{
	if (!Parser)
	{
		UE_LOG(LogTemp, Error, TEXT("No glTF Asset loaded."));
		return false;
	}

	return Parser->LoadNode(Index, Node);
}

UStaticMesh* UglTFRuntimeAsset::LoadStaticMesh(int32 MeshIndex)
{
	return nullptr;
}

USkeletalMesh* UglTFRuntimeAsset::LoadSkeletalMesh(int32 MeshIndex, int32 SkinIndex)
{
	if (!Parser)
	{
		UE_LOG(LogTemp, Error, TEXT("No glTF Asset loaded."));
		return false;
	}

	return Parser->LoadSkeletalMesh(MeshIndex, SkinIndex);
}