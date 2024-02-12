// Myth Game, All Rights Reserved.


#include "UI/MTBaseButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"


void UMTBaseButton::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if(ButtonBase)
    {
        ButtonBase->OnClicked.AddDynamic(this, &UMTBaseButton::OnButtonClicked);
    }
}

void UMTBaseButton::OnButtonClicked() 
{
    OnBaseButtonClicked.Broadcast();
}

