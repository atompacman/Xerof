#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "..\src\engine\Assets.h"
/*============================================================================||
| Anything that as an asset attached to it
|-----------------------------------------------------------------------------||
| This class should be expanded and renamed
\=============================================================================*/

enum MapElemType
{
	ENVIRONNEMENT, OBJECT
};

class MapElement
{
public:
	// ASSET
	virtual AssetID assetFile() const = 0;
};