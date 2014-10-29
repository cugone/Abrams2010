/**************************************************************************************************
// file:	Engine\Games\ADTGame.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the Game abstract data type.
 **************************************************************************************************/
#ifndef A2DE_ADTGAME_H
#define A2DE_ADTGAME_H

#include "../a2de_vals.h"
#include "../GFX/CGameWindow.h"
#include "../Time/CStopwatch.h"

A2DE_BEGIN

class Game {
public:

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     * <param name="window">The window to attach to this game. !The game will take ownership of the pointer!</param>
     **************************************************************************************************/
    Game(a2de::GameWindow* window);

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     * <param name="frame_rate">    The number of frames per second in frames.</param>
     * <param name="max_frame_time">The maximum allowed time between frames in seconds.</param>
     * <param name="window">The window to attach to this game. !The game will take ownership of the pointer!</param>
     **************************************************************************************************/
    Game(double frame_rate, double max_frame_time, a2de::GameWindow* window);

    /**************************************************************************************************
     * <summary>Destructor.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     **************************************************************************************************/
    virtual ~Game();

    /**************************************************************************************************
     * <summary>Runs the game.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     **************************************************************************************************/
    void Run(int argc, char** argv);

    /**************************************************************************************************
     * <summary>Initialization phase method. A method to set up any variables, etc. before the main loop starts.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Initialize(int argc, char** argv)=0;

    /**************************************************************************************************
     * <summary>Processing phase method. This method is called as many times as needed per frame to keep the frame rate as close to the defined frame rate as
     * possible.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     * <param name="gameTime"> The elapsed time of the game.</param>
     * <param name="deltaTime">The time between frames in seconds.</param>
     **************************************************************************************************/
    virtual void Processing(a2de::StopWatch& gameTime, double deltaTime)=0;

    /**************************************************************************************************
     * <summary>Rendering phase method. This method is called once per frame.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     * <param name="gameTime"> Time of the game.</param>
     * <param name="deltaTime">Time since the last frame.</param>
     **************************************************************************************************/
    virtual void Render(a2de::StopWatch& gameTime, double deltaTime)=0;

    /**************************************************************************************************
     * <summary>Clean up phase method. This method is called after the game loop to free up any memory. The user is responsible for deleting any
     * heap-allocated variables from Initialize here.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     **************************************************************************************************/
    virtual void CleanUp()=0;

    /**************************************************************************************************
     * <summary>Gets the game window.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     * <returns>null if it fails, else the window.</returns>
     **************************************************************************************************/
    a2de::GameWindow* GetWindow() const;

    /**************************************************************************************************
     * <summary>Gets the game window.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     * <returns>null if it fails, else the window.</returns>
     **************************************************************************************************/
    a2de::GameWindow* GetWindow();

    /**************************************************************************************************
     * <summary>Quits the game.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     **************************************************************************************************/
    void Quit();

    /**************************************************************************************************
     * <summary>Query if the game is quitting.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     * <returns>true if quitting, false if not.</returns>
     **************************************************************************************************/
    bool IsQuitting() const;

    /**************************************************************************************************
     * <summary>Query if the game is quitting.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     * <returns>true if quitting, false if not.</returns>
     **************************************************************************************************/
    bool IsQuitting();

    /**************************************************************************************************
     * <summary>Gets the elapsed time the game window has been open.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     * <returns>The game time.</returns>
     **************************************************************************************************/
    const a2de::StopWatch& GetGameTime() const;

    /**************************************************************************************************
     * <summary>Gets the elapsed time the game window has been open.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     * <returns>The game time.</returns>
     **************************************************************************************************/
    a2de::StopWatch& GetGameTime();

protected:
private:

    /**************************************************************************************************
     * <summary>Main loop.</summary>
     * <remarks>Casey Ugone, 11/23/2013.</remarks>
     **************************************************************************************************/
    void MainLoop();

    /**************************************************************************************************
     * <summary>Initialises the gamewindow for use.</summary>
     * <remarks>Casey Ugone, 11/23/2013.</remarks>
     * <param name="window">[in,out] If non-null, the window.</param>
     **************************************************************************************************/
    void init(a2de::GameWindow* window);

    /**************************************************************************************************
     * <summary>Uninitialises the gamewindow.</summary>
     * <remarks>Casey Ugone, 11/23/2013.</remarks>
     **************************************************************************************************/
    void deinit();

    /// <summary> The time between frames in seconds.</summary>
    double _FRAME_RATE;
    /// <summary> Maximum allowed time between frames </summary>
    double _MAX_FRAME_TIME;
    /// <summary> Time since the last frame.</summary>
    double _deltaTime;
    /// <summary> Elapsed game time</summary>
    a2de::StopWatch _gameTime;
    /// <summary> The game window </summary>
    a2de::GameWindow* _gameWindow;
    /// <summary> true if is quitting </summary>
    bool _isQuitting;

};

A2DE_END

#endif