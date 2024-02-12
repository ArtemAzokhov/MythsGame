// Myth Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MTComplete.generated.h"

UCLASS()
class MYTH_API AMTComplete : public AActor
{
    GENERATED_BODY()

public:
    AMTComplete();

    UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
    AActor* Trigger;

protected:
    UFUNCTION(BlueprintImplementableEvent)
    void CompleteAction(); // Call in blueprint for visualisation

    virtual void BeginPlay() override;
};
