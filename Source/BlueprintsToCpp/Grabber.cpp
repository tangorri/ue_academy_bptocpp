// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
//#include "Kismet/KismetMathLibrary.h"
#include "Engine/EngineTypes.h"
#include "Kismet/KismetSystemLibrary.h"

#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("Grabber Constructor"));
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber BeginPlay"));

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	GetPhysicsComponent()->SetTargetLocationAndRotation(GetHoldLocation(), GetComponentRotation());
}

FVector UGrabber::GetMaxGrabLocation() const
{
	return GetComponentLocation() + GetComponentRotation().Vector() * MaxGrabDistance;
}

FVector UGrabber::GetHoldLocation() const
{
	return GetComponentLocation() + GetComponentRotation().Vector() * HoldDistance;
}

UPhysicsHandleComponent* UGrabber::GetPhysicsComponent() const
{
	return GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}

void UGrabber::Grab()
{
	AActor* HitActor;
	UPrimitiveComponent* HitComponent;
	if (TraceForPhysicsBodies(HitActor, HitComponent))
	{
		HitComponent->SetSimulatePhysics(true);
		FVector Location = HitComponent->GetCenterOfMass();
		GetPhysicsComponent()->GrabComponentAtLocationWithRotation(HitComponent, NAME_None, Location, FRotator());
		NotifyQuestActor(HitActor);
	}

}

void UGrabber::Release()
{
	GetPhysicsComponent()->ReleaseComponent();
}

bool UGrabber::TraceForPhysicsBodies(AActor*& HitActor, UPrimitiveComponent*& HitComponent)
{
	UE_LOG(LogTemp, Warning, TEXT("Trace for Physics Bodies called"))
	//return false;

	//UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	static FName SweepTestForGabbableName = TEXT("SweepTestForGabbable");
	FCollisionQueryParams collQueryParams(SweepTestForGabbableName, false, GetOwner());
	FHitResult OutHit;
	FCollisionObjectQueryParams CollObjQueryParams(ECC_PhysicsBody);
	UWorld* CurrentWorld = GetWorld();

	bool const bHit = CurrentWorld ? CurrentWorld->SweepSingleByObjectType(
		OutHit, GetComponentLocation(), GetMaxGrabLocation(), 
		FQuat::Identity, CollObjQueryParams, FCollisionShape::MakeSphere(GrabRadius), collQueryParams
	) : false;

	HitActor = OutHit.GetActor();
	HitComponent = OutHit.GetComponent();

//#if ENABLE_DRAW_DEBUG
	// DrawDebugSphereTraceSingle(World, Start, End, Radius, DrawDebugType, bHit, OutHit, TraceColor, TraceHitColor, DrawTime);
//#endif

	return bHit;
}