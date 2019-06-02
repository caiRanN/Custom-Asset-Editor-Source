#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

class UMyCustomAsset;

/**
 * Public interface to Custom Asset Editor
 */
class ICustomAssetEditor : public FAssetEditorToolkit
{
public:
	/** Retrieves the current custom asset. */
	virtual UMyCustomAsset* GetCustomAsset() = 0;

	/** Set the current custom asset. */
	virtual void SetCustomAsset(UMyCustomAsset* InCustomAsset) = 0;
};