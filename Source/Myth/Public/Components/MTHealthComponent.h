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

    UFUNCTION(BlueprintCallable)
    bool IsDead() const { return Health <= 0.0f; }

    float GetHealth() const { return Health; }
    float GetMaxHealth() const { return MaxHealth; }

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0", ClampMax = "1000"))
    float MaxHealth = 100.0f;

    virtual void BeginPlay() override;

private:
    float Health = 0.0f;

    UFUNCTION()
    void OnTakeAnyDamage(
        AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
