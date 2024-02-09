// Myth Game, All Rights Reserved.

#include "Dev/MTStore.h"
#include "Components/MTInventoryComponent.h"

AMTStore::AMTStore()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMTStore::BeginPlay()
{
    Super::BeginPlay();
}

void AMTStore::NotifyActorBeginOverlap(AActor* OtherActor)
{
    const auto Component = OtherActor->GetComponentByClass(UMTInventoryComponent::StaticClass());
    if (!Component) return;

    InventoryComponent = Cast<UMTInventoryComponent>(Component);

    if (!IsValid(InventoryComponent)) return;

    IsDeliveryInProgress = true;
    if (InventoryComponent->GetPickupAmount() > 0)
    {
        GetWorldTimerManager().SetTimer(DeliveryTimer, this, //
            &AMTStore::Delivering,                           //
            DeliveryRate,                                    //
            true,                                            //
            DeliveryDelay);
    }
}

void AMTStore::NotifyActorEndOverlap(AActor* OtherActor)
{
    const auto Component = OtherActor->GetComponentByClass(UMTInventoryComponent::StaticClass());
    if (!Component) return;

    const auto OtherINventoryComponent = Cast<UMTInventoryComponent>(Component);
    if (!OtherINventoryComponent) return;

    IsDeliveryInProgress = false;
}

void AMTStore::Delivering()
{
    if (InventoryComponent->GetPickupAmount() > 0 && IsDeliveryInProgress)
    {
        InventoryComponent->DecreasePickup();
    }
    else
    {
        IsDeliveryInProgress = false;
        GetWorldTimerManager().ClearTimer(DeliveryTimer);
    }
}
