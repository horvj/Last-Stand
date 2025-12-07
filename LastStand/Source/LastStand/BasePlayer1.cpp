#include "BasePlayer1.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "Data/CharacterData.h"

ABasePlayer1::ABasePlayer1()
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

void ABasePlayer1::BeginPlay()
{
    Super::BeginPlay();
    InitializeCharacterFromData();
}

void ABasePlayer1::InitializeCharacterFromData()
{
    if (!CharacterData)
    {
        return;
    }

    if (CharacterData->SkeletalMesh)
    {
        GetMesh()->SetSkeletalMesh(CharacterData->SkeletalMesh);
    }

    if (CharacterData->SpecialAbility && AbilitySystemComponent)
    {
        AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(CharacterData->SpecialAbility, 1, 0));
    }

    if (CharacterData->CharacterHealth)
    {
        PlayerHealth = CharacterData->CharacterHealth;
    }
    
    if (CharacterData->CharacterPunchAttackPower)
    {
        PlayerPunchAttackPower = CharacterData->CharacterPunchAttackPower;
    }

    if (CharacterData->CharacterKickAttackPower)
    {
        PlayerKickAttackPower = CharacterData->CharacterKickAttackPower;
    }
}

void ABasePlayer1::SetCharacterData(UCharacterData* InCharacterData)
{
    CharacterData = InCharacterData;
    InitializeCharacterFromData();
}
