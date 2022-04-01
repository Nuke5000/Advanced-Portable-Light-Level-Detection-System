// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define APLLDS_API GAME_API
#define ActorName "ThirdPersonCharacter"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Math/Vector.h" //Get
#include "CollisionQueryParams.h" //GET
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "UObject/NameTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/PointLight.h"
#include "EngineUtils.h"
#include "Components/PointLightComponent.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "DrawDebugHelpers.h"
#include "Engine/PointLight.h"
#include "Engine/DirectionalLight.h"
#include "Engine/SpotLight.h"
#include "Engine/RectLight.h"
#include "Engine/SkyLight.h"
#include "APLLDS_Component.generated.h"

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class APLLDS_API UAPLLDS_Component : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UAPLLDS_Component();

    UFUNCTION(BlueprintCallable, Category = "Light Level Detection")  //Primary function to start the work
        float Get_Light_Level(FVector ActorLocation, FRotator ActorRot);
    UFUNCTION(BlueprintCallable, Category = "Light Level Detection") //Calculates for all point lights
        void PointLight_Calculate(FRotator &ActorRot, FVector &ActorLocation);
    UFUNCTION(BlueprintCallable, Category = "Light Level Detection") //Calculates for all spot lights
        void SpotLight_Calculate(FRotator &ActorRot, FVector &ActorLocation);
    UFUNCTION(BlueprintCallable, Category = "Light Level Detection") //Calculates for all rect lights
        void RectLight_Calculate(FRotator &ActorRot, FVector &ActorLocation);

    //Functions that call to Blueprints
    UFUNCTION(BlueprintNativeEvent)
        void Set_SpotLight_Radius(USpotLightComponent* LightComp); //Getting Attenuation radius using blueprint
        void Set_SpotLight_Radius_Implementation(USpotLightComponent* LightComp);
    UFUNCTION(BlueprintNativeEvent) //Getting light falloff exponent using blueprint
        void Set_SpotLight_LightFalloffExponent(USpotLightComponent* LightComp);
        void Set_SpotLight_LightFalloffExponent_Implementation(USpotLightComponent* LightComp);
    UFUNCTION(BlueprintNativeEvent) //Getting Attenuation radius using blueprint
        void Set_RectLight_Radius(URectLightComponent* LightComp);
        void Set_RectLight_Radius_Implementation(URectLightComponent* LightComp);


    FCollisionQueryParams Params;

    //General Values needed
    //Finding all instances of the character or NPC
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection");
    TSubclassOf<AActor> Character_Editor;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection");
    ACharacter* myFindMe;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection");
    FVector NPC_Location; //Character location
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection");
    FVector NPC_Rot; //Character rotation
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection");
    int Character_Count; //Number of character instances found
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light Level Detection");
    float Lit_Percent_AllLights; //The light percent for all lights combined
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection");
    float APLLDS_Level_Modifier; //Used to modify Lit_Percent_AllLights on a level wide scale

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection");
    float Non_Falloff_Light_Percent; //Used with overlap boxes to manually add lighting percent for light sources that do not have any kind of falloff. This value will get changed when the character overlaps an overlap box at different points in the level.


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection");
    FString Char_LitPercent_All_Lights;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection");
    FString PointLight_Result_Str;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection");
    FString RectLight_Result_Str;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection");
    FString SpotLight_Result_Str;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection");
    float Base_Level_Lit_Percent; //Assume that there are no lights in the level at all but there is still some light in the level. This represents that value on a scale of 0 to 100. You simply have to approximate this value as best you can. The default value is 0;









    //Point light properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection Point Lights");
    int PointLight_Character_Count; //WTF is this?


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection Point Lights");
    float PointLight_Radius_Multiplier;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection Point Lights");
    float PointLight_Result;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection Point Lights");
    float PointLight_Result_Multiplier; //Used to get the percent to between 0 and 100
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light Level Detection Point Lights");
    float PointLight_Lit_Percent; //0 to 100 percent that the spot or character is lit just from point lights
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection Point Lights");
    float PointLight_LightFalloffExponent; //Lighting falloff for point lights
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection Point Lights");
    float PointLight_Fully_Lit; //The number at which the spot or character is %100 completely lit just from point lights
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection Point Lights");
    int PointLight_instanceCount; //The total number of point lights


    //Spot light properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection Spot Lights");
    float SpotLight_Radius_Multiplier;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection Spot Lights");
    float SpotLight_Result;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection Spot Lights");
    float SpotLight_Result_Multiplier;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light Level Detection Spot Lights");
    float SpotLight_Lit_Percent;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection Spot Lights");
    float SpotLight_LightFalloffExponent;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection Spot Lights");
    float SpotLight_Fully_Lit;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection Spot Lights");
    int SpotLight_instanceCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection Spot Lights");
    float SpotLight_LightRadius;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection Spot Lights");
    float Get_SpotLightFalloffExponent; //Needed?????




    //Rect Light Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection Rect Lights");
    float RectLight_Radius_Multiplier;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection Rect Lights");
    float RectLight_Result;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection Rect Lights");
    float RectLight_Result_Multiplier;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light Level Detection Rect Lights");
    float RectLight_Lit_Percent;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection Rect Lights");
    float RectLight_Fully_Lit;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection Rect Lights");
    int RectLight_instanceCount;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Level Detection Rect Lights");
    float RectLight_LightRadius;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
