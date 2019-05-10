// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSPlayer.generated.h"

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	NoWeapon UMETA(DisplayName = "NoWeapon"),
	FirstWeapon UMETA(DisplayName = "FirstWeapon"),
	SecondWeapon UMETA(DisplayName = "SecondWeapon"),
};

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

	// ���� ���� �޽� ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	class UStaticMeshComponent* SecondWeaponMesh;

	// �� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	class UStaticMeshComponent* WeaponBack;

	// �� ��������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	class UStaticMeshComponent* SecondWeaponBack;

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

	void ReloadEnd();
	void Aggro();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Victory")
	void VictoryUI();
	

protected:
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EWeaponState WeaponState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class AFPSGameMode* gameMode;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void Sprint();
	void StopSprinting();

	void BowFire();
	void Fire();
	void StopFire();
	void StartFire();
	
	void Reload();
	void Death();

	UFUNCTION(BlueprintNativeEvent)
	void Interaction();

	UFUNCTION(BlueprintImplementableEvent)
	void CameraShake();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool OverlapRadio;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CheckWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CheckBow;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool Aiming;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsSprint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsReloading;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool BowState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	int32 Ammo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	int32 RemainAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	int32 Bolt;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	int32 RemainBolt;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	int32 Magazine;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	int32 BoltMagazine;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	float PlayerHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	float PlayerMAXHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	float Damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	float ActualDamage;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	class USoundCue* ShotCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	class USoundCue* MetalCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	class USoundCue* CrossBowCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	class USoundCue* ExplosionCue;
	// �޸��� �ӵ�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement: Walking")
	float SprintSpeedMultiplier;
	
	UPROPERTY()
	class UGameplayStatics* GameStatic;

	UPROPERTY()
	class UParticleSystem * FireParticle;

	UPROPERTY()
	class UParticleSystem * BloodParticle;

	UPROPERTY()
	class UParticleSystem * SmokeParticle;

	UPROPERTY()
	class UParticleSystem * ExplosionParticle;

private:
	UPROPERTY()
	class UFPSAnimInstance* FPSAnim;

	UPROPERTY()
	class AZombie * Zombie;

	UPROPERTY()
	FTimerHandle timer;

	UPROPERTY()
	bool FireDelay;

	void Delay();
	bool isFiring;
	
};
