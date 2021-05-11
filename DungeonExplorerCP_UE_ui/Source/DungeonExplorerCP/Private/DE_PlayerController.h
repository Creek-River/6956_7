// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "MainHUD.h"

#include "DE_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ADE_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MomomoWorks")
		TSubclassOf<class UMainHUD> W_MainHUD;

	//void AddKey();

	UMainHUD* DE_MainHUD;

	virtual void BeginPlay() override;
	
};
