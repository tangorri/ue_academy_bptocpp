// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestLibrary.h"
#include "../Core/MainGameMode.h"

AQuestManager* UQuestLibrary::GetQuestManager(UObject* WorldContext)
{
	// UE_LOG(LogTemp, Warning, NULL, TEXT("MODIFIED"))
	UE_LOG(LogTemp, Warning, TEXT("UQuestLibrary::GetQuesteManager code rollback"))
	if (WorldContext == nullptr) return nullptr;
	UWorld* World = WorldContext->GetWorld();
	if (World == nullptr) return nullptr;

	AMainGameMode* GameMode = Cast<AMainGameMode>(World->GetAuthGameMode());
	if (GameMode == nullptr) return nullptr;
	return GameMode->GetQuestManager();
}

