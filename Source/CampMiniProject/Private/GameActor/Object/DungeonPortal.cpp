#include "GameActor/Object/DungeonPortal.h"

#include "Blueprint/UserWidget.h"
#include "Components/SphereComponent.h"
#include "GameActor/Character/Player/BaseCharacter.h"
#include "UI/Object/Portal/PortalWidget.h"


ADungeonPortal::ADungeonPortal()
{
	PrimaryActorTick.bCanEverTick = false;
	
#pragma region RootComponent
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
#pragma endregion 
	
#pragma region Mesh
	DefaultMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	DefaultMesh->SetupAttachment(RootComponent);
#pragma endregion
	
#pragma region Collision
	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	InteractionSphere->SetSphereRadius(400.f);
	InteractionSphere->SetupAttachment(DefaultMesh);
#pragma endregion 
	
#pragma region Niagara
	PortalEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PortalEffect"));
	PortalEffect->SetupAttachment(RootComponent);
#pragma endregion 
	
}


void ADungeonPortal::BeginPlay()
{
	Super::BeginPlay();
	
	InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &ADungeonPortal::OnOverlapBegin);
	InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &ADungeonPortal::OnOverlapEnd);
}

void ADungeonPortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PortalToolTipWidgetClass)
	{
		PortalToolTipWidget = CreateWidget<UUserWidget>(GetWorld(),PortalToolTipWidgetClass);
		if (PortalToolTipWidget)
		{
			PortalToolTipWidget->AddToViewport();
		}
	}
	
	
	
	UE_LOG(LogTemp,Warning,TEXT("던전 입구에 접근했습니다 E를 눌러 상호작용 하세요"));
	
	if (ABaseCharacter* BasePlayer = Cast<ABaseCharacter>(OtherActor))
	{
		BasePlayer->SetInteractiveActor(this);
	}
	
	bIsOpenWidget = true;
	
}

void ADungeonPortal::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (PortalToolTipWidget)
	{
		PortalToolTipWidget->RemoveFromParent();
	}
	UE_LOG(LogTemp,Warning,TEXT("던전 입구근처에 플레이어 없음"));
	
	if (PortalWidget)
	{
		PortalWidget->RemoveFromParent();
		bIsOpenWidget = false;
	}
}

void ADungeonPortal::OpenDungeonEnterWidget()
{
	if (bIsOpenWidget)
	{
		bIsOpenWidget = false;
		
		PortalWidget = CreateWidget<UPortalWidget>(GetWorld(),PortalWidgetClass);
		
		if (PortalWidget)
		{
			PortalWidget->AddToViewport();
		}
		
	}
}



