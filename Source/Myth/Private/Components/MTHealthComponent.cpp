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
    SetHealth(Health + HealPerSecond * HealUpdateTime);

    if (IsHealthFull() && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }
}

void UMTHealthComponent::SetHealth(float NewHealth)
{
    const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    Health = NextHealth;

    OnHealthChange.Broadcast(Health);
}

bool UMTHealthComponent::TryToAddHealth(float HealthAmount)
{
    if (IsDead() || IsHealthFull()) return false;

    SetHealth(Health + HealthAmount);
    return true;
}

bool UMTHealthComponent::IsHealthFull() const
{
    return FMath::IsNearlyEqual(Health, MaxHealth);
}