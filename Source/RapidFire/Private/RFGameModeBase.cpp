// Rapid Fire Game. All Rights Reserved.

#include "RFGameModeBase.h"
#include "Player/RFBaseCharacter.h"
#include "Player/RFPlayerController.h"

ARFGameModeBase::ARFGameModeBase()
{
    DefaultPawnClass = ARFBaseCharacter::StaticClass();
    PlayerControllerClass = ARFPlayerController::StaticClass();
}
