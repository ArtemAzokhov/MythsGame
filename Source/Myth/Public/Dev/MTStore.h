// Myth Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Dev/MTTrigger.h"
#include "MTStore.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeliveringAmountChangeSignature, int32);

class UBoxComponent;
class UMTInventoryComponent;

UCLASS()
class MYTH_API AMTStore : public AMTTrigger
{
    GENERATED_BODY()

public:
    AMTStore();

    FOnDeliveringAmountChangeSignature OnDeliveringAmountChange;

protected:
    UPROPERTY(VisibleAnywhere, Category = "Store")
    UBoxComponent* EventCollisionComponent;

    UPROPERTY(VisibleAnywhere, Category = "Store")
    UBoxComponent* DeliveryCollisionComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Store")
    float DeliveryRate = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Store")
    float DeliveryDelay = 1.0f;

    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Event")
    int32 DeliveryGoal = 20;

    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Event")
    int32 EventConundDown = 20;// in secunds

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Event")
    float EventDelay = 1.0f;

 

    virtual void BeginPlay() override;
    //virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
    //virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

private:
    UMTInventoryComponent* InventoryComponent = nullptr;
    FTimerHandle DeliveryTimer;
    bool IsCanDelivery = true;

    int32 DeliveringAmount = 0;

    UFUNCTION()
    void EventCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void StopEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UFUNCTION()
    void StartDelivery(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void StopDelivery(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    void Delivering();

    void UpdateTimer();
};
