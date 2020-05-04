// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	StartYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = StartYaw;
	TargetYaw += StartYaw;

	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s has a door component, but no Pressure Plate set!"), *GetOwner()->GetName());
	}
}

void UOpenDoor::OpenDoor(float DeltaTime) 
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 2);
	
	FRotator NewRotation(0.f, CurrentYaw, 0.f);

	GetOwner()->SetActorRelativeRotation(NewRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorOnCollide)) {
		UE_LOG(LogTemp, Warning, TEXT("%s is overlapping!"), *ActorOnCollide->GetName());

		OpenDoor(DeltaTime);
	}
}