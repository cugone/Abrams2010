/**************************************************************************************************
// file:	Engine\Audio\CSoundTrack.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the sound track class
 **************************************************************************************************/
#ifndef A2DE_CSOUNDTRACK_H
#define A2DE_CSOUNDTRACK_H

#include "../a2de_vals.h"
#include <vector>
#include <iostream>

A2DE_BEGIN

class Music;

/**************************************************************************************************
 * <summary>Soundtrack.</summary>
 * <remarks>Casey Ugone, 7/27/2011.</remarks>
 **************************************************************************************************/
class Soundtrack {

public:

    /**************************************************************************************************
     * <summary>Values that represent REPEATTYPE.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     **************************************************************************************************/
    enum REPEATTYPE {
	    /// <summary>Song does not repeat.</summary>
	    REPEAT_OFF = 0,
	    /// <summary>Currently playing song repeats.</summary>
	    REPEAT_ONE = 1,
	    /// <summary>After the last song has finished, play begins from the first song.</summary>
	    REPEAT_ALL = 2,
    };

    /**************************************************************************************************
     * <summary>Creates the instance of a soundtrack.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <returns>null if it fails, else a pointer to the soundtrack object.</returns>
     **************************************************************************************************/
	static Soundtrack* CreateInstance();

    /**************************************************************************************************
     * <summary>Destructor</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     **************************************************************************************************/
	~Soundtrack();

    /**************************************************************************************************
     * <summary>Gets the current track number.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <returns>The current track number.</returns>
     **************************************************************************************************/
	long GetCurrentTrackNumber();

    /**************************************************************************************************
     * <summary>Adds a track.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="track">[in,out] If non-null, the track. The track must be a pointer created with Music::CreateMusic(...) that SoundTrack will take ownership
     * of.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    bool AddTrack(Music* track);

    /**************************************************************************************************
     * <summary>Removes the track described by index, and deallocates its memory.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="index">Zero-based index of the track.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
	bool RemoveTrack(long index);

    /**************************************************************************************************
     * <summary>Skip to the next track, continuing to the first track if necessary.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     **************************************************************************************************/
	void SkipNext();

    /**************************************************************************************************
     * <summary>Skip to the previous track, continuing to the last track if necessary.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     **************************************************************************************************/
    void SkipPrevious();

    /**************************************************************************************************
     * <summary>Gets the music object at the specified index.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="index">Zero-based index of the music object.</param>
     * <returns>null if it fails, else the music at index.</returns>
     **************************************************************************************************/
    Music* GetMusicAt(long index);

    /**************************************************************************************************
     * <summary>Gets the total number of tracks.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <returns>The number of tracks.</returns>
     **************************************************************************************************/
	long GetSize();

    /**************************************************************************************************
     * <summary>Gets the current track.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <returns>null if it fails, else the current track.</returns>
     **************************************************************************************************/
    Music* GetCurrentTrack();

    /**************************************************************************************************
     * <summary>Sets the repeat setting to the next value in the enumeration. Sets to OFF if the previous setting was ALL.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     **************************************************************************************************/
	void Repeat();

    /**************************************************************************************************
     * <summary>Sets the repeat setting to a specific predefined value.</summary>
     * <remarks>Casey Ugone, 6/3/2012.</remarks>
     * <param name="setting">The value to set the repeat setting to.</param>
     **************************************************************************************************/
    void Repeat(Soundtrack::REPEATTYPE setting);

    /**************************************************************************************************
     * <summary>Gets the repeat setting.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <returns>The repeat setting.</returns>
     **************************************************************************************************/
	Soundtrack::REPEATTYPE GetRepeatSetting();

    /**************************************************************************************************
     * <summary>Plays the track at the current track index.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     **************************************************************************************************/
    void Play();

    /**************************************************************************************************
     * <summary>Stops the currently playing Music object.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     **************************************************************************************************/
    void Stop();

    /**************************************************************************************************
     * <summary>Pauses or Unpauses the currently playing Music object.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     **************************************************************************************************/
    void Pause();

protected:
private:
    /// <summary> The allocated tracks </summary>
    std::vector<Music*>* _tracks;
    /// <summary> The current track </summary>
    long _curTrack;
    /// <summary> The singleton instance </summary>
    static Soundtrack* _instance;
    /// <summary> The repeat setting</summary>
    Soundtrack::REPEATTYPE _repeat;
    /// <summary> true if paused </summary>
    bool _isPaused;
    /// <summary> true if currently playing </summary>
    bool _isPlaying;

    /**************************************************************************************************
     * <summary>Initializes a new instance of the Soundtrack class.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     **************************************************************************************************/
    Soundtrack();

};

A2DE_END

#endif