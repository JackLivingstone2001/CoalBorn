#include "MainMenuHUDBase.h"
#include <Kismet/GameplayStatics.h>
#include "WaveSaveGameBase.h"
#include "WaveGameInstanceBase.h"

void UMainMenuHUDBase::NativeConstruct()
{
	Super::NativeConstruct();

	CreateMinerGameButton->OnClicked.AddDynamic(this, &UMainMenuHUDBase::OnCreateMinerGameButtonClicked);
	LoadMinerGameButton->OnClicked.AddDynamic(this, &UMainMenuHUDBase::OnLoadMinerGameButtonClicked);

	CreateHealerGameButton->OnClicked.AddDynamic(this, &UMainMenuHUDBase::OnCreateHealerGameButtonClicked);
	LoadHealerGameButton->OnClicked.AddDynamic(this, &UMainMenuHUDBase::OnLoadHealerGameButtonClicked);

	CreateBrawlerGameButton->OnClicked.AddDynamic(this, &UMainMenuHUDBase::OnCreateBrawlerGameButtonClicked);
	LoadBrawlerGameButton->OnClicked.AddDynamic(this, &UMainMenuHUDBase::OnLoadBrawlerGameButtonClicked);

	CreateRangerGameButton->OnClicked.AddDynamic(this, &UMainMenuHUDBase::OnCreateRangerGameButtonClicked);
	LoadRangerGameButton->OnClicked.AddDynamic(this, &UMainMenuHUDBase::OnLoadRangerGameButtonClicked);
}

void UMainMenuHUDBase::OnCreateMinerGameButtonClicked()
{
	CreateSaveGame("MinerClassGame", MinerClassController, MinerClassCharacter);
}

void UMainMenuHUDBase::OnLoadMinerGameButtonClicked()
{
	LoadGame("MinerClassGame");
}

void UMainMenuHUDBase::OnCreateHealerGameButtonClicked()
{
	CreateSaveGame("HealerClassGame", HealerClassController, HealerClassCharacter);
}

void UMainMenuHUDBase::OnLoadHealerGameButtonClicked()
{
	LoadGame("HealerClassGame");
}

void UMainMenuHUDBase::OnCreateBrawlerGameButtonClicked()
{
	CreateSaveGame("BrawlerClassGame", BrawlerClassController, BrawlerClassCharacter);
}

void UMainMenuHUDBase::OnLoadBrawlerGameButtonClicked()
{
	LoadGame("BrawlerClassGame");
}

void UMainMenuHUDBase::OnCreateRangerGameButtonClicked()
{
	CreateSaveGame("RangerClassGame", RangerClassController, RangerClassCharacter);
}

void UMainMenuHUDBase::OnLoadRangerGameButtonClicked()
{
	LoadGame("RangerClassGame");
}

void UMainMenuHUDBase::CreateSaveGame(FString saveName, TSubclassOf<AClassPlayerControllerBase> controller, TSubclassOf<AClassPlayerCharacterBase> character)
{
	UWaveSaveGameBase* saveGame = Cast<UWaveSaveGameBase>(UGameplayStatics::CreateSaveGameObject(UWaveSaveGameBase::StaticClass()));
	saveGame->CurrentRound = 1;
	saveGame->ControllerClass = controller;
	saveGame->CharacterClass = character;

	bool wasSuccessful = UGameplayStatics::SaveGameToSlot(saveGame, saveName, 0);

	LoadGame(saveName);
}

void UMainMenuHUDBase::LoadGame(FString saveName)
{
	UWaveSaveGameBase* loadGame = Cast<UWaveSaveGameBase>(UGameplayStatics::LoadGameFromSlot(saveName, 0));
	if (!loadGame)
	{
		return;
	}

	UWaveGameInstanceBase* gameInstance = Cast<UWaveGameInstanceBase>(GetWorld()->GetGameInstance());
	if (gameInstance)
	{
		gameInstance->SetLoadedGame(loadGame);
		gameInstance->ControllerClass = loadGame->ControllerClass;
		gameInstance->CharacterClass = loadGame->CharacterClass;

		UGameplayStatics::OpenLevel(GetWorld(), FName("TestLevel"));
	}
}