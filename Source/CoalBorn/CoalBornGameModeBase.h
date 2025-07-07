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
	virtual void BeginPlay() override;

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
	bool m_saveGameLoaded = false;
	FTimerHandle m_roundTimer;

	// Enemies
	void SpawnEnemy();
};