// Fill out your copyright notice in the Description page of Project Settings.


#include "Graber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGraber::UGraber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGraber::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UGraber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// MyRotator = GetComponentRotation();
	// FString MyRotatorString = MyRotator.ToCompactString();

	// UE_LOG(LogTemp, Display, TEXT("Rotation : %s"),*MyRotatorString);

	
	// float Time = GetWorld()->TimeSeconds;
	// UE_LOG(LogTemp, Display, TEXT("current Time is : %f"),Time);
	// ...
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if(PhysicsHandle && PhysicsHandle->GetGrabbedComponent()){
		FVector TargetLocation=GetComponentLocation()+GetForwardVector()*HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation,GetComponentRotation());
	}

	

}

void UGraber::Release(){
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if(PhysicsHandle==nullptr)return ;
	if(PhysicsHandle->GetGrabbedComponent()!=nullptr){
		AActor* GrabbedActor = PhysicsHandle->GetGrabbedComponent()->GetOwner();
		GrabbedActor->Tags.Remove("Grabbed");
		PhysicsHandle->ReleaseComponent();

	}
}

void UGraber::Grab(){
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if(PhysicsHandle==nullptr){
		return;
	}

	FHitResult HitResult;
	bool HasHit = GetGrabbableInReach(HitResult);
	if(HasHit){ 
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->SetSimulatePhysics(true);
		HitComponent->WakeAllRigidBodies();
		AActor* HitActor= HitResult.GetActor();
		HitActor->Tags.Add("Grabbed");
		HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
}

UPhysicsHandleComponent* UGraber::GetPhysicsHandle() const{
	UPhysicsHandleComponent* Result =GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(Result==nullptr){
		UE_LOG(LogTemp, Error, TEXT("Graber requires a UPhysicsHandleComponent. "));
	}
	return Result;
}

bool UGraber::GetGrabbableInReach(FHitResult& OutHitResult)const{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector()*MaxGrabDistance;
	DrawDebugLine(GetWorld(),Start,End,FColor::Red);
	DrawDebugSphere(GetWorld(),End,10,10,FColor::Blue,false,5);

	FCollisionShape Sphere= FCollisionShape::MakeSphere(GrabRadius);
	FHitResult HitResult;
	
	return GetWorld()->SweepSingleByChannel(
		OutHitResult,
		Start,
		End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
	);
}


