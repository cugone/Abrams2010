/**************************************************************************************************
// file:	Engine\GFX\CTileSet.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the tile set class
 **************************************************************************************************/
#include "CTileSet.h"

#include <cassert>
#include "../a2de_exceptions.h"
#include "CBitmapCache.h"

A2DE_BEGIN

TileSet* TileSet::CreateTileSet(const std::string& file, int tileWidth, int tileHeight) {
    if(exists(file.c_str()) == 0) {
        throw FileNotFoundException(file);
    }
    assert(tileWidth > 0);
    assert(tileHeight > 0);
    if(tileWidth < 1) {
        throw InvalidArgumentException("Tile Width cannot be less than one.");
    }
    else if(tileHeight < 1) {
        throw InvalidArgumentException("Tile Height cannot be less than one.");
    }

    return new TileSet(file, tileWidth, tileHeight);
}

TileSet::TileSet(const std::string& file, int tileWidth, int tileHeight) : _file(), _tileWidth(tileWidth), _tileHeight(tileHeight), _sheetWidth(0), _sheetHeight(0), _max_rows(0), _max_columns(0), _max_tiles(0), _tileSheet(nullptr) {

    std::string f(file);
    _file = fix_filename_slashes(&f[0]);
    _tileSheet = BitmapCache::GetBitmap(_file);
    if(_tileSheet == nullptr) {
        throw BitmapLoadFailureException(file);
    }

    _sheetWidth = _tileSheet->w;
    _sheetHeight = _tileSheet->h;

    _max_columns = _sheetWidth / _tileWidth;
    _max_rows = _sheetHeight / _tileHeight;
    _max_tiles = _max_columns * _max_rows;

}

TileSet::~TileSet() {
    if(_tileSheet) {
        BitmapCache::DecrementRefCount(_file);
        _tileSheet = nullptr;
    }
}

void TileSet::DrawTile(BITMAP* dest, unsigned int column, unsigned int row, int dest_x, int dest_y) {
    if(dest == nullptr) return;
    if(column >= _max_columns || row >= _max_rows) return;
    blit(_tileSheet, dest, column * _tileWidth, row * _tileHeight, dest_x, dest_y, _tileWidth, _tileHeight);
}

void TileSet::DrawTile(BITMAP* dest, unsigned int index, int dest_x, int dest_y) {
    if(dest == nullptr) return;
    if(index >= _max_tiles) return;

    unsigned int row = index / _max_columns;
    unsigned int column = index % _max_columns;

    DrawTile(dest, column, row, dest_x, dest_y);
}

unsigned int TileSet::GetTileWidth() const {
    return _tileWidth;
}

unsigned int TileSet::GetTileWidth() {
    return static_cast<const TileSet&>(*this).GetTileWidth();
}

unsigned int TileSet::GetTileHeight() const {
    return _tileHeight;
}

unsigned int TileSet::GetTileHeight() {
    return static_cast<const TileSet&>(*this).GetTileHeight();
}

unsigned int TileSet::GetSheetWidth() const {
    return _sheetWidth;
}

unsigned int TileSet::GetSheetWidth() {
    return static_cast<const TileSet&>(*this).GetSheetWidth();
}

unsigned int TileSet::GetSheetHeight() const {
    return _sheetHeight;
}

unsigned int TileSet::GetSheetHeight() {
    return static_cast<const TileSet&>(*this).GetSheetHeight();
}


A2DE_END