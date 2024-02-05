// Myth Game, All Rights Reserved.

#include "Player/MTBaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

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
}

void AMTBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
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
