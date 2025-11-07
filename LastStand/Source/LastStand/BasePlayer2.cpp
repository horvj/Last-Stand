#include "BasePlayer2.h"
#include "InputActionValue.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystemComponent.h"
#include "Data/CharacterData.h"
#include "Subsystems/CharacterSelectSubsytem.h"

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

    // Create Ability System Component
    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

void ABasePlayer2::BeginPlay()
{
    Super::BeginPlay();

    InitializeCharacterFromData();

    // Add Input Mapping Context for Player 2
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            if (Player2MappingContext)
            {
                Subsystem->AddMappingContext(Player2MappingContext, 0);
            }
        }
    }
}

void ABasePlayer2::InitializeCharacterFromData()
{
    if (!CharacterData)
    {
        return;
    }

    // Set skeletal mesh
    if (CharacterData->SkeletalMesh)
    {
        GetMesh()->SetSkeletalMesh(CharacterData->SkeletalMesh);
    }

    // Apply stats
    // You might want to store these in a stats component or player state
    // For now, just log them as an example
    UE_LOG(LogTemp, Warning, TEXT("Character: %s - Health: %f, Attack Power: %f"),
        *CharacterData->CharacterName, CharacterData->Health, CharacterData->AttackPower);

    // Grant special ability
    if (CharacterData->SpecialAbility && AbilitySystemComponent)
    {
        AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(CharacterData->SpecialAbility, 1, 0));
        UE_LOG(LogTemp, Warning, TEXT("Granted special ability to %s"), *CharacterData->CharacterName);
    }
}

void ABasePlayer2::SetCharacterData(UCharacterData* InCharacterData)
{
    CharacterData = InCharacterData;
    InitializeCharacterFromData();
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

    if (Controller != nullptr && MovementVector.Y != 0.0f)
    {
        FVector RightDirection = FVector(0, 1, 0);
        AddMovementInput(RightDirection, MovementVector.Y);
    }

    // Zero out Y axis (no forward/back movement)
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