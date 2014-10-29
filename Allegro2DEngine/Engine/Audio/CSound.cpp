/**************************************************************************************************
// file:	Engine\Audio\CSound.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the sound class
 **************************************************************************************************/
#include "CSound.h"
#include <allegro/file.h>
#include "../a2de_exceptions.h"

A2DE_BEGIN

const int Sound::PITCH_MIN = 100;
const int Sound::PITCH_DEFAULT = 1000;
const int Sound::PITCH_MAX = 10000;
const unsigned char Sound::VOLUME_MIN = 0;
const unsigned char Sound::VOLUME_MID = 128;
const unsigned char Sound::VOLUME_MAX = 255;

Sound* Sound::CreateSound(const std::string& file) {
    TypeNotSupportedException::RegisterFileType("wav");

    if(exists(file.c_str()) == false) {
        throw FileNotFoundException(file);
    }
    if(TypeNotSupportedException::CheckFileType(get_extension(file.c_str())) == false) {
        throw TypeNotSupportedException(get_extension(file.c_str()));
    }

    SAMPLE* temp = load_sample(file.c_str());
    if(!temp || (temp->bits != 8 && temp->bits != 16)) {
        destroy_sample(temp);
        throw Exception(std::string("Error loading sample: ").append(file));
    }
    destroy_sample(temp);
    return new Sound(file);
}

Sound::Sound(const std::string& file)
      : _sample(nullptr), _file(file), _volume(Sound::VOLUME_MAX), _pan(Sound::PAN_CENTER), _pitch(Sound::PITCH_DEFAULT), _bitrate(0), _stereo(true), _loop(false) {
    _sample = load_sample(file.c_str());
    _bitrate = _sample->bits;
    _stereo = _sample->stereo != 0; //Coerce from C-style bool to C++-style bool
    adjust_sample(_sample, _volume, _pan, _pitch, _loop);
}

Sound::~Sound() {
    if(_sample) {
        destroy_sample(_sample);
        _sample = nullptr;
    }
    _volume = -1;
    _pan = -1;
    _pitch = -1;
    _bitrate = -1;
}

const std::string& Sound::GetFilename() const {
	return _file;
}

std::string& Sound::GetFilename() {
    return const_cast<std::string&>(static_cast<const Sound&>(*this).GetFilename());
}

int Sound::GetVolume() const {
    return _volume;
}

int Sound::GetVolume() {
    return static_cast<const Sound&>(*this).GetVolume();
}

int Sound::GetPan() const {
    return _pan;
}

int Sound::GetPan() {
    return static_cast<const Sound&>(*this).GetPan();
}

int Sound::GetPitch() const {
    return _pitch;
}

int Sound::GetPitch() {
    return static_cast<const Sound&>(*this).GetPitch();
}

int Sound::GetBitRate() const {
    return _bitrate;
}

int Sound::GetBitRate() {
    return static_cast<const Sound&>(*this).GetBitRate();
}

const SAMPLE* Sound::GetSample() const {
    return _sample;
}

SAMPLE* Sound::GetSample() {
    return const_cast<SAMPLE*>(static_cast<const Sound&>(*this).GetSample());
}

void Sound::ChangeSample(const std::string& file) {
	if(exists(file.c_str()) == false) return;
	SAMPLE* temp = load_sample(file.c_str());
	if(temp == nullptr) return;
	stop_sample(_sample);
	destroy_sample(_sample);
	destroy_sample(temp);
	_file = file;
	_sample = load_sample(_file.c_str());
    this->_bitrate = _sample->bits;
    this->_stereo = _sample->stereo != 0;
	play_sample(_sample, _volume, _pan, _pitch, _loop);
}

void Sound::SetVolume(unsigned char volume) {
    _volume = volume;
    adjust_sample(_sample, _volume, _pan, _pitch, _loop);
}

void Sound::SetPan(unsigned char pan) {
    _pan = pan;
    adjust_sample(_sample, _volume, _pan, _pitch, _loop);
}

void Sound::SetPan(Sound::PAN pan) {
    _pan = pan;
    adjust_sample(_sample, _volume, _pan, _pitch, _loop);
}

void Sound::SetPitch(int pitch) {
    if(pitch < Sound::PITCH_MIN) pitch = Sound::PITCH_MIN;
    if(pitch > Sound::PITCH_MAX) pitch = Sound::PITCH_MAX;
    adjust_sample(_sample, _volume, _pan, _pitch, _loop);
}

void Sound::SetLoop(bool loop) {
	_loop = loop;
	adjust_sample(_sample, _volume, _pan, _pitch, _loop);
}

bool Sound::CanLoop() {
    return _loop;
}

void Sound::Play(){
     play_sample(_sample, _volume, _pan, _pitch, _loop);
}

void Sound::Stop() {
    stop_sample(_sample);
}

A2DE_END