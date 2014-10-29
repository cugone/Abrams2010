/**************************************************************************************************
// file:	Engine\Audio\CMusic.h
// Allegro2DEngine
// Copyright (c) 2012 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for support.
// summary:	Declares the music class
 **************************************************************************************************/
#ifndef A2DE_CMUSIC_H
#define A2DE_CMUSIC_H

#include "../a2de_vals.h"
#include <string>
#include <allegro/midi.h>

A2DE_BEGIN

/**************************************************************************************************
 * <summary>Music.</summary>
 * <remarks>Casey Ugone, 7/27/2011.</remarks>
 **************************************************************************************************/
class Music {
    public:

        /**************************************************************************************************
         * <summary>Creates a music object.</summary>
         * <remarks>Casey Ugone, 7/26/2011.</remarks>
         * <param name="file">The file.</param>
         * <param name="loop">true to loop.</param>
         * <returns>null if it fails, else.</returns>
         **************************************************************************************************/
        static Music* CreateMusic(std::string file, bool loop);

        /**************************************************************************************************
         * <summary>Destructor.</summary>
         * <remarks>Casey Ugone, 7/26/2011.</remarks>
         **************************************************************************************************/
        ~Music();

        /**************************************************************************************************
         * <summary>Gets the filename.</summary>
         * <remarks>Casey Ugone, 7/26/2011.</remarks>
         * <returns>The filename.</returns>
         **************************************************************************************************/
        std::string GetFilename() const;

        /**************************************************************************************************
         * <summary>Gets the filename.</summary>
         * <remarks>Casey Ugone, 6/29/2012.</remarks>
         * <returns>The filename.</returns>
         **************************************************************************************************/
        std::string GetFilename();

        /**************************************************************************************************
         * <summary>Gets the midi.</summary>
         * <remarks>Casey Ugone, 7/26/2011.</remarks>
         * <returns>null if it fails, else the midi.</returns>
         **************************************************************************************************/
        MIDI* GetMidi() const;

        /**************************************************************************************************
         * <summary>Gets the midi.</summary>
         * <remarks>Casey Ugone, 6/29/2012.</remarks>
         * <returns>null if it fails, else the midi.</returns>
         **************************************************************************************************/
        MIDI* GetMidi();

        /**************************************************************************************************
         * <summary>Query if this object is playing.</summary>
         * <remarks>Casey Ugone, 7/26/2011.</remarks>
         * <returns>true if playing, false if not.</returns>
         **************************************************************************************************/
        bool IsPlaying();

        /**************************************************************************************************
         * <summary>Query if this object is looped.</summary>
         * <remarks>Casey Ugone, 7/26/2011.</remarks>
         * <returns>true if looped, false if not.</returns>
         **************************************************************************************************/
        bool IsLooped();

        /**************************************************************************************************
         * <summary>Query if this object has ended.</summary>
         * <remarks>Casey Ugone, 7/26/2011.</remarks>
         * <returns>true if ended, false if not.</returns>
         **************************************************************************************************/
		bool HasEnded();

        /**************************************************************************************************
         * <summary>Sets the midi to loop.</summary>
         * <remarks>Casey Ugone, 7/26/2011.</remarks>
         * <param name="loop">true to loop.</param>
         **************************************************************************************************/
        void SetLooped(bool loop);

        /**************************************************************************************************
         * <summary>Change midi to a different song. Can be changed mid-playback.</summary>
         * <remarks>Casey Ugone, 7/26/2011.</remarks>
         * <param name="midi">[in,out] If non-null, the midi.</param>
         **************************************************************************************************/
        void ChangeMidi(MIDI* midi);

        /**************************************************************************************************
         * <summary>Plays or Restarts this object.</summary>
         * <remarks>Casey Ugone, 7/26/2011.</remarks>
         **************************************************************************************************/
        void Play();

        /**************************************************************************************************
         * <summary>Stops this object.</summary>
         * <remarks>Casey Ugone, 7/26/2011.</remarks>
         **************************************************************************************************/
        void Stop();

        /**************************************************************************************************
         * <summary>Pauses or Unpauses this object.</summary>
         * <remarks>Casey Ugone, 7/26/2011.</remarks>
         **************************************************************************************************/
        void Pause();

        /**************************************************************************************************
         * <summary>Gets the position in beats.</summary>
         * <remarks>Casey Ugone, 7/26/2011.</remarks>
         * <returns>The position in beats.</returns>
         **************************************************************************************************/
		long GetPositionInBeats();

        /**************************************************************************************************
         * <summary>Gets the current position in seconds.</summary>
         * <remarks>Casey Ugone, 7/26/2011.</remarks>
         * <returns>The position seconds.</returns>
         **************************************************************************************************/
		long GetPositionInSeconds();

        /**************************************************************************************************
         * <summary>Gets the length as beats.</summary>
         * <remarks>Casey Ugone, 7/26/2011.</remarks>
         * <returns>The length as beats.</returns>
         **************************************************************************************************/
		long GetLengthInBeats();

        /**************************************************************************************************
         * <summary>Gets the length as seconds.</summary>
         * <remarks>Casey Ugone, 7/26/2011.</remarks>
         * <returns>The length as seconds.</returns>
         **************************************************************************************************/
		long GetLengthInSeconds();

private:

    /**************************************************************************************************
     * <summary>Initializes a new instance of the Music class.</summary>
     * <remarks>Casey Ugone, 7/26/2011.</remarks>
     * <param name="file">The file.</param>
     * <param name="loop">true to loop.</param>
     **************************************************************************************************/
    Music(std::string file, bool loop);

    /// <summary> The filename </summary>
    std::string _file;
    /// <summary> The allocated midi </summary>
    MIDI* _midi;
    /// <summary> true if set to loop </summary>
    bool _loop;
    /// <summary> true if is paused </summary>
    bool _isPaused;
    /// <summary> The position in beats </summary>
    long _positionBeats;
    /// <summary> The position in seconds </summary>
    long _positionSecs;
    /// <summary> The length in seconds </summary>
    long _lengthSecs;
    /// <summary> The length in beats </summary>
    long _lengthBeats;
    /// <summary> The previous position in beats </summary>
    long _prevpositionBeats;
    /// <summary> The previous position in seconds </summary>
    long _prevpositionSecs;

    /**************************************************************************************************
     * <summary>Updates this object.</summary>
     * <remarks>Casey Ugone, 7/26/2011.</remarks>
     **************************************************************************************************/
    void Update();

    /**************************************************************************************************
     * <summary>Sets a midi.</summary>
     * <remarks>Casey Ugone, 7/26/2011.</remarks>
     * <param name="midi">[in,out] If non-null, the midi.</param>
     **************************************************************************************************/
    void SetMidi(MIDI* midi);

};

A2DE_END

#endif
