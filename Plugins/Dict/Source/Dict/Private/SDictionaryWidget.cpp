// Fill out your copyright notice in the Description page of Project Settings.


#include "SDictionaryWidget.h"

#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
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
			SNew(SBorder)
			.BorderBackgroundColor(FLinearColor::Gray)
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
		]
	];
}

FReply SDictionaryWidget::OnAddElementClicked()
{
	if (!Dictionary->Contains(TEXT("")))
	{
		Dictionary->Add(TEXT(""),TEXT(""));
		
		DictionaryContainer->AddSlot()
		.AutoHeight()
		[
			SNew(SDictionaryEntryWidget)
			.DictEntryKey(TEXT(""))
			.DictEntryValue(TEXT(""))
			.RemoveElement(TDelegate<void(FString)>::CreateSP(this, &SDictionaryWidget::RemoveElement))
			.UpdateDictionaryEntry(TDelegate<void(FString, FString, FString)>::CreateSP(this,&SDictionaryWidget::UpdateDictionaryEntry ))
		];
	}
	
	return FReply::Handled();
}

void SDictionaryWidget::RemoveElement(FString Key)
{
	UE_LOG(LogTemp, Warning, TEXT("RemoveElement"));
	
	Dictionary->Remove(Key);
	
	UpdateDictionary();
}

void SDictionaryWidget::UpdateDictionaryEntry(FString Key, FString Value, FString OldKey)
{
	if (Key == OldKey)
	{
		(*Dictionary)[Key] = Value;
	}
	else
	{
		if (!Dictionary->Contains(Key))
		{
			FString TempValue = (*Dictionary)[OldKey];
			Dictionary->Remove(OldKey);
			Dictionary->Add(Key, Value);
			(*Dictionary)[Key] = Value;
		}
		else
		{
			UpdateDictionary();
		}
	}
}

void SDictionaryWidget::UpdateDictionary()
{
	DictionaryContainer->ClearChildren();
	
	for (const auto& Elem : *Dictionary)
	{
		DictionaryContainer->AddSlot()
		.AutoHeight()
		[
			SNew(SDictionaryEntryWidget)
			.DictEntryKey(Elem.Key)
			.DictEntryValue(Elem.Value)
			.RemoveElement(TDelegate<void(FString)>::CreateSP(this, &SDictionaryWidget::RemoveElement))
			.UpdateDictionaryEntry(TDelegate<void(FString, FString, FString)>::CreateSP(this,&SDictionaryWidget::UpdateDictionaryEntry ))
		];
	}
}

FReply SDictionaryWidget::OnSaveDataClicked()
{
	FString SavePath = GetFilePath();
	if (SavePath.IsEmpty())
	{
		return FReply::Handled();
	}
	FString JsonString;
	TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&JsonString);
	Writer->WriteObjectStart();

	for (const auto& Pair : *Dictionary)
	{
		Writer->WriteValue(Pair.Key, Pair.Value);
	}

	Writer->WriteObjectEnd();
	Writer->Close();
	
	FFileHelper::SaveStringToFile(JsonString, *SavePath);

	return FReply::Handled();
}

FString SDictionaryWidget::GetFilePath()
{
	TSharedPtr<IDesktopPlatform> DesktopPlatform = TSharedPtr<IDesktopPlatform>(FDesktopPlatformModule::Get());
	
	void* ParentWindowHandle = nullptr;
	TArray<FString> OutFiles;
	const FString DefaultPath = FPaths::ProjectSavedDir();
	const FString FileTypeFilters = TEXT("JSON Files (*.json)|*.json|All Files (*.*)|*.*");

	bool Success = DesktopPlatform->SaveFileDialog(
		ParentWindowHandle,
		TEXT("Save Dictionary as JSON"),
		DefaultPath,
		TEXT("DictionaryData.json"),
		FileTypeFilters,
		EFileDialogFlags::None,
		OutFiles
	);

	return Success && OutFiles.Num() > 0 ? OutFiles[0] : TEXT("");
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
