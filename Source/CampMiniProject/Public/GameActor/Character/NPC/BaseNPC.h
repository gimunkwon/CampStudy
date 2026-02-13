#pragma once

#include "CoreMinimal.h"
#include "GameActor/Character/Player/BaseCharacter.h"
#include "BaseNPC.generated.h"

class USphereComponent;

UCLASS()
class CAMPMINIPROJECT_API ABaseNPC : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseNPC();
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly,Category="Collision|Interaction")
	TObjectPtr<USphereComponent> InteractionSphere;
	
	
	// 접근 감지시
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
						bool bFromSweep, const FHitResult& SweepResult);
	
	// 접근 해제시
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
					  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
