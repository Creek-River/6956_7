// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

// datatime構造体を扱うために必須
#include "Runtime/Core/Public/Misc/Timespan.h"
#include "DE_GameInstance.generated.h"

/**
 *
 */
UCLASS()
class DUNGEONEXPLORERCP_API UDE_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// プレイヤー残機
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MomomoWorks")
		int32 playerNum = 3;

	// ゲーム開始時刻
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MomomoWorks")
		FDateTime startTime;

};
