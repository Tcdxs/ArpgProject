// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ArpgProject/Interface/I_DataTransfer.h"
#include "ArpgProject/PlayerCharacter/PlayerCharacter.h"
#include "V_JumpStart.generated.h"

/**
 * 
 */
UCLASS()
class ARPGPROJECT_API UV_JumpStart : public UAnimNotify, public II_DataTransfer
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;	
	
	UPROPERTY()
	TScriptInterface<II_DataTransfer> DataInterface;
private:
	UPROPERTY()
	APlayerCharacter* PlayerCharacter;
};
