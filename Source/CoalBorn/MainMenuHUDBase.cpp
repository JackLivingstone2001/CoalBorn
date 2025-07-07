#include "MainMenuHUDBase.h"
#include <Kismet/GameplayStatics.h>
#include "WaveSaveGameBase.h"
#include "WaveGameInstanceBase.h"

void UMainMenuHUDBase::NativeConstruct()
{
	Super::NativeConstruct();

	CreateMinerGameButton->OnClicked.AddDynamic(this, &UMainMenuHUDBase::OnCreateMinerGameButtonClicked);
	LoadMinerGameButton->OnClicked.AddDynamic(this, &UMainMenuHUDBase::OnLoadMinerGameButtonClicked);
}

void UMainMenuHUDBase::OnCreateMinerGameButtonClicked()
{
	UWaveSaveGameBase* saveGame = Cast<UWaveSaveGameBase>(UGameplayStatics::CreateSaveGameObject(UWaveSaveGameBase::StaticClass()));
	bool wasSuccessful = UGameplayStatics::SaveGameToSlot(saveGame, "MinerClassGame", 0);

	OnLoadMinerGameButtonClicked();
}

void UMainMenuHUDBase::OnLoadMinerGameButtonClicked()
{
	UWaveSaveGameBase* loadGame = Cast<UWaveSaveGameBase>(UGameplayStatics::LoadGameFromSlot("MinerClassGame", 0));
	UWaveGameInstanceBase* gameInstance = Cast<UWaveGameInstanceBase>(GetWorld()->GetGameInstance());

	if (gameInstance && loadGame)
	{
		gameInstance->SetLoadedGame(loadGame);

		UGameplayStatics::OpenLevel(GetWorld(), FName("TestLevel"));
	}
}