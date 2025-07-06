#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnemyCharacterBase.h"
#include "CoalBornGameModeBase.generated.h"

UCLASS()
class COALBORN_API ACoalBornGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// Round
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Round")
	float TimeBetweenRounds;

	void StartRound();
	void FinishRound();

	// Enemies
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	TSubclassOf<AEnemyCharacterBase> TestEnemyToSpawn;

	void SpawnEnemies();
private:
	// Round
	FTimerHandle RoundTimer;

	// Enemies
	void SpawnEnemy();
};