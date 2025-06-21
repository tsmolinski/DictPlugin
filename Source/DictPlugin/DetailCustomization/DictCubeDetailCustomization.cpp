// Fill out your copyright notice in the Description page of Project Settings.


#include "DictCubeDetailCustomization.h"

#include "DiffResults.h"

#if WITH_EDITOR

#include "Editor/PropertyEditor/Public/DetailLayoutBuilder.h"
#include "Editor/PropertyEditor/Public/DetailCategoryBuilder.h"
#include "Editor/PropertyEditor/Public/DetailWidgetRow.h"
#include "Runtime/Slate/Public/Widgets/Text/STextBlock.h"
#include "Runtime/Slate/Public/Widgets/Input/SButton.h"
#include "../Gameplay/DictCube.h"

#define LOCTEXT_NAMESPACE "DictCubeDetail"

TSharedRef<IDetailCustomization> FDictCubeDetailCustomization::MakeInstance()
{
	return MakeShareable(new FDictCubeDetailCustomization());
}

void FDictCubeDetailCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	IDetailCategoryBuilder& DetailCategoryBuilder = DetailLayout.EditCategory("DictCubeTest", FText::GetEmpty(), ECategoryPriority::Default);
	TObjectPtr<ADictCube> DictCube = nullptr;
	TArray<TWeakObjectPtr<UObject>> CustomizedObjects;
	DetailLayout.GetObjectsBeingCustomized(CustomizedObjects);

	for (auto& CustomizedObject : CustomizedObjects)
	{
		if (CustomizedObject.IsValid())
		{
			DictCube = Cast<ADictCube>(CustomizedObject);
			if (DictCube)
			{
				break;
			}
		}
	}

	check(DictCube);

	DetailCategoryBuilder.AddCustomRow(LOCTEXT("RowSearchName", "DictCube"))
	.NameContent()
	[
		SNew(STextBlock)
		.Text(LOCTEXT("DetailName", "DictCubeButton"))
		.Font(IDetailLayoutBuilder::GetDetailFont())
	]
	.ValueContent()
	[
		SNew(SButton)
		.Text(LOCTEXT("ButtonText", "Button"))
		.HAlign(HAlign_Center)
	];
}

#undef LOCTEXT_NAMESPACE
#endif