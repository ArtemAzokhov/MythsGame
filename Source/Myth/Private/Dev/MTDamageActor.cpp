// Myth Game, All Rights Reserved.

#include "MTDamageActor.h"
#include "Kismet/GameplayStatics.h"

AMTDamageActor::AMTDamageActor()
{
    PrimaryActorTick.bCanEverTick = true;

    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SetRootComponent(SceneComponent);
}

void AMTDamageActor::BeginPlay()
{
    Super::BeginPlay();
}

void AMTDamageActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, nullptr, {}, this, nullptr, DoFoolDamage);
}
