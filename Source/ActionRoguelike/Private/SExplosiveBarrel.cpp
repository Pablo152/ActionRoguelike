// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"

#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	StaticMeshComp->SetCollisionProfileName("Projectile");
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/ExampleContent/Meshes/SM_RedBarrel.SM_RedBarrel"));
	StaticMeshComp->SetStaticMesh(MeshObj.Object);
	StaticMeshComp->SetCollisionProfileName("PhysicsActor");

	FString MaterialName = TEXT("/Engine/MapTemplates/Materials/BasicAsset01.BasicAsset01");
	UMaterialInterface* Material = static_cast<UMaterialInterface*>(StaticLoadObject(UMaterialInterface::StaticClass(),
		nullptr, *MaterialName, nullptr, LOAD_None,nullptr));
	
	StaticMeshComp->SetMaterial(0, Material);
	StaticMeshComp->SetSimulatePhysics(true);
	StaticMeshComp->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnComponentHitCallback);
	
	RootComponent = StaticMeshComp;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->ImpulseStrength = 2000.0f;
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->SetupAttachment(StaticMeshComp);
}

// Called when the game starts or when spawned
void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASExplosiveBarrel::OnComponentHitCallback(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComp->FireImpulse();
}
