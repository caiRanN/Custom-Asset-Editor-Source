// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "CustomAssetEditorModule.h"
#include "MyCustomAsset.h"
#include "Modules/ModuleManager.h"
#include "IToolkit.h"
#include "CustomAssetEditor.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "AssetTypeActions_MyCustomAsset.h"

const FName CustomAssetEditorAppIdentifier = FName(TEXT("StaticMeshEditorApp"));

#define LOCTEXT_NAMESPACE "FCustomAssetEditorModule"

/**
 * StaticMesh editor module
 */
class FCustomAssetEditorModule : public ICustomAssetEditorModule
{
public:
	/** Constructor */
	FCustomAssetEditorModule() { }

	/**
	* Called right after the module DLL has been loaded and the module object has been created
	*/
	virtual void StartupModule() override
	{
		MenuExtensibilityManager = MakeShareable(new FExtensibilityManager);
		ToolBarExtensibilityManager = MakeShareable(new FExtensibilityManager);

		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_MyCustomAsset()));
	}

	/**
	* Called before the module is unloaded, right before the module object is destroyed.
	*/
	virtual void ShutdownModule() override
	{
		MenuExtensibilityManager.Reset();
		ToolBarExtensibilityManager.Reset();

		if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
		{
			// Unregister our custom created assets from the AssetTools
			IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
			for (int32 i = 0; i < CreatedAssetTypeActions.Num(); ++i)
			{
				AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeActions[i].ToSharedRef());
			}
		}

		CreatedAssetTypeActions.Empty();
	}

	/**
	* Creates a new custom asset editor for a MyCustomAsset
	*/
	virtual TSharedRef<ICustomAssetEditor> CreateCustomAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UMyCustomAsset* CustomAsset) override
	{
		TSharedRef<FCustomAssetEditor> NewCustomAssetEditor(new FCustomAssetEditor());
		NewCustomAssetEditor->InitCustomAssetEditorEditor(Mode, InitToolkitHost, CustomAsset);
		return NewCustomAssetEditor;
	}

	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
	{
		AssetTools.RegisterAssetTypeActions(Action);
		CreatedAssetTypeActions.Add(Action);
	}

	/** Gets the extensibility managers for outside entities to extend static mesh editor's menus and toolbars */
	virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override { return MenuExtensibilityManager; }
	virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override { return ToolBarExtensibilityManager; }

private:
	TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;
	TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;

	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;
};

#undef LOCTEXT_NAMESPACE

IMPLEMENT_GAME_MODULE(FCustomAssetEditorModule, CustomAssetEditor);