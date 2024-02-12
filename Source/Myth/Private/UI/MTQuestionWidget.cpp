// Myth Game, All Rights Reserved.

#include "UI/MTQuestionWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

DEFINE_LOG_CATEGORY_STATIC(LogQuestionWidget, All, All);

void UMTQuestionWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (YesButton)
    {
        YesButton->OnClicked.AddDynamic(this, &UMTQuestionWidget::OnYesClicked);
    }

    if (NoButton)
    {
        NoButton->OnClicked.AddDynamic(this, &UMTQuestionWidget::OnNoClicked);
    }
}

void UMTQuestionWidget::OnYesClicked()
{
    UE_LOG(LogQuestionWidget, Display, TEXT("%OnYesClicked"));
}

void UMTQuestionWidget::OnNoClicked()
{
    UE_LOG(LogQuestionWidget, Display, TEXT("%OnNoClicked"));
}

void UMTQuestionWidget::SetMissionText(int32 NewGoalAmount, int32 ConundDownTime)
{
    FString MissionText = TEXT("You need deliver");
    FText FormattedTime = FText::AsTimespan(FTimespan(0, 0, ConundDownTime));
    FString FormattedTimeString = FormattedTime.ToString();
    MissionText.Append(FString::FromInt(NewGoalAmount)).Append(TEXT("blocks in ")).Append(FormattedTimeString);

    MissionTextBlock->SetText(FText::FromString(MissionText));
}