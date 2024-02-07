// Myth Game, All Rights Reserved.

#include "Pickups/MTHealthPickup.h"
#include "Components/MTHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool AMTHealthPickup::GivePickTo(APawn* PlayerPawn)
{

    const auto Component = PlayerPawn->GetComponentByClass(UMTHealthComponent::StaticClass());
    const auto HealthComponent = Cast<UMTHealthComponent>(Component);
    if (!HealthComponent)
    {
        UE_LOG(LogHealthPickup, Error, TEXT("HealthComponent error"));
        return false;
    }

    UE_LOG(LogHealthPickup, Display, TEXT("Health was taken"));
    return HealthComponent->TryToAddHealth(HealthAmount);
}
