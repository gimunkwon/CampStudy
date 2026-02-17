#include "GameActor/Character/Enemy/BaseEnemey.h"

#include "Blueprint/UserWidget.h"
#include "Components/SphereComponent.h"
#include "GameActor/Character/Player/BaseCharacter.h"


ABaseEnemey::ABaseEnemey()
{
	PrimaryActorTick.bCanEverTick = false;
	
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	InteractiveMesh = CreateDefaultSubobject<USphereComponent>(TEXT("InteractiveMesh"));
	InteractiveMesh->SetupAttachment(RootComponent);
	InteractiveMesh->SetSphereRadius(100.f);
	InteractiveMesh->SetRelativeLocation(FVector(150.0f, 0.0f, 0.f));
	
}


void ABaseEnemey::BeginPlay()
{
	Super::BeginPlay();
	
	InteractiveMesh->OnComponentBeginOverlap.AddDynamic(this, &ABaseEnemey::OnOverlapBegin);
	InteractiveMesh->OnComponentEndOverlap.AddDynamic(this, &ABaseEnemey::OnOverlapEnd);
}

void ABaseEnemey::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Warning,TEXT("%s 범위내에 들어왔습니다 격돌 상호작용을 하십시오"),*OtherActor->GetName());
	
	if (ClashToolTipWidgetClass)
	{
		ClashToolTipWidget = CreateWidget(GetWorld(),ClashToolTipWidgetClass);
		if (ClashToolTipWidget)
		{
			ClashToolTipWidget->AddToViewport();
		}
	}
	
	
	if (ABaseCharacter* BasePlayer = Cast<ABaseCharacter>(OtherActor))
	{
		BasePlayer->SetClashActor(this);
	}
	
}

void ABaseEnemey::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (ClashToolTipWidget)
	{
		ClashToolTipWidget->RemoveFromParent();
	}
	
	UE_LOG(LogTemp,Warning,TEXT("%s 범위에서 나감"),*OtherActor->GetName());
}

void ABaseEnemey::PlayEnemyClash()
{
	if (ClashToolTipWidget)
	{
		ClashToolTipWidget->RemoveFromParent();
	}
	
	InteractiveMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (UAnimInstance* BaseAnimInstance = GetMesh()->GetAnimInstance())
	{
		if (EnemyClashMontage_01)
		{
			BaseAnimInstance->Montage_Play(EnemyClashMontage_01);
		}
		
	}
}

void ABaseEnemey::EndEnemyClash()
{
	FTimerHandle DestroyTimer;
	
	GetWorld()->GetTimerManager().SetTimer(DestroyTimer, [this]()
	{
		this->Destroy();
	},4.f,false);

}	

