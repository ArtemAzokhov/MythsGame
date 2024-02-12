// Myth Game, All Rights Reserved.

#include "Dev/MTStore.h"
#include "Components/MTInventoryComponent.h"
#include "Components/BoxComponent.h"
#include "Player/MTBaseCharacter.h"
#include "Components/MTEventComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogStore, All, All);

AMTStore::AMTStore()
{
    PrimaryActorTick.bCanEverTick = true;

    DeliveryCollisionComponent = CreateDefaultSubobject<UBoxComponent>("DeliveryCollisionComponent");
    DeliveryCollisionComponent->InitBoxExtent(FVector(50.0f, 50.0f, 35.0f));
    DeliveryCollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    DeliveryCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    DeliveryCollisionComponent->SetGenerateOverlapEvents(true);
    SetRootComponent(DeliveryCollisionComponent);

    EventCollisionComponent = CreateDefaultSubobject<UBoxComponent>("EventCollisionComponent");
    EventCollisionComponent->InitBoxExtent(FVector(120.0f, 120.0f, 35.0f));
    EventCollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    EventCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    EventCollisionComponent->SetGenerateOverlapEvents(true);
}

void AMTStore::BeginPlay()
{
    Super::BeginPlay();

    DeliveryCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AMTStore::StartDelivery);
    DeliveryCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AMTStore::StopDelivery);

    EventCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AMTStore::EventCollisionBeginOverlap);
    EventCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AMTStore::StopEvent);
}

//void AMTStore::NotifyActorBeginOverlap(AActor* OtherActor) {}

//void AMTStore::NotifyActorEndOverlap(AActor* OtherActor) {}

void AMTStore::Delivering()
{
    if (!InventoryComponent || !IsCanDelivery) return;
    if (InventoryComponent->GetPickupAmount() > 0)
    {
        InventoryComponent->DecreasePickup();
        ++DeliveringAmount;

        OnDeliveringAmountChange.Broadcast(DeliveringAmount);
        UE_LOG(LogStore, Display, TEXT("Now %i in store"), DeliveringAmount);

        if (DeliveringAmount == DeliveryGoal)
        {
            IsCanDelivery = false;
            GetWorldTimerManager().ClearTimer(DeliveryTimer);
            OnTriggerEvent.Broadcast();
            UE_LOG(LogStore, Display, TEXT("Your goal is complete!!!"));
        }
    }
    else
    {
        GetWorldTimerManager().ClearTimer(DeliveryTimer);
    }
}

void AMTStore::EventCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    const auto Character = Cast<AMTBaseCharacter>(OtherActor);
    if (!Character) return;

    const auto Component = Character->GetComponentByClass(UMTEventComponent::StaticClass());
    const auto EventComponent = Cast<UMTEventComponent>(Component);

    if (EventComponent)
    {
        EventComponent->StartEvent(this, EventConundDown, DeliveryGoal);
    }


}

void AMTStore::StopEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AMTStore::StartDelivery(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!IsCanDelivery) return;

    const auto Component = OtherActor->GetComponentByClass(UMTInventoryComponent::StaticClass());
    if (!Component) return;

    InventoryComponent = Cast<UMTInventoryComponent>(Component);

    if (!IsValid(InventoryComponent)) return;

    if (InventoryComponent->GetPickupAmount() > 0)
    {
        GetWorldTimerManager().SetTimer(DeliveryTimer, this, //
            &AMTStore::Delivering,                           //
            DeliveryRate,                                    //
            true,                                            //
            DeliveryDelay);
    }
}

void AMTStore::StopDelivery(
    UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (!IsCanDelivery)
    {
        InventoryComponent = nullptr;
        return;
    }

    const auto Component = OtherActor->GetComponentByClass(UMTInventoryComponent::StaticClass());
    if (!Component) return;

    const auto OtherInventoryComponent = Cast<UMTInventoryComponent>(Component);
    if (!OtherInventoryComponent) return;

    InventoryComponent = nullptr;
    GetWorldTimerManager().ClearTimer(DeliveryTimer);
}

void AMTStore::UpdateTimer() {}
