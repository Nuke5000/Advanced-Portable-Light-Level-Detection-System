#include "APLLDS_Component.h"

void UAPLLDS_Component::RectLight_Calculate(FRotator &ActorRot, FVector &ActorLocation)
{

    //Rect Light
    TArray<AActor*> Found_RectLight_Actors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARectLight::StaticClass(), Found_RectLight_Actors);

    RectLight_instanceCount = Found_RectLight_Actors.Num();
    int RectLight_Count = 0;


    while (RectLight_Count < RectLight_instanceCount)
    {
        ARectLight* Find_RectLights = Cast<ARectLight>(Found_RectLight_Actors[RectLight_Count]);

        if (Find_RectLights)
        {
            URectLightComponent* LightComp = Find_RectLights->RectLightComponent;

            if (LightComp)
            {
                //Setting LineTrace Variables
                FVector LightLocation = Find_RectLights->GetActorLocation();
                FRotator Rot = ActorRot;
                FHitResult Hit;

                float Distance = FVector::Dist(ActorLocation, LightLocation);

                Set_RectLight_Radius(LightComp);

                FCollisionQueryParams TraceParams;
                bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, ActorLocation, LightLocation, ECC_Visibility, TraceParams);

                //DrawDebugLine(GetWorld(), ActorLocation, LightLocation, FColor::Orange, false, 1.0f); //KEEP for debugging reasons

                //LineeTrace itself
                bool LineTraceTestByObjectType(const FVector& Start,const FVector& End,const FCollisionObjectQueryParams& ObjectQueryParams, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam);
                //Calculating the Light level results
                float RectLight_LightFalloffExponent = 2.0; //The variable is actually called Shadow Exponent. You MUST manually assign this value. To get the vaue create a rect blueprint and click on the light component. Look n the right and you will find Shadow Exponent

                RectLight_Result = FMath::Pow(FMath::Max(0.0f, 1.0f - (Distance / RectLight_LightRadius)), (RectLight_LightFalloffExponent + 1)) * (RectLight_LightRadius * RectLight_Radius_Multiplier);
                RectLight_Result *= RectLight_Result_Multiplier;
                RectLight_Lit_Percent = (RectLight_Result / RectLight_Fully_Lit) * 100;
                Lit_Percent_AllLights += RectLight_Lit_Percent;

                RectLight_Result_Str = "Rect Light Result: " + FString::SanitizeFloat(RectLight_Result);

                //Printing out results KEEP for debugging reasons
                //FString TempFString = FString::SanitizeFloat(RectLight_Result);
                //GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TempFString);
                //TempFString = FString::SanitizeFloat(RectLight_Lit_Percent);
                //GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TempFString);
            }
        }
        RectLight_Count++;
    }
}

void UAPLLDS_Component::Set_RectLight_Radius_Implementation(URectLightComponent* LightComp)
{

}

