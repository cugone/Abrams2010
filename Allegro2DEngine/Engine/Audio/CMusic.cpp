/**************************************************************************************************
// file:	Engine\Audio\CMusic.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the music class
 **************************************************************************************************/
#include "CMusic.h"

#include <allegro/file.h>
#include <string>
#include "../a2de_exceptions.h"

A2DE_BEGIN


Music* Music::CreateMusic(std::string file, bool loop) {
    TypeNotSupportedException::RegisterFileType("mid");

    if(exists(file.c_str()) == false) throw FileNotFoundException(file);
    if(TypeNotSupportedException::CheckFileType(get_extension(file.c_str())) == false)
        throw TypeNotSupportedException(std::string(get_extension(file.c_str())));
    if(file.find('#', 0) != std::string::npos)
        throw TypeNotSupportedException("PACKFILE");
    return (new Music(file, loop));
}

Music::Music(std::string file, bool loop) {
    _midi = load_midi(file.c_str());
	_file = file;
    _loop = loop;
    _isPaused = false;
    _lengthBeats = get_midi_length(_midi);
    _lengthSecs = midi_time;
    _positionBeats = midi_pos;
    _positionSecs = midi_time;
    _prevpositionBeats = 0;
    _prevpositionSecs = 0;
}

Music::~Music() {
    if(_midi) {
        destroy_midi(_midi);
        _midi = nullptr;
        _loop = false;
        _isPaused = false;
        _lengthBeats = 0;
        _lengthSecs = 0;
        _positionBeats = 0;
        _positionSecs = 0;
		_prevpositionBeats = 0;
		_prevpositionSecs = 0;
    }
}

MIDI* Music::GetMidi() const {
      return _midi;
}

MIDI* Music::GetMidi() {
    return static_cast<const Music&>(*this).GetMidi();
}

void Music::SetMidi(MIDI* midi) {
    _midi = midi;
    _lengthBeats = get_midi_length(_midi);
    _lengthSecs = midi_time;
    _positionBeats = midi_pos;
    _positionSecs = midi_time;
}

std::string Music::GetFilename() const {
    return _file;
}

std::string Music::GetFilename() {
    return static_cast<const Music&>(*this).GetFilename();
}

void Music::Update() {
	_prevpositionBeats = _positionBeats;
	_prevpositionSecs = _positionSecs;
    _positionBeats = midi_pos;
    _positionSecs = midi_time;
}

bool Music::IsPlaying() {
    Update();
    return (midi_pos > 0);
}

bool Music::IsLooped() {
     return _loop;
}

bool Music::HasEnded() {
	Update();
	return (_prevpositionBeats > 0 && _positionBeats < 0);
}

void Music::SetLooped(bool loop) {
     _loop = loop;
}

void Music::Play(){
     play_midi(_midi,_loop);
}

void Music::Stop(){
     stop_midi();
}

void Music::Pause() {
    _isPaused = !_isPaused;
    if(_isPaused) {
        midi_pause();
        _positionBeats = midi_pos;
    } else {
        midi_seek(_positionBeats);
        midi_resume();
    }
}

void Music::ChangeMidi(MIDI* midi) {
    Stop();
    SetMidi(midi);
    Play();
}

long Music::GetPositionInBeats() {
    Update();
	return _positionBeats;
}

long Music::GetPositionInSeconds() {
    Update();
	return _positionSecs;
}

long Music::GetLengthInBeats() {
    Update();
	return _lengthBeats;
}

long Music::GetLengthInSeconds() {
    Update();
	return _lengthSecs;
}

A2DE_END