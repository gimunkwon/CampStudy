#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "DungeonPortal.generated.h"

class UPortalWidget;
class USphereComponent;

UCLASS()
class CAMPMINIPROJECT_API ADungeonPortal : public AActor
{
	GENERATED_BODY()

public:
	ADungeonPortal();
	
	void OpenDungeonEnterWidget();
	
protected:
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditAnywhere,Category="Mesh")
	TObjectPtr<UStaticMeshComponent> DefaultMesh;
	
	UPROPERTY(EditDefaultsOnly,Category="Collision|Interaction")
	TObjectPtr<USphereComponent> InteractionSphere;
	
#pragma region NiagaraComponent
	UPROPERTY(VisibleAnywhere,Category="Niagara|Components")
	TObjectPtr<UNiagaraComponent> PortalEffect;
	
	UPROPERTY(EditAnywhere,Category="Niagara|Effects")
	TObjectPtr<UNiagaraSystem> PortalSystem;
#pragma endregion 
	
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
	
#pragma region Widget
	UPROPERTY(EditAnywhere,Category="Widget")
	TSubclassOf<UUserWidget> PortalWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UPortalWidget> PortalWidget;
#pragma endregion 

private:
	bool bIsOpenWidget = false;
};
