// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"

#include "../GameFramework/ETPlayerController.h"

#include "ETHealthPacksActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTakeHealthPackSignature);

UCLASS()
class EXISTSTEST_API AETHealthPacksActor : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* CollisionComponent;

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = GAS)
	TSubclassOf<UGameplayEffect> HealEffects;

	FOnTakeHealthPackSignature TakeHealthPackDelegate;

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_NewMesh)
	TObjectPtr<UStaticMesh> NewMesh;

private:
	TObjectPtr<UStaticMesh> Mesh = nullptr;

public:	
	// Sets default values for this actor's properties
	AETHealthPacksActor();

	UFUNCTION(Server, Reliable)
	void CollisionHit(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(Server, Reliable)
	void UpdateGameRating(const FString& PlayerName);

	UFUNCTION()
	void OnRep_NewMesh();

	void AddHealthBox();

protected:
	// To add mapping context
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
