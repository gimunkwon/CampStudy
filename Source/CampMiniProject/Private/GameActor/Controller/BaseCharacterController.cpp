#include "GameActor/Controller/BaseCharacterController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameActor/Character/Enemy/BaseEnemey.h"
#include "GameActor/Character/Player/BaseCharacter.h"
#include "GameActor/Object/DungeonPortal.h"
#include "UI/Enemy/EnemyClashWidget.h"
#include "UI/HUD/MiniHUD.h"

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
		SubSystem->AddMappingContext(ClashMappingContext,1);
	}
	
}

void ABaseCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EInputComp = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EInputComp->BindAction(IA_ClickToMove, ETriggerEvent::Started, this, &ABaseCharacterController::OnInputClickToMove);
		EInputComp->BindAction(IA_ClickToMove, ETriggerEvent::Triggered, this, &ABaseCharacterController::OnInputClickToMove);
		EInputComp->BindAction(IA_Interactive,ETriggerEvent::Started, this, &ABaseCharacterController::OnInputInteractive);
		
		EInputComp->BindAction(IA_Clash_Q,ETriggerEvent::Started,this, &ABaseCharacterController::OnInputClashKey);
		EInputComp->BindAction(IA_Clash_W,ETriggerEvent::Started,this, &ABaseCharacterController::OnInputClashKey);
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

void ABaseCharacterController::OnInputInteractive()
{
	StopMovement();
	
	if (ABaseCharacter* GPlayer = Cast<ABaseCharacter>(GetPawn()))
	{
		if (ADungeonPortal* Portal = GPlayer->GetInteractiveActor())
		{
			Portal->OpenDungeonEnterWidget();
			GPlayer->SetInteractiveActor(nullptr);
		}
		if (ABaseEnemey* Enemy = Cast<ABaseEnemey>(GPlayer->GetClashActor()))
		{
			GPlayer->PlayClash();
			Enemy->PlayEnemyClash();
		}
	}
}

void ABaseCharacterController::OnInputClashKey(const FInputActionInstance& Instance)
{
	const UInputAction* TriggeredAction = Instance.GetSourceAction();
	
	AMiniHUD* MainHUD = Cast<AMiniHUD>(GetHUD());
	UEnemyClashWidget* ClashWidget = Cast<UEnemyClashWidget>(MainHUD->GetClashWidget());
	
	if (TriggeredAction == IA_Clash_Q)
	{
		UE_LOG(LogTemp,Warning,TEXT("Q key Pressed"));
		
		if (ClashWidget)
		{
			ClashWidget->HideQ_Widet();
		}
	}
	
	if (TriggeredAction == IA_Clash_W)
	{
		UE_LOG(LogTemp,Warning,TEXT("W key Pressed"));
		if (ClashWidget)
		{
			ClashWidget->HideW_Widget();
		}
	}
	
}

void ABaseCharacterController::ResumeEnemyAnimation()
{
	if (ABaseCharacter* GPlayer = Cast<ABaseCharacter>(GetPawn()))
	{
		if (ABaseEnemey* Enemy = Cast<ABaseEnemey>(GPlayer->GetClashActor()))
		{
			if (UAnimInstance* EnemyAnimInst = Enemy->GetMesh()->GetAnimInstance())
			{
				EnemyAnimInst->Montage_SetPlayRate(EnemyAnimInst->GetCurrentActiveMontage(),1.f);
			}
			Enemy->EndEnemyClash();
		}
		
		GPlayer->SetClashActor(nullptr);
		GPlayer->EndClash();
	}
}
