// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* HitParticles;
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* LaunchSound;
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* HitSound;
	UPROPERTY(VisibleAnywhere, Category = "Effects")
	class UParticleSystemComponent* TrailParticles;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(EditAnywhere, Category = "Damage")
	float DamageAmount = 50.f;

	float ProjectileInitialSpeed = 1500.f;
	float ProjectileMaxSpeed = 1500.f;
	float ProjectileGravity = 1.f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
