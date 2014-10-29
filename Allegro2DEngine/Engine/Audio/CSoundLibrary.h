/**************************************************************************************************
// file:	Engine\Audio\CSoundLibrary.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the sound library class
 **************************************************************************************************/
#ifndef A2DE_CSOUNDLIBRARY_H
#define A2DE_CSOUNDLIBRARY_H

#include "../a2de_vals.h"
#include <map>
#include <string>
#include <utility>
#include <vector>
#include "CSound.h"

A2DE_BEGIN

/**************************************************************************************************
 * <summary>Sound library.</summary>
 * <remarks>Casey Ugone, 7/27/2011.</remarks>
 **************************************************************************************************/
class SoundLibrary {

public:

    /**************************************************************************************************
     * <summary>Values that represent DIRECTION. </summary>
     * <remarks>Casey Ugone, 6/24/2012.</remarks>
     **************************************************************************************************/
    enum DIRECTION {
        /// <summary>Play in a forward direction, do not loop.</summary>
        DIR_FORWARD_NONLOOPING = PLAYMODE_FORWARD,
        /// <summary>Play in a forward direction, do loop.</summary>
        DIR_FORWARD_LOOPING = PLAYMODE_FORWARD | PLAYMODE_LOOP,
        /// <summary>Play in a backward direction, do not loop.</summary>
        DIR_BACKWARD_NONLOOPING = PLAYMODE_BACKWARD,
        /// <summary>Play in a backward direction, do loop.</summary>
        DIR_BACKWARD_LOOPING = PLAYMODE_BACKWARD | PLAYMODE_LOOP,
        /// <summary>Play in a forward then backward direction, do loop.</summary>
        DIR_BIDIRECTIONAL_LOOPING = PLAYMODE_BIDIR | PLAYMODE_LOOP,
    };

    /**************************************************************************************************
     * <summary>Creates an instance.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="numVoices">Number of voices.</param>
     * <returns>null if it fails, else.</returns>
     **************************************************************************************************/
	static SoundLibrary* CreateInstance(int numVoices);

    /**************************************************************************************************
     * <summary>Destructor</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     **************************************************************************************************/
	~SoundLibrary();

    /**************************************************************************************************
     * <summary>Adds a sound.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name"> The name of the sound.</param>
     * <param name="sound">[in,out] If non-null, the sound.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    bool AddSound(const std::string& name, Sound* sound);

    /**************************************************************************************************
     * <summary>Removes the sound described by name.</summary>
     * <remarks>Casey Ugone, 2/24/2012.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    bool RemoveSound(const std::string& name);

    /**************************************************************************************************
     * <summary>Loops.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <param name="dir"> The desired direction in which to play the sound.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
    void Loop(const std::string& name, SoundLibrary::DIRECTION dir);

    /**************************************************************************************************
     * <summary>Gets the loop start position.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>The loop start position, if name is invalid, returns -1.</returns>
     **************************************************************************************************/
    long GetLoopStartPos(const std::string& name) const;

    /**************************************************************************************************
     * <summary>Gets the loop start position.</summary>
     * <remarks>Casey Ugone, 6/24/2012.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>The loop start position, if name is invalid, returns -1.</returns>
     **************************************************************************************************/
    long GetLoopStartPos(const std::string& name);

    /**************************************************************************************************
     * <summary>Gets the loop end position.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>The loop end position, if name is invalid, returns -1.</returns>
     **************************************************************************************************/
    long GetLoopEndPos(const std::string& name) const;

    /**************************************************************************************************
     * <summary>Gets a loop end position.</summary>
     * <remarks>Casey Ugone, 6/24/2012.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>The loop end position, if name is invalid, returns -1.</returns>
     **************************************************************************************************/
    long GetLoopEndPos(const std::string& name);

