// Myth Game, All Rights Reserved.

#include "MTGameModeBase.h"
#include "Player/MTPlayerController.h"
#include "Player/MTBaseCharacter.h"
#include "UI/MTGameHUD.h"

AMTGameModeBase::AMTGameModeBase()
{
    DefaultPawnClass = AMTBaseCharacter::StaticClass();
    PlayerControllerClass = AMTPlayerController::StaticClass();
    HUDClass = AMTGameHUD::StaticClass();
}
