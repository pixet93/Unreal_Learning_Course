// Copyright by Erik Pettersson 2020

#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	
	SetupInputComponent();
}


void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!PhysicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("Could not find a physics handle for: %s"), *GetOwner()->GetName());
	}
}


void UGrabber::SetupInputComponent() 
{
	// Bind a delegate function to the action when pressing 'E' or 'Mouse Right Btn'
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}


FVector UGrabber::GetPlayerReach() const
{
	FVector PlayerLocation;
	FRotator PlayerRotation;

	// Get Player's viewpoint
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerLocation, OUT PlayerRotation);

	return PlayerLocation + (PlayerRotation.Vector() * Reach);
}


FHitResult UGrabber::GetFirstPhysicsBodyHit() const
{
	FHitResult HitResult;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GetOwner()->GetActorLocation(),
		GetPlayerReach(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams);

	return HitResult;
}


void UGrabber::Grab() 
{
	FHitResult PhysicsBodyHit = GetFirstPhysicsBodyHit();

	if (PhysicsHandle && PhysicsBodyHit.GetActor()) {
		UPrimitiveComponent* GrabComponent = PhysicsBodyHit.GetComponent();
		PhysicsHandle->GrabComponentAtLocation(GrabComponent, NAME_None, GetPlayerReach());
	}
}


void UGrabber::Release() 
{
	if (PhysicsHandle) {
		PhysicsHandle->ReleaseComponent();
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the Physics Handle is attached
	if(PhysicsHandle->GetGrabbedComponent()) {

		PhysicsHandle->SetTargetLocation(GetPlayerReach());
	}
}