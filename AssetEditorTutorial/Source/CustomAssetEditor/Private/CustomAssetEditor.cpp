
#include "CustomAssetEditor.h"
#include "Modules/ModuleManager.h"
#include "EditorStyleSet.h"
#include "Widgets/Docking/SDockTab.h"
#include "PropertyEditorModule.h"
#include "IDetailsView.h"
#include "Editor.h"
#include "AssetEditorToolkit.h"
#include "CustomAssetEditorModule.h"

#define LOCTEXT_NAMESPACE "CustomAssetEditor"

const FName FCustomAssetEditor::ToolkitFName(TEXT("CustomAssetEditor"));
const FName FCustomAssetEditor::PropertiesTabId(TEXT("CustomAssetEditor_Properties"));

void FCustomAssetEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_CustomAssetEditor", "Custom Asset Editor"));

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(PropertiesTabId, FOnSpawnTab::CreateSP(this, &FCustomAssetEditor::SpawnPropertiesTab))
		.SetDisplayName(LOCTEXT("PropertiesTab", "Details"))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef())
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));
}

void FCustomAssetEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner(PropertiesTabId);
}

void FCustomAssetEditor::InitCustomAssetEditorEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UMyCustomAsset* InCustomAsset)
{
	const bool bIsUpdatable = false;
	const bool bAllowFavorites = true;
	const bool bIsLockable = false;

	SetCustomAsset(InCustomAsset);

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	const FDetailsViewArgs DetailsViewArgs(bIsUpdatable, bIsLockable, true, FDetailsViewArgs::ObjectsUseNameArea, false);
	DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);

	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_CustomAssetEditor_Layout_v1")
	->AddArea
	(
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
		->Split
		(
			FTabManager::NewStack()
			->SetSizeCoefficient(0.1f)
			->SetHideTabWell(true)
			->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
		)
		->Split
		(
			FTabManager::NewSplitter()
			->Split
			(
				FTabManager::NewStack()
				->AddTab(PropertiesTabId, ETabState::OpenedTab)
			)
		)
	);

	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;

	FAssetEditorToolkit::InitAssetEditor(
		Mode,
		InitToolkitHost,
		CustomAssetEditorAppIdentifier,
		StandaloneDefaultLayout,
		bCreateDefaultStandaloneMenu,
		bCreateDefaultToolbar,
		(UObject*)InCustomAsset);

	// Set the asset we are editing in the details view
	if (DetailsView.IsValid())
	{
		DetailsView->SetObject((UObject*)CustomAsset);
	}
}

FCustomAssetEditor::~FCustomAssetEditor()
{
	DetailsView.Reset();
	PropertiesTab.Reset();
}

FName FCustomAssetEditor::GetToolkitFName() const
{
	return ToolkitFName;
}

FText FCustomAssetEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Custom Asset Editor");
}

FText FCustomAssetEditor::GetToolkitToolTipText() const
{
	return LOCTEXT("ToolTip", "Custom Asset Editor");
}

FString FCustomAssetEditor::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "AnimationDatabase ").ToString();
}

FLinearColor FCustomAssetEditor::GetWorldCentricTabColorScale() const
{
	return FColor::Red;
}

UMyCustomAsset* FCustomAssetEditor::GetCustomAsset()
{
	return CustomAsset;
}

void FCustomAssetEditor::SetCustomAsset(UMyCustomAsset* InCustomAsset)
{
	CustomAsset = InCustomAsset;
}

TSharedRef<SDockTab> FCustomAssetEditor::SpawnPropertiesTab(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == PropertiesTabId);

	return SNew(SDockTab)
		.Icon(FEditorStyle::GetBrush("GenericEditor.Tabs.Properties"))
		.Label(LOCTEXT("GenericDetailsTitle", "Details"))
		.TabColorScale(GetTabColorScale())
		[
			DetailsView.ToSharedRef()
		];
}

#undef LOCTEXT_NAMESPACE
