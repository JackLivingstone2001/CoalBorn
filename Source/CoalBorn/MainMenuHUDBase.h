#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainMenuHUDBase.generated.h"

UCLASS()
class COALBORN_API UMainMenuHUDBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* CreateMinerGameButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* LoadMinerGameButton;
private:
	UFUNCTION()
	void OnCreateMinerGameButtonClicked();
	UFUNCTION()
	void OnLoadMinerGameButtonClicked();
};