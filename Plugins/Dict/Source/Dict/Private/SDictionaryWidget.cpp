// Fill out your copyright notice in the Description page of Project Settings.


#include "SDictionaryWidget.h"

#include "SDictionaryEntryWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SDictionaryWidget::Construct(const FArguments& InArgs)
{
	Dictionary = MakeShared<TMap<FString, FString>>();
	
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
					.OnClicked(this, &SDictionaryWidget::OnSaveDataClicked)
				]
			]
		]
	];
}

FReply SDictionaryWidget::OnAddElementClicked()
{
	if (!Dictionary->Contains(TEXT("")))
	{
		Dictionary->Add(TEXT(""),TEXT(""));
	
		UE_LOG(LogTemp, Warning, TEXT("OnAddElementClicked"));
		for (const auto& Elem : *Dictionary)
		{
			UE_LOG(LogTemp, Warning, TEXT("Key: %s, Value: %s"), *Elem.Key, *Elem.Value);
		}
	}
	
		DictionaryContainer->AddSlot()
		.AutoHeight()
		[
			SNew(SDictionaryEntryWidget)
			.DictEntryKey(TEXT(""))
			.DictEntryValue(TEXT(""))
			.RemoveElement(TDelegate<void(FString)>::CreateSP(this, &SDictionaryWidget::RemoveElement))
			.UpdateDictionaryEntry(TDelegate<void(FString, FString)>::CreateSP(this,&SDictionaryWidget::UpdateDictionaryEntry ))
		];
	
	return FReply::Handled();
}

void SDictionaryWidget::RemoveElement(FString Key)
{
	UE_LOG(LogTemp, Warning, TEXT("RemoveElement"));
	
	Dictionary->Remove(Key);
	
	UpdateDictionary();
}

void SDictionaryWidget::UpdateDictionaryEntry(FString Key, FString Value)
{
	if (Dictionary->Contains(Key))
	{
		(*Dictionary)[Key] = Value;
		UE_LOG(LogTemp, Warning, TEXT("UpdateDictionaryEntry1"));
		for (const auto& Elem : *Dictionary)
		{
			UE_LOG(LogTemp, Warning, TEXT("Key: %s, Value: %s"), *Elem.Key, *Elem.Value);
		}
	}
	else
	{
		Dictionary->Add(Key, Value);
		
		UE_LOG(LogTemp, Warning, TEXT("UpdateDictionaryEntry2"));
		for (const auto& Elem : *Dictionary)
		{
			UE_LOG(LogTemp, Warning, TEXT("Key: %s, Value: %s"), *Elem.Key, *Elem.Value);
		}
	}
}

void SDictionaryWidget::UpdateDictionary()
{
	DictionaryContainer->ClearChildren();

	UE_LOG(LogTemp, Warning, TEXT("UpdateDictionary"));
	for (const auto& Elem : *Dictionary)
	{
		UE_LOG(LogTemp, Warning, TEXT("Key: %s, Value: %s"), *Elem.Key, *Elem.Value);
			
		DictionaryContainer->AddSlot()
		.AutoHeight()
		[
			SNew(SDictionaryEntryWidget)
			.DictEntryKey(Elem.Key)
			.DictEntryValue(Elem.Value)
			.RemoveElement(TDelegate<void(FString)>::CreateSP(this, &SDictionaryWidget::RemoveElement))
			.UpdateDictionaryEntry(TDelegate<void(FString, FString)>::CreateSP(this,&SDictionaryWidget::UpdateDictionaryEntry ))
		];
	}
}

FReply SDictionaryWidget::OnSaveDataClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("OnSaveDataCliced"));
	
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
