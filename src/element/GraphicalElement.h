#pragma once

/*============================================================================\\
| Base class of every game element that is graphically representable
|-----------------------------------------------------------------------------||
| Class hierarchy:
| GraphicalElement -> ...
\=============================================================================*/

typedef unsigned int ElemID;

enum AssetID;

class GraphicalElement
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    GraphicalElement(AssetID i_AssetID) : 
        m_AssetID(i_AssetID) 
    {}

    // GETTERS
    AssetID assetFile() const { return m_AssetID; }

protected:
    AssetID m_AssetID;
};