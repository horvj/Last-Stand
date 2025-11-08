// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "Player2Controller.generated.h"


class UEnhancedInputComponent;
class UEnhancedInputLocalPlayerSubsystem;
class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class LASTSTAND_API APlayer2Controller : public APlayerController
{
	GENERATED_BODY()

public:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
    UInputMappingContext* InputMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
    UInputAction* JumpAction;

private:
    void Move(const FInputActionValue& Value);
    void Jump();
    void StopJumping();

	
};
