#include "BasePlayer1.h"
#include "InputActionValue.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ABasePlayer1::ABasePlayer1()
{
    PrimaryActorTick.bCanEverTick = false;

    // Set size for collision capsule
    GetCapsuleComponent()->SetCapsuleHalfHeight(88.0f);
    GetCapsuleComponent()->SetCapsuleRadius(34.0f);

    // Configure character movement for Street Fighter style
    GetCharacterMovement()->bOrientRotationToMovement = false; // Don't auto-rotate
    GetCharacterMovement()->MaxWalkSpeed = 400.0f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2048.0f;
    GetCharacterMovement()->GroundFriction = 8.0f;
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;

    // Don't rotate when the controller rotates
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;
}

void ABasePlayer1::BeginPlay()
{
    Super::BeginPlay();

    // Add Input Mapping Context for Player 1
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            if (Player1MappingContext)
            {
                Subsystem->AddMappingContext(Player1MappingContext, 0);
            }
        }
    }
}

void ABasePlayer1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // Moving
        EnhancedInputComponent->BindAction(P1_MoveAction, ETriggerEvent::Triggered, this, &ABasePlayer1::Move);

        // Jumping
        EnhancedInputComponent->BindAction(P1_JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(P1_JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
    }
}

void ABasePlayer1::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    UE_LOG(LogTemp, Warning, TEXT("Player1 Move: X=%f, Y=%f"), MovementVector.X, MovementVector.Y);

    if (Controller != nullptr && MovementVector.Y != 0.0f)  // Use Y instead of X
    {
        FVector RightDirection = FVector(0, 1, 0);
        AddMovementInput(RightDirection, MovementVector.Y);  // Use Y instead of X
    }


    // **STREET FIGHTER STYLE: Zero out Y axis (no forward/back movement)**
    MovementVector.Y = 0.0f;

    if (Controller != nullptr)
    {
        // Find out which way is right (left/right movement)
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // Get right direction for left/right movement
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        // Add movement (use X axis for left/right)
        AddMovementInput(RightDirection, MovementVector.X);
    }
}