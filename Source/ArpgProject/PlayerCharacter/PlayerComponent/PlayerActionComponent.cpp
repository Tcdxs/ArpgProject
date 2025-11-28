// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerActionComponent.h"

/*				接口实现				*/

void UPlayerActionComponent::ToTriggerAction_Implementation(UPrimaryActionData* ActionDataAsset,  EActionPriorityType ActionDataPriority)
{
	TriggerAction(ActionDataAsset,  ActionDataPriority);
}

EMovementMode UPlayerActionComponent::GetMovementModeValue_Implementation(const FString& Key) const
{
	if (Key == "PlayerMovementMode")
	{
		return PlayerMovementMode;
	}
	return MOVE_None;
}


UPlayerActionComponent::UPlayerActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UPlayerActionComponent::TriggerAction(UPrimaryActionData* ActionDataAsset, EActionPriorityType ActionDataPriority)
{
	
	/*								PriorityArea							*/
	
	EActionPriorityType Priority = ActionDataPriority;
	ActionPriority = GetActionPrioritySelectionValue(Priority);
	
	if (!(ActionPriority < PreviousActionPriority)&&!ActionDataAsset)
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
							switch (LightComboNumber)
							{
								case EComboNumber::One:

									LightComboNumber = EComboNumber::Two;
									return;
								
								case EComboNumber::Two:

									LightComboNumber = EComboNumber::Three;
									return;
								
								case EComboNumber::Three:

									LightComboNumber = EComboNumber::Four;
									return;
								
								case EComboNumber::Four:

									LightComboNumber = EComboNumber::Five;
									return;
								
								case EComboNumber::Five:

									LightComboNumber = EComboNumber::One;
									return;

								case EComboNumber::Max:
									return;
							}
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
	LightComboNumber = EComboNumber::One;
	HeavyComboNumber = EComboNumber::One;
}
