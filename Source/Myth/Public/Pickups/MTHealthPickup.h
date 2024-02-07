// Myth Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/MTBasePickup.h"
#include "MTHealthPickup.generated.h"

UCLASS()
class MYTH_API AMTHealthPickup : public AMTBasePickup
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "100.0"))
    float HealthAmount = 20.0f;

private:
    virtual bool GivePickTo(APawn* PlayerPawn) override;
};
