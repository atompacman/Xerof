#pragma once
#include "allegro5\bitmap.h"
#include "allegro5\bitmap_io.h"
#include "..\engine\dialog\FatalErrorDialog.h"
#include <string>

static ALLEGRO_BITMAP** assets;
const int NB_ASSETS = 9;

enum Asset
{
	GRASSLAND_TILE_FILE,
	OCEAN_TILE_FILE,
	PLAINS_TILE_FILE,
	ROCKY_TILE_FILE,
	TUNDRA_TILE_FILE,

	ALPHA_TEST_PACMAN,
	STICKMAN,
	SELECTION,
	APARATUS3
};

static bool loadBitmap(Asset id, const char* filePath);

static bool loadAssets()
{
	assets = new ALLEGRO_BITMAP*[NB_ASSETS];

	if (loadBitmap(GRASSLAND_TILE_FILE, "assets/background/grassland.tga"))				{ return EXIT_FAILURE; }
	if (loadBitmap(OCEAN_TILE_FILE,		"assets/background/ocean.tga"))					{ return EXIT_FAILURE; }
	if (loadBitmap(PLAINS_TILE_FILE,	"assets/background/plains.tga"))				{ return EXIT_FAILURE; }
	if (loadBitmap(ROCKY_TILE_FILE,		"assets/background/rocky.tga"))					{ return EXIT_FAILURE; }
	if (loadBitmap(TUNDRA_TILE_FILE,	"assets/background/tundra.tga"))				{ return EXIT_FAILURE; }
	if (loadBitmap(ALPHA_TEST_PACMAN,	"assets/testalpha.tga"))						{ return EXIT_FAILURE; }
	if (loadBitmap(STICKMAN,			"assets/foreground/character/stickman.tga"))	{ return EXIT_FAILURE; }
	if (loadBitmap(SELECTION,			"assets/foreground/selection.tga"))				{ return EXIT_FAILURE; }
	if (loadBitmap(APARATUS3,			"assets/foreground/character/Aparatus3.tga"))	{ return EXIT_FAILURE; }

	return EXIT_SUCCESS;
}

static bool loadBitmap(Asset id, const char* filePath)
{
	ALLEGRO_BITMAP* bitmap = al_load_bitmap(filePath);
	if (bitmap == nullptr) {
		std::string msg = filePath;
		msg = "Failed to load asset at \"" + msg + "\".";
		FatalErrorDialog(msg.c_str());
		return EXIT_FAILURE;
	}
	assets[id] = bitmap;

	return EXIT_SUCCESS;
}

static void destroyAssets()
{
	for (int i = 0; i < NB_ASSETS; ++i) {
		al_destroy_bitmap(assets[i]);
	}
	delete assets;
}