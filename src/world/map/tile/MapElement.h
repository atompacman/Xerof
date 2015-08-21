#pragma once

/*============================================================================\\
| Anything that as an asset attached to it
|-----------------------------------------------------------------------------||
| This class should be expanded and renamed
\=============================================================================*/

enum AssetID;

class MapElement
{
public:
    // ASSET
    virtual AssetID assetFile() const = 0;
};