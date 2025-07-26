// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAnimNotify.h"

#include "ArpgProject/Enemy/CPP_EnemyBase.h"


void UAttackAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;
	ACPP_EnemyBase* Enemy = Cast<ACPP_EnemyBase>(MeshComp->GetOwner());
	if (Enemy)
	{
		if (bActivateCollision)
			{
				//Enemy->ActivateWeaponCollision();
			}
		else
		{
			//Enemy->DeactivateWeaponCollision();
		}
	}
}
