#pragma once

#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"
#include "Components/ActorComponent.h"

#include "CoreAlchemyComponent.generated.h"


UENUM(BlueprintType)
enum class EAlchemicalTrait : uint8
{
	Standard UMETA(DisplayName = "Standard"),			// adds Modifiers: Temperature, Density, Acidity
	Inverter UMETA(DisplayName = "Inverter"),			// flips Acidity: acidity * (-1)
	Neutralizer UMETA(DisplayName = "Neutralizer")		// balances extremes: highest - 1 and lowest +1
};

class UBoxComponent;
class AAlchemyIngredient;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCauldronStateChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCauldronExploded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCauldronCleaned);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CAULDRONOFCOMPLAINTS_API UCoreAlchemyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCoreAlchemyComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Alchemy State")
	int32 Temperature;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Alchemy State")
	int32 Acidity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Alchemy State")
	int32 Density;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Alchemy State")
	bool IsDirty;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Alchemy Settings")
	int32 MaxParameterValue = 5;

	UFUNCTION(BlueprintCallable, Category = "Alchemy Actions")
	void SetupCauldronTrigger(UBoxComponent* TriggerZone);

	UFUNCTION()
	void OnIngredientEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Alchemy Actions")
	void ProcessIngredient(EAlchemicalTrait OperationType, int32 TemperatureModifier, int32 AcidModifier, int32 DensityModifier);

	UFUNCTION(BlueprintCallable, Category = "Alchemy Actions")
	void CleanCauldron();

	UFUNCTION(BlueprintCallable, Category = "Alchemy Actions")
	void EmptyCauldron();

protected:
	virtual void BeginPlay() override;

private:
	void CheckForExplosion();

public:
	UPROPERTY(BlueprintAssignable, Category = "Alchemy Events")
	FOnCauldronStateChanged OnStateChanged;

	UPROPERTY(BlueprintAssignable, Category = "Alchemy Events")
	FOnCauldronExploded OnExploded;

	UPROPERTY(BlueprintAssignable, Category = "Alchemy Events")
	FOnCauldronCleaned OnCleaned;
};
