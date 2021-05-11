 // Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "EnemyCPCharacter.h" // エネミーキャラクタを扱ううえで必要

// コンストラクタ
AEnemyAIController::AEnemyAIController(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	// BlackBoardコンポーネントを作成
	bb = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Black Board"));
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	// Waypoint取得のため、enemyCharacterを取得
	AEnemyCPCharacter* enemyCharacter = Cast<AEnemyCPCharacter>(GetPawn());

	if (bt != NULL)
		RunBehaviorTree(bt); // BTを起動
	if (bb != NULL) {
		// Waypointを取得し、BBキー値として登録
		for (int i = 0; i < enemyCharacter->waypointTargets.Num(); i++) {
			FString key = "waypoint" + FString::FromInt(i + 1);
			bb->SetValueAsObject(*key, enemyCharacter->waypointTargets[i]);
		}
	}

	// Pawn Sensorのパラメータ設定
	PawnSensor->SightRadius = 900.0f;
	PawnSensor->SensingInterval = 0.5f;
	PawnSensor->bEnableSensingUpdates = true;
	PawnSensor->bOnlySensePlayers = false;
	PawnSensor->SetPeripheralVisionAngle(30.0f);
	// Delegateを登録
	FScriptDelegate OnSeePawnDelegate;
	OnSeePawnDelegate.BindUFunction(this, "OnSeePawn");
	PawnSensor->OnSeePawn.Add(OnSeePawnDelegate);
	FScriptDelegate OnHearNoiseDelegate;
	OnHearNoiseDelegate.BindUFunction(this, "OnHearNoise");
	PawnSensor->OnHearNoise.Add(OnHearNoiseDelegate);
}

void AEnemyAIController::OnHearNoise(APawn *OtherActor, const FVector &Location, float Volume)
{

	// 今回は実装なし    
}

void AEnemyAIController::OnSeePawn(APawn *OtherPawn)
{
	// デバッグ出力
	FString message = TEXT("Saw Pawn ") + OtherPawn->GetName();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);

	bb->SetValueAsObject("Player", OtherPawn); // Playerキー値を入力
	// コールバックのタイマー発動
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AEnemyAIController::OnChaseTimeOut, 3.0f, true);
}

// タイマーからコールされる
void AEnemyAIController::OnChaseTimeOut()
{
	// キー値をNULLに設定して巡回行動に戻す
	bb->SetValueAsObject("Player", NULL);
	// デバッグ出力
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Timeout");
}
