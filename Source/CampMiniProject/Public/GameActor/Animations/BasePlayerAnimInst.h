#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BasePlayerAnimInst.generated.h"


class ABaseCharacter;

UCLASS()
class CAMPMINIPROJECT_API UBasePlayerAnimInst : public UAnimInstance
{
	GENERATED_BODY()
public:
	void AnimNotify_ResumeClash();
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Movement|Speed")
	float GroundSpeed;
	
	UFUNCTION(BlueprintCallable)
	void AnimNotify_PauseClash();

private:
	UPROPERTY()
	TObjectPtr<ACharacter> OwnerCharacter;
};
