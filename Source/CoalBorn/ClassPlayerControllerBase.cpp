#include "ClassPlayerControllerBase.h"
#include "ClassPlayerHUDBase.h"
#include "CoalBornGameModeBase.h"
#include <Kismet/GameplayStatics.h>

/*
    UE
*/

void AClassPlayerControllerBase::BeginPlay()
{
    // Lock the cursor and make it invisible
    FInputModeGameOnly InputMode;
    SetInputMode(InputMode);

    // Set the cursor to be locked to the center and hide it
    bShowMouseCursor = false;
    SetMouseLocation(0, 0);

    // Add HUD to viewport
    if (HeadsUpDisplay)
    {
        m_headsUpDisplay = CreateWidget<UClassPlayerHUDBase>(this, HeadsUpDisplay);
        
        if (m_headsUpDisplay)
        {
            m_headsUpDisplay->AddToViewport();
        }
    }

    // Start first round
    Cast<ACoalBornGameModeBase>(UGameplayStatics::GetGameMode(this))->StartRound();
}

/*
    UI
*/

UClassPlayerHUDBase* AClassPlayerControllerBase::GetHeadsUpDisplay()
{
    return m_headsUpDisplay;
}