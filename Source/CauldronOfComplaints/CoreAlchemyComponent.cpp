#include "CoreAlchemyComponent.h"
#include "Components/BoxComponent.h"
#include "AlchemyIngredient.h"

UCoreAlchemyComponent::UCoreAlchemyComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	MaxParameterValue = 5;
	IsDirty = false;
}


void UCoreAlchemyComponent::BeginPlay()
{
	Super::BeginPlay();

	Temperature = 0;
	Acidity = 0;
	Density = 0;
}

void UCoreAlchemyComponent::SetupCauldronTrigger(UBoxComponent* TriggerZone)
{
	if (TriggerZone)
	{
		TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &UCoreAlchemyComponent::OnIngredientEntered);
	}
}

void UCoreAlchemyComponent::OnIngredientEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetOwner())
	{
		AAlchemyIngredient* Ingredient = Cast<AAlchemyIngredient>(OtherActor);

		if (Ingredient)
		{
			ProcessIngredient(Ingredient->OperationType, Ingredient->TemperatureModifier, Ingredient->AcidModifier, Ingredient->DensityModifier);
			Ingredient->Destroy();
		}
	}
}


void UCoreAlchemyComponent::ProcessIngredient(EAlchemicalTrait OperationType, int32 TemperatureModifier, int32 AcidModifier, int32 DensityModifier)
{
	if (IsDirty)
	{
		// dodac UI message - "Clean the cauldron ifrst"
		return;
	}

	switch (OperationType)
	{
		case EAlchemicalTrait::Standard:
		{
			Temperature += TemperatureModifier;
			Acidity += AcidModifier;
			Density += DensityModifier;
			break;
		}
		case EAlchemicalTrait::Inverter:
		{
			Acidity = -Acidity;

			Temperature += TemperatureModifier;
			Acidity += AcidModifier;
			Density += DensityModifier;
			break;
		}
		case EAlchemicalTrait::Neutralizer:
		{
			int32* Highest = &Temperature;
			int32* Lowest = &Temperature;

			if (Acidity > *Highest)
			{
				Highest = &Acidity;
			}
			if (Density > *Highest)
			{
				Highest = &Density;
			}

			if (Acidity < *Lowest)
			{
				Lowest = &Acidity;
			}
			if (Density < *Lowest)
			{
				Lowest = &Density;
			}

			if (Highest == Lowest) //jak wszystkie zmienne sa rowne (np. 0, 0, 0)
			{
				*Highest -= 1; // Wtedy wszystkich odejmujemy 2 i dodajemy 1, co daje -1
			}
			else
			{
				*Highest -= 2;
				*Lowest += 1;
			}
			break;
		}
	}

	CheckForExplosion();

	if (!IsDirty)
	{
		OnStateChanged.Broadcast();
	}
}


void UCoreAlchemyComponent::CheckForExplosion()
{
	if (FMath::Abs(Temperature) > MaxParameterValue || FMath::Abs(Acidity) > MaxParameterValue || FMath::Abs(Density) > MaxParameterValue)
	{
		OnStateChanged.Broadcast();
		IsDirty = true;

		Temperature = 0;
		Acidity = 0;
		Density = 0;

		OnExploded.Broadcast();
	}
}

void UCoreAlchemyComponent::CleanCauldron()
{
	if (IsDirty)
	{
		IsDirty = false;

		Temperature = 0;
		Acidity = 0;
		Density = 0;

		OnCleaned.Broadcast();
		OnStateChanged.Broadcast();
	}
}

void UCoreAlchemyComponent::EmptyCauldron()
{
	if (!IsDirty)
	{
		Temperature = 0;
		Acidity = 0;
		Density = 0;

		OnStateChanged.Broadcast();
	}
}