    /**************************************************************************************************
     * <summary>Sets the loop start position.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <param name="pos"> The position.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
    void SetLoopStartPos(const std::string& name, long pos);

    /**************************************************************************************************
     * <summary>Sets a loop end position.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <param name="pos"> The position.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
    void SetLoopEndPos(const std::string& name, long pos);

    /**************************************************************************************************
     * <summary>Plays the Sound using the current Loop Start, Loop End, Pan, Position, Volume, Frequency, and PLAYMODE settings.
     * Default PLAYMODE settings are FORWARD flag set and LOOP flag cleared.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound to play.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
    void Play(const std::string& name);

    /**************************************************************************************************
     * <summary>Query if 'name' is playing.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>true if playing, false if not or the sound name is invalid.</returns>
     **************************************************************************************************/
	bool IsPlaying(const std::string& name) const;

    /**************************************************************************************************
     * <summary>Stops a sound. Subsequent calls to Play will resume at the Loop Start position.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
	void Stop(const std::string& name);

    /**************************************************************************************************
     * <summary>Restarts a sound from the Loop Start position.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
    void Restart(const std::string& name);

    /**************************************************************************************************
     * <summary>Pauses a sound. Subsequent calls to Play will resume at the current position.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
    void Pause(const std::string& name);

    /**************************************************************************************************
     * <summary>Gets a sound's length in samples.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>The length, if name is invalid, returns -1.</returns>
     **************************************************************************************************/
    long GetLength(const std::string& name) const;

    /**************************************************************************************************
     * <summary>Gets a sound's length in samples.</summary>
     * <remarks>Casey Ugone, 6/24/2012.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>The length, if name is invalid, returns -1.</returns>
     **************************************************************************************************/
    long GetLength(const std::string& name);

    /**************************************************************************************************
     * <summary>Gets a sound's length in seconds.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>The length in seconds, if name is invalid, returns -1.0.</returns>
     **************************************************************************************************/
    double GetLengthInSeconds(const std::string& name) const;

    /**************************************************************************************************
     * <summary>Gets a sound's length in seconds.</summary>
     * <remarks>Casey Ugone, 6/24/2012.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>The length in seconds, if name is invalid, returns -1.0.</returns>
     **************************************************************************************************/
    double GetLengthInSeconds(const std::string& name);

    /**************************************************************************************************
     * <summary>Gets a sound's current position in samples.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>The position in samples, if name is invalid, returns -1.</returns>
     **************************************************************************************************/
    long GetPosition(const std::string& name) const;

    /**************************************************************************************************
     * <summary>Gets a sound's current position in samples.</summary>
     * <remarks>Casey Ugone, 6/24/2012.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>The position, if name is invalid, returns -1.</returns>
     **************************************************************************************************/
    long GetPosition(const std::string& name);

    /**************************************************************************************************
     * <summary>Sets a sound's current position in samples.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <param name="pos"> The position in samples.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
    void SetPosition(const std::string& name, unsigned long pos);

    /**************************************************************************************************
     * <summary>Gets a sound's elapsed position in samples.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>The elapsed position in samples, if name is invalid, returns -1.</returns>
     **************************************************************************************************/
    long GetElapsed(const std::string& name) const;

    /**************************************************************************************************
     * <summary>Gets a sound's elapsed position in samples.</summary>
     * <remarks>Casey Ugone, 6/24/2012.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>The elapsed position in samples, if name is invalid, returns -1.</returns>
     **************************************************************************************************/
    long GetElapsed(const std::string& name);

    /**************************************************************************************************
     * <summary>Gets a sound's remaining position in samples.</summary>
     * <remarks>Casey Ugone, 7/30/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>The remaining samples until the end of the sound, if name is invalid, returns -1.</returns>
     **************************************************************************************************/
    long GetRemaining(const std::string& name) const;

    /**************************************************************************************************
     * <summary>Gets a sound's remaining position in samples.</summary>
     * <remarks>Casey Ugone, 6/24/2012.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>The remaining samples until the end of the sound, if name is invalid, returns -1.</returns>
     **************************************************************************************************/
    long GetRemaining(const std::string& name);

    /**************************************************************************************************
     * <summary>Gets a sound's elapsed position in seconds.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>The elapsed position in seconds, if name is invalid or the sound is not playing, returns -1.0.</returns>
     **************************************************************************************************/
    double GetElapsedInSeconds(const std::string& name) const;

