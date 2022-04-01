#include "APLLDS_Component.h"

void UAPLLDS_Component::SpotLight_Calculate(FRotator &ActorRot, FVector &ActorLocation)
{

    //Spot Light
    TArray<AActor*> Found_SpotLight_Actors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpotLight::StaticClass(), Found_SpotLight_Actors);

    SpotLight_instanceCount = Found_SpotLight_Actors.Num();
    int SpotLight_Count = 0;

    while (SpotLight_Count < SpotLight_instanceCount)
    {
        ASpotLight* Find_SpotLights = Cast<ASpotLight>(Found_SpotLight_Actors[SpotLight_Count]);

        if (Find_SpotLights)
        {
            USpotLightComponent* LightComp = Find_SpotLights->SpotLightComponent;

            if (LightComp)
            {
                //Setting LineTrace Variables
                FVector LightLocation = Find_SpotLights->GetActorLocation();
                FRotator Rot = ActorRot;
                FHitResult Hit;
                float Distance = FVector::Dist(ActorLocation, LightLocation);
                Set_SpotLight_Radius(LightComp); //HERE!!!!!

                //Linetrace parameters
                FCollisionQueryParams TraceParams;
                bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, ActorLocation, LightLocation, ECC_Visibility, TraceParams);
                //DrawDebugLine(GetWorld(), ActorLocation, LightLocation, FColor::Orange, false, 1.0f); //KEEP for debugging reasons

                //LineeTrace myself
                bool LineTraceTestByObjectType(const FVector& Start,const FVector& End,const FCollisionObjectQueryParams& ObjectQueryParams, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam);

                //Calculating the Light level results
                Set_SpotLight_LightFalloffExponent(LightComp);

                //Formula that Unreal Engine uses
                SpotLight_Result = FMath::Pow(FMath::Max(0.0f, 1.0f - (Distance / SpotLight_LightRadius)), (SpotLight_LightFalloffExponent + 1)) * (SpotLight_LightRadius * SpotLight_Radius_Multiplier);
                SpotLight_Result *= SpotLight_Result_Multiplier;

                SpotLight_Lit_Percent = (SpotLight_Result / SpotLight_Fully_Lit) * 100;
                Lit_Percent_AllLights += SpotLight_Lit_Percent;

                SpotLight_Result_Str = "Spot Light Result: " + FString::SanitizeFloat(SpotLight_Result);

                //Printing out results KEEP for debugging reasons
                //FString TempFString = FString::SanitizeFloat(SpotLight_Result);
                //GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TempFString);
                //TempFString = FString::SanitizeFloat(SpotLight_Lit_Percent);
                //GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TempFString);
            }
        }
        SpotLight_Count++;
    }
}

void UAPLLDS_Component::Set_SpotLight_Radius_Implementation(USpotLightComponent* LightComp)
{

}
void UAPLLDS_Component::Set_SpotLight_LightFalloffExponent_Implementation(USpotLightComponent* LightComp)
{

}
