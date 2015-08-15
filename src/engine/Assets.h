#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <iomanip>
#include <string>
//  | =   =   =   =   =   =   =   =   LIB   =   =   =   =   =   =   =   =   = ||
#include "allegro5\allegro_font.h"
#include "allegro5\bitmap.h"
#include "allegro5\bitmap_io.h"
#include "..\lib\easylogging++.h"
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "..\utils\FatalErrorDialog.h"
/*============================================================================||
| Assets management
|-----------------------------------------------------------------------------||
| Load and desallocate assets from disk using a routing file (linking an AssetID
| to a bitmap file).
\=============================================================================*/

// Directory of selected datapack
static const char* DATAPACK_DIR = "assets/0.3.0 - antialiasing/";

// Important: AssetIDs must be in the same order than the keys in the graphic
// pack content file
enum AssetID
{
    // Biomes
    BIOME_GRASSLAND,
    BIOME_OCEAN,
    BIOME_PLAINS,
    BIOME_ROCKY,
    BIOME_TUNDRA,

    // Characters
    CHARACTER,
    SELECTION,

    // Others
    WINDOW_ICON
};

// The number of bitmap assets
static UINT numAssets;

// The location of the asset routing file
static const char* GRAPHIC_PACK_CONTENT_FILE ="assets/graphic_pack_content.txt";

// Assets that are not bitmaps
static const char* GAME_FONT = "assets/font.tga";

// Load assets from disk
static ALLEGRO_BITMAP** loadAssets()
{
    LOG(DEBUG) << "Assets loading - Reading datapack content in \"" 
               << GRAPHIC_PACK_CONTENT_FILE << "\"";

    std::ifstream fis(GRAPHIC_PACK_CONTENT_FILE);
    std::string name, path;
    std::vector<ALLEGRO_BITMAP*> bitmapVec;
    ALLEGRO_BITMAP* bitmap;

    while (!fis.eof()) {
        fis >> name >> path >> path;

        // Skip comment lines
        if (name[0] == '#') {
            continue;
        }

        // Append datapack name at the beginning of the path
        path = DATAPACK_DIR + path;

        LOG(TRACE) << "Assets loading - " << std::setw(24)
                   << std::left << name << " at " << path;

        bitmap = al_load_bitmap(path.c_str());

        if (bitmap == NULL) {
            FatalErrorDialog(("Failed to load asset \"" + name
                + "\" at \"" + path + "\".").c_str());
        }
        bitmapVec.push_back(bitmap);
    }

    numAssets = bitmapVec.size();
    ALLEGRO_BITMAP** bitmaps = new ALLEGRO_BITMAP*[numAssets];
    for (UINT i = 0; i < numAssets; ++i) {
        bitmaps[i] = bitmapVec[i];
    }

    LOG(DEBUG) <<"Assets loading - Successfully loaded "<< numAssets<< " files";

    return bitmaps;
}

// Load game font
static ALLEGRO_FONT& loadGameFont()
{
    LOG(DEBUG) <<"Assets loading - Loading game font at \""<< GAME_FONT << "\"";

    al_init_font_addon();
    ALLEGRO_FONT* font(al_load_font(GAME_FONT, 0, 0));
    if (font == NULL) {
        LOG(WARNING) << "Asset loading - Could not load the game font";
    }
    return *font;
}

// Desallocate assets from memory
static void destroyAssets(ALLEGRO_BITMAP** io_Assets, ALLEGRO_FONT& io_Font)
{
    LOG(TRACE) << "Desallocation - Assets";
    for (UINT i = 0; i < numAssets; ++i) {
        al_destroy_bitmap(io_Assets[i]);
    }
    delete[] io_Assets;

    al_destroy_font(&io_Font);
}