    /**************************************************************************************************
     * <summary>Gets a sound's elapsed position in seconds.</summary>
     * <remarks>Casey Ugone, 6/24/2012.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>The elapsed in seconds, if name is invalid or the sound is not playing, returns -1.0.</returns>
     **************************************************************************************************/
    double GetElapsedInSeconds(const std::string& name);

    /**************************************************************************************************
     * <summary>Gets a sound's remaining position in seconds.</summary>
     * <remarks>Casey Ugone, 7/30/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>The remaining seconds, if name is invalid or the sound is not playing, returns -1.0.</returns>
     **************************************************************************************************/
    double GetRemainingInSeconds(const std::string& name) const;

    /**************************************************************************************************
     * <summary>Gets a sound's remaining position in seconds.</summary>
     * <remarks>Casey Ugone, 6/24/2012.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>The remaining in seconds, if name is invalid or the sound is not playing, returns -1.0.</returns>
     **************************************************************************************************/
    double GetRemainingInSeconds(const std::string& name);

    /**************************************************************************************************
     * <summary>Gets a sound's current pan setting.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>The pan setting, if name is invalid or the sound is not playing, returns -1.</returns>
     **************************************************************************************************/
    int GetPan(const std::string& name) const;

    /**************************************************************************************************
     * <summary>Gets a sound's current pan setting.</summary>
     * <remarks>Casey Ugone, 6/24/2012.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>The pan, if name is invalid or the sound is not playing, returns -1.</returns>
     **************************************************************************************************/
    int GetPan(const std::string& name);

    /**************************************************************************************************
     * <summary>Sets a pan.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <param name="pan"> The pan setting.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
    void SetPan(const std::string& name, unsigned char pan);

    /**************************************************************************************************
     * <summary>Sets a pan left.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
    void SetPanLeft(const std::string& name);

    /**************************************************************************************************
     * <summary>Sets a pan center.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
    void SetPanCenter(const std::string& name);

    /**************************************************************************************************
     * <summary>Sets a pan right.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
    void SetPanRight(const std::string& name);

    /**************************************************************************************************
     * <summary>Sets a pan left-center.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
    void SetPanLeftCenter(const std::string& name);

    /**************************************************************************************************
     * <summary>Sets a pan right-center.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
    void SetPanRightCenter(const std::string& name);

    /**************************************************************************************************
     * <summary>Starts a pan sweep.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">        The name of the sound.</param>
     * <param name="timeperiodMS">The timeperiod in milliseconds.</param>
     * <param name="endPos">      The end position.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
    void StartPanSweep(const std::string& name, int timeperiodMS, Sound::PAN endPos);

    /**************************************************************************************************
     * <summary>Stop a pan sweep.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
    void StopPanSweep(const std::string& name);

    /**************************************************************************************************
     * <summary>Gets a sound's volume.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>The volume, if name is invalid, returns 0.</returns>
     **************************************************************************************************/
    unsigned char GetVolume(const std::string& name) const;

    /**************************************************************************************************
     * <summary>Gets a sound's volume.</summary>
     * <remarks>Casey Ugone, 6/24/2012.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>The volume, if name is invalid, returns 0.</returns>
     **************************************************************************************************/
    unsigned char GetVolume(const std::string& name);

