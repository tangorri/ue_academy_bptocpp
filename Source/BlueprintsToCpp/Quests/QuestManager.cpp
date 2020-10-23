// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"

// Sets default values
AQuestManager::AQuestManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AQuestManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AQuestManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AQuestManager::CompleteQuest_Implementation(FName QuestId, bool CompleteWholeQuest)
{
	int32 QuestIndex = GetQuestIndex(QuestId);
	FQuestInfo Quest = QuestList[QuestIndex];
	if (CompleteWholeQuest)
	{
		UE_LOG(LogTemp, Warning, TEXT("COMPLETED %s"), *Quest.QuestId.ToString())
		QuestList[QuestIndex].Progress = Quest.ProgressTotal;
	}
	else
	{
		QuestList[QuestIndex].Progress = FMath::Min(Quest.Progress + 1, Quest.ProgressTotal);
	}

	CompletedQuest.Broadcast(QuestIndex);
}

FQuestInfo AQuestManager::GetQuest(FName QuestName) const
{
	int32 QuestIndex = GetQuestIndex(QuestName);
	FQuestInfo Quest = QuestList[QuestIndex];
	return Quest;
}

bool AQuestManager::IsQuestComplete(FQuestInfo Quest) const
{
	return Quest.Progress == Quest.ProgressTotal;
}

TArray<FQuestInfo> AQuestManager::GetQuests() const
{
	return QuestList;
}

int32 AQuestManager::GetQuestIndex(FName QuestId) const
{
	for (auto i = 0; i < QuestList.Num(); i++)
	{
		if (QuestList[i].QuestId == QuestId) { return i; }
	}
	UE_LOG(LogTemp, Warning, TEXT("QuestId not found ! no index !"))
	return -1;
}

bool AQuestManager::IsActiveIndex(int32 Index) const
{
	for (auto i = 0; i < QuestList.Num(); ++i)
	{
		if (i == Index) return true;
		else if (IsQuestComplete(QuestList[Index]) == false) return false;
	}
	return false;
}