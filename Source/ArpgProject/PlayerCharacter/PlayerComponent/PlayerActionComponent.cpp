// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerActionComponent.h"

#include "ArpgProject/NCPP_Enemy/NCPP_Enemy.h"
#include "ArpgProject/PlayerCharacter/PlayerCharacter.h"
#include "Navigation/PathFollowingComponent.h"

/*				接口实现				*/

void UPlayerActionComponent::ToTriggerAction_Implementation(const EActionType ActionType,  EActionPriorityType ActionDataPriority)
{
	TriggerAction(ActionType,  ActionDataPriority);
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

	
	/*					身份识别					*/

	APlayerCharacter* Type_Player = Cast<APlayerCharacter>(GetOwner());
	if (Type_Player)
	{
		OwnerType = EOwnerType::Player;
		AttackDetectType = Type_Player->AttackDetectType;
	}
	else
	{
		ANCPP_Enemy* Type_Enemy = Cast<ANCPP_Enemy>(GetOwner());
		if (Type_Enemy)
		{
			OwnerType = EOwnerType::Enemy;
			AttackDetectType = EHitDetectType::None;
		}
		else
		{
			OwnerType = EOwnerType::Boss;
			AttackDetectType = EHitDetectType::None;
		}
	}
}


void UPlayerActionComponent::TriggerAction(EActionType ActionType, EActionPriorityType ActionDataPriority)
{
	
	/*								PriorityArea							*/
	
	EActionPriorityType Priority = ActionDataPriority;
	ActionPriority = GetActionPrioritySelectionValue(Priority);
	
	if (ActionPriority >= PreviousActionPriority)
	{
		if ((ActionType != EActionType::NoAction)&&(ActionType != EActionType::CanCombo))
		{
			UE_LOG(LogTemp, Warning, TEXT("Return"));
			return;
		}
	}
	PreviousActionPriority = ActionPriority;

	
	/*						ActionSelectionLibraryArea						*/

	switch (OwnerType)
	{
		case EOwnerType::Player:
			UE_LOG(LogTemp, Warning, TEXT("TriggerAction: EOwnerType::Player"));
			switch (ActionType)
			{
				case EActionType::CanCombo:
					SetPriority(1);
					return;
				
				case EActionType::NoAction:
					SetPriority(2);
					return;
				
				case EActionType::Attack:
					switch (AttackDetectType)
					{
						case EHitDetectType::None:
							return;
						
						case EHitDetectType::Sword:
							switch (LightComboNumber)
							{
								case EComboNumber::One:
									if (Sword_LightCombo1)ActionDataAsset = Sword_LightCombo1;
									IncreaseLightComboNumber();
									return;
								
								case EComboNumber::Two:
									if (Sword_LightCombo2)ActionDataAsset = Sword_LightCombo2;
									IncreaseLightComboNumber();
									return;
								
								case EComboNumber::Three:
									if (Sword_LightCombo3)ActionDataAsset = Sword_LightCombo3;
									IncreaseLightComboNumber();
									return;
								
								case EComboNumber::Four:
									if (Sword_LightCombo4)ActionDataAsset = Sword_LightCombo4;
									IncreaseLightComboNumber();
									return;
								
								case EComboNumber::Five:
									if (Sword_LightCombo5)ActionDataAsset = Sword_LightCombo5;
									IncreaseLightComboNumber();
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

	if (ActionDataAsset == nullptr)  // 防止空指针报错
	{
		UE_LOG(LogTemp, Error, TEXT("ActionDataAsset Is Nullptr"));
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
	if (ActionDataAsset != nullptr)
	{
		OwnerCharacter = Cast<ACharacter>(GetOwner());
		if (ActionDataAsset->Montage) OwnerCharacter->PlayAnimMontage(ActionDataAsset->Montage,1.f,FName("Default"));
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

void UPlayerActionComponent::ResetLightComboNumber()
{
	LightComboNumber = EComboNumber::One;
}

void UPlayerActionComponent::ResetHeavyComboNumber()
{
	HeavyComboNumber = EComboNumber::One;
}

void UPlayerActionComponent::IncreaseLightComboNumber()
{
	switch(LightComboNumber)
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
	
}

void UPlayerActionComponent::IncreaseHeavyComboNumber()
{
	switch(HeavyComboNumber)
	{
	case EComboNumber::One:
		HeavyComboNumber = EComboNumber::Two;
		return;
		
	case EComboNumber::Two:
		HeavyComboNumber = EComboNumber::Three;
		return;
		
	case EComboNumber::Three:
		HeavyComboNumber = EComboNumber::Four;
		return;
		
	case EComboNumber::Four:
		HeavyComboNumber = EComboNumber::Five;
		return;
		
	case EComboNumber::Five:
		HeavyComboNumber = EComboNumber::One;
		return;
	case EComboNumber::Max:
		return;
	}
}

void UPlayerActionComponent::MontageBlendingOut(UAnimMontage* Montage, bool bInterrupted)
{
	
}
