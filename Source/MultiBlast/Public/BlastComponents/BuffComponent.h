// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuffComponent.generated.h"

class ABlastCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MULTIBLAST_API UBuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuffComponent();

	friend class ABlastCharacter;

	void Heal(float HealAmount, float HealingTime);

	void ReplenishShield(float ShieldAmount, float ReplenishTime);

	void BuffSpeed(float BuffBaseSpeed, float BuffCrouchSpeed, float BuffTime);

	void SetInitialSpeeds(float BaseSpeed, float CrouchSpeed);

	void BuffJump(float BuffJumpVelocity, float BuffTime);

	void SetInitialJumpVelocity(float Velocity);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void HealRampUp(float DeltaTime);

	void ShieldRampUp(float DeltaTime);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY()
	ABlastCharacter* Character;

	/* Heal Buff. */

	bool bHealing = false;

	float HealingRate = 0.f;

	float AmountToHeal = 0.f;

	/* Shield Buff. */

	bool bShieldReplenish = false;

	float ShieldReplenishRate = 0.f;

	float ShieldReplenishAmount = 0.f;

	/* Speed Buffs. */

	FTimerHandle SpeedBuffTimer;

	void ResetSpeeds();

	float InitialBaseSpeed;

	float InitialCrouchSpeed;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastSpeedBuff(float BaseSpeed, float CrouchSpeed);

	/* Jump Buff. */

	FTimerHandle JumpBuffTimer;

	void ResetJump();

	float InitialJumpVelocity;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastJumpBuff(float JumpVelocity);
};
