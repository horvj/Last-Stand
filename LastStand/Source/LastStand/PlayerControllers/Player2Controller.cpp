#include "Player2Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"

void APlayer2Controller::BeginPlay()
{
    Super::BeginPlay();

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
        GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
    {
        if (InputMappingContext)
        {
            Subsystem->AddMappingContext(InputMappingContext, 0);
            UE_LOG(LogTemp, Warning, TEXT("Player2Controller: IMC added successfully"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Player2Controller: InputMappingContext is NULL!"));
        }
    }
}

void APlayer2Controller::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInputComponent =
        CastChecked<UEnhancedInputComponent>(InputComponent))
    {
        if (MoveAction)
        {
            EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,
                this, &APlayer2Controller::Move);
        }

        if (JumpAction)
        {
            EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started,
                this, &APlayer2Controller::Jump);
            EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed,
                this, &APlayer2Controller::StopJumping);
        }
    }
}

void APlayer2Controller::Move(const FInputActionValue& Value)
{
    if (ACharacter* ControlledCharacter = Cast<ACharacter>(GetPawn()))
    {
        FVector2D MovementVector = Value.Get<FVector2D>();

        if (MovementVector.Y != 0.0f)
        {
            FVector RightDirection = FVector(0, 1, 0);
            ControlledCharacter->AddMovementInput(RightDirection, MovementVector.Y);
        }

        MovementVector.Y = 0.0f;

        if (MovementVector.X != 0.0f)
        {
            const FRotator Rotation = GetControlRotation();
            const FRotator YawRotation(0, Rotation.Yaw, 0);
            const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
            ControlledCharacter->AddMovementInput(RightDirection, MovementVector.X);
        }
    }
}

void APlayer2Controller::Jump()
{
    if (ACharacter* ControlledCharacter = Cast<ACharacter>(GetPawn()))
    {
        ControlledCharacter->Jump();
    }
}

void APlayer2Controller::StopJumping()
{
    if (ACharacter* ControlledCharacter = Cast<ACharacter>(GetPawn()))
    {
        ControlledCharacter->StopJumping();
    }
}