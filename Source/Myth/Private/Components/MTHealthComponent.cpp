// Myth Game, All Rights Reserved.

#include "Components/MTHealthComponent.h"

UMTHealthComponent::UMTHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UMTHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    Health = MaxHealth;

    AActor* ComponentOwner = GetOwner();
    if(ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UMTHealthComponent::OnTakeAnyDamage);
    }
}

void UMTHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.0f || IsDead()) return;
    Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
    OnHealthChange.Broadcast(Health);

    if(IsDead())
    {
        OnDeath.Broadcast();
    }
}
