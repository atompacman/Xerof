#pragma once
#include "allegro5\bitmap.h"
#include "allegro5\bitmap_io.h"
#include "..\engine\internal\dialog\FatalErrorDialog.h"
#include <string>

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

static ALLEGRO_BITMAP* loadBitmap(const char* filePath)
{
	ALLEGRO_BITMAP* bitmap = al_load_bitmap(filePath);
	if (bitmap == nullptr) {
		std::string msg = filePath;
		msg = "Failed to load asset at \"" + msg + "\".";
		FatalErrorDialog(msg.c_str());
	}
	return bitmap;
}

static ALLEGRO_BITMAP** loadAssets()
{
	ALLEGRO_BITMAP** assets = new ALLEGRO_BITMAP*[NB_ASSETS];

	assets[GRASSLAND_TILE_FILE] = loadBitmap("assets/background/grassland.tga");
	assets[OCEAN_TILE_FILE] = loadBitmap("assets/background/ocean.tga");
	assets[PLAINS_TILE_FILE] = loadBitmap("assets/background/plains.tga");
	assets[ROCKY_TILE_FILE] = loadBitmap("assets/background/rocky.tga");
	assets[TUNDRA_TILE_FILE] = loadBitmap("assets/background/tundra.tga");
	assets[ALPHA_TEST_PACMAN] = loadBitmap("assets/testalpha.tga");
	assets[STICKMAN] = loadBitmap("assets/foreground/character/stickman.tga");
	assets[SELECTION] = loadBitmap("assets/foreground/selection.tga");
	assets[APARATUS3] = loadBitmap("assets/foreground/character/Aparatus3.tga");

	return assets;
}

static void destroyAssets(ALLEGRO_BITMAP** assets)
{
	for (int i = 0; i < NB_ASSETS; ++i) {
		al_destroy_bitmap(assets[i]);
	}
	delete assets;
}