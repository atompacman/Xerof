#pragma once

/*============================================================================||
| Assets management
|-----------------------------------------------------------------------------||
| Load and desallocate assets from disk using a routing file (linking an AssetID
| to a bitmap file).
\=============================================================================*/

struct ALLEGRO_BITMAP;
struct ALLEGRO_FONT;

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
static unsigned int numAssets;

// The location of the asset routing file
static const char* GRAPHIC_PACK_CONTENT_FILE ="assets/graphic_pack_content.txt";

// Assets that are not bitmaps
static const char* GAME_FONT = "assets/font.tga";

// Load assets from disk
ALLEGRO_BITMAP** loadAssets();

// Load game font
ALLEGRO_FONT& loadGameFont();

// Desallocate assets from memory
void destroyAssets(ALLEGRO_BITMAP** io_Assets, ALLEGRO_FONT& io_Font);