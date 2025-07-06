#include "ClassPlayerCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyCharacterBase.h"

AClassPlayerCharacterBase::AClassPlayerCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	LineTracePoint = CreateDefaultSubobject<USceneComponent>(TEXT("Line Trace Point"));
	LineTracePoint->SetupAttachment(GetRootComponent());
}

void AClassPlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	// Set initial values
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AClassPlayerCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AClassPlayerCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Axis inputs
	PlayerInputComponent->BindAxis("MoveForward", this, &AClassPlayerCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AClassPlayerCharacterBase::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AClassPlayerCharacterBase::LookUp);
	PlayerInputComponent->BindAxis("LookAround", this, &AClassPlayerCharacterBase::LookAround);

	// Action inputs
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AClassPlayerCharacterBase::Jump);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AClassPlayerCharacterBase::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AClassPlayerCharacterBase::StopSprint);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AClassPlayerCharacterBase::Attack);
}

/*
	MOVEMENT
*/

void AClassPlayerCharacterBase::MoveForward(float value)
{
	if (Controller && value != 0.0f)
	{
		const FRotator rot = Controller->GetControlRotation();
		const FRotator yaw(0, rot.Yaw, 0);
		const FVector dir = FRotationMatrix(yaw).GetUnitAxis(EAxis::X);

		AddMovementInput(dir, value);
	}
}

void AClassPlayerCharacterBase::MoveRight(float value)
{
	if (Controller && value != 0.0f)
	{
		const FRotator rot = Controller->GetControlRotation();
		const FRotator yaw(0, rot.Yaw, 0);
		const FVector dir = FRotationMatrix(yaw).GetUnitAxis(EAxis::Y);

		AddMovementInput(dir, value);
	}
}

void AClassPlayerCharacterBase::LookUp(float value)
{
	AddControllerPitchInput(value);
}

void AClassPlayerCharacterBase::LookAround(float value)
{
	AddControllerYawInput(value);
}

void AClassPlayerCharacterBase::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AClassPlayerCharacterBase::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

/*
	ATTACKING
*/

void AClassPlayerCharacterBase::Attack()
{
	FVector Start = LineTracePoint->GetComponentLocation();
	FVector End = Start + LineTracePoint->GetForwardVector() * 10000.0f;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	FHitResult HitResult;

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility,
		QueryParams
	);

	if (bHit)
	{
		// Check if the hit actor is of type AEnemyCharacterBase
		AEnemyCharacterBase* HitEnemy = Cast<AEnemyCharacterBase>(HitResult.GetActor());
		if (HitEnemy)
		{
			HitEnemy->Damage(20.0f);
		}
	}
}