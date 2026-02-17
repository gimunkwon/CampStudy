#include "GameActor/Character/Player/BaseCharacter.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameActor/Animations/BasePlayerAnimInst.h"
#include "GameFramework/SpringArmComponent.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
#pragma region Camera,SpringArm
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 900.f;
	SpringArmComp->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArmComp->bUsePawnControlRotation = false;
	SpringArmComp->bDoCollisionTest = true;
	SpringArmComp->bInheritPitch = false;
	SpringArmComp->bInheritRoll = false;
	SpringArmComp->bInheritYaw = false;
	
	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCamera->SetupAttachment(SpringArmComp);
	TopDownCamera->bUsePawnControlRotation = false;
#pragma endregion 
	
#pragma region Weapon
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(GetMesh(),TEXT("WeaponSocket"));
	
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh->SetCollisionResponseToAllChannels(ECR_Overlap);
	WeaponMesh->SetCanEverAffectNavigation(false);
#pragma endregion 
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABaseCharacter::PlayClash()
{
	DefaultTarArmLength = SpringArmComp->TargetArmLength;
	DefaultTargetArmRotation = SpringArmComp->GetRelativeRotation();
	
	SpringArmComp->TargetArmLength = 400.f;
	SpringArmComp->SetRelativeRotation(FRotator(0.f,-30.f,0.f));
	
	if (UAnimInstance* BaseAnimInst = Cast<UAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		if (ClashAnimMontage)
		{
			BaseAnimInst->Montage_Play(ClashAnimMontage);
		}
	}
}

void ABaseCharacter::EndClash()
{
	if (UAnimInstance* AnimInst = GetMesh()->GetAnimInstance())
	{
		AnimInst->Montage_Stop(0.2f, ClashAnimMontage);
	}
	
	SpringArmComp->SetRelativeRotation(DefaultTargetArmRotation);
	SpringArmComp->TargetArmLength = DefaultTarArmLength;
}

void ABaseCharacter::MoveToLocation(FVector& TargetLocation)
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(),TargetLocation);
}







