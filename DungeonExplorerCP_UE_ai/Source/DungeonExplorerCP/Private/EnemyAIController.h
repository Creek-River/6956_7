// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"


#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyAllTYpes.h"

#include "Runtime/AIModule/Classes/Perception/PawnSensingComponent.h"

#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class AEnemyAIController : public AAIController
{
	GENERATED_BODY()

	AEnemyAIController(const class FObjectInitializer& PCIP);

protected:
	UPROPERTY(BlueprintReadWrite)
		class UBehaviorTree* bt;

	UPROPERTY(BlueprintReadWrite)
		class UBlackboardComponent* bb;

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
		class UPawnSensingComponent* PawnSensor;
	
	UFUNCTION()
		void OnHearNoise(APawn *OtherActor, const FVector& Location, float Volume);

	UFUNCTION()
		void OnSeePawn(APawn *OtherPawn);

	FTimerHandle timerHandle;
		void OnChaseTimeOut();

};
