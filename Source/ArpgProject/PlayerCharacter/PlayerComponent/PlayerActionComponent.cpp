// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerActionComponent.h"

/*				接口实现				*/

void UPlayerActionComponent::ToTriggerAction_Implementation(UPrimaryActionData* ActionDataAsset)
{
	TriggerAction(ActionDataAsset);
}


UPlayerActionComponent::UPlayerActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UPlayerActionComponent::TriggerAction(UPrimaryActionData* ActionDataAsset)
{
	UE_LOG(LogTemp, Warning, TEXT("TriggerAction"));
	if (ActionDataAsset == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("TriggerAction: ActionAsset is null!"));
		return;
	}

	
	/*								PriorityArea							*/

	FString ActionName = ActionDataAsset->NameOfAction.ToString();
	EActionPriorityType Priority = ActionDataAsset->Priority;
	ActionPriority = GetActionPrioritySelectionValue(Priority);
	if (!(ActionPriority < PreviousActionPriority))
	{
		if ((ActionDataAsset->ActionType != EActionType::NoAction)&&(ActionDataAsset->ActionType != EActionType::CanCombo))
		{
			return;
		}
	}
	PreviousActionPriority = ActionPriority;

	
	/*						ActionSelectionLibraryArea						*/

	switch (ActionDataAsset->OwnerType)
	{
		case EOwnerType::Player:
			UE_LOG(LogTemp, Warning, TEXT("TriggerAction: EOwnerType::Player"));
			switch (ActionDataAsset->ActionType)
			{
				case EActionType::CanCombo:
					SetPriority(1);
					return;
				
				case EActionType::NoAction:
					SetPriority(2);
					return;
				
				case EActionType::Attack:
					switch (ActionDataAsset->AttackDectectType)
					{
						case EHitDetectType::None:
							return;
						
						case EHitDetectType::Sword:
						
							return;
						
						case EHitDetectType::Spear:

							return;
						
						case EHitDetectType::Dagger:

							return;

						case EHitDetectType::Max:

							return;
						
					}
					return;
				
				case EActionType::Dodge:

					return;
				
				case EActionType::PerfectDodge:

					return;
				
				case EActionType::Parry:

					return;
				
				case EActionType::Skill:

					return;
				
				case EActionType::Item:

					return;
				
				case EActionType::Max:
					return;
			}
			
			return;
		
		case EOwnerType::Enemy:
			UE_LOG(LogTemp, Warning, TEXT("TriggerAction: EOwnerType::Enemy"));
		
			return;
		
		case EOwnerType::Boss:
			UE_LOG(LogTemp, Warning, TEXT("TriggerAction: EOwnerType::Boss"));
		
			return;
		
		case EOwnerType::Max:
			return;
	}

	/*				DataTransferAndSettingArea				*/




	/*					DetectArea					*/
	
	if (ActionDataAsset->PlayerUseMotionWarping)
	{
		switch (ActionDataAsset->WhichMotionWarpingPlayerUsed)
		{
		case EWhichMotionWarping::OnGroundCombo:

			return;
		case EWhichMotionWarping::OnGroundDodge:

			return;
		case EWhichMotionWarping::Parry:

			return;
		case EWhichMotionWarping::NoWarping:

			return;
		case EWhichMotionWarping::Max:
			return;
		}
	}

	
	/*					ExecutionArea					*/

	CE_PlayMontage(WarpLocation, WarpRotation, ActionDataAsset->PlayerUseMotionWarping);
}

void UPlayerActionComponent::CE_PlayMontage(FVector F_WarpLocation, FRotator F_WarpRotation, bool UseWarping)
{
	WarpLocation_Final = F_WarpLocation;
	WarpRotation_Final = F_WarpRotation;


	/*				MotionWarpingArea				*/
	
	if (UseWarping)
	{
		
	}
	else
	{
		
	}
}


void UPlayerActionComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UPlayerActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


inline void UPlayerActionComponent::SetPriority(int32 PriorityIndex)
{
	PreviousActionPriority = PriorityIndex;
	
}

void UPlayerActionComponent::ResetComboNumber()
{
	LightComboNumber = 0;
	HeavyComboNumber = 0;
}
