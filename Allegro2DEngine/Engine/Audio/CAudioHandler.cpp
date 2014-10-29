/**************************************************************************************************
// file:	Engine\Audio\CAudioHandler.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the audio handler class
 **************************************************************************************************/
#include "CAudioHandler.h"

#include "../a2de_exceptions.h"

#include <allegro/sound.h>
#include <allegro/midi.h>

A2DE_BEGIN

namespace AudioHandler {

unsigned long Initialize(AudioHandler::AUDIOOPTIONS options) {
    if((options | AUDIO_NONE) == 0) return 0;

    unsigned long numVoices = 0;
    int selected_sound_driver = DIGI_NONE;
    int selected_midi_driver = MIDI_NONE;
    if(options & AUDIO_SOUND) {
        selected_sound_driver = DIGI_AUTODETECT;
        if((numVoices = detect_digi_driver(DIGI_AUTODETECT)) == 0) {
            throw AudioNotAvailableException();
        }
    }
    if(options & AUDIO_MUSIC) {
        selected_midi_driver = MIDI_AUTODETECT;
        if(detect_midi_driver(MIDI_AUTODETECT) == 0) {
            throw AudioNotAvailableException();
        }
    }
    if(install_sound(selected_sound_driver, selected_midi_driver, nullptr) == -1) {
        throw AudioNotAvailableException();
    }
	return numVoices;
}

void Release() {
	remove_sound();
}

}

A2DE_END