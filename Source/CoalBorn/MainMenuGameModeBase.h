#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuHUDBase.h"
#include "MainMenuGameModeBase.generated.h"

UCLASS()
class COALBORN_API AMainMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UMainMenuHUDBase> MainMenuUI;
	UMainMenuHUDBase* GetMainMenuUI();
private:
	UMainMenuHUDBase* m_mainMenuUI;
};