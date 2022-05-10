#include "CoreMinimal.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Materials/MaterialInstanceDynamic.h"

class FglTFGenMipmaps
{
public:

	static TMap<int32, FRunnable*> SyncMipmapThreads;
	static UMaterialInstanceDynamic* ___;
	
	static UTextureRenderTarget2D* TextureToTextureRenderTarget2D(UTexture2D* Texture, bool sRGB = true)
	{
		auto Context = GWorld->GetGameInstance()->GetWorld();
		UTextureRenderTarget2D* RenderTarget = UKismetRenderingLibrary::CreateRenderTarget2D(
			Context,
			Texture->GetSizeX(),
			Texture->GetSizeY(),
			sRGB ? ETextureRenderTargetFormat::RTF_RGBA8_SRGB : ETextureRenderTargetFormat::RTF_RGBA8,
			FLinearColor::Transparent,
			true);
		if( !___ )
		{
			auto __ = LoadObject<UMaterialInterface>(nullptr, *FString::Printf(TEXT("/glTFRuntime/__/M___.M___")));
			___ = UKismetMaterialLibrary::CreateDynamicMaterialInstance(Context, __);
			___->AddToRoot();
		}
		___->SetTextureParameterValue("Texture", Texture);
		UKismetRenderingLibrary::DrawMaterialToRenderTarget(Context, RenderTarget, ___);
		return RenderTarget;
	}

	static void RebuildTextureMipmaps(UTexture2D* Texture, const TArray<FglTFRuntimeMipMap>& Mips)
	{
		FGraphEventRef Task = FFunctionGraphTask::CreateAndDispatchWhenReady([Texture,Mips](){
			if (IsInGameThread())
			{
				FTexturePlatformData* PlatformData = Texture->PlatformData;
				for (const FglTFRuntimeMipMap& MipMap : Mips)
				{
					FTexture2DMipMap* Mip = new FTexture2DMipMap();
					PlatformData->Mips.Add(Mip);
					Mip->SizeX = MipMap.Width;
					Mip->SizeY = MipMap.Height;
					Mip->BulkData.Lock(LOCK_READ_WRITE);
					void* Data = Mip->BulkData.Realloc(MipMap.Pixels.Num());
					FMemory::Memcpy(Data, MipMap.Pixels.GetData(), MipMap.Pixels.Num());
					Mip->BulkData.Unlock();
				}
				Texture->UpdateResource();
			}
		}, TStatId(), nullptr, ENamedThreads::GameThread);
		FTaskGraphInterface::Get().WaitUntilTaskCompletes(Task);
	}
};

UMaterialInstanceDynamic* FglTFGenMipmaps::___ = nullptr;
TMap<int32, FRunnable*> FglTFGenMipmaps::SyncMipmapThreads;