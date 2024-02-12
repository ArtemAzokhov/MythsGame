// Myth Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MTPlayerHUDWidget.generated.h"

class UProgressBar;
class UTextBlock;
class UHorizontalBox;
class UMTQuestionWidget;
class UEventInfoWidget;

UCLASS()
class MYTH_API UMTPlayerHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void UpdateDisplayHealth(float NewHealth);
    void UpdateDisplayInventory(int32 NewCapacity, int32 NewPickupAmount);
    void ShowQuestionMenu(int32 EventConundDown, int32 DeliveryGoal);
    void HideQuestionMenu();

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

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> QuestionWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> EventInfoWidgetClass;

private:
    float MaxHealthUI = 0.0f;
    int32 MaxCapacityUI = 0;

    UMTQuestionWidget* QuestionMenu;

    void GetHealthComponent();
    void GetInventoryComponent();
    void GetEventComponent();
};
