// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "EnemyCPCharacter.h"

AEnemyAIController::AEnemyAIController(const class FObjectInitializer& PCIP)
	:Super(PCIP)
{
	bb = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Black Board"));
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	AEnemyCPCharacter* enemyCharacter = Cast<AEnemyCPCharacter>(GetPawn());

	if (bt != NULL)
		RunBehaviorTree(bt);
	if (bb != NULL) {
		for (int i = 0; i < enemyCharacter->waypointTargets.Num(); i++) {
			FString key = "waypoint" + FString::FromInt(i + 1);
			bb->SetValueAsObject(*key, enemyCharacter->waypointTargets[i]);
		}
	}

	PawnSensor->SightRadius = 900.0f;
	PawnSensor->SensingInterval = 0.5f;
	PawnSensor->bEnableSensingUpdates = true;
	PawnSensor->bOnlySensePlayers = false;
	PawnSensor->SetPeripheralVisionAngle(30.0f);

	FScriptDelegate OnSeePawnDelegate;
	OnSeePawnDelegate.BindUFunction(this, "OnSeePawn");
	PawnSensor->OnSeePawn.Add(OnSeePawnDelegate);
	FScriptDelegate OnHearNoiseDelegate;
	OnHearNoiseDelegate.BindUFunction(this, "OnHearNoise");
	PawnSensor->OnHearNoise.Add(OnHearNoiseDelegate);

}

void AEnemyAIController::OnHearNoise(APawn* OtherActor, const FVector &Location, float Volume)
{

}

void AEnemyAIController::OnSeePawn(APawn* OtherPawn)
{
	FString message = TEXT("SawPawn") + OtherPawn->GetName();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, message);

	bb->SetValueAsObject("Player", OtherPawn);
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AEnemyAIController::OnChaseTimeOut, 3.0f, true);

}

void AEnemyAIController::OnChaseTimeOut()
{
	bb->SetValueAsObject("Player", NULL);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "TimeOut");
}

