// Fill out your copyright notice in the Description page of Project Settings.


#include "SDictionaryWidget.h"

#include "SDictionaryEntryWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SDictionaryWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SAssignNew(DictionaryContainer, SVerticalBox)
			]
			
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				[
					SNew(SButton)
					.Text(FText::FromString("Add element"))
					.OnClicked(this, &SDictionaryWidget::OnAddElementClicked)
				]
				+SHorizontalBox::Slot()
				[
					SNew(SButton)
					.Text(FText::FromString("Save to Json"))
					//.OnClicked(this, &SDictionaryWidget::)
				]
			]
		]
	];
}

FReply SDictionaryWidget::OnAddElementClicked()
{
	DictionaryContainer->AddSlot()
	.AutoHeight()
	[
		SNew(SDictionaryEntryWidget)
	];

	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
