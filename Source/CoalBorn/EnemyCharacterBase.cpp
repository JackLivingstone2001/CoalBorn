#include "EnemyCharacterBase.h"
#include "CoalBornGameStateBase.h"
#include <Kismet/GameplayStatics.h>
#include <AIController.h>
#include "ClassPlayerCharacterBase.h"

AEnemyCharacterBase::AEnemyCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	// Setup stats
	m_health = MaxHealth;
}

void AEnemyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		AIController->MoveToLocation(FVector(0.0f, 0.0f, 0.0f));
	}
}

/*
	HEALTH
*/

void AEnemyCharacterBase::Damage(float amount)
{
	// Decrease health
	m_health -= amount;

	// Check if below 0
	if (m_health <= 0)
	{
		Kill();
	}
}

void AEnemyCharacterBase::Kill()
{
	if (HasAuthority())
	{
		Cast<ACoalBornGameStateBase>(UGameplayStatics::GetGameState(this))->OnEnemyKilled();
		Destroy();
	}
}