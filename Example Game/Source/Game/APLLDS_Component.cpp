// Fill out your copyright notice in the Description page of Project Settings.


#include "APLLDS_Component.h"

// Sets default values for this component's properties
UAPLLDS_Component::UAPLLDS_Component()
{
    PrimaryComponentTick.bCanEverTick = true;

    //Setting some default values
    NPC_Location = FVector(0.0f, 0.0f, 0.0f);
    Base_Level_Lit_Percent = 0;
    Lit_Percent_AllLights = 0;
    APLLDS_Level_Modifier = 1.0;

    //Point Light Initial Values
    PointLight_Radius_Multiplier = 1;
    PointLight_Result_Multiplier = 100;
    PointLight_Lit_Percent = 0;
    PointLight_LightFalloffExponent = 8;
    PointLight_Fully_Lit = 1000;
    PointLight_instanceCount = 0;
    Non_Falloff_Light_Percent = 0;

    //Spot Light Initial Values
    SpotLight_Radius_Multiplier = 1;
    SpotLight_Result_Multiplier = 100;
    SpotLight_Lit_Percent = 0;
    SpotLight_LightFalloffExponent = 8;
    SpotLight_Fully_Lit = 1000;
    SpotLight_instanceCount = 0;

    //Rect Light Initial Values
    RectLight_Radius_Multiplier = 1;
    RectLight_Result_Multiplier = 100;
    RectLight_Lit_Percent = 0;
    RectLight_Fully_Lit = 1000;
    RectLight_instanceCount = 0;

}

// Called when the game starts
void UAPLLDS_Component::BeginPlay()
{
    Super::BeginPlay();



}

float UAPLLDS_Component::Get_Light_Level(FVector ActorLocation, FRotator ActorRot)
{
    Lit_Percent_AllLights = 0;

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), FoundActors);
    int instanceCount = FoundActors.Num();
    Character_Count = 0;

    while (Character_Count < instanceCount)
    {
        myFindMe = Cast<ACharacter>(FoundActors[Character_Count]); //HERE!!!!
        FString tempString = "temp";

        //ThirdPersonCharacter
        if(ActorName == UKismetSystemLibrary::GetDisplayName(myFindMe))
        {

            FName ShadowLevelDetect = TEXT("Shadow Level Detect");
            Params = FCollisionQueryParams(ShadowLevelDetect, true, myFindMe);

            //Calling th functions to search for the lights
            PointLight_Calculate(ActorRot, ActorLocation);
            SpotLight_Calculate(ActorRot, ActorLocation); //HERE
            RectLight_Calculate(ActorRot, ActorLocation);


            //Printing out Lit_Percent_AllLights
            Lit_Percent_AllLights *= APLLDS_Level_Modifier;
            Lit_Percent_AllLights = Lit_Percent_AllLights + Non_Falloff_Light_Percent + Base_Level_Lit_Percent;
            //Ensures that the percent does not go above 100.
            if(Lit_Percent_AllLights > 100)
            {
                Lit_Percent_AllLights = 100;
            }

            //This will execute only if there is atleast one normal light like a point light in the scene
            if(Lit_Percent_AllLights != 0)
            {
                Char_LitPercent_All_Lights = "Total Character Lit Percent: " + FString::SanitizeFloat(Lit_Percent_AllLights);
                //GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Green, "Character Lit Percent: " + TempFString); //KEEP for testing purposes
            }

        }
        Character_Count++;
    }

    //This will execute when there are no normal lights in the scene
    if(Lit_Percent_AllLights == 0)
    {
        Lit_Percent_AllLights = Lit_Percent_AllLights + Non_Falloff_Light_Percent + Base_Level_Lit_Percent;
        Char_LitPercent_All_Lights = "Total Character Lit Percent: " + FString::SanitizeFloat(Lit_Percent_AllLights);
        //GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Green, "Character Lit Percent: " + TempFString); //KEEP for testing purposes
    }

    return 0;
}

// Called every frame
void UAPLLDS_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}
