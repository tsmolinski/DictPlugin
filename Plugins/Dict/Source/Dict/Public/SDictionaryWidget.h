// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class DICT_API SDictionaryWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDictionaryWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	TSharedPtr<TMap<FString, FString>> Dictionary;
	TSharedPtr<SVerticalBox> DictionaryContainer;

	FReply OnAddElementClicked();

	void RemoveElement(FString Key);

	void UpdateDictionaryEntry(FString Key, FString Value, FString OldKey);

	void UpdateDictionary();
	
	FReply OnSaveDataClicked();
};
