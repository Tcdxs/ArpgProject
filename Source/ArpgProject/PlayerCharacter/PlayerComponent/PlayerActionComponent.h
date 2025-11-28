// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionData/PrimaryActionData.h"
#include "ArpgProject/Interface/I_DataTransfer.h"
#include "Components/ActorComponent.h"
#include "PlayerActionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARPGPROJECT_API UPlayerActionComponent : public UActorComponent, public II_DataTransfer
{
	GENERATED_BODY()

	/*					接口相关					*/
public:
	virtual void ToTriggerAction_Implementation(EActionType ActionType,  EActionPriorityType ActionDataPriority) override;
	virtual EMovementMode GetMovementModeValue_Implementation (const FString& Key) const override;
	
	/*					variable			 	*/


public:

protected:
	EComboNumber LightComboNumber = EComboNumber::One;
	EComboNumber HeavyComboNumber = EComboNumber::One;
	int32 ActionPriority = 3;
	int32 PreviousActionPriority = 3;

	FVector WarpLocation;
	FRotator WarpRotation;
	FVector WarpLocation_Final;
	FRotator WarpRotation_Final;

	TEnumAsByte<EMovementMode> PlayerMovementMode;
private:
	EOwnerType OwnerType;
	EHitDetectType AttackDetectType;
	
	UPrimaryActionData* ActionDataAsset;
	

	/*					function				*/

	
public:	
	UPlayerActionComponent();

	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
protected:
	virtual void BeginPlay() override;
	
	void TriggerAction(const EActionType ActionType,  EActionPriorityType ActionDataPriority);

	void CE_PlayMontage(FVector WarpLocation, FRotator WarpRotation, bool UseWarping);

	void SetPriority(int32 PriorityIndex);

	void ResetComboNumber();
	

private:

		
	
};

