// Fill out your copyright notice in the Description page of Project Settings.


#include "SDictionaryEntryWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SDictionaryEntryWidget::Construct(const FArguments& InArgs)
{
	DictEntryKey = InArgs._DictEntryKey;
	DictEntryValue = InArgs._DictEntryValue;
	UpdateDictionaryEntry = InArgs._UpdateDictionaryEntry;
	RemoveElement = InArgs._RemoveElement;
	
	ChildSlot
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			[
				SNew(SBorder)
				.BorderBackgroundColor(FLinearColor::Gray)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.FillWidth(1.0f)
					.Padding(0, 0, 2, 0)
					[
						SNew(SBorder)
						.BorderBackgroundColor(FLinearColor::Gray)
						[
							SNew(SEditableText)
							.Text(FText::FromString(DictEntryKey))
							.Font(FSlateFontInfo(FSlateFontInfo(FCoreStyle::GetDefaultFont(), 10)))
							.OnTextCommitted(this, &SDictionaryEntryWidget::OnDictKeyChanged)
						]
					]
					+ SHorizontalBox::Slot()
					.FillWidth(1.0f)
					[
						SNew(SBorder)
						.BorderBackgroundColor(FLinearColor::Gray)
						[
							SNew(SEditableText)
							.Text(FText::FromString(DictEntryValue))
							.Font(FSlateFontInfo(FSlateFontInfo(FCoreStyle::GetDefaultFont(), 10)))
							.OnTextCommitted(this, &SDictionaryEntryWidget::OnDictValueChanged)
						]
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(SButton)
						.Text(FText::FromString("Remove"))
						.OnClicked(this, &SDictionaryEntryWidget::OnRemoveClicked)
					]
				]
			]
		];
}

void SDictionaryEntryWidget::OnDictKeyChanged(const FText& NewKey, ETextCommit::Type CommitType)
{
	FString OldKey = DictEntryKey;
	DictEntryKey = NewKey.ToString();
	if (UpdateDictionaryEntry.IsBound())
	{
		UpdateDictionaryEntry.Execute(DictEntryKey, DictEntryValue, OldKey);
	}
}

void SDictionaryEntryWidget::OnDictValueChanged(const FText& NewValue, ETextCommit::Type CommitType)
{
	FString OldKey = DictEntryKey;
	DictEntryValue = NewValue.ToString();
	if (UpdateDictionaryEntry.IsBound())
	{
		UpdateDictionaryEntry.Execute(DictEntryKey, DictEntryValue, OldKey);
	}
}

FReply SDictionaryEntryWidget::OnRemoveClicked()
{
	if (RemoveElement.IsBound())
	{
		RemoveElement.Execute(DictEntryKey);
	}
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
