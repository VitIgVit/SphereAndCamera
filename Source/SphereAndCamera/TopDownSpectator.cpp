// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownSpectator.h"

// Sets default values
ATopDownSpectator::ATopDownSpectator()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->AttachTo(Root);
	SpringArm->TargetArmLength = 350.f;
	SpringArm->SetWorldRotation(FRotator(-10.f, 0.f, 0.f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachTo(SpringArm);

	ActiveMouseL = false;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ATopDownSpectator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATopDownSpectator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActiveMouseL == false) return;

	FRotator NewYaw = GetActorRotation();
	NewYaw.Yaw += MouseInput.X;
	SetActorRotation(NewYaw);

	FRotator NewPitch = SpringArm->GetComponentRotation();

	NewPitch.Pitch = FMath::Clamp(NewPitch.Pitch + MouseInput.Y, -89.f, 0.f);
	SpringArm->SetWorldRotation(NewPitch);

}

// Called to bind functionality to input
void ATopDownSpectator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("MouseL", IE_Pressed, this, &ATopDownSpectator::MouseBegin);
	InputComponent->BindAction("MouseL", IE_Released, this, &ATopDownSpectator::MouseStop);

	InputComponent->BindAxis("MouseYaw", this, &ATopDownSpectator::MouseYaw);
	InputComponent->BindAxis("MousePitch", this, &ATopDownSpectator::MousePitch);
	InputComponent->BindAxis("CameraZoom", this, &ATopDownSpectator::CameraZoom);
}

void ATopDownSpectator::MouseBegin()
{
	GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, TEXT("Begin"));
	ActiveMouseL = true;
}

void ATopDownSpectator::MouseStop()
{
	GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, TEXT("Stop"));
	ActiveMouseL = false;
}

void ATopDownSpectator::MouseYaw(float axis)
{
	MouseInput.X = axis;
}

void ATopDownSpectator::MousePitch(float axis)
{
	MouseInput.Y = axis;
}

void ATopDownSpectator::CameraZoom(const float Value)
{
	if (Value == 0.f) return;

	const float NewTargetZoom = SpringArm->TargetArmLength + Value * ZoomStep;
	SpringArm->TargetArmLength = FMath::Clamp(NewTargetZoom, MinZoomLengh, MaxZoomLengh);
}
