#include "ClassPlayerHUDBase.h"

void UClassPlayerHUDBase::UpdateRoundUI(int round, int enemiesLeft)
{
	// Round text
	if (RoundText)
	{
		RoundText->SetText(FText::FromString(FString::Printf(TEXT("Round: %d"), round)));
	}

	// Enemies left text
	if (EnemiesLeftText)
	{
		EnemiesLeftText->SetText(FText::FromString(FString::Printf(TEXT("Enemies: %d"), enemiesLeft)));
	}
}

void UClassPlayerHUDBase::ClearRoundUI()
{
	if (RoundText)
	{
		RoundText->SetText(FText::FromString(""));
	}

	if (EnemiesLeftText)
	{
		EnemiesLeftText->SetText(FText::FromString(""));
	}
}