#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyCharacterBase.h"
#include "Components/BoxComponent.h"
#include "EnemySpawnerBase.generated.h"

UCLASS()
class COALBORN_API AEnemySpawnerBase : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* TriggerBox;

	AEnemySpawnerBase();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void SpawnEnemy(TSubclassOf<AEnemyCharacterBase> enemyToSpawn);
};