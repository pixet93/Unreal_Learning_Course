// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	DoorActor = GetOwner();
	DoorLastOpened = 0.f;
	CurrentTime = 0.f;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	StartYaw = DoorActor->GetActorRotation().Yaw;
	CurrentYaw = StartYaw;

	// 'TargetYaw' is a editable property for each Door Actor
	SetTargetYaw(uDoorAngle += StartYaw);

	if (!uPressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s has a door component, but no Pressure Plate set!"), *DoorActor->GetName());
	}

	// Returns the Actor Pawn from the first available Player Controller
	uActorOnCollide = GetWorld()->GetFirstPlayerController()->GetPawn();

	UE_LOG(LogTemp, Warning, TEXT("This is the actor that is colliding on plate: %s"), *uActorOnCollide->GetName());
}

void UOpenDoor::OpenDoor(float DeltaTime) 
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, uDoorAngle, DeltaTime, uDoorOpenSpeed);
	
	FRotator NewRotation(0.f, CurrentYaw, 0.f);

	DoorActor->SetActorRelativeRotation(NewRotation);
}


void UOpenDoor::CloseDoor(float DeltaTime) 
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, StartYaw, DeltaTime, uDoorCloseSpeed);

	FRotator NewRotation(0.f, CurrentYaw, 0.f);

	DoorActor->SetActorRelativeRotation(NewRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurrentTime = GetWorld()->GetTimeSeconds();

	if (uPressurePlate && uPressurePlate->IsOverlappingActor(uActorOnCollide)) {
		//UE_LOG(LogTemp, Warning, TEXT("%s is overlapping!"), *ActorOnCollide->GetName());

		OpenDoor(DeltaTime);

		DoorLastOpened = GetWorld()->GetTimeSeconds();

		UE_LOG(LogTemp, Warning, TEXT("The door was last opened at: %f seconds."), DoorLastOpened);
	}

	else if (uPressurePlate && !uPressurePlate->IsOverlappingActor(uActorOnCollide)) {
		//UE_LOG(LogTemp, Warning, TEXT("%s is NOT overlapping!"), *ActorOnCollide->GetName());

		float TimeDifference = CurrentTime - DoorLastOpened;

		if (TimeDifference > uDoorCloseDelay) {
			//UE_LOG(LogTemp, Warning, TEXT("The door started closing at: %f."), CurrentTime);

			CloseDoor(DeltaTime);
		}	
	}
}