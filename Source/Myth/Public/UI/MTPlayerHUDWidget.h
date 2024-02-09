// Myth Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MTPlayerHUDWidget.generated.h"

class UProgressBar;
class UTextBlock;
class UHorizontalBox;

UCLASS()
class MYTH_API UMTPlayerHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void UpdateDisplayHealth(float NewHealth);
    void UpdateDisplayInventory(int32 NewCapacity, int32 NewPickupAmount);

    virtual void NativeOnInitialized() override;

protected:
    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthProgressBar;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* HealthTextBlock;

    UPROPERTY(meta = (BindWidget))
    UProgressBar* InventoryProgressBar;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* AmountTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* InventoryCapacityTextBlock;

    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* InventoryComponentBox;

private:
    float MaxHealthUI = 0.0f;
    int32 MaxCapacityUI = 0;

    void GetHealthComponent();
    void GetInventoryComponent();
};
