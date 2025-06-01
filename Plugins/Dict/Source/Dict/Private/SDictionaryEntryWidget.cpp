// Fill out your copyright notice in the Description page of Project Settings.


#include "SDictionaryEntryWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SDictionaryEntryWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.FillWidth(1.0f)
				[
					SNew(SEditableText)
					.Text(FText::FromString("1"))
					//.OnTextCommitted(this, &SDictionaryEntryWidget::)
				]
				+ SHorizontalBox::Slot()
				.FillWidth(1.0f)
				[
					SNew(SEditableText)
					.Text(FText::FromString("2"))
					//.OnTextCommitted(this, &SDictionaryEntryWidget::)
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(FText::FromString("Remove"))
					//.OnClicked(this, &SDictionaryEntryWidget::)
				]
			]
		];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
