// Fill out your copyright notice in the Description page of Project Settings.

#include "Zombie.h"
#include "Sound/SoundCue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/AudioComponent.h"
#include "ConstructorHelpers.h"
#include "ZombieAnimInstance.h"
#include "ZombieAIController.h"

// Sets default values
AZombie::AZombie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AZombieAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// ���̷�Ż �޽� ����
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ZBMESH(TEXT("SkeletalMesh'/Game/zombie/jill.jill'"));
	if (ZBMESH.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(ZBMESH.Object);
	}
	// �ִϸ��̼� �������Ʈ �Ӽ�����
	static ConstructorHelpers::FClassFinder<UAnimInstance> ZombieAnimBP(TEXT("AnimBlueprint'/Game/Character/AnimBP_zombie.AnimBP_zombie_C'")); // _C�� �ٿ� Ŭ���������� ������
	if (ZombieAnimBP.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ZombieAnimBP.Class);
	}

	IsAttacking = false;
}

// Called when the game starts or when spawned
void AZombie::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZombie::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ZombieAnim = Cast<UZombieAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr != ZombieAnim)
	{
		ZombieAnim->OnMontageEnded.AddDynamic(this, &AZombie::OnAttackMontageEnded);
	}
}


// Called to bind functionality to input
void AZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AZombie::OnAttackMontageEnded(UAnimMontage * Montage, bool bInterrupted)
{
	IsAttacking = false;

	OnAttackEnd.Broadcast();
}

void AZombie::Attack()
{
	if (!IsAttacking)
	{
		UE_LOG(LogTemp, Log, TEXT("zombie attack!"));
		ZombieAnim->PlayAttackMontage();
		IsAttacking = true;
	}
}

