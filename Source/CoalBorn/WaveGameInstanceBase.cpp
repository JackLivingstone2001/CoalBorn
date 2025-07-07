#include "WaveGameInstanceBase.h"
#include <Kismet/GameplayStatics.h>
#include "CoalBornGameModeBase.h"

void UWaveGameInstanceBase::SetLoadedGame(UWaveSaveGameBase* loadedGame)
{
	m_loadedGame = loadedGame;
}

UWaveSaveGameBase* UWaveGameInstanceBase::GetLoadedGame()
{
	return m_loadedGame;
}