// Rapid Fire Game. All Rights Reserved.

#include "RFGameModeBase.h"
#include "Player/RFBaseCharacter.h"
#include "Player/RFPlayerController.h"
#include "UI/RFGameHUD.h"

ARFGameModeBase::ARFGameModeBase()
{
    DefaultPawnClass = ARFBaseCharacter::StaticClass();
    PlayerControllerClass = ARFPlayerController::StaticClass();
    HUDClass = ARFGameHUD::StaticClass();
}
