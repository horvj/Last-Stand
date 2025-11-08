#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasePlayer2.generated.h"

class UCharacterData;
class UAbilitySystemComponent;

UCLASS()
class LASTSTAND_API ABasePlayer2 : public ACharacter
{
    GENERATED_BODY()
public:
    ABasePlayer2();

protected:
    virtual void BeginPlay() override;

    // Player 2 spawn info 
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Setup")
    FVector DefaultSpawnLocation = FVector(200, 0, 100);
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Setup")
    FRotator DefaultSpawnRotation = FRotator(0, -90, 0);

    // Character Data
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
    UCharacterData* CharacterData;

    UPROPERTY()
    UAbilitySystemComponent* AbilitySystemComponent;

    // Character initialization
    void InitializeCharacterFromData();

public:
    // Getters for spawn info
    UFUNCTION(BlueprintPure, Category = "Player Setup")
    FVector GetDefaultSpawnLocation() const { return DefaultSpawnLocation; }
    UFUNCTION(BlueprintPure, Category = "Player Setup")
    FRotator GetDefaultSpawnRotation() const { return DefaultSpawnRotation; }

    UFUNCTION(BlueprintCallable, Category = "Character")
    void SetCharacterData(UCharacterData* InCharacterData);
};
