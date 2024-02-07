// Myth Game, All Rights Reserved.

#include "UI/MTGameHUD.h"
#include "Blueprint/UserWidget.h"

void AMTGameHUD::BeginPlay()
{
    Super::BeginPlay();

    auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
    if (PlayerHUDWidget)
    {
        PlayerHUDWidget->AddToViewport();
    }
}
