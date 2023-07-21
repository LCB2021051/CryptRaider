// Fill out your copyright notice in the Description page of Project Settings.


#include "FinalDisplay.h"

// Sets default values for this component's properties
UFinalDisplay::UFinalDisplay()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFinalDisplay::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFinalDisplay::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	AActor* Actor =GetAcceptableActor();
	if(Actor != nullptr){
		SetDisplay(true);
	}
	else{
		SetDisplay(false);
	}

	if(display){
		UE_LOG(LogTemp, Display, TEXT("SUCCESS"));
	}
	else{
		UE_LOG(LogTemp, Display, TEXT("Bring the Golden Statue"));
	}
}

AActor* UFinalDisplay::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOwner()->GetOverlappingActors(Actors);
	for(AActor* Actor: Actors){
		if(Actor->ActorHasTag(AcceptableActorTag) && !Actor->ActorHasTag("Grabbed")){
			return Actor;
		}
	}
	return nullptr;
}

void UFinalDisplay:: SetDisplay(bool NewDisplay){
	display=NewDisplay;
}
