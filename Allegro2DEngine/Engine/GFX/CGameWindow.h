/**************************************************************************************************
// file:	Engine\GFX\CGameWindow.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the game Windows Form
 **************************************************************************************************/
#ifndef A2DE_CGAMEWINDOW_H
#define A2DE_CGAMEWINDOW_H

#include "../a2de_vals.h"
#include <utility>
#include <string>

//Forward declarations for cohesive pointer types.
struct BITMAP;
struct GFX_MODE;
struct GFX_MODE_LIST;

A2DE_BEGIN

class Mouse;

/**************************************************************************************************
 * <summary>Form for viewing the game. </summary>
 * <remarks>Casey Ugone, 9/3/2012.</remarks>
 **************************************************************************************************/
class GameWindow {

public:

    enum WINDOWMODE {
        WINDOWMODE_WINDOWED,
        WINDOWMODE_FULLSCREEN
    };

    /**************************************************************************************************
     * <summary>Default constructor.</summary>
     * <remarks>Casey Ugone, 7/26/2011.</remarks>
     **************************************************************************************************/
    GameWindow();

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 7/26/2011.</remarks>
     * <param name="windowed">true to set windowed mode, false to set fullscreen.</param>
     **************************************************************************************************/
    GameWindow(a2de::GameWindow::WINDOWMODE mode);

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 7/26/2011.</remarks>
     * <param name="windowed">true to set windowed mode, false to set fullscreen.</param>
     * <param name="width">   The width of the window; it does not include the window title bar and edges if set to windowed mode!.</param>
     * <param name="height">  The height of the window; it does not include the window title bar and edges if set to windowed mode!.</param>
     **************************************************************************************************/
    GameWindow(a2de::GameWindow::WINDOWMODE mode, int width, int height); /* throws Exception */

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 7/26/2011.</remarks>
     * <param name="windowed">true to set windowed mode, false to set fullscreen.</param>
     * <param name="width">   The width of the window; it does not include the window title bar and edges if set to windowed mode!.</param>
     * <param name="height">  The height of the window; it does not include the window title bar and edges if set to windowed mode!.</param>
     * <param name="title">   The text to display as the program title.</param>
     **************************************************************************************************/
	GameWindow(a2de::GameWindow::WINDOWMODE mode, int width, int height, const std::string& title); /* throws Exception */

    /**************************************************************************************************
     * <summary>Destructor.</summary>
     * <remarks>Casey Ugone, 7/26/2011.</remarks>
     **************************************************************************************************/
    ~GameWindow();

    /**************************************************************************************************
     * <summary>Query if the window is set to windowed mode.</summary>
     * <remarks>Casey Ugone, 7/26/2011.</remarks>
     * <returns>true if windowed, false if not.</returns>
     **************************************************************************************************/
    bool IsWindowed() const;

    /**************************************************************************************************
     * <summary>Gets the width of the window.</summary>
     * <remarks>Casey Ugone, 7/26/2011.</remarks>
     * <returns>The width of the window not including the title bar or edges.</returns>
     **************************************************************************************************/
    int GetWidth() const;

    /**************************************************************************************************
     * <summary>Gets the height of the window.</summary>
     * <remarks>Casey Ugone, 7/26/2011.</remarks>
     * <returns>The height of the window not including the title bar or edges.</returns>
     **************************************************************************************************/
    int GetHeight() const;

    /**************************************************************************************************
     * <summary>Gets the pixel depth of the window.</summary>
     * <remarks>Casey Ugone, 7/26/2011.</remarks>
     * <returns>Always returns 32.</returns>
     **************************************************************************************************/
    int GetDepth() const;

    /**************************************************************************************************
     * <summary>Gets the back buffer memory bitmap.</summary>
     * <remarks>Casey Ugone, 7/26/2011.</remarks>
     * <returns>null if it fails, else the back buffer.</returns>
     **************************************************************************************************/
    BITMAP* GetBackBuffer() const;
    
    /**************************************************************************************************
     * <summary>Registers a mouse to automatically handle hiding and showing between screen draws.</summary>
     * <remarks>Casey Ugone, 7/26/2011.</remarks>
     * <param name="mouse">[in,out] The mouse to register. If null, does nothing.</param>
     **************************************************************************************************/
	void RegisterMouse(Mouse* mouse);

    /**************************************************************************************************
     * <summary>Unregisters a mouse with the window.</summary>
     * <remarks>Casey Ugone, 7/26/2011.</remarks>
     **************************************************************************************************/
	void UnRegisterMouse();

    /**************************************************************************************************
     * <summary>Enumerates the available resolutions of the adapter at position 0.</summary>
     * <remarks>Casey Ugone, 7/26/2011.</remarks>
     * <remarks>This method is not guaranteed to succeed. If the window is in fullscreen it will always fail.</remarks>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
	bool EnumerateResolutions();

    /**************************************************************************************************
     * <summary>Cleans up after a call to EnumerateResolutions.</summary>
     * <remarks>Casey Ugone, 7/26/2011.</remarks>
     **************************************************************************************************/
	void DenumerateResolutions();

    /**************************************************************************************************
     * <summary>Gets the number of resolutions.</summary>
     * <remarks>Casey Ugone, 7/26/2011.</remarks>
     * <returns>The maximum number of resolutions if EnumerateResolutions() succeeded or zero if it did not.</returns>
     **************************************************************************************************/
	int GetNumResolutions() const;

    /**************************************************************************************************
     * <summary>Gets the resolutions.</summary>
     * <remarks>Casey Ugone, 7/26/2011.</remarks>
     * <returns>null if EnumerateResolutions() failed, else the resolutions.</returns>
     **************************************************************************************************/
    GFX_MODE* GetResolutions() const;

    /**************************************************************************************************
     * <summary>Displays the window to the screen.</summary>
     * <remarks>Casey Ugone, 7/26/2011.</remarks>
     **************************************************************************************************/
    void ShowWindow();

    /**************************************************************************************************
     * <summary>Starts a render operation.</summary>
     * <remarks>Casey Ugone, 7/26/2011.</remarks>
     **************************************************************************************************/
    void StartRender();

    /**************************************************************************************************
     * <summary>Ends a render operation.</summary>
     * <remarks>Casey Ugone, 7/26/2011.</remarks>
     * <remarks>This method assumes the offset coordinate is at (0,0).</remarks>
     **************************************************************************************************/
    void EndRender();


    /**************************************************************************************************
     * <summary>Attempts to set the resolution to the new values.</summary>
     * <remarks>Casey Ugone, 6/21/2014.</remarks>
     * <param name="width"> The width.</param>
     * <param name="height">The height.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    bool RequestResolution(int width, int height);

private:
	/// <summary> windowed mode </summary>
	a2de::GameWindow::WINDOWMODE _window_mode;
	/// <summary> screen dimensions </summary>
	std::pair<int, int> _dimensions;
	/// <summary> The bit-depth </summary>
	int _depth;
	/// <summary> resolution error code number 0 = success.</summary>
	int _resolution;
	/// <summary> The mouse </summary>
	Mouse* _mouse;
	/// <summary> The modes </summary>
	GFX_MODE_LIST* _modes;
	/// <summary> The title </summary>
	std::string _title;
    /// <summary> The backbuffer </summary>
    BITMAP* _backbuffer;

    /**************************************************************************************************
     * <summary>Attempts to set the resolution to the stored value.</summary>
     * <remarks>Casey Ugone, 7/26/2011.</remarks>
     **************************************************************************************************/
	void SetResolution();

};

A2DE_END

#endif
