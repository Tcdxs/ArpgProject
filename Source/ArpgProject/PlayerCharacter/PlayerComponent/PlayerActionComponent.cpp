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

	ActionPriority = 3;
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
	
					return;
				
				case EActionType::NoAction:

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

	
	
}


void UPlayerActionComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UPlayerActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

