// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AlchemyTypes.generated.h"

UENUM(BlueprintType)
enum class EAlchemicalTrait : uint8
{
	Standard UMETA(DisplayName = "Standard"),
	Inverter UMETA(DisplayName = "Inverter"),
	Neutralizer UMETA(DisplayName = "Neutralizer")
};
