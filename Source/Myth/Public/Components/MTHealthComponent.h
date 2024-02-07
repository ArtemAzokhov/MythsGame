// Myth Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MTHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangeSignature, float);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) class MYTH_API UMTHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UMTHealthComponent();

    FOnDeathSignature OnDeath;
    FOnHealthChangeSignature OnHealthChange;

    UFUNCTION(BlueprintCallable, Category = "Health")
    bool IsDead() const { return FMath::IsNearlyZero(Health); }

    float GetHealth() const { return Health; }
    float GetMaxHealth() const { return MaxHealth; }

    bool TryToAddHealth(float HealthAmount);
    bool IsHealthFull() const;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0", ClampMax = "1000"))
    float MaxHealth = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
    bool AutoHeal = true;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealPerSecond = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealUpdateTime = 0.25f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealDelay = 3.0f;

    virtual void BeginPlay() override;

private:
    float Health = 0.0f;

    FTimerHandle HealTimerHandle;

    UFUNCTION()
    void OnTakeAnyDamage(
        AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

    void HealUpdate();
    void SetHealth(float NewHealth);
};
