#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoreAlchemyComponent.h"

#include "AlchemyIngredient.generated.h"


class UStaticMeshComponent;

UCLASS(Blueprintable)
class CAULDRONOFCOMPLAINTS_API AAlchemyIngredient : public AActor
{
	GENERATED_BODY()

public:
	AAlchemyIngredient();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")		// skladnik
		UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alchemy Modifiers")
	EAlchemicalTrait OperationType = EAlchemicalTrait::Standard;				//zeby w Blueprincie mozna bylo tez wybrac typ operacji

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alchemy Modifiers")
	int32 TemperatureModifier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alchemy Modifiers")
	int32 AcidModifier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alchemy Modifiers")
	int32 DensityModifier = 0;
};
