// Myth Game, All Rights Reserved.

#include "Dev/MTComplete.h"
#include "Dev/MTTrigger.h"

AMTComplete::AMTComplete()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AMTComplete::BeginPlay()
{
    Super::BeginPlay();

    const auto TriggerActor = Cast<AMTTrigger>(Trigger);
    if (TriggerActor)
    {
        TriggerActor->OnTriggerEvent.AddUObject(this, &AMTComplete::CompleteAction); // this function callin in blueprint as Event
    }
}
