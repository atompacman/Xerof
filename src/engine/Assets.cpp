#include <allegro5\allegro_font.h>
#include <allegro5\bitmap.h>
#include <allegro5\bitmap_io.h>
#include <Assets.h>
#include <easylogging++.h>
#include <FatalErrorDialog.h>
#include <iomanip>
#include <string>

ALLEGRO_BITMAP** loadAssets()
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
    for (unsigned int i = 0; i < numAssets; ++i) {
        bitmaps[i] = bitmapVec[i];
    }

    LOG(DEBUG) <<"Assets loading - Successfully loaded "<< numAssets <<" files";

    return bitmaps;
}

ALLEGRO_FONT& loadGameFont()
{
    LOG(DEBUG) <<"Assets loading - Loading game font at \""<< GAME_FONT << "\"";
    al_init_font_addon();
    ALLEGRO_FONT* font(al_load_font(GAME_FONT, 0, 0));
    if (font == NULL) {
        LOG(WARNING) << "Asset loading - Could not load the game font";
    }
    return *font;
}

void destroyAssets(ALLEGRO_BITMAP** io_Assets, ALLEGRO_FONT& io_Font)
{
    LOG(TRACE) << "Desallocation - Assets";
    for (unsigned int i = 0; i < numAssets; ++i) {
        al_destroy_bitmap(io_Assets[i]);
    }
    delete[] io_Assets;
    al_destroy_font(&io_Font);
}