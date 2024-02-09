// Myth Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MTInventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInventoryChangeSignature, int32, int32);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYTH_API UMTInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UMTInventoryComponent();

    FOnInventoryChangeSignature OnInventoryChange;

    int32 GetCapacity() const { return Capacity; }
    int32 GetMaxCapacity() const { return MaxCapacity; }
    int32 GetPickupAmount() const { return PickupAmount; }

    bool TryToAddInventory(int32 TakenAmount);
    bool IsInvetoryFull() const;
    bool IsCapacityEnough(int32 InventoryAmount) const;

    void DecreasePickup();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory", meta = (ClampMin = "0", ClampMax = "100"))
    int32 MaxCapacity = 10;

    virtual void BeginPlay() override;

private:
    int32 Capacity = 0;
    int32 PickupAmount = 0;

    void SetCapacity(int32 NewCapacity);
    void AddPickup(int32 TakenAmount);
};
