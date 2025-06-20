// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#if WITH_EDITOR
#include "Editor/DetailCustomizations/Public/DetailCustomizations.h"
#include "Editor/PropertyEditor/Public/IDetailCustomization.h"

/**
 * 
 */
class FDictCubeDetailCustomization : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;
};

#endif