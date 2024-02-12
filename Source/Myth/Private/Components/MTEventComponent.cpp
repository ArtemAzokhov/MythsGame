// Myth Game, All Rights Reserved.


#include "Components/MTEventComponent.h"
#include "Dev/MTTrigger.h"

DEFINE_LOG_CATEGORY_STATIC(LogEventComponent, All, All);

// Sets default values for this component's properties
UMTEventComponent::UMTEventComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMTEventComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMTEventComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMTEventComponent::StartEvent(AMTTrigger* Trigger, int32 EventConundDown, int32 DeliveryGoal)
{
    
    UE_LOG(LogEventComponent, Display, TEXT("Player %s Start event"), *(GetOwner()->GetName()));

	OnEventStateChange.Broadcast(EventConundDown, DeliveryGoal);
}

void UMTEventComponent::StopEvent(AMTTrigger * Trigger, int32 EventConundDown, int32 DeliveryGoal)
{

}