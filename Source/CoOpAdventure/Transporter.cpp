// Fill out your copyright notice in the Description page of Project Settings.


#include "Transporter.h"

// Sets default values
UTransporter::UTransporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);

	MoveTime = 3.0f;
	ActivatedTriggerCount = 0;
	ArePointsSet = false;
	StartPoint, EndPoint = FVector::Zero();
	

}

void UTransporter::SetPoints(FVector Point1, FVector Point2)
{
	if (Point1.Equals(Point2)) return;
	
	StartPoint = Point1;
	EndPoint = Point2;
	ArePointsSet = true;
}

// Called when the game starts or when spawned
void UTransporter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void UTransporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


