/**************************************************************************************************
// file:	Engine\Audio\CSoundTrack.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the sound track class
 **************************************************************************************************/
#include "CSoundTrack.h"

#include "CMusic.h"
#include <allegro/midi.h>
#include "../a2de_exceptions.h"

A2DE_BEGIN

Soundtrack* Soundtrack::_instance = nullptr;

Soundtrack::Soundtrack()
    : _tracks(new std::vector<Music*>()), _curTrack(0), _repeat(Soundtrack::REPEAT_OFF), _isPaused(false), _isPlaying(false) { }

Soundtrack* Soundtrack::CreateInstance() {
	if(_instance != nullptr) return _instance;
	_instance = new Soundtrack();
	return _instance;
}

Soundtrack::~Soundtrack() {
	if(_tracks != nullptr) {
        std::size_t sz = _tracks->size();
        for(size_t i = 0; i < sz; ++i) {
            delete _tracks->at(i);
        }
	    _tracks->clear();
	    delete _tracks;
	    _tracks = nullptr;
    }
    _instance = nullptr;
}

long Soundtrack::GetSize() {
	return (static_cast<long>(_tracks->size()));
}

long Soundtrack::GetCurrentTrackNumber() {
	return _curTrack;
}

bool Soundtrack::AddTrack(Music* track) {
	try {
		_tracks->push_back(track);
	} catch(...) {
		throw;
	}
	return true;
}

bool Soundtrack::RemoveTrack(long index) {
	if(index >= static_cast<long>(_tracks->size()) || index < 0) return false;
    delete _tracks->at(index);
    std::vector<Music*>::iterator _iter = _tracks->begin() + index;
	_tracks->erase(_iter);
	return true;
}

void Soundtrack::Repeat() {
	switch(_repeat) {
		case Soundtrack::REPEAT_OFF:
			_repeat = Soundtrack::REPEAT_ONE;
			break;
		case Soundtrack::REPEAT_ONE:
			_repeat = Soundtrack::REPEAT_ALL;
			break;
		case Soundtrack::REPEAT_ALL:
			_repeat = Soundtrack::REPEAT_OFF;
			break;
	}
}

void Soundtrack::Repeat(Soundtrack::REPEATTYPE setting) {
    _repeat = setting;
}

void Soundtrack::SkipNext() {
	Stop();
	++_curTrack;
	if(_curTrack >= static_cast<long>(_tracks->size())) {
		_curTrack = 0;
	}
	Play();
}

void Soundtrack::SkipPrevious() {
	Stop();
    --_curTrack;
	if(_curTrack < 0) {
		_curTrack = static_cast<long>(_tracks->size()) - 1;
	}
	Play();
}

Music* Soundtrack::GetMusicAt(long index) {
	if(index >= static_cast<long>(_tracks->size()) || index < 0) return nullptr;
    return _tracks->at(index);
}

Soundtrack::REPEATTYPE Soundtrack::GetRepeatSetting() {
	return _repeat;
}

void Soundtrack::Play() {
    if(_isPlaying) return;
	_isPlaying = true;
	play_midi(GetMusicAt(_curTrack)->GetMidi(), (_repeat == Soundtrack::REPEAT_ONE ? true : false ));
}

void Soundtrack::Stop() {
    if(!_isPlaying) return;
	_isPlaying = false;
	GetMusicAt(_curTrack)->Stop();
}

void Soundtrack::Pause() {
    _isPaused = !_isPaused;
	GetMusicAt(_curTrack)->Pause();
}

Music* Soundtrack::GetCurrentTrack() {
    return GetMusicAt(_curTrack);
}

A2DE_END