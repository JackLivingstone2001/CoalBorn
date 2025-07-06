#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ClassPlayerCharacterBase.generated.h"

UCLASS()
class COALBORN_API AClassPlayerCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AClassPlayerCharacterBase();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement (Speeds)")
	float WalkSpeed = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement (Speeds)")
	float SprintSpeed = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement (Speeds)")
	float CrouchSpeed = 0.0f;

	// Attacking
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* LineTracePoint;
private:
	// Movement
	void MoveForward(float value);
	void MoveRight(float value);
	void LookUp(float value);
	void LookAround(float value);

	void StartSprint();
	void StopSprint();

	// Attacking
	void Attack();
};