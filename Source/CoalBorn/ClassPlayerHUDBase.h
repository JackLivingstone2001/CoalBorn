#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include "ClassPlayerHUDBase.generated.h"

UCLASS()
class COALBORN_API UClassPlayerHUDBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Text
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* RoundText = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* EnemiesLeftText = nullptr;
	
	// Round
	void UpdateRoundUI(int round, int enemiesLeft);
	void ClearRoundUI();
private:
};