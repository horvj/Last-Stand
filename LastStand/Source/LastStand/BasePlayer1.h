#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasePlayer1.generated.h"

// Forward declarations
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class LASTSTAND_API ABasePlayer1 : public ACharacter
{
    GENERATED_BODY()

public:
    ABasePlayer1();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    // Player 1 spawn info
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Setup")
    FVector DefaultSpawnLocation = FVector(-200, 0, 100);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Setup")
    FRotator DefaultSpawnRotation = FRotator(0, 90, 0);

    // Player 1 Input 
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputMappingContext* Player1MappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* P1_MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* P1_JumpAction;

    // Movement function
    void Move(const FInputActionValue& Value);

public:
    // Getters for spawn info
    UFUNCTION(BlueprintPure, Category = "Player Setup")
    FVector GetDefaultSpawnLocation() const { return DefaultSpawnLocation; }

    UFUNCTION(BlueprintPure, Category = "Player Setup")
    FRotator GetDefaultSpawnRotation() const { return DefaultSpawnRotation; }
};