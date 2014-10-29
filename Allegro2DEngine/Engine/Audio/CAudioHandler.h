/**************************************************************************************************
// file:	Engine\Audio\CAudioHandler.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the audio handler class
 **************************************************************************************************/
#ifndef A2DE_CAUDIOHANDLER_H
#define A2DE_CAUDIOHANDLER_H

#include "../a2de_vals.h"

A2DE_BEGIN

//Inclusion into the AudioHandler namespace prevents old a2de::AudioHandler::Initialize(...) code from breaking.
namespace AudioHandler {

    /**************************************************************************************************
     * <summary>Values that represent the available AUDIOOPTIONS. </summary>
     * <remarks>Casey Ugone, 5/25/2012.</remarks>
     **************************************************************************************************/
    enum AUDIOOPTIONS {
        /// <summary>Neither sound nor music.</summary>
        AUDIO_NONE = 0,
        /// <summary>Sound only. No music.</summary>
        AUDIO_SOUND = 1,
        /// <summary>Music only. No sound.</summary>
        AUDIO_MUSIC = AUDIO_SOUND << 1,
        /// <summary>Both sound and music.</summary>
        AUDIO_BOTH = AUDIO_SOUND | AUDIO_MUSIC,
    };

    /**************************************************************************************************
     * <summary>Initializes the audio drivers.</summary>
     * <remarks>Casey Ugone, 5/25/2012.</remarks>
     * <param name="options">Options for controlling which drivers are initialized.</param>
     * <returns>The maximum number of voices allowed for use by the sound driver.</returns>
     **************************************************************************************************/
    unsigned long Initialize(AudioHandler::AUDIOOPTIONS options);

    /**************************************************************************************************
     * <summary>Uninitializes the sound drivers.</summary>
     * <remarks>Casey Ugone, 5/25/2012.</remarks>
     **************************************************************************************************/
    void Release();

};

A2DE_END

#endif