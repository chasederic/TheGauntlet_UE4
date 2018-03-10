// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "PatrolRoute.h"
#include "BehaviorTree/BlackboardComponent.h"




EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    //get the patrol points
    auto controlledPawn = OwnerComp.GetAIOwner()->GetPawn();
    auto patrolRoute = controlledPawn->FindComponentByClass<UPatrolRoute>();
    if(!patrolRoute){
        FString name = GetName();
        UE_LOG(LogTemp, Warning, TEXT("%s is missing patrol component"), *name);
        return EBTNodeResult::Failed;} //no ensure, checks at runtime
    
    //check for empty patrol routes
    auto patrolPoints = patrolRoute->GetPatrolPoints();
    if(patrolPoints.Num() == 0)
    {
        FString name = GetName();
        UE_LOG(LogTemp, Warning, TEXT("%s is missing patrol points"), *name);
        return EBTNodeResult::Failed;
    }
   
    
    //set next waypoints
    UBlackboardComponent* blackboardComp = OwnerComp.GetBlackboardComponent();          //Get the blackboard component
    if(!ensure(blackboardComp)){ return EBTNodeResult::Failed;}
    auto index = blackboardComp->GetValueAsInt(indexKey.SelectedKeyName);
    blackboardComp->SetValueAsObject(waypointKey.SelectedKeyName, patrolPoints[index]);
    
    //cycle index
    auto nextIndex = (index + 1) % patrolPoints.Num();
    blackboardComp->SetValueAsInt(indexKey.SelectedKeyName, nextIndex);

    //UE_LOG(LogTemp, Warning, TEXT("Waypoint index: %i"), index);
    return EBTNodeResult::Succeeded;
}
