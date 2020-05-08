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

	if (PhysicsHandle) {
		// We found the Physics Handle, what do you want to do with it?
	}
	else {
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


FHitResult UGrabber::GetFirstPhysicsBodyHit(FVector PlayerLocation, FVector EndReach) const
{
	FHitResult HitResult;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		PlayerLocation,
		EndReach,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams);

	return HitResult;
}


void UGrabber::Grab() 
{
	UE_LOG(LogTemp, Warning, TEXT("Pressing a key to grab object!"));

	FVector PlayerLocation;
	FRotator PlayerRotation;

	// Get Player's viewpoint
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerLocation, OUT PlayerRotation);

	FVector EndReach = PlayerLocation + (PlayerRotation.Vector() * Reach);

	FHitResult PhysicsBodyHit = GetFirstPhysicsBodyHit(PlayerLocation, EndReach);

	if (PhysicsHandle && PhysicsBodyHit.GetActor()) {
		UPrimitiveComponent* GrabComponent = PhysicsBodyHit.GetComponent();
		PhysicsHandle->GrabComponentAtLocation(GrabComponent, NAME_None, EndReach);
	}
}


void UGrabber::Release() 
{
	UE_LOG(LogTemp, Warning, TEXT("Pressing a key to release object!"));

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
		// Then move the object that is held 
		FVector PlayerLocation;
		FRotator PlayerRotation;

		// Get Player's viewpoint
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerLocation, OUT PlayerRotation);

		FVector EndReach = PlayerLocation + (PlayerRotation.Vector() * Reach);

		PhysicsHandle->SetTargetLocation(EndReach);
	}
}