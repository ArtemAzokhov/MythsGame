// Myth Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MTStore.generated.h"

class USphereComponent;
class UMTInventoryComponent;

UCLASS()
class MYTH_API AMTStore : public AActor
{
    GENERATED_BODY()

public:
    AMTStore();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Store")
    USphereComponent* CollisionComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Store")
    float DeliveryRate = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Store")
    float DeliveryDelay = 1.0f;

    virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
    virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

private:
    UMTInventoryComponent* InventoryComponent = nullptr;
    FTimerHandle DeliveryTimer;
    bool IsDeliveryInProgress = false;

    void Delivering();
};
