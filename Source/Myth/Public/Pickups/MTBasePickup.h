// Myth Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MTBasePickup.generated.h"

class USphereComponent;

UCLASS()
class MYTH_API AMTBasePickup : public AActor
{
    GENERATED_BODY()

public:
    AMTBasePickup();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* CollisionComponent;

    UPROPERTY(EditAnywhere, Category = "Pickup")
    float RespawnTime = 5.0f;

    virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    virtual bool GivePickTo(APawn* PlayerPawn);
    void PickupWasTaken();
    void Respawn();
};
