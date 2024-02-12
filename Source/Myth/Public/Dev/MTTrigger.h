
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MTTrigger.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnTriggerEventSignature);

UCLASS()
class MYTH_API AMTTrigger : public AActor
{
    GENERATED_BODY()

public:
    AMTTrigger();

    FOnTriggerEventSignature OnTriggerEvent;

protected:
    virtual void BeginPlay() override;
};
