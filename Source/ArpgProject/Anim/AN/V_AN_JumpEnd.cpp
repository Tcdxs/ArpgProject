// Fill out your copyright notice in the Description page of Project Settings.


#include "V_AN_JumpEnd.h"


void UV_AN_JumpEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp && MeshComp->GetOwner())
	{
		PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
		if (PlayerCharacter)
		{
			II_DataTransfer::Execute_Jump_End(PlayerCharacter);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("1"));
		}
		
	}
}
