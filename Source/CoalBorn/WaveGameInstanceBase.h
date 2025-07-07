#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WaveSaveGameBase.h"
#include "ClassPlayerCharacterBase.h"
#include "ClassPlayerControllerBase.h"
#include "WaveGameInstanceBase.generated.h"

UCLASS()
class COALBORN_API UWaveGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AClassPlayerCharacterBase> CharacterClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AClassPlayerControllerBase> ControllerClass;

	void SetLoadedGame(UWaveSaveGameBase* loadedGame);
	UWaveSaveGameBase* GetLoadedGame();
private:
	UWaveSaveGameBase* m_loadedGame;
};