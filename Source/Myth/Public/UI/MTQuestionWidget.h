// Myth Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MTQuestionWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class MYTH_API UMTQuestionWidget : public UUserWidget
{
    GENERATED_BODY()

public:
        void SetMissionText(int32 NewGoalAmount, int32 ConundDownTime);

protected:


    UPROPERTY(meta = (BindWidget))
    UButton* YesButton;

    UPROPERTY(meta = (BindWidget))
    UButton* NoButton;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* MissionTextBlock;

    UFUNCTION()
    void OnYesClicked();

    UFUNCTION()
    void OnNoClicked();

    virtual void NativeOnInitialized() override;
};
