/**************************************************************************************************
// file:	Engine\GFX\CTileSet.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the tile set class
 **************************************************************************************************/
#ifndef A2DE_CTILESET_H
#define A2DE_CTILESET_H

#include "../a2de_vals.h"

#include <vector>
#include <string>

#include <allegro/file.h>
#include <allegro/gfx.h>
#include <allegro/draw.h>
#include <allegro/datafile.h>
#include <allegro/color.h>

A2DE_BEGIN

/**************************************************************************************************
 * <summary>Tile set. </summary>
 * <remarks>Casey Ugone, 7/6/2012.</remarks>
 **************************************************************************************************/
class TileSet {

public:

    /**************************************************************************************************
     * <summary>Creates a tile set.</summary>
     * <remarks>Casey Ugone, 4/2/2012.</remarks>
     * <param name="file">       The .bmp file containing the tiles.</param>
     * <param name="tile_width"> Width of all tiles in pixels.</param>
     * <param name="tile_height">Height of all tiles in pixels</param>
     * <returns>null if it fails, else.</returns>
     **************************************************************************************************/
    static TileSet* CreateTileSet(const std::string& file, int tile_width, int tile_height);

    /**************************************************************************************************
     * <summary>Destructor.</summary>
     * <remarks>Casey Ugone, 4/2/2012.</remarks>
     **************************************************************************************************/
    ~TileSet();

    /**************************************************************************************************
     * <summary>Draw tiles a tile to a BITMAP.</summary>
     * <remarks>Casey Ugone, 4/2/2012.</remarks>
     * <param name="dest">  If non-null, destination BITMAP for the tile to draw.</param>
     * <param name="column">Zero-based index of the column of the tile.</param>
     * <param name="row">   Zero-based index of the row of the tile.</param>
     * <param name="dest_x">Destination x coordinate in pixels.</param>
     * <param name="dest_y">Destination y coordinate in pixels.</param>
     **************************************************************************************************/
    void DrawTile(BITMAP* dest, unsigned int column, unsigned int row, int dest_x, int dest_y);

    /**************************************************************************************************
     * <summary>Draw tiles a tile to a BITMAP.</summary>
     * <remarks>Casey Ugone, 4/2/2012.</remarks>
     * <param name="dest">  [in,out] If non-null, destination for the tile to draw.</param>
     * <param name="index"> Zero-based index of the tile.</param>
     * <param name="dest_x">Destination x coordinate in pixels.</param>
     * <param name="dest_y">Destination y coordinate in pixels.</param>
     **************************************************************************************************/
    void DrawTile(BITMAP* dest, unsigned int index, int dest_x, int dest_y);

    /**************************************************************************************************
     * <summary>Gets the tile width.</summary>
     * <remarks>Casey Ugone, 4/3/2012.</remarks>
     * <returns>The tile width in pixels.</returns>
     **************************************************************************************************/
    unsigned int GetTileWidth() const;

    /**************************************************************************************************
     * <summary>Gets the tile width.</summary>
     * <remarks>Casey Ugone, 7/6/2012.</remarks>
     * <returns>The tile width.</returns>
     **************************************************************************************************/
    unsigned int GetTileWidth();

    /**************************************************************************************************
     * <summary>Gets the tile height.</summary>
     * <remarks>Casey Ugone, 4/3/2012.</remarks>
     * <returns>The tile height in pixels.</returns>
     **************************************************************************************************/
    unsigned int GetTileHeight() const;

    /**************************************************************************************************
     * <summary>Gets the tile height.</summary>
     * <remarks>Casey Ugone, 7/6/2012.</remarks>
     * <returns>The tile height.</returns>
     **************************************************************************************************/
    unsigned int GetTileHeight();

    /**************************************************************************************************
     * <summary>Gets the tile sheet width.</summary>
     * <remarks>Casey Ugone, 4/3/2012.</remarks>
     * <returns>The sheet width in pixels.</returns>
     **************************************************************************************************/
    unsigned int GetSheetWidth() const;

    /**************************************************************************************************
     * <summary>Gets the sheet width.</summary>
     * <remarks>Casey Ugone, 7/6/2012.</remarks>
     * <returns>The sheet width.</returns>
     **************************************************************************************************/
    unsigned int GetSheetWidth();

    /**************************************************************************************************
     * <summary>Gets the tile sheet height.</summary>
     * <remarks>Casey Ugone, 4/3/2012.</remarks>
     * <returns>The sheet height in pixels.</returns>
     **************************************************************************************************/
    unsigned int GetSheetHeight() const;

    /**************************************************************************************************
     * <summary>Gets the sheet height.</summary>
     * <remarks>Casey Ugone, 7/6/2012.</remarks>
     * <returns>The sheet height.</returns>
     **************************************************************************************************/
    unsigned int GetSheetHeight();

protected:
private:

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 4/2/2012.</remarks>
     * <param name="file">       The file.</param>
     * <param name="tile_width"> Width of the tile.</param>
     * <param name="tile_height">Height of the tile.</param>
     **************************************************************************************************/
    TileSet(const std::string& file, int tile_width, int tile_height);   

    /// <summary> The file </summary>
    std::string _file;
    /// <summary> Width of a tile </summary>
    int _tileWidth;
    /// <summary> Height of a tile </summary>
    int _tileHeight;
    /// <summary> Width of the sheet </summary>
    unsigned int _sheetWidth;
    /// <summary> Height of the sheet </summary>
    unsigned int _sheetHeight;
    /// <summary> The maximum rows </summary>
    unsigned int _max_rows;
    /// <summary> The maximum columns </summary>
    unsigned int _max_columns;
    /// <summary> The maximum tiles </summary>
    unsigned int _max_tiles;
    /// <summary> The tile sheet </summary>
    BITMAP* _tileSheet;

};

A2DE_END

#endif