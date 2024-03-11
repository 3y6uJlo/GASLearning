// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "Aura/AbilitySystem/AuraAbilitySystemComponent.h"
#include "Aura/Player/AuraPlayerState.h"
#include "Aura/UI/Widgets/HUD/AuraHUD.h"
#include "GameFramework/CharacterMovementComponent.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority())
		return;

	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (HasAuthority())
		return;

	InitAbilityActorInfo();
}

int32 AAuraCharacter::GetCharacterLevel()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	if (!AuraPlayerState)
		return 0;
	
	return AuraPlayerState->GetCharacterLevel(); 
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	if (!AuraPlayerState)
		return;

	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();
	
	AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	APlayerController* PlayerController = AuraPlayerState->GetPlayerController();
	if (!PlayerController)
		return;
	
	AAuraHUD* AuraHUD = PlayerController->GetHUD<AAuraHUD>();
	if (!AuraHUD)
		return;
	
	AuraHUD->InitHUD(PlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);

	InitializeAttributes();
}
