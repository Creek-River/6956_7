// Fill out your copyright notice in the Description page of Project Settings.


#include "DE_PlayerController.h"

void ADE_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	{
		if (W_MainHUD) {
			// widgetを作成
			DE_MainHUD = CreateWidget<UMainHUD>(this, W_MainHUD);

			if (DE_MainHUD) {
				// 生成したHUDをビューポートに表示
				DE_MainHUD->AddToViewport();
			}
			// ボタンが押せるようにマウス操作の許可
			bShowMouseCursor = true;
		}


	}



}