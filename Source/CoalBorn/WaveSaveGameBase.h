#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ClassPlayerCharacterBase.h"
#include "ClassPlayerControllerBase.h"
#include "WaveSaveGameBase.generated.h"

UCLASS()
class COALBORN_API UWaveSaveGameBase : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int CurrentRound = 1;
	UPROPERTY()
	TSubclassOf<AClassPlayerCharacterBase> CharacterClass;
	UPROPERTY()
	TSubclassOf<AClassPlayerControllerBase> ControllerClass;
};