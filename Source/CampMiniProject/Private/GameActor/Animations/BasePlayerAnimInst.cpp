#include "GameActor/Animations/BasePlayerAnimInst.h"

#include "GameActor/Character/Player/BaseCharacter.h"
#include "GameActor/Character/Enemy/BaseEnemey.h"
#include "UI/HUD/MiniHUD.h"

void UBasePlayerAnimInst::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void UBasePlayerAnimInst::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (!OwnerCharacter) return;
	
	GroundSpeed = OwnerCharacter->GetVelocity().Size2D();
}

void UBasePlayerAnimInst::AnimNotify_PauseClash()
{
	// Montage_Pause(GetCurrentActiveMontage());
	Montage_SetPlayRate(GetCurrentActiveMontage(),0.01f);
	
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (AMiniHUD* HUD = Cast<AMiniHUD>(PC->GetHUD()))
		{
			HUD->OpenClashWidet();
		}
	}
}

void UBasePlayerAnimInst::AnimNotify_ResumeClash()
{
	Montage_SetPlayRate(GetCurrentActiveMontage(),1.f);
}
