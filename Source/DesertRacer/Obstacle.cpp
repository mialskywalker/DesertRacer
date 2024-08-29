#include "Obstacle.h"

#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	ObstacleSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ObstacleSprite"));
	ObstacleSprite->SetupAttachment(RootComponent);
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();

	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OverlapBegin);

	AGameModeBase *GameMode = UGameplayStatics::GetGameMode(GetWorld());
	MyGameMode = Cast<AMyGameMode>(GameMode);
}

void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObstacle::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter *Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		if (Player->CanMove)
		{
			Player->CanMove = false;

			UGameplayStatics::PlaySound2D(GetWorld(), HitSound);
			
			MyGameMode->ResetLevel(IsFinishLine);
		}
	}
}


