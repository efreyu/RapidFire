// Rapid Fire Game.

#include "FTGameModeBase.h"

void AFTGameModeBase::temp()
{
	for (int i = 0; i < 10; i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hello World!"));
	}

	switch (ScoreToWin)
	{
		case 0:
			UE_LOG(LogTemp, Warning, TEXT("Score is 0"));
			break;
		case 1:
			UE_LOG(LogTemp, Warning, TEXT("Score is 1"));
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("Score is 1"));
			break;
	}
}
