// Myth Game, All Rights Reserved.

#include "Components/MTInventoryComponent.h"

UMTInventoryComponent::UMTInventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UMTInventoryComponent::BeginPlay()
{
    Super::BeginPlay();

    SetCapacity(Capacity);
}

bool UMTInventoryComponent::TryToAddInventory(int32 TakenAmount)
{
    if (IsInvetoryFull() || !IsCapacityEnough(TakenAmount)) return false;

    AddPickup(TakenAmount);
    return true;
}

bool UMTInventoryComponent::IsInvetoryFull() const
{
    return Capacity == MaxCapacity;
}

bool UMTInventoryComponent::IsCapacityEnough(int32 InventoryAmount) const
{
    return Capacity + InventoryAmount <= MaxCapacity;
}

void UMTInventoryComponent::SetCapacity(int32 NewCapacity)
{
    Capacity = NewCapacity;

    OnInventoryChange.Broadcast(Capacity, PickupAmount);
}

void UMTInventoryComponent::AddPickup(int32 TakenAmount)
{
    PickupAmount = PickupAmount + TakenAmount;
    SetCapacity(Capacity + TakenAmount);
}