    /**************************************************************************************************
     * <summary>Sets a sound's volume.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <param name="vol"> The volume.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
    void SetVolume(const std::string& name, unsigned char vol);

    /**************************************************************************************************
     * <summary>Increase volume.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
	void IncreaseVolume(const std::string& name);

    /**************************************************************************************************
     * <summary>Decrease volume.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
	void DecreaseVolume(const std::string& name);

    /**************************************************************************************************
     * <summary>Starts a volume ramp.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">        The name of the sound.</param>
     * <param name="timeperiodMS">The timeperiod in milliseconds.</param>
     * <param name="endVol">      The end volume.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
    void StartVolumeRamp(const std::string& name, int timeperiodMS, unsigned char endVol);

    /**************************************************************************************************
     * <summary>Stops a volume ramp.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
    void StopVolumeRamp(const std::string& name);

    /**************************************************************************************************
     * <summary>Increase frequency.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
    void IncreaseFrequency(const std::string& name);

    /**************************************************************************************************
     * <summary>Decrease frequency.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
    void DecreaseFrequency(const std::string& name);

    /**************************************************************************************************
     * <summary>Gets a sound's current frequency.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>The frequency, if name is invalid, returns -1.</returns>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
    int GetFrequency(const std::string& name) const;

    /**************************************************************************************************
     * <summary>Gets a sound's current frequency.</summary>
     * <remarks>Casey Ugone, 6/24/2012.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>The frequency, if name is invalid, returns -1.</returns>
     **************************************************************************************************/
    int GetFrequency(const std::string& name);

    /**************************************************************************************************
     * <summary>Sets a frequency.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <param name="Hz">  The hertz, that is, samples per second.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
    void SetFrequency(const std::string& name, int Hz);

    /**************************************************************************************************
     * <summary>Resets the frequency to the default value, usually 8000 samples per second.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
    void ResetFrequency(const std::string& name);

    /**************************************************************************************************
     * <summary>Starts a frequency sweep.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">        The name of the sound.</param>
     * <param name="timeperiodMS">The timeperiod in milliseconds.</param>
     * <param name="endHz">       The end hertz, that is, samples per second.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
    void StartFrequencySweep(const std::string& name, int timeperiodMS, int endHz);

    /**************************************************************************************************
     * <summary>Stops a frequency sweep.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <param name="name">The name of the sound.</param>
     * <remarks>If name is invalid, does nothing.</remarks>
     **************************************************************************************************/
    void StopFrequencySweep(const std::string& name);

protected:
private:
    /// <summary> Number of voices </summary>
    int _numVoices;
    /// <summary> The allocated voices </summary>
    std::map<std::string, std::pair<int, Sound*> >* _mvoices;
    /// <summary> The maximum voices </summary>
    static const int MAX_VOICES;
    /// <summary> The volume step </summary>
    static const double VOLUME_STEP;
    /// <summary> The frequency step </summary>
    static const double FREQUENCY_STEP;

    //Must use named constructor!

    /**************************************************************************************************
     * <summary>Initializes a new instance of the SoundLibrary class.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <remarks>Must use named constructor.</remarks>
     * <param name="numVoices">Number of voices.</param>
     **************************************************************************************************/
    SoundLibrary(int numVoices);

    /**************************************************************************************************
     * <summary>Initializes a new instance of the SoundLibrary class.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <remarks>NO COPYING ALLOWED!</remarks>
     * <param name="">.</param>
     **************************************************************************************************/
    SoundLibrary(const SoundLibrary&);

    /**************************************************************************************************
     * <summary>Assignment operator.</summary>
     * <remarks>Casey Ugone, 7/27/2011.</remarks>
     * <remarks>NO COPYING ALLOWED!</remarks>
     * <param name="">.</param>
     * <returns>A shallow copy of this object.</returns>
     **************************************************************************************************/
    SoundLibrary* operator=(const SoundLibrary&);

    /**************************************************************************************************
     * <summary>Verifies that the named song exists in memory.</summary>
     * <remarks>Casey Ugone, 6/24/2012.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    bool Verify(const std::string& name) const;

    /**************************************************************************************************
     * <summary>Gets index of the song by the given name.</summary>
     * <remarks>Casey Ugone, 6/24/2012.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>The index of.</returns>
     **************************************************************************************************/
    int GetIndexOf(const std::string& name) const;

    /**************************************************************************************************
     * <summary>Gets the sound specified by the given name.</summary>
     * <remarks>Casey Ugone, 6/24/2012.</remarks>
     * <param name="name">The name of the sound.</param>
     * <returns>null if it fails, else the sound at.</returns>
     **************************************************************************************************/
    Sound* GetSoundAt(const std::string& name) const;

};

A2DE_END

#endif