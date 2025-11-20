#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasePlayer1.generated.h"

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

    // Character Data
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
    UCharacterData* CharacterData;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
    UAbilitySystemComponent* AbilitySystemComponent;

    // Character initialization
    void InitializeCharacterFromData();

public:
    UFUNCTION(BlueprintCallable, Category = "Character")
    void SetCharacterData(UCharacterData* InCharacterData);
};
