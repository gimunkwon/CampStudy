#include "GameActor/Controller/BaseCharacterController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameActor/Character/BaseCharacter.h"

ABaseCharacterController::ABaseCharacterController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ABaseCharacterController::BeginPlay()
{
	Super::BeginPlay();
	
	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		SubSystem->AddMappingContext(DefaultMappingContext, 0);
	}
	
}

void ABaseCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EInputComp = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EInputComp->BindAction(IA_ClickToMove, ETriggerEvent::Started, this, &ABaseCharacterController::OnInputClickToMove);
		EInputComp->BindAction(IA_ClickToMove, ETriggerEvent::Triggered, this, &ABaseCharacterController::OnInputClickToMove);
	}
}

void ABaseCharacterController::OnInputClickToMove()
{
	FHitResult Hit;
	
	if (GetHitResultUnderCursor(ECC_Visibility, 0, Hit))
	{
		if (ABaseCharacter* GPlayer = Cast<ABaseCharacter>(GetPawn()))
		{
			GPlayer->MoveToLocation(Hit.Location);
		}
		
	}
}
