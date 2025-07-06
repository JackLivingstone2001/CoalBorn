#include "EnemySpawnerBase.h"
#include "Components/CapsuleComponent.h"
#include <Kismet/GameplayStatics.h>

AEnemySpawnerBase::AEnemySpawnerBase()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	TriggerBox->SetupAttachment(GetRootComponent());
}

void AEnemySpawnerBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemySpawnerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemySpawnerBase::SpawnEnemy(TSubclassOf<AEnemyCharacterBase> enemyToSpawn)
{
    FVector BoxCenter = TriggerBox->GetComponentLocation();
    FVector BoxExtent = TriggerBox->GetScaledBoxExtent();

    FVector RandomPosition = BoxCenter + FVector(
        FMath::RandRange(-BoxExtent.X, BoxExtent.X),
        FMath::RandRange(-BoxExtent.Y, BoxExtent.Y),
        0.0f
    );

    if (AEnemyCharacterBase* SpawnedEnemy = GetWorld()->SpawnActor<AEnemyCharacterBase>(enemyToSpawn, RandomPosition, FRotator::ZeroRotator))
    {
        UCapsuleComponent* Capsule = SpawnedEnemy->FindComponentByClass<UCapsuleComponent>();
        if (Capsule)
        {
            float CapsuleHeight = Capsule->GetUnscaledCapsuleHalfHeight() * 2.0f;
            FVector AdjustedPosition = RandomPosition;
            AdjustedPosition.Z -= CapsuleHeight / 2.0f;

            SpawnedEnemy->SetActorLocation(AdjustedPosition);
        }
    }
}