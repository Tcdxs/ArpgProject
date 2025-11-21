// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArpgProject/PlayerCharacter/Enums/GameEnums.h"
#include "Engine/DataAsset.h"
#include "PrimaryActionData.generated.h"

/**
 * 
 */
UCLASS()
class ARPGPROJECT_API UPrimaryActionData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NameOfAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EOwnerType OwnerType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EActionPriorityType Priority;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EActionType ActionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EHitDetectType AttackDectectType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAttackType AttackType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool PlayerUseMotionWarping;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWhichMotionWarping WhichMotionWarpingPlayerUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayerWarpTriggerRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayerDistanceBeforeEnemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayerWarpingOffset_X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayerWarpingOffset_Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayerWarpingOffset_Z;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayerInterpSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayerInterpTimeLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool UseSeperateEnemyHitAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* EnemyHitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* EnemyHitMontage_InAir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AudioStartTime_Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* AttackSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* EnemyHitSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool EnemyUseMotionWarping;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWhichMotionWarpingEnemyUse WhichMotionWarpingEnemyUse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EnemyBackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EnemyWarpingOffset_Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EnemyWarpingOffset_Z;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EMovementMode> EnemyMovementModeWhenHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EnemyInterpSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EnemyInterpTimeLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool PlayCameraShake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECameraShakeType CameraShakeType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageValue;
};
