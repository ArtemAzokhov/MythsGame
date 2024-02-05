// Myth Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MTDamageActor.generated.h"

UCLASS()
class MYTH_API AMTDamageActor : public AActor
{
    GENERATED_BODY()

public:
    AMTDamageActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    USceneComponent* SceneComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Radius = 300.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool DoFoolDamage = false;

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
};
