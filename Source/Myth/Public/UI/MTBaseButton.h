// Myth Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MTBaseButton.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnBaseButtonClickedSignature);

class UButton;
class UTextBlock;

UCLASS()
class MYTH_API UMTBaseButton : public UUserWidget
{
    GENERATED_BODY()

public:
    FOnBaseButtonClickedSignature OnBaseButtonClicked;

protected:
    virtual void NativeOnInitialized() override;

    UPROPERTY(meta = (BindWidget))
    UButton* ButtonBase;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ButtonText;

    UFUNCTION()
    void OnButtonClicked();
};
