// Myth Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MTPlayerHUDWidget.generated.h"

class UProgressBar;
class UTextBlock;

UCLASS()
class MYTH_API UMTPlayerHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void UpdateDisplayHealth(float NewHealth);

    virtual void NativeConstruct() override;

protected:
    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthProgressBar;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* HealthTextBlock;

    float MaxHealthUI = 0.0f;
};
