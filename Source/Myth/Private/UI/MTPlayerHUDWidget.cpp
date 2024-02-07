// Myth Game, All Rights Reserved.

#include "UI/MTPlayerHUDWidget.h"
#include "Components/MTHealthComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

DEFINE_LOG_CATEGORY_STATIC(PlayerHUDWidgetLog, All, All);

void UMTPlayerHUDWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    const auto Player = GetOwningPlayerPawn();
    if (!Player) return;

    const auto Component = Player->GetComponentByClass(UMTHealthComponent::StaticClass());
    const auto HealthComponent = Cast<UMTHealthComponent>(Component);
    if (!HealthComponent) return;

    MaxHealthUI = HealthComponent->GetMaxHealth();

    HealthComponent->OnHealthChange.AddUObject(this, &UMTPlayerHUDWidget::UpdateDisplayHealth);

    UE_LOG(PlayerHUDWidgetLog, Display, TEXT("%s  was construct"), *GetName());
}

void UMTPlayerHUDWidget::UpdateDisplayHealth(float NewHealth)
{
    HealthProgressBar->SetPercent(NewHealth / MaxHealthUI);

    FNumberFormattingOptions ZeroDig;
    ZeroDig.SetMaximumFractionalDigits(0); // setting the format without digits after a comma

    HealthTextBlock->SetText((FText::AsNumber(NewHealth, &ZeroDig)));

    UE_LOG(PlayerHUDWidgetLog, Display, TEXT("%s have %0.f health"), *GetName(), NewHealth);
}
