#include "GameActor/Animations/BasePlayerAnimInst.h"

#include "GameActor/Character/BaseCharacter.h"

void UBasePlayerAnimInst::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	OwnerCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
}

void UBasePlayerAnimInst::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (!OwnerCharacter) return;
	
	GroundSpeed = OwnerCharacter->GetVelocity().Size2D();
}
