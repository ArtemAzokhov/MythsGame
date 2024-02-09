// Myth Game, All Rights Reserved.

#include "UI/MTPlayerHUDWidget.h"
#include "Components/MTHealthComponent.h"
#include "Components/MTInventoryComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"

DEFINE_LOG_CATEGORY_STATIC(PlayerHUDWidgetLog, All, All);

void UMTPlayerHUDWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    GetHealthComponent();
    GetInventoryComponent();

    UE_LOG(PlayerHUDWidgetLog, Display, TEXT("%s  was construct"), *GetName());
}

void UMTPlayerHUDWidget::UpdateDisplayHealth(float NewHealth)
{
    HealthProgressBar->SetPercent(NewHealth / MaxHealthUI);

    FNumberFormattingOptions ZeroDig;
    ZeroDig.SetMaximumFractionalDigits(0); // setting the format without digits after a comma

    HealthTextBlock->SetText(FText::AsNumber(NewHealth, &ZeroDig));

    UE_LOG(PlayerHUDWidgetLog, Display, TEXT("%s have %0.f health"), *GetName(), NewHealth);
}

void UMTPlayerHUDWidget::UpdateDisplayInventory(int32 NewCapacity, int32 NewPickupAmount)
{
    float PercentNewCapacity = NewCapacity;
    float PercerntMaxCapacity = MaxCapacityUI;
    InventoryProgressBar->SetPercent(PercentNewCapacity / PercerntMaxCapacity);

    FString CapacityDisplay = FString::FromInt(NewCapacity);
    CapacityDisplay.Append(TEXT(" / ")).Append(FString::FromInt(MaxCapacityUI));
    InventoryCapacityTextBlock->SetText(FText::FromString(CapacityDisplay));

    if (NewPickupAmount > 0)
    {
        AmountTextBlock->SetText(FText::AsNumber(NewPickupAmount));
        InventoryComponentBox->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        InventoryComponentBox->SetVisibility(ESlateVisibility::Collapsed);
    }

    UE_LOG(PlayerHUDWidgetLog, Display,                                //
        TEXT("%s have %i NewCapacity / %i, and have %i PickupAmount"), //
        *GetName(), NewCapacity, MaxCapacityUI, NewPickupAmount);
}

void UMTPlayerHUDWidget::GetHealthComponent()
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player) return;

    const auto Component = Player->GetComponentByClass(UMTHealthComponent::StaticClass());
    const auto HealthComponent = Cast<UMTHealthComponent>(Component);
    if (!HealthComponent) return;

    MaxHealthUI = HealthComponent->GetMaxHealth();

    HealthComponent->OnHealthChange.AddUObject(this, &UMTPlayerHUDWidget::UpdateDisplayHealth);
}

void UMTPlayerHUDWidget::GetInventoryComponent()
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player) return;

    const auto Component = Player->GetComponentByClass(UMTInventoryComponent::StaticClass());
    const auto InventoryComponent = Cast<UMTInventoryComponent>(Component);
    if (!InventoryComponent) return;

    MaxCapacityUI = InventoryComponent->GetMaxCapacity();

    InventoryComponent->OnInventoryChange.AddUObject(this, &UMTPlayerHUDWidget::UpdateDisplayInventory);
}
