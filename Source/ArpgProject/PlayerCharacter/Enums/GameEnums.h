// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "GameEnums.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ECameraShakeType: uint8
{
	None UMETA(DisplayName = "None"),
	Light UMETA(DisplayName = "Light"),
	Average UMETA(DisplayName = "Average"),
	Heavy UMETA(DisplayName = "Heavy"),
	Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EComboNumber: uint8
{
	One UMETA(DisplayName = "One"),
	Two UMETA(DisplayName = "Two"),
	Three UMETA(DisplayName = "Three"),
	Four UMETA(DisplayName = "Four"),
	Five UMETA(DisplayName = "Five"),
	Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EHitDetectType: uint8
{
	None UMETA(DisplayName = "None"),
	Sword UMETA(DisplayName = "Sword"),
	Spear UMETA(DisplayName = "Spear"),
	Dagger UMETA(DisplayName = "Dagger"),
	Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EWhichMotionWarping: uint8
{
	OnGroundCombo UMETA(DisplayName = "On Ground Combo"),
	OnGroundDodge UMETA(DisplayName = "On Ground Dodge"),
	NoWarping UMETA(DisplayName = "No Warping"),
	Parry UMETA(DisplayName = "Parry"),
	Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EWhichMotionWarpingEnemyUse: uint8
{
	OnGroundHit UMETA(DisplayName = "On Ground Hit"),
	NoWarping UMETA(DisplayName = "No Warping"),
	Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EActionType: uint8
{
	Attack UMETA(DisplayName = "Attack"),
	Dodge UMETA(DisplayName = "Dodge"),
	PerfectDodge UMETA(DisplayName = "PerfectDodge"),
	Parry UMETA(DisplayName = "Parry"),
	Skill UMETA(DisplayName = "Skill"),
	Item UMETA(DisplayName = "Item"),
	NoAction UMETA(DisplayName = "NoAction"),
	CanCombo UMETA(DisplayName = "CanCombo"),
	Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EAttackType: uint8
{
	NoAttack UMETA(DisplayName = "NoAttack"),
	Light UMETA(DisplayName = "Light"),
	Heavy UMETA(DisplayName = "Heavy"),
	Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EActionPriorityType: uint8
{
	Supreme UMETA(DisplayName = "Supreme"),
	High UMETA(DisplayName = "High"),
	Medium UMETA(DisplayName = "Medium"),
	Low UMETA(DisplayName = "Low"),
	Bottom UMETA(DisplayName = "Bottom"),
	Max UMETA(Hidden)
};

inline int32 GetActionPrioritySelectionValue(EActionPriorityType Level)
{
	switch (Level)
	{
	case EActionPriorityType::Bottom: return 2;
	case EActionPriorityType::Low: return 1;
	case EActionPriorityType::Medium: return 0;
	case EActionPriorityType::High: return -1;
	case EActionPriorityType::Supreme: return -2;
	case EActionPriorityType::Max: return 3;
	}
	return 0;
}

UENUM (BlueprintType)
enum class EOwnerType: uint8
{
	Player UMETA(DisplayName = "Player"),
	Enemy UMETA(DisplayName = "Enemy"),
	Boss UMETA(DisplayName = "Boss"),
	Max UMETA(Hidden)
};

UCLASS()
class ARPGPROJECT_API UGameEnums : public UUserDefinedEnum
{
	GENERATED_BODY()
	
	
	
	
};
