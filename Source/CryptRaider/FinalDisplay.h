// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FinalDisplay.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UFinalDisplay : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFinalDisplay();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetDisplay(bool Display);

private:
	UPROPERTY(EditAnywhere)
	FName AcceptableActorTag = "GoldenStatue";

	bool display = false;

	AActor* GetAcceptableActor() const;
		
};
