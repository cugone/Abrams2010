/**************************************************************************************************
// file:	Engine\Audio\CSound.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the sound class
 **************************************************************************************************/
#ifndef A2DE_CSOUND_H
#define A2DE_CSOUND_H

#include "../a2de_vals.h"
#include <string>
#include <allegro/sound.h>

A2DE_BEGIN

/**************************************************************************************************
 * <summary>Sound.</summary>
 * <remarks>Casey Ugone, 7/27/2011.</remarks>
 **************************************************************************************************/
class Sound {

public:

    /*******************************************************************************
     * <summary>Values that represent panning sequences. </summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
    *******************************************************************************/
    enum PAN {
        /// <summary>Panned fully to Left speaker</summary>
        PAN_LEFT = 0x00,
        /// <summary>Centered between Left and Center speakers</summary>
        PAN_LEFT_CENTER = 0x40,
        /// <summary>Centered between Left and Right speakers (or to Center Speaker)</summary>
        PAN_CENTER = 0x80,
        /// <summary>Centered between Center and Right speakers</summary>
        PAN_RIGHT_CENTER = 0xC0,
        /// <summary>Panned fully to Right speaker</summary>
        PAN_RIGHT = 0xFF,
    };

    /// <summary> The minimum pitch </summary>
    static const int PITCH_MIN;
    /// <summary> The default pitch </summary>
    static const int PITCH_DEFAULT;
    /// <summary> The maximum pitch </summary>
    static const int PITCH_MAX;

    /// <summary> The minimum volume </summary>
    static const unsigned char VOLUME_MIN;
    /// <summary> The middle volume </summary>
    static const unsigned char VOLUME_MID;
    /// <summary> The maximum volume </summary>
    static const unsigned char VOLUME_MAX;

    /**************************************************************************************************
     * <summary>Creates a sound.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="file">The file.</param>
     * <returns>null if it fails, else.</returns>
     **************************************************************************************************/
    static Sound* CreateSound(const std::string& file);

    /**************************************************************************************************
     * <summary>Destructor.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     **************************************************************************************************/
    ~Sound();

    /**************************************************************************************************
     * <summary>Gets the filename.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <returns>The filename.</returns>
     **************************************************************************************************/
	const std::string& GetFilename() const;

    /**************************************************************************************************
     * <summary>Gets the filename.</summary>
     * <remarks>Casey Ugone, 3/13/2014.</remarks>
     * <returns>The filename.</returns>
     **************************************************************************************************/
    std::string& GetFilename();

    /**************************************************************************************************
     * <summary>Gets the volume.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <returns>The volume.</returns>
     **************************************************************************************************/
    int GetVolume() const;

    /**************************************************************************************************
     * <summary>Gets the volume.</summary>
     * <remarks>Casey Ugone, 3/13/2014.</remarks>
     * <returns>The volume.</returns>
     **************************************************************************************************/
    int GetVolume();

    /**************************************************************************************************
     * <summary>Gets the pan.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <returns>The pan.</returns>
     **************************************************************************************************/
    int GetPan() const;

    /**************************************************************************************************
     * <summary>Gets the pan.</summary>
     * <remarks>Casey Ugone, 3/13/2014.</remarks>
     * <returns>The pan.</returns>
     **************************************************************************************************/
    int GetPan();

    /**************************************************************************************************
     * <summary>Gets the pitch.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <returns>The pitch.</returns>
     **************************************************************************************************/
    int GetPitch() const;

    /**************************************************************************************************
     * <summary>Gets the pitch.</summary>
     * <remarks>Casey Ugone, 3/13/2014.</remarks>
     * <returns>The pitch.</returns>
     **************************************************************************************************/
    int GetPitch();

    /**************************************************************************************************
     * <summary>Gets the bit rate.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <returns>The bit rate.</returns>
     **************************************************************************************************/
    int GetBitRate() const;

    /**************************************************************************************************
     * <summary>Gets bit rate.</summary>
     * <remarks>Casey Ugone, 3/13/2014.</remarks>
     * <returns>The bit rate.</returns>
     **************************************************************************************************/
    int GetBitRate();

    /**************************************************************************************************
     * <summary>Gets the sample.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <returns>null if it fails, else the sample.</returns>
     **************************************************************************************************/
    const SAMPLE* GetSample() const;

    /**************************************************************************************************
     * <summary>Gets the sample.</summary>
     * <remarks>Casey Ugone, 3/13/2014.</remarks>
     * <returns>null if it fails, else the sample.</returns>
     **************************************************************************************************/
    SAMPLE* GetSample();

    /**************************************************************************************************
     * <summary>Change the sample mid-playback.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="file">The file.</param>
     **************************************************************************************************/
	void ChangeSample(const std::string& file);

    /**************************************************************************************************
     * <summary>Sets the volume.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="volume">The volume where { volume | 0 &lt; volume &lt;= 255 }</param>
     **************************************************************************************************/
    void SetVolume(unsigned char volume);

    /**************************************************************************************************
     * <summary>Sets the pan to a user-defined location.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="pan">The pan where { pan | 0 &lt; pan &lt;= 255 }</param>
     **************************************************************************************************/
    void SetPan(unsigned char pan);
    
    /**************************************************************************************************
     * <summary>Sets the pan to a pre-defined location.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="pan">The pan where { pan | pan = LEFT|LEFT_CENTER|CENTER|RIGHT_CENTER|RIGHT }</param>
     **************************************************************************************************/
    void SetPan(Sound::PAN pan);

    /**************************************************************************************************
     * <summary>Sets the pitch.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="pitch">The pitch where { pitch | MIN_PITCH &lt;= pitch &lt;= MAX_PITCH }</param>
     **************************************************************************************************/
    void SetPitch(int pitch);

    /**************************************************************************************************
     * <summary>Sets a loop.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="loop">true to loop.</param>
     **************************************************************************************************/
    void SetLoop(bool loop);

    /**************************************************************************************************
     * <summary>Queries if we can loop.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    bool CanLoop();

    /**************************************************************************************************
     * <summary>Plays this object.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     **************************************************************************************************/
    void Play();

    /**************************************************************************************************
     * <summary>Stops this object.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     **************************************************************************************************/
    void Stop();

private:

    /**************************************************************************************************
     * <summary>Initializes a new instance of the Sound class.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="file">The file.</param>
     **************************************************************************************************/
    Sound(const std::string& file);
    /// <summary> The filename </summary>
    std::string _file;
    /// <summary> The volume setting </summary>
    int _volume;
    /// <summary> The pan setting </summary>
    int _pan;
    /// <summary> The pitch setting </summary>
    int _pitch;
    /// <summary> The allocated sample </summary>
    SAMPLE* _sample;
    /// <summary> The stereo setting </summary>
    bool _stereo;
    /// <summary> The loop setting </summary>
    bool _loop;
    /// <summary> The bitrate </summary>
    int _bitrate;
};

A2DE_END

#endif