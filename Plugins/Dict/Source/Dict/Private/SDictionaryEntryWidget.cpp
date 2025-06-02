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
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.FillWidth(1.0f)
				[
					SNew(SEditableText)
					.Text(FText::FromString(DictEntryKey))
					.OnTextCommitted(this, &SDictionaryEntryWidget::OnDictKeyChanged)
				]
				+ SHorizontalBox::Slot()
				.FillWidth(1.0f)
				[
					SNew(SEditableText)
					.Text(FText::FromString(DictEntryValue))
					.OnTextCommitted(this, &SDictionaryEntryWidget::OnDictValueChanged)
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(FText::FromString("Remove"))
					.OnClicked(this, &SDictionaryEntryWidget::OnRemoveClicked)
				]
			]
		];
}

void SDictionaryEntryWidget::OnDictKeyChanged(const FText& NewKey, ETextCommit::Type CommitType)
{
	DictEntryKey = NewKey.ToString();
	if (UpdateDictionaryEntry.IsBound())
	{
		UpdateDictionaryEntry.Execute(DictEntryKey, DictEntryValue);
	}
}

void SDictionaryEntryWidget::OnDictValueChanged(const FText& NewValue, ETextCommit::Type CommitType)
{
	DictEntryValue = NewValue.ToString();
	if (UpdateDictionaryEntry.IsBound())
	{
		UpdateDictionaryEntry.Execute(DictEntryKey, DictEntryValue);
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
