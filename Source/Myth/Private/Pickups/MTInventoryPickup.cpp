// Myth Game, All Rights Reserved.

#include "Pickups/MTInventoryPickup.h"
#include "Components/MTInventoryComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogInventoryPickup, All, All);

bool AMTInventoryPickup::GivePickTo(APawn* PlayerPawn)
{
    const auto Component = PlayerPawn->GetComponentByClass(UMTInventoryComponent::StaticClass());
    const auto InventoryComponent = Cast<UMTInventoryComponent>(Component);
    if (!InventoryComponent)
    {
        UE_LOG(LogInventoryPickup, Error, TEXT("InventoryComponent error"));
        return false;
    }

    UE_LOG(LogInventoryPickup, Display, TEXT("Inventory was taken"));

    return InventoryComponent->TryToAddInventory(InventoryAmount);
}
