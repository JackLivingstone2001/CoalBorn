#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WaveSaveGameBase.h"
#include "WaveGameInstanceBase.generated.h"

UCLASS()
class COALBORN_API UWaveGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()
	
public:
	void SetLoadedGame(UWaveSaveGameBase* loadedGame);
	UWaveSaveGameBase* GetLoadedGame();
private:
	UWaveSaveGameBase* m_loadedGame;
};