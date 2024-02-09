// Myth Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/MTBasePickup.h"
#include "MTInventoryPickup.generated.h"

UCLASS()
class MYTH_API AMTInventoryPickup : public AMTBasePickup
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1", ClampMax = "10"))
    int32 InventoryAmount = 2;

private:
    virtual bool GivePickTo(APawn* PlayerPawn) override;
};
