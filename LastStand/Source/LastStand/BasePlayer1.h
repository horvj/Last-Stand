#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasePlayer1.generated.h"

// Forward declarations
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UCharacterData;
class UAbilitySystemComponent;

UCLASS()
class LASTSTAND_API ABasePlayer1 : public ACharacter
{
    GENERATED_BODY()

public:
    ABasePlayer1();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    // Character Data Asset
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
    class UCharacterData* CharacterData;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
    class UAbilitySystemComponent* AbilitySystemComponent;

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

    // Initialize character from data asset
    void InitializeCharacterFromData();

public:
    // Getters for spawn info
    UFUNCTION(BlueprintPure, Category = "Player Setup")
    FVector GetDefaultSpawnLocation() const { return DefaultSpawnLocation; }

    UFUNCTION(BlueprintPure, Category = "Player Setup")
    FRotator GetDefaultSpawnRotation() const { return DefaultSpawnRotation; }

    // Setters and Getters for character data
    UFUNCTION(BlueprintCallable, Category = "Character")
    void SetCharacterData(UCharacterData* InCharacterData);

    UFUNCTION(BlueprintPure, Category = "Character")
    UCharacterData* GetCharacterData() const { return CharacterData; }

    UFUNCTION(BlueprintPure, Category = "Combat")
    UAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent; }


};