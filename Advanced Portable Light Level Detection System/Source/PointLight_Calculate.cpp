#include "APLLDS_Component.h"

void UAPLLDS_Component::PointLight_Calculate(FRotator &ActorRot, FVector &ActorLocation)
{

    //Finds all the Point Lights
    TArray<AActor*> Found_PointLight_Actors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APointLight::StaticClass(), Found_PointLight_Actors);

    PointLight_instanceCount = Found_PointLight_Actors.Num();
    int PointLight_Count = 0;

    while (PointLight_Count < PointLight_instanceCount)
    {
        //Casts to the point light instance
        APointLight* Find_PointLights = Cast<APointLight>(Found_PointLight_Actors[PointLight_Count]);

        if (Find_PointLights)
        {
            //Gets the point light light component
            UPointLightComponent* LightComp = Find_PointLights->PointLightComponent;

            if (LightComp)
            {
                //Setting LineTrace Variables
                FVector LightLocation = Find_PointLights->GetActorLocation(); //Gets the point light location
                FRotator Rot = ActorRot;
                FHitResult Hit;
                float Distance = FVector::Dist(ActorLocation, LightLocation); //Distance between character and the light
                float LightRadius = LightComp->AttenuationRadius; //Gets the lights attenuation radius

                //Linetrace parameters
                FCollisionQueryParams TraceParams;
                bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, ActorLocation, LightLocation, ECC_Visibility, TraceParams);
                //DrawDebugLine(GetWorld(), ActorLocation, LightLocation, FColor::Orange, false, 1.0f); //KEEP for debugging reasons

                //LineeTrace itself
                bool LineTraceTestByObjectType(const FVector& Start,const FVector& End,const FCollisionObjectQueryParams& ObjectQueryParams, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam);


                //Calculating the Light level results
                LightComp->LightFalloffExponent = PointLight_LightFalloffExponent; //8 by default
                //Formula that Unreal Engine uses
                PointLight_Result = FMath::Pow(FMath::Max(0.0f, 1.0f - (Distance / LightRadius)), (LightComp->LightFalloffExponent + 1)) * (LightRadius * PointLight_Radius_Multiplier);
                PointLight_Result *= PointLight_Result_Multiplier;

                PointLight_Lit_Percent = (PointLight_Result / PointLight_Fully_Lit) * 100; //Sets the point light percent to somewhere between 0 and 100
                Lit_Percent_AllLights += PointLight_Lit_Percent; //Adds PointLight_Lit_Percent to the total level percent

                PointLight_Result_Str = "Point Light Result: " + FString::SanitizeFloat(PointLight_Result);



                //Printing out results KEEP for debugging reasons
                //FString TempFString = FString::SanitizeFloat(PointLight_Result);
                //GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TempFString);
                //TempFString = FString::SanitizeFloat(PointLight_Lit_Percent);
                //GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TempFString);
            }
        }
        PointLight_Count++;
    }
}
