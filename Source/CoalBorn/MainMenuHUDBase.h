#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "ClassPlayerControllerBase.h"
#include "ClassPlayerCharacterBase.h"
#include "MainMenuHUDBase.generated.h"

UCLASS()
class COALBORN_API UMainMenuHUDBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	TSubclassOf<AGameModeBase> CoalBornGameMode;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* CreateMinerGameButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* LoadMinerGameButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
	TSubclassOf<AClassPlayerControllerBase> MinerClassController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
	TSubclassOf<AClassPlayerCharacterBase> MinerClassCharacter;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* CreateHealerGameButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* LoadHealerGameButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
	TSubclassOf<AClassPlayerControllerBase> HealerClassController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
	TSubclassOf<AClassPlayerCharacterBase> HealerClassCharacter;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* CreateBrawlerGameButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* LoadBrawlerGameButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
	TSubclassOf<AClassPlayerControllerBase> BrawlerClassController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
	TSubclassOf<AClassPlayerCharacterBase> BrawlerClassCharacter;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* CreateRangerGameButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* LoadRangerGameButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
	TSubclassOf<AClassPlayerControllerBase> RangerClassController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
	TSubclassOf<AClassPlayerCharacterBase> RangerClassCharacter;

private:
	UFUNCTION()
	void OnCreateMinerGameButtonClicked();
	UFUNCTION()
	void OnLoadMinerGameButtonClicked();

	UFUNCTION()
	void OnCreateHealerGameButtonClicked();
	UFUNCTION()
	void OnLoadHealerGameButtonClicked();

	UFUNCTION()
	void OnCreateBrawlerGameButtonClicked();
	UFUNCTION()
	void OnLoadBrawlerGameButtonClicked();

	UFUNCTION()
	void OnCreateRangerGameButtonClicked();
	UFUNCTION()
	void OnLoadRangerGameButtonClicked();

	UFUNCTION()
	void CreateSaveGame(FString saveName, TSubclassOf<AClassPlayerControllerBase> controller, TSubclassOf<AClassPlayerCharacterBase> character);
	UFUNCTION()
	void LoadGame(FString saveName);
};