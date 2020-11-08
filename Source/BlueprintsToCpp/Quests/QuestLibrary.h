// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "QuestManager.h"
#include "QuestLibrary.generated.h"

/**
 * 
 */
UCLASS()
class BLUEPRINTSTOCPP_API UQuestLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	// @url https://forums.unrealengine.com/development-discussion/c-gameplay-programming/31818-how-can-i-spawn-an-actor-via-static-function-using-bpfuncitonlibrary

	UFUNCTION(BlueprintCallable, Meta=(WorldContext = "WorldContext"), Category="Quests", BlueprintPure)
	static AQuestManager* GetQuestManager(UObject* WorldContext);
	
};
