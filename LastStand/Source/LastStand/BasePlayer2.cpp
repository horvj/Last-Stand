#include "BasePlayer2.h"
#include "InputActionValue.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ABasePlayer2::ABasePlayer2()
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

void ABasePlayer2::BeginPlay()
{
    Super::BeginPlay();

    // Debug to see if Player 2 is being possessed
    UE_LOG(LogTemp, Warning, TEXT("Player2 BeginPlay - Controller: %s"), Controller ? TEXT("YES") : TEXT("NO"));

    // Add Input Mapping Context for Player 2
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        UE_LOG(LogTemp, Warning, TEXT("Player2 has PlayerController!"));
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            if (Player2MappingContext)
            {
                UE_LOG(LogTemp, Warning, TEXT("Player2 adding mapping context"));
                Subsystem->AddMappingContext(Player2MappingContext, 0);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Player2 mapping context is NULL!"));
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Player2 has NO PlayerController!"));
    }
}

void ABasePlayer2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // Moving
        EnhancedInputComponent->BindAction(P2_MoveAction, ETriggerEvent::Triggered, this, &ABasePlayer2::Move);

        // Jumping
        EnhancedInputComponent->BindAction(P2_JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(P2_JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
    }
}

void ABasePlayer2::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    // Add debug for Player 2
    UE_LOG(LogTemp, Warning, TEXT("Player2 Move: X=%f, Y=%f"), MovementVector.X, MovementVector.Y);

    // Zero out X axis (no forward/back movement)
    MovementVector.X = 0.0f;

    if (Controller != nullptr && MovementVector.Y != 0.0f) 
    {
        // Find out which way is right (left/right movement)
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // Get right direction for left/right movement
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        // Add movement (use Y axis for left/right)
        AddMovementInput(RightDirection, MovementVector.Y); 
    }
}
