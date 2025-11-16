// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "ActionDataTable.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FPlayerActionDataTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ActionTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Comment;  
};

UCLASS()
class ARPGPROJECT_API UActionDataTable : public UDataTable
{
	GENERATED_BODY()
	public:
	
	UPROPERTY(EditDefaultsOnly)
	UDataTable* ActionDataTable;  //调用结构体
};

