// Fill out your copyright notice in the Description page of Project Settings.

#include "Net/UnrealNetwork.h"
#include "CollectableKey.h"
#include "CoOpAdventureCharacter.h"

// Sets default values
ACollectableKey::ACollectableKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetupAttachment(RootComp);
	Capsule->SetIsReplicated(true);
	Capsule->SetCollisionProfileName(FName("OverlapAllDynamic"));
	Capsule->SetRelativeLocation(FVector::Zero());
	Capsule->SetCapsuleHalfHeight(150.0f);
	Capsule->SetCapsuleRadius(100.0f);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComp);
	Mesh->SetIsReplicated(true);
	Mesh->SetCollisionProfileName(FName("OverlapAllDynamic"));
	Mesh->SetRelativeLocation(FVector::Zero());

	CollectAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("CollectAudio"));
	CollectAudio->SetupAttachment(RootComp);
	CollectAudio->SetAutoActivate(false);
	CollectAudio->SetRelativeLocation(FVector::Zero());

	_relativeStartingLocationZ = Capsule->GetRelativeLocation().Z;
	RotationSpeed = 100.0f;
	FloatSpeed = 3.0f;
	FloatHeight = 50.0f;
}

// Called when the game starts or when spawned
void ACollectableKey::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollectableKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		//Rotate the static mesh
		Mesh->AddRelativeRotation(FRotator(0.0f, RotationSpeed*DeltaTime, 0.0f));
		
		Mesh->SetRelativeLocation(FVector(0.0f, 0.0f,
			(FMath::Sin(GetGameTimeSinceCreation() * FloatSpeed) * FloatHeight + _relativeStartingLocationZ)));
		
		TArray<AActor*> OverlappingActors;
		Capsule->GetOverlappingActors(OverlappingActors, ACoOpAdventureCharacter::StaticClass());

		// A player is overlapping an uncollected capsule
		if (!OverlappingActors.IsEmpty() && !IsCollected)
		{
			IsCollected = true;
			OnRep_IsCollected();
		}
	}
}

void ACollectableKey::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACollectableKey, IsCollected);
}

void ACollectableKey::OnRep_IsCollected()
{
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Display, TEXT("OnRep_IsCollected called from Server!"));
		
		if (IsCollected)
		{
			OnCollected.Broadcast();
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("OnRep_IsCollected called from Client!"));
	}

	Mesh->SetVisibility(!IsCollected);
	CollectAudio->Play();

	if (IsCollected && KeyHolderRef)
	{
		KeyHolderRef->ActivateKeyMesh();
		UE_LOG(LogTemp, Display, TEXT("Keyholder key mesh turn on."));
	}
}



