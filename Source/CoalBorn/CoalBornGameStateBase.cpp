#include "CoalBornGameStateBase.h"
#include "CoalBornGameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include "ClassPlayerControllerBase.h"
#include "WaveGameInstanceBase.h"

/*
	ROUND
*/

void ACoalBornGameStateBase::OnRoundStarted()
{
	// Set current round
	m_currentRound = Cast<UWaveSaveGameBase>(UGameplayStatics::LoadGameFromSlot("MinerClassGame", 0))->CurrentRound;

	// Update class HUD
	Cast<AClassPlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetHeadsUpDisplay()->UpdateRoundUI(m_currentRound, GetEnemyAmountForRound() - m_enemiesKilledInRound);
}

void ACoalBornGameStateBase::OnRoundFinished()
{
	// Reset round vars
	m_enemiesKilledInRound = 0;
	m_enemiesSpawnedInRound = 0;

	// Increase round
	m_currentRound++;

	// Clear class HUD
	Cast<AClassPlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetHeadsUpDisplay()->ClearRoundUI();

	// Save game
	UWaveSaveGameBase* saveGame = Cast<UWaveSaveGameBase>(UGameplayStatics::CreateSaveGameObject(UWaveSaveGameBase::StaticClass()));
	saveGame->CurrentRound = m_currentRound;

	bool wasSuccessful = UGameplayStatics::SaveGameToSlot(saveGame, Cast<AClassPlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->ClassSaveSlotName, 0);
}

bool ACoalBornGameStateBase::IsRoundFinished()
{
	// Check if enemies killed matches enemies for round
	if (m_enemiesKilledInRound != GetEnemyAmountForRound()) return false;

	// Finish round
	Cast<ACoalBornGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->FinishRound();
	return true;
}

void ACoalBornGameStateBase::SetCurrentRound(int round)
{
	m_currentRound = round;
}

/*
	ENEMIES
*/

void ACoalBornGameStateBase::OnEnemyKilled()
{
	// Increase enemies killed
	m_enemiesKilledInRound++;
	if (IsRoundFinished()) return;

	// Check if all required enemies have been spawned
	if (GetEnemyAmountForRound() != m_enemiesSpawnedInRound)
	{
		// Spawn extra enemies if necessary
		Cast<ACoalBornGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->SpawnEnemies();
	}

	// Update class HUD
	Cast<AClassPlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetHeadsUpDisplay()->UpdateRoundUI(m_currentRound, GetEnemyAmountForRound() - m_enemiesKilledInRound);
}

void ACoalBornGameStateBase::OnEnemySpawned()
{
	// Increase enemies spawned
	m_enemiesSpawnedInRound++;
}

int ACoalBornGameStateBase::GetEnemiesKilledInRound()
{
	return m_enemiesKilledInRound;
}

int ACoalBornGameStateBase::GetEnemiesSpawnedInRound()
{
	return m_enemiesSpawnedInRound;
}

int ACoalBornGameStateBase::GetEnemyAmountForRound()
{
	float count = EnemiesInRoundBase + FMath::FloorToInt(FMath::Pow(m_currentRound, 2.0f) * EnemiesInRoundMultiplier);
	return FMath::CeilToInt(count);
}

int ACoalBornGameStateBase::GetEnemiesLeftForRound()
{
	return GetEnemyAmountForRound() - m_enemiesKilledInRound;
}