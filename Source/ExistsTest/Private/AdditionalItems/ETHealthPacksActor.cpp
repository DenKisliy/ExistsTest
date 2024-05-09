// Fill out your copyright notice in the Description page of Project Settings.


#include "AdditionalItems/ETHealthPacksActor.h"

// Sets default values
AETHealthPacksActor::AETHealthPacksActor()
{
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitBoxExtent(FVector(100));
	CollisionComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	CollisionComponent->CanCharacterStepUpOn = ECB_No;
	CollisionComponent->SetShouldUpdatePhysicsVolume(true);
	CollisionComponent->SetCanEverAffectNavigation(false);
	CollisionComponent->bDynamicObstacle = true;
	RootComponent = CollisionComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(CollisionComponent);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AETHealthPacksActor::CollisionHit);

	SetReplicates(true);
}

void AETHealthPacksActor::UpdateGameRating_Implementation(const FString& PlayerName)
{
	if (GetWorld()->GetGameState())
	{
		TArray<TObjectPtr<APlayerState>> playerArray = GetWorld()->GetGameState()->PlayerArray;
		for (APlayerState* playerState : GetWorld()->GetGameState()->PlayerArray)
		{
			if (IsValid(playerState))
			{
				AETPlayerController* playerController = Cast<AETPlayerController>(playerState->GetPlayerController());
				if (IsValid(playerController))
				{
					playerController->UpdateGameRatingForEachPlayers(PlayerName);
				}
			}
		}
	}
}

void AETHealthPacksActor::OnRep_NewMesh()
{
	MeshComponent->SetStaticMesh(NewMesh);
}

void AETHealthPacksActor::AddHealthBox()
{
	if (Mesh)
	{
		NewMesh = Mesh;
		MeshComponent->SetStaticMesh(Mesh);
	}
}

void AETHealthPacksActor::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh = MeshComponent->GetStaticMesh();

	MeshComponent->SetStaticMesh(nullptr);
}

void AETHealthPacksActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AETHealthPacksActor, NewMesh);
}

void AETHealthPacksActor::CollisionHit_Implementation(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (MeshComponent->GetStaticMesh())
	{
		if (AExistsTestCharacter* chatacter = Cast<AExistsTestCharacter>(Other))
		{
			MeshComponent->SetStaticMesh(nullptr);
			NewMesh = nullptr;
			
			chatacter->ApplayEffect(HealEffects);
			
			TakeHealthPackDelegate.Broadcast();
			
			UpdateGameRating(chatacter->GetPlayerState()->GetPlayerName());
		}
	}
}

