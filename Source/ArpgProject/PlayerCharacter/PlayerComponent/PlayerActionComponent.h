// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionData/PrimaryActionData.h"
#include "Components/ActorComponent.h"
#include "PlayerActionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARPGPROJECT_API UPlayerActionComponent : public UActorComponent
{
	GENERATED_BODY()

	
	/*					variable			 	*/


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category= "DataAsset")
	UPrimaryActionData* Test;

	int32 ActionPriority;
	int32 PreviousActionPriority = 2;
protected:


private:


	/*					function				*/

	
public:	
	UPlayerActionComponent();

	void TriggerAction(UPrimaryActionData* ActionAsset);
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
protected:
	virtual void BeginPlay() override;

private:

		
	
};
