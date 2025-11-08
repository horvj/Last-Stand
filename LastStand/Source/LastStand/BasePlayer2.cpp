#include "BasePlayer2.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "Data/CharacterData.h"

ABasePlayer2::ABasePlayer2()
{
    PrimaryActorTick.bCanEverTick = false;

    GetCapsuleComponent()->SetCapsuleHalfHeight(88.0f);
    GetCapsuleComponent()->SetCapsuleRadius(34.0f);

    GetCharacterMovement()->bOrientRotationToMovement = false;
    GetCharacterMovement()->MaxWalkSpeed = 400.0f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2048.0f;
    GetCharacterMovement()->GroundFriction = 8.0f;
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

void ABasePlayer2::BeginPlay()
{
    Super::BeginPlay();
    InitializeCharacterFromData();
}

void ABasePlayer2::InitializeCharacterFromData()
{
    if (!CharacterData)
    {
        return;
    }

    if (CharacterData->SkeletalMesh)
    {
        GetMesh()->SetSkeletalMesh(CharacterData->SkeletalMesh);
    }

    UE_LOG(LogTemp, Warning, TEXT("Character: %s - Health: %f, Attack Power: %f"),
        *CharacterData->CharacterName, CharacterData->Health, CharacterData->AttackPower);

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
