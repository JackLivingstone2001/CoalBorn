#include "CoalBornGameModeBase.h"
#include "CoalBornGameStateBase.h"
#include <Kismet/GameplayStatics.h>
#include "EnemySpawnerBase.h"
#include "WaveGameInstanceBase.h"

void ACoalBornGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Delay starting the round to ensure all systems are ready (especially GameInstance)
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ACoalBornGameModeBase::StartRound, 0.1f, false);
}

/*
	ROUND
*/

void ACoalBornGameModeBase::StartRound()
{
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