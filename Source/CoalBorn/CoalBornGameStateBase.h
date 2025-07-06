#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CoalBornGameStateBase.generated.h"

UCLASS()
class COALBORN_API ACoalBornGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	// Round
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Round")
	int EnemiesInRoundBase = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Round")
	float EnemiesInRoundMultiplier = 0.0f;
	void OnRoundStarted();
	void OnRoundFinished();
	bool IsRoundFinished();

	// Enemies
	void OnEnemyKilled();
	void OnEnemySpawned();

	int GetEnemiesSpawnedInRound();
	int GetEnemiesKilledInRound();

	int GetEnemyAmountForRound();
	int GetEnemiesLeftForRound();
private:
	// Round
	int m_currentRound = 0;
	int m_enemiesKilledInRound = 0;
	int m_enemiesSpawnedInRound = 0;

};