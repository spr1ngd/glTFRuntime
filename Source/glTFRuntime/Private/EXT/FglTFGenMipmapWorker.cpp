#include "EXT/FglTFGenMipmapWorker.h"

#include "ImageUtils.h"

FglTFGenMipmapWorker::FglTFGenMipmapWorker()
{
	
}

FglTFGenMipmapWorker::~FglTFGenMipmapWorker()
{
	if( nullptr != Thread )
		delete Thread;
}

bool FglTFGenMipmapWorker::Init()
{
	return true;
}

uint32 FglTFGenMipmapWorker::Run()
{
	TArray64<FColor> UncompressedColors;

	if (FMath::IsPowerOfTwo(Width) && FMath::IsPowerOfTwo(Height))
	{
		NumOfMips = FMath::FloorLog2(FMath::Max(Width, Height)) + 1;
		NumOfMips = FMath::Max(NumOfMips, 5);
			
		for (int32 MipY = 0; MipY < Height; MipY++)
		{
			for (int32 MipX = 0; MipX < Width; MipX++)
			{
				int64 MipColorIndex = ((MipY * Width) + MipX) * 4;
				uint8 MipColorB = UncompressedBytes[MipColorIndex];
				uint8 MipColorG = UncompressedBytes[MipColorIndex + 1];
				uint8 MipColorR = UncompressedBytes[MipColorIndex + 2];
				uint8 MipColorA = UncompressedBytes[MipColorIndex + 3];
				UncompressedColors.Add(FColor(MipColorR, MipColorG, MipColorB, MipColorA));
			}
		}
	}

	int32 MipWidth = FMath::Max(Width / 2, 1);
    int32 MipHeight = FMath::Max(Height / 2, 1);

	for (int32 MipIndex = 1; MipIndex < NumOfMips; MipIndex++)
	{
		FglTFRuntimeMipMap MipMap(TextureIndex);
		MipMap.Width = MipWidth;
		MipMap.Height = MipHeight;

		// Resize Image
		if (MipIndex > 0)
		{
			TArray64<FColor> ResizedMipData;
			ResizedMipData.AddUninitialized(MipWidth * MipHeight);
			FImageUtils::ImageResize(Width, Height, UncompressedColors, MipWidth, MipHeight, ResizedMipData, sRGB, false);
			for (FColor& Color : ResizedMipData)
			{
				MipMap.Pixels.Add(Color.B);
				MipMap.Pixels.Add(Color.G);
				MipMap.Pixels.Add(Color.R);
				MipMap.Pixels.Add(Color.A);
			}
		}
		else
		{
			MipMap.Pixels = UncompressedBytes;
		}

		Mips.Add(MipMap);

		MipWidth = FMath::Max(MipWidth / 2, 1);
		MipHeight = FMath::Max(MipHeight / 2, 1);
	}

	if( GenMipmapCompleted.IsBound() )
	{
		GenMipmapCompleted.Execute(TextureIndex, Mips);
	}
	
	return 1;
}

void FglTFGenMipmapWorker::Stop()
{
	
}

void FglTFGenMipmapWorker::Exit()
{
	
}