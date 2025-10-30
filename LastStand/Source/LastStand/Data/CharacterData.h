// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Abilities/GameplayAbility.h" 
#include "CharacterData.generated.h"

/**
 * 
 */
UCLASS()
class LASTSTAND_API UCharacterData : public UDataAsset
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
    FString CharacterName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
    class USkeletalMesh* SkeletalMesh;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
    TSubclassOf<class UGameplayAbility> SpecialAbility;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    float Health = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    float AttackPower = 1.0f;

};
