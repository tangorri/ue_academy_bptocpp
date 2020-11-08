// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestMarker.h"

// Sets default values
AQuestMarker::AQuestMarker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	
	SetRootComponent(Root);
	ParticleSystem->SetupAttachment(Root);
}

void AQuestMarker::BeginPlay()
{
	//GetQuestManager()->CompletedQuest.AddDynamic(this, &AQuestMarker::QuestUpdate);
	//RefreshVisibility();
}

void AQuestMarker::RefreshVisibility()
{
	AQuestManager* QuestManager = GetQuestManager();
	FQuestInfo Quest = QuestManager->GetQuest(QuestName);
	bool ParticleVisibility = ShowAtProgress == Quest.Progress && QuestManager->IsActiveQuest(QuestName);
	ParticleSystem->SetVisibility(ParticleVisibility);
}

void AQuestMarker::QuestUpdate(int32 Index)
{
	RefreshVisibility();
}
