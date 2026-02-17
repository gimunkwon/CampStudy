#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class ABaseEnemey;
class ADungeonPortal;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class CAMPMINIPROJECT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	FORCEINLINE void SetInteractiveActor(ADungeonPortal* InInteractiveActor) {Portal = InInteractiveActor;}
	FORCEINLINE ADungeonPortal* GetInteractiveActor() {return Portal;}
	
	FORCEINLINE void SetClashActor(ABaseEnemey* InClashActor) {ClashActor = InClashActor;}
	FORCEINLINE ABaseEnemey* GetClashActor() {return ClashActor;}
	
	void PlayClash();
	void EndClash();
	
#pragma region Movement
	void MoveToLocation(FVector& TargetLocation);
#pragma endregion
	
protected:
	virtual void BeginPlay() override;
	
#pragma region Camera,SpringArm
	UPROPERTY(VisibleAnywhere, Category="Camera")
	TObjectPtr<UCameraComponent> TopDownCamera;
	UPROPERTY(VisibleAnywhere, Category="Camera|SpringArm")
	TObjectPtr<USpringArmComponent> SpringArmComp;
#pragma endregion
	
#pragma region Weapon
	UPROPERTY(EditAnywhere,Category="Mesh|Weapon")
	TObjectPtr<UStaticMeshComponent> WeaponMesh;
#pragma endregion
	
#pragma region Animations
	UPROPERTY(EditAnywhere,Category="Animations|AnimMontage")
	TObjectPtr<UAnimMontage> ClashAnimMontage;
#pragma endregion 
private:
#pragma region Actor
	UPROPERTY()
	TObjectPtr<ADungeonPortal> Portal;
	UPROPERTY()
	TObjectPtr<ABaseEnemey> ClashActor;
#pragma endregion
	
	float DefaultTarArmLength;
	FRotator DefaultTargetArmRotation;
};
