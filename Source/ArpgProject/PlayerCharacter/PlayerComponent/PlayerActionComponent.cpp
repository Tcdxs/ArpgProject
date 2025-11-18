// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerActionComponent.h"


UPlayerActionComponent::UPlayerActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


void UPlayerActionComponent::TriggerAction(UPrimaryActionData* ActionDataAsset)
{
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

			return;
		
		case EOwnerType::Enemy:

			return;
		
		case EOwnerType::Boss:

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

