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
	UWaveSaveGameBase* saveGame = Cast<UWaveSaveGameBase>(UGameplayStatics::LoadGameFromSlot("MinerClassGame", 0));
	UWaveGameInstanceBase* gameInstance = Cast<UWaveGameInstanceBase>(GetWorld()->GetGameInstance());
	if (gameInstance && saveGame)
	{
		gameInstance->SetLoadedGame(saveGame);

		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if (PC)
		{
			PC->bShowMouseCursor = true;
			PC->SetInputMode(FInputModeUIOnly());

			FInputModeUIOnly InputMode;
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);
			PC->SetInputMode(InputMode);
		}

		UGameplayStatics::OpenLevel(this, FName("TestLevel"));
	}
}