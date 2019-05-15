// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BossZombie.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);
DECLARE_MULTICAST_DELEGATE(FSprintDelegate);

UCLASS()
class FPSRPG_API ABossZombie : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABossZombie();

	void Attack();
	void Attack2();
	void Attack3();
	void Run();
	void Walk();
	void Death();

	UFUNCTION()
	void ReceivePointDamage(float Damage, const UDamageType * DamageType, FVector HitLocation, FVector HitNormal, UPrimitiveComponent * HitComponent, FName BoneName, FVector ShotFromDirection, AController * InstigatedBy, AActor * DamageCauser, const FHitResult & HitInfo);

	UFUNCTION()
	void ReceiveRadialDamage(float DamageReceived, const class UDamageType * DamageType, FVector Origin, const struct FHitResult & HitInfo, class AController * InstigatedBy, AActor * DamageCauser);

	UFUNCTION(BlueprintImplementableEvent, Category = "particle")
	void Attack3_Particle();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsRun;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsHead;

	FOnAttackEndDelegate OnAttackEnd;
	FSprintDelegate OnSprint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	class UAudioComponent* AudioComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	class USoundCue* ZombieSound;

	UPROPERTY()
	class UBossZombieAnimInstance* ZombieAnim;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void AttackCheck();
	void AttackCheck2();
	void AttackCheck3();

	UPROPERTY()
	class AActor* BPZombie;

	UPROPERTY()
	class ABossZombieAIController* ZombieAI;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsAttacking;

	UPROPERTY(VisibleAnywhere)
	float HP;

	UPROPERTY(VisibleAnywhere)
	bool IsDeath;
	
	
};
