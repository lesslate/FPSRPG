// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSPlayer.generated.h"



UCLASS()
class FPSRPG_API AFPSPlayer : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	AFPSPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// �������� ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* TPSpringArm;

	// ī�޶� ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	// ���� �޽� ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	class UStaticMeshComponent* WeaponMesh;

	// ����� ������Ʈ
	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	class UAudioComponent* AudioComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool GetWeaponState();
	bool GetAimingState();
	


protected:
	void MoveForward(float Value);
	void MoveRight(float Value);

	void Sprint();
	void StopSprinting();

	void Fire();
	void StopFire();
	void StartFire();


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CheckWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Ammo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool Aiming;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	class USoundCue* ShotCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	class USoundCue* MetalCue;

	// �޸��� �ӵ�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement: Walking")
	float SprintSpeedMultiplier;
	
	UPROPERTY()
	class UGameplayStatics* Particle;

	UPROPERTY()
	class UParticleSystem * FireParticle;


private:
	UPROPERTY()
	class UFPSAnimInstance* FPSAnim;

	UPROPERTY()
	FTimerHandle timer;

	bool isFiring;

};
