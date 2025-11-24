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
	virtual void ToTriggerAction_Implementation(UPrimaryActionData* ActionDataAsset,  EActionPriorityType ActionDataPriority) override;
	virtual EMovementMode GetMovementModeValue_Implementation (const FString& Key) const override;
	
	/*					variable			 	*/


public:

protected:
	int32 LightComboNumber = 0;
	int32 HeavyComboNumber = 0;
	int32 ActionPriority = 3;
	int32 PreviousActionPriority = 3;

	FVector WarpLocation;
	FRotator WarpRotation;
	FVector WarpLocation_Final;
	FRotator WarpRotation_Final;

	TEnumAsByte<EMovementMode> PlayerMovementMode;
private:


	/*					function				*/

	
public:	
	UPlayerActionComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
protected:
	virtual void BeginPlay() override;
	
	void TriggerAction(UPrimaryActionData* ActionAsset,  EActionPriorityType ActionDataPriority);

	void CE_PlayMontage(FVector WarpLocation, FRotator WarpRotation, bool UseWarping);

	void SetPriority(int32 PriorityIndex);

	void ResetComboNumber();
	

private:

		
	
};

