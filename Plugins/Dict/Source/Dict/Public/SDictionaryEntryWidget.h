// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class DICT_API SDictionaryEntryWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDictionaryEntryWidget)
	{}
		SLATE_ARGUMENT(FString, DictEntryKey)
		SLATE_ARGUMENT(FString, DictEntryValue)
		SLATE_EVENT(TDelegate<void(FString, FString)>, UpdateDictionaryEntry)
		SLATE_EVENT(TDelegate<void(FString)>, RemoveElement)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	FString DictEntryKey;
	FString DictEntryValue;
	TDelegate<void(FString)> RemoveElement;
	TDelegate<void(FString, FString)> UpdateDictionaryEntry;

	void OnDictKeyChanged(const FText& NewKey, ETextCommit::Type CommitType);
	void OnDictValueChanged(const FText& NewValue, ETextCommit::Type CommitType);

	FReply OnRemoveClicked();
	
};
