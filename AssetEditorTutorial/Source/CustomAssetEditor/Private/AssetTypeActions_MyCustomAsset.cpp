
#include "AssetTypeActions_MyCustomAsset.h"
#include "MyCustomAsset.h"
#include "CustomAssetEditorModule.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions_MyCustomAsset"

FText FAssetTypeActions_MyCustomAsset::GetName() const
{
	return NSLOCTEXT("AssetTypeActions_MyCustomAsset", "AssetTypeActions_MyCustomAsset", "MyCustomAsset");
}

FColor FAssetTypeActions_MyCustomAsset::GetTypeColor() const
{
	return FColor::Magenta;
}

UClass* FAssetTypeActions_MyCustomAsset::GetSupportedClass() const
{
	return UMyCustomAsset::StaticClass();
}

void FAssetTypeActions_MyCustomAsset::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor /*= TSharedPtr<IToolkitHost>()*/)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto MyCustomAsset = Cast<UMyCustomAsset>(*ObjIt);
		if (MyCustomAsset != NULL)
		{
			ICustomAssetEditorModule* CustomAssetEditorModule = &FModuleManager::LoadModuleChecked<ICustomAssetEditorModule>("CustomAssetEditor");
			CustomAssetEditorModule->CreateCustomAssetEditor(Mode, EditWithinLevelEditor, MyCustomAsset);
		}
	}
}

uint32 FAssetTypeActions_MyCustomAsset::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

#undef LOCTEXT_NAMESPACE
