#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemey.generated.h"

class USphereComponent;

UCLASS()
class CAMPMINIPROJECT_API ABaseEnemey : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseEnemey();
	
	void PlayEnemyClash();
	void EndEnemyClash();
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,Category="Mesh|Weapon")
	TObjectPtr<UStaticMeshComponent> WeaponMesh;
	
	// QTE를 감지할 영역
	UPROPERTY(EditAnywhere,Category="Collision|Interactive")
	TObjectPtr<USphereComponent> InteractiveMesh;
	
#pragma region CollisionEvent
	// 접근 감지시
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
						bool bFromSweep, const FHitResult& SweepResult);
	
	// 접근 해제시
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
					  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
#pragma endregion
	
#pragma region Animations
	UPROPERTY(Editanywhere,Category="Animation|AnimMontage")
	TObjectPtr<UAnimMontage> EnemyClashMontage_01;
#pragma endregion
	
#pragma region Widget
	UPROPERTY(EditAnywhere,Category="Widget")
	TSubclassOf<UUserWidget> ClashToolTipWidgetClass;
	UPROPERTY()
	TObjectPtr<UUserWidget> ClashToolTipWidget;
#pragma endregion
};
