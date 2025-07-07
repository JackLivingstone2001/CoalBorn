#include "CoalBornGameModeBase.h"
#include "CoalBornGameStateBase.h"
#include <Kismet/GameplayStatics.h>
#include "EnemySpawnerBase.h"
#include "WaveGameInstanceBase.h"

/*
	ROUND
*/

void ACoalBornGameModeBase::StartRound()
{
	// Check if game loaded
	if (!m_saveGameLoaded)
	{
		UWaveGameInstanceBase* gameInstance = Cast<UWaveGameInstanceBase>(UGameplayStatics::GetGameInstance(GetWorld()));

		if (gameInstance)
		{
			Cast<ACoalBornGameStateBase>(UGameplayStatics::GetGameState(GetWorld()))->SetCurrentRound(gameInstance->GetLoadedGame()->CurrentRound);

			m_saveGameLoaded = true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Game instance not loaded"));
		}
	}

	// Update game state
	Cast<ACoalBornGameStateBase>(UGameplayStatics::GetGameState(this))->OnRoundStarted();

	// Spawn enemies
	SpawnEnemies();
}

void ACoalBornGameModeBase::FinishRound()
{
	// Update game state
	Cast<ACoalBornGameStateBase>(UGameplayStatics::GetGameState(this))->OnRoundFinished();

	// Start next round after delay
	GetWorldTimerManager().SetTimer(m_roundTimer, this, &ACoalBornGameModeBase::StartRound, TimeBetweenRounds, false);
}

/*
	ENEMIES
*/

void ACoalBornGameModeBase::SpawnEnemies()
{
	// Get amount of enemies to spawn from gamestate
	ACoalBornGameStateBase* gameState = Cast<ACoalBornGameStateBase>(UGameplayStatics::GetGameState(this));
	int enemyAmount = gameState->GetEnemyAmountForRound() - gameState->GetEnemiesSpawnedInRound();
	for (int i = 0; i < enemyAmount; i++)
	{
		// Update game state
		Cast<ACoalBornGameStateBase>(UGameplayStatics::GetGameState(this))->OnEnemySpawned();

		// Spawn enemy
		SpawnEnemy();
	}
}

void ACoalBornGameModeBase::SpawnEnemy()
{
	// Initialise arrays
	TArray<AEnemySpawnerBase*> spawners;
	TArray<AActor*> actors;

	// Get all actors from class
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawnerBase::StaticClass(), actors);
	for (AActor* a : actors)
	{
		// Cast to spawner class array
		spawners.Add(Cast<AEnemySpawnerBase>(a));
	}

	// Get a random spawner if any were found
	if (spawners.Num() > 0)
	{
		int32 rand = FMath::RandRange(0, spawners.Num() - 1);
		AEnemySpawnerBase* spawner = spawners[rand];

		// Spawn enemy inside that spawner
		spawner->SpawnEnemy(TestEnemyToSpawn);
	}
}