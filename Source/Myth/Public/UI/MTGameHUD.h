// Myth Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MTGameHUD.generated.h"

UCLASS()
class MYTH_API AMTGameHUD : public AHUD
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

    virtual void BeginPlay() override;
};
