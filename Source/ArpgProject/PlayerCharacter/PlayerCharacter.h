// Fill out your copyright notice in the Description page of Project Settings.
#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ARPGPROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	/*						增强输入组件							*/
	
	// 增强输入组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UEnhancedInputComponent* EnhancedInputComponent;

	// 增强输入映射上下文
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* InputMappingContext;

	// 输入动作
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* JumpAction;

	// 移动属性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float WalkSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintSpeed = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float LookSensitivity = 1.0f;		//视角灵敏度

	//输入处理函数
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void StopJumping(const FInputActionValue& Value);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	//弹簧手臂
	UPROPERTY(VisibleAnywhere , Category= Camera)
	class USpringArmComponent* CameraBoom;

	//运动相机
	UPROPERTY(VisibleAnywhere , Category= Camera)
	class UCameraComponent* FollowCamera;
public:	
	
};
