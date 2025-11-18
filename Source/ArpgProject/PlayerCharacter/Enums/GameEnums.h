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
	Sword UMETA(DisplayName = "Sword"),
	Spear UMETA(DisplayName = "Spear"),
	Dagger UMETA(DisplayName = "Dagger"),
	Max UMETA(Hidden)
};



UCLASS()
class ARPGPROJECT_API UGameEnums : public UUserDefinedEnum
{
	GENERATED_BODY()
	
	
	
	
};
