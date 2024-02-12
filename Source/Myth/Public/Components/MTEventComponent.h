// Myth Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MTEventComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEventStateChangeSignature, int32 EventConundDown, int32 DeliveryGoal);

class AMTTrigger;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYTH_API UMTEventComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UMTEventComponent();

    FOnEventStateChangeSignature OnEventStateChange;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    void StartEvent(AMTTrigger* Trigger, int32 EventConundDown, int32 DeliveryGoal);
    void StopEvent(AMTTrigger* Trigger, int32 EventConundDown, int32 DeliveryGoal);

    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    FTimerHandle EventTimer;
};
