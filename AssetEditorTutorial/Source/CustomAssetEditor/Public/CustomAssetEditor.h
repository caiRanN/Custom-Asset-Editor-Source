#pragma once

#include "CoreMinimal.h"
#include "Toolkits/IToolkitHost.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Editor/PropertyEditor/Public/PropertyEditorDelegates.h"
#include "ICustomAssetEditor.h"

class IDetailsView;
class SDockableTab;
class UMyCustomAsset;

/**
 * 
 */
class CUSTOMASSETEDITOR_API FCustomAssetEditor : public ICustomAssetEditor
{
public:

	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;

	/**
	 * Edits the specified asset object
	 *
	 * @param	Mode					Asset editing mode for this editor (standalone or world-centric)
	 * @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within
	 * @param	InCustomAsset			The Custom Asset to Edit
	 */
	void InitCustomAssetEditorEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UMyCustomAsset* InCustomAsset);

	/** Destructor */
	virtual ~FCustomAssetEditor();

	/** Begin IToolkit interface */
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual bool IsPrimaryEditor() const override { return true; }
	/** End IToolkit interface */

	/** Begin ICustomAssetEditor initerface */
	virtual UMyCustomAsset* GetCustomAsset();
	virtual void SetCustomAsset(UMyCustomAsset* InCustomAsset);
	/** End ICustomAssetEditor initerface */

public:
	/** The name given to all instances of this type of editor */
	static const FName ToolkitFName;

private:
	/** Create the properties tab and its content */
	TSharedRef<SDockTab> SpawnPropertiesTab(const FSpawnTabArgs& Args);

	/** Dockable tab for properties */
	TSharedPtr< SDockableTab > PropertiesTab;

	/** Details view */
	TSharedPtr<class IDetailsView> DetailsView;

	/**	The tab ids for all the tabs used */
	static const FName PropertiesTabId;

	/** The Custom Asset open within this editor */
	UMyCustomAsset* CustomAsset;
};