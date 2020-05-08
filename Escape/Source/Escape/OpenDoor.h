// Copyright by Erik Pettersson 2020

#pragma once

#include <string>

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Functions for interacting with Door Actors
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

	// Getters and Setters
	void SetTargetYaw(float Value) {uDoorAngle = Value;};
	float GetTargetYaw() {return uDoorAngle;}

private:
	float StartYaw;
	float CurrentYaw;
	float DoorLastOpened;
	float CurrentTime;

	AActor* DoorActor;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* uPressurePlate;

	UPROPERTY(EditAnywhere)
	AActor* uActorOnCollide;

	UPROPERTY(EditAnywhere)
	float uDoorAngle = 90.f;

	UPROPERTY(EditAnywhere)
	float uDoorCloseDelay = 2.f;

	UPROPERTY(EditAnywhere)
	float uDoorOpenSpeed = 2.f;
	
	UPROPERTY(EditAnywhere)
	float uDoorCloseSpeed = 0.5f;
};
