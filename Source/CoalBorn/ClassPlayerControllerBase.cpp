#include "ClassPlayerControllerBase.h"
#include "ClassPlayerHUDBase.h"
#include "CoalBornGameModeBase.h"
#include <Kismet/GameplayStatics.h>

/*
    UE
*/

void AClassPlayerControllerBase::BeginPlay()
{
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