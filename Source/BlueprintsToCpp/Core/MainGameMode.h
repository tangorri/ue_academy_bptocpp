// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../Quests/QuestManager.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BLUEPRINTSTOCPP_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()

	AMainGameMode(const FObjectInitializer& ObjectInitializer);

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	AQuestManager* GetQuestManager();
protected:
	AQuestManager* QuestManager;

	TSubclassOf<class AQuestManager> QuestManagerClass;
};
