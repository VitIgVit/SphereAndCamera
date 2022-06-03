#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TopDownSpectator.generated.h"



UCLASS()
class SPHEREANDCAMERA_API ATopDownSpectator : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATopDownSpectator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MouseBegin();
	void MouseStop();

	void MouseYaw(float axis);
	void MousePitch(float axis);

	void CameraZoom(const float Value);

	//Vector
	FVector2D MouseInput;

private:
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "CameraZoom")
	float MinZoomLengh = 0.f;

	UPROPERTY(EditAnywhere, Category = "CameraZoom")
	float MaxZoomLengh = 350.f;

	UPROPERTY(EditAnywhere, Category = "CameraZoom")
	float ZoomStep = 10.f;

	UPROPERTY(EditAnywhere)
	bool ActiveMouseL;
};
