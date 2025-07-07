#include "MainMenuGameModeBase.h"

void AMainMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuUI)
	{
		m_mainMenuUI = CreateWidget<UMainMenuHUDBase>(GetWorld(), MainMenuUI);
		
		if (m_mainMenuUI)
		{
			m_mainMenuUI->AddToViewport();
		}
	}

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->SetInputMode(FInputModeUIOnly());

		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetWidgetToFocus(m_mainMenuUI->TakeWidget());
		PC->SetInputMode(InputMode);
	}
}

UMainMenuHUDBase* AMainMenuGameModeBase::GetMainMenuUI()
{
	return m_mainMenuUI;
}