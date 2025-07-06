#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacterBase.generated.h"

UCLASS()
class COALBORN_API AEnemyCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacterBase();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats (Health)")
	float MaxHealth = 0.0f;

	void Damage(float amount);
private:
	// Stats
	float m_health = 0.0f;

	void Kill();
};