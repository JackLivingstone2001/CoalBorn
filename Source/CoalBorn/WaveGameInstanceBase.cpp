#include "WaveGameInstanceBase.h"

void UWaveGameInstanceBase::SetLoadedGame(UWaveSaveGameBase* loadedGame)
{
	m_loadedGame = loadedGame;
}

UWaveSaveGameBase* UWaveGameInstanceBase::GetLoadedGame()
{
	return m_loadedGame;
}