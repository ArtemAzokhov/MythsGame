// Myth Game, All Rights Reserved.

#include "Player/MTBaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/MTHealthComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);

AMTBaseCharacter::AMTBaseCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetRelativeRotation(FRotator(-50.0f, 0.0f, 0.0f));
    SpringArmComponent->TargetArmLength = 2000.0f;
    SpringArmComponent->bDoCollisionTest = false;
    SpringArmComponent->SetupAttachment(GetRootComponent());

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->FieldOfView = 45.0f;
    CameraComponent->SetupAttachment(SpringArmComponent);

    HealthComponent = CreateDefaultSubobject<UMTHealthComponent>("HealthComponent");
}

void AMTBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    OnHealthChanged(HealthComponent->GetHealth()); // to set health value before the AMTBaseCharacter is constracted
    HealthComponent->OnDeath.AddUObject(this, &AMTBaseCharacter::OnDeath);
    HealthComponent->OnHealthChange.AddUObject(this, &AMTBaseCharacter::OnHealthChanged);

    LandedDelegate.AddDynamic(this, &AMTBaseCharacter::OnGroundLanded);
    LandedDamage = FVector2D(LandedDamage.X, HealthComponent->GetMaxHealth()); // to kill a character when he's lended from extreme heights.
}

void AMTBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMTBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Get the player controller
    APlayerController* PC = Cast<APlayerController>(GetController());

    // Get the local player subsystem
    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

    // Clear out existing mapping, and add our mapping
    Subsystem->ClearAllMappings();
    Subsystem->AddMappingContext(InputMapping, 0);

    UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

    Input->BindAction(InputMove, ETriggerEvent::Triggered, this, &AMTBaseCharacter::Move);
    Input->BindAction(InputLook, ETriggerEvent::Triggered, this, &AMTBaseCharacter::Look);
    Input->BindAction(InputJump, ETriggerEvent::Started, this, &ACharacter::Jump);
    Input->BindAction(InputJump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
}

void AMTBaseCharacter::Move(const FInputActionValue& Value)
{
    if (!Controller) return;

    const FVector2D MoveValue = Value.Get<FVector2D>();
    const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);

    // Forward/Backward direction
    if (MoveValue.Y != 0.f)
    {
        // Get forward vector
        const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);

        AddMovementInput(Direction, MoveValue.Y);
    }

    // Right/Left direction
    if (MoveValue.X != 0.f)
    {
        // Get right vector
        const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);

        AddMovementInput(Direction, MoveValue.X);
    }
}

void AMTBaseCharacter::Look(const FInputActionValue& Value)
{
    if (!Controller) return;

    const FVector2D LookValue = Value.Get<FVector2D>();

    if (LookValue.X != 0.f)
    {
        AddControllerYawInput(LookValue.X);
    }

    if (LookValue.Y != 0.f)
    {
        IsNegatePitch ? AddControllerPitchInput(LookValue.Y) : AddControllerPitchInput(LookValue.Y * -1.0);
    }
}

void AMTBaseCharacter::OnDeath()
{
    UE_LOG(BaseCharacterLog, Display, TEXT("Player %s is dead"), *GetName());

    PlayAnimMontage(DeathAnimMontage);
    GetCharacterMovement()->DisableMovement();

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);
}

void AMTBaseCharacter::OnHealthChanged(float NewHealth)
{
    UE_LOG(BaseCharacterLog, Display, TEXT("Player %s have %0.f health"), *GetName(), NewHealth);
}

void AMTBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
    const auto FallVelocityZ = -GetVelocity().Z;

    if (FallVelocityZ < LandedDamageVelocity.X) return;

    const auto FallDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
    TakeDamage(FallDamage, FDamageEvent{}, nullptr, nullptr);

    UE_LOG(BaseCharacterLog, Display, TEXT("On landed: %f"), FallVelocityZ);
    UE_LOG(BaseCharacterLog, Display, TEXT("Fall damage: %f"), FallDamage);
}