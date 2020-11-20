// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

AMainGameMode::AMainGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("GameMode CPP Ctor"))
	static ConstructorHelpers::FObjectFinder<UBlueprint> QuestManagerBP(TEXT("Blueprint'/Game/Quests/BP_QuestManager.BP_QuestManager'"));
	if (QuestManagerBP.Object)
	{
		QuestManagerClass = (UClass*)QuestManagerBP.Object->GeneratedClass;
	}
	//QuestManagerClass = Cast<TSubclassOf<AQuestManager>>(QuestManagerBP.Object->GetClass());
}

AQuestManager* AMainGameMode::GetQuestManager()
{
	
	if (QuestManagerClass && QuestManager == nullptr) {
		//FVector Location(0.0f, 0.0f, 0.0f);
		//FRotator Rotation(0.0f, 0.0f, 0.0f);
		//FActorSpawnParameters SpawnParams;
		//QuestManager = GetWorld()->SpawnActor<AQuestManager>(Location, Rotation);
		QuestManager = Cast<AQuestManager>(GetWorld()->SpawnActor(QuestManagerClass));
	}
	return QuestManager;
}