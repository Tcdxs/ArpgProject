// Fill out your copyright notice in the Description page of Project Settings.


#include "V_JumpStart.h"

#include "ArpgProject/PlayerCharacter/PlayerCharacter.h"


void UV_JumpStart::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                          const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp && MeshComp->GetOwner())
	{
		PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
		if (PlayerCharacter)
		{
			II_DataTransfer::Execute_ToTriggerAction_Jump(PlayerCharacter);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("1"));
		}
		
	}
}
