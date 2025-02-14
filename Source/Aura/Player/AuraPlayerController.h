// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class IEnemyInterface;

UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	AAuraPlayerController();
	
protected:
	
	virtual void BeginPlay() override;
	virtual  void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	
private:

	void Move(const FInputActionValue& InputActionValue);
	void CursorTrace();
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext> AuraContext;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> MoveAction;

	TObjectPtr<IEnemyInterface> LastActor;
	TObjectPtr<IEnemyInterface> CurrentActor;
};
