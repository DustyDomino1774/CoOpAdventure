// Fill out your copyright notice in the Description page of Project Settings.


#include "Transporter.h"

// Sets default values
ATransporter::ATransporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATransporter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATransporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

