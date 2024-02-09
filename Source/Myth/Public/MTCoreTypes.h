#pragma once

#include "MTCoreTypes.generated.h"

USTRUCT(BlueprintType)
struct FPickupData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory pickup")
    FName PickupName = "Pickup name";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory pickup")
    int32 Value = 0;
};