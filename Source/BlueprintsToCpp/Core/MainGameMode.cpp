// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

AQuestManager* AMainGameMode::GetQuestManager()
{
	if (!IsValid(QuestManager)) {
		FVector Location(0.0f, 0.0f, 0.0f);
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnParams;
		QuestManager = GetWorld()->SpawnActor<AQuestManager>(Location, Rotation);
	}
	return QuestManager;
}