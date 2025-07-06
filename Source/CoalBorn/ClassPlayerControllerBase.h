#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ClassPlayerHUDBase.h"
#include "ClassPlayerControllerBase.generated.h"

UCLASS()
class COALBORN_API AClassPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
public:
	// UE
	virtual void BeginPlay() override;

	// Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float HealthRegenDelay = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float HealthRegenAmount = 0.0f;

	// UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UClassPlayerHUDBase> HeadsUpDisplay;

	UClassPlayerHUDBase* GetHeadsUpDisplay();
private:
	// UI
	UClassPlayerHUDBase* m_headsUpDisplay;
};