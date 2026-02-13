#include "GameActor/Character/NPC/BaseNPC.h"

#include "Components/SphereComponent.h"


ABaseNPC::ABaseNPC()
{
	PrimaryActorTick.bCanEverTick = false;
	
	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	InteractionSphere->SetupAttachment(RootComponent);
	InteractionSphere->SetSphereRadius(200.f);
}


void ABaseNPC::BeginPlay()
{
	Super::BeginPlay();
	
	/*----Binding Delegate----*/
	InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseNPC::OnOverlapBegin);
	InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &ABaseNPC::OnOverlapEnd);
}

void ABaseNPC::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this && OtherActor->IsA(APawn::StaticClass()))
	{
		UE_LOG(LogTemp,Warning,TEXT("플레이어가 접근했습니다. E로 상호작용을 하십시오"))
		if (ABaseCharacter* BasePlayer = Cast<ABaseCharacter>(OtherActor))
		{
			BasePlayer->SetIsConnectedNPC(true);
		}
		
	}
	
}

void ABaseNPC::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherActor!= this && OtherActor->IsA(APawn::StaticClass()))
	{
		UE_LOG(LogTemp,Warning,TEXT("플레이어가 멀어졌습니다. 감지 종료"));
	}
}


