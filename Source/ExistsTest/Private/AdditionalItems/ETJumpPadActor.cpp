// Fill out your copyright notice in the Description page of Project Settings.


#include "AdditionalItems/ETJumpPadActor.h"

#include "GameFramework/PawnMovementComponent.h"

// Sets default values
AETJumpPadActor::AETJumpPadActor()
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(100.0f);
	CollisionComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	CollisionComponent->CanCharacterStepUpOn = ECB_No;
	CollisionComponent->SetShouldUpdatePhysicsVolume(true);
	CollisionComponent->SetCanEverAffectNavigation(false);
	CollisionComponent->bDynamicObstacle = true;
	RootComponent = CollisionComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(CollisionComponent);

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AETJumpPadActor::CollisionHit);

	SetReplicates(true);
}

void AETJumpPadActor::CollisionHit_Implementation(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AExistsTestCharacter* chatacter = Cast<AExistsTestCharacter>(Other))
	{
		TArray<AActor*> findActors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("CenterHealthPack"), findActors);
		
		if (findActors.Num() > 0)
		{
			FVector velocity = (findActors[0]->GetActorLocation() - GetActorLocation()) * 2;

			velocity.Z = velocity.Z * 2;

			chatacter->LaunchCharacter(velocity, false, false);
		}
	}
}

