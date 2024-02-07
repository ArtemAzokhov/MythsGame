// Myth Game, All Rights Reserved.

#include "Components/MTHealthComponent.h"

UMTHealthComponent::UMTHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UMTHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    SetHealth(MaxHealth);

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UMTHealthComponent::OnTakeAnyDamage);
    }
}

void UMTHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.0f || IsDead() || !GetWorld()) return;

    SetHealth(Health - Damage);

    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
    else if (AutoHeal)
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, //
            &UMTHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
    }
}

void UMTHealthComponent::HealUpdate()
{
    SetHealth(Health + HealPerSecond*HealUpdateTime);

    if (FMath::IsNearlyEqual(Health, MaxHealth) && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }
}

void UMTHealthComponent::SetHealth(float NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);

    OnHealthChange.Broadcast(Health);
}
