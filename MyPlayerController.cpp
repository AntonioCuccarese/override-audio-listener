// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

void AMyPlayerController::GetAudioListenerPosition(FVector& OutLocation, FVector& OutFrontDir, FVector& OutRightDir) const {
    
    FVector ViewLocation;
    FRotator ViewRotation;

    if (bOverrideAudioListener) {
        USceneComponent* ListenerComponent = AudioListenerComponent.Get();
        if (ListenerComponent != nullptr) {
            ViewRotation = ListenerComponent->GetComponentRotation() + AudioListenerRotationOverride;
            ViewLocation = ListenerComponent->GetComponentLocation() + ViewRotation.RotateVector(AudioListenerLocationOverride);
        } else {
            ViewLocation = AudioListenerLocationOverride;
            ViewRotation = AudioListenerRotationOverride;
        }
    } else {
        GetPlayerViewPoint(ViewLocation, ViewRotation);
        if (GetPawn()) {
            ViewLocation = GetPawn()->GetActorLocation();
        }
    }

    const FRotationTranslationMatrix ViewRotationMatrix(ViewRotation, ViewLocation);

    OutLocation = ViewLocation;
    OutFrontDir = ViewRotationMatrix.GetUnitAxis(EAxis::X);
    OutRightDir = ViewRotationMatrix.GetUnitAxis(EAxis::Y);

}
