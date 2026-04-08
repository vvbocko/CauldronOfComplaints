#include "AlchemyIngredient.h"
#include "Components/StaticMeshComponent.h"
#include "CoreAlchemyComponent.h"


AAlchemyIngredient::AAlchemyIngredient()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetCollisionProfileName(TEXT("PhysicsActor"));
}


void AAlchemyIngredient::BeginPlay()
{
	Super::BeginPlay();
}
