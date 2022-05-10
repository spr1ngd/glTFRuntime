#pragma once
#include "glTFRuntimeParser.h"

DECLARE_DELEGATE_TwoParams(FglTFGenMipmapCompleted, const int32 TextureIndex, TArray<FglTFRuntimeMipMap>& Mips);

class FglTFGenMipmapWorker : public FRunnable
{
private:
	bool bThreadRunning = false;
	
public:
	FRunnableThread* Thread = nullptr;

	int32 NumOfMips = 0;
	TArray<uint8> UncompressedBytes;
	bool sRGB;
	int32 Width = 0;
	int32 Height = 0;
	int32 TextureIndex = 0;
	TArray<FglTFRuntimeMipMap> Mips;
	FglTFGenMipmapCompleted GenMipmapCompleted;
	
	FglTFGenMipmapWorker();
	~FglTFGenMipmapWorker() override;

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;
};
