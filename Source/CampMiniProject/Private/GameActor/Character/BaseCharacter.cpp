#include "GameActor/Character/BaseCharacter.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
#pragma region Camera,SpringArm
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 600.f;
	SpringArmComp->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArmComp->bUsePawnControlRotation = false;
	SpringArmComp->bDoCollisionTest = false;
	SpringArmComp->bInheritPitch = false;
	SpringArmComp->bInheritRoll = false;
	SpringArmComp->bInheritYaw = false;
	
	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCamera->SetupAttachment(SpringArmComp);
	TopDownCamera->bUsePawnControlRotation = false;
#pragma endregion 
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABaseCharacter::MoveToLocation(FVector& TargetLocation)
{
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = TargetLocation;
	
	FVector GoalLocation = TargetLocation - StartLocation;
	GoalLocation.Z = 0.f;
	
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(),GoalLocation);
	
}






