// Myth Game, All Rights Reserved.

#include "Pickups/MTBasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

AMTBasePickup::AMTBasePickup()
{
    PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(50.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);
}

void AMTBasePickup::BeginPlay()
{
    Super::BeginPlay();
}

void AMTBasePickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMTBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    const auto Pawn = Cast<APawn>(OtherActor);
    if (GivePickTo(Pawn))
    {
        PickupWasTaken();
    }

    UE_LOG(LogBasePickup, Display, TEXT("Pickup was taken"));
}

bool AMTBasePickup::GivePickTo(APawn* PlayerPawn)
{
    return false;
}

void AMTBasePickup::PickupWasTaken()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    if (GetRootComponent())
    {
        GetRootComponent()->SetVisibility(false, true);
    }
    FTimerHandle RespawnTimerHandle;
    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AMTBasePickup::Respawn, RespawnTime);
}

void AMTBasePickup::Respawn()
{
    if (GetRootComponent())
    {
        GetRootComponent()->SetVisibility(true, true);
    }
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}