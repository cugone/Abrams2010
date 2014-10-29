/**************************************************************************************************
// file:	Engine\Audio\CSoundLibrary.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the sound library class
 **************************************************************************************************/
#include "CSoundLibrary.h"
#include "../a2de_exceptions.h"

#include <allegro/digi.h>
#include <allegro/midi.h>
#include <utility>

A2DE_BEGIN

typedef std::map<std::string, std::pair<int, Sound*> > MapStrPairIntSnd;
typedef std::map<std::string, std::pair<int, Sound*> >::iterator MapStrPairIntSndIter;

const int SoundLibrary::MAX_VOICES = 256;
const double SoundLibrary::VOLUME_STEP = 2.55;
const double SoundLibrary::FREQUENCY_STEP = 0.01f;

SoundLibrary* SoundLibrary::CreateInstance(int numVoices) {
	if(numVoices > MAX_VOICES) numVoices = MAX_VOICES;
	return new SoundLibrary(numVoices);
}

SoundLibrary::SoundLibrary(int numVoices)
            :  _numVoices(numVoices), _mvoices(nullptr) {
                _mvoices = new MapStrPairIntSnd();
}

SoundLibrary::~SoundLibrary() {
    MapStrPairIntSndIter b = _mvoices->begin();
    MapStrPairIntSndIter e = _mvoices->end();
    for(MapStrPairIntSndIter _iter = b; _iter != e; /* DO NOTHING */) {

        deallocate_voice(_iter->second.first);
        _iter->second.first = -1;

        delete _iter->second.second;
        _iter->second.second = nullptr;

        _mvoices->erase(_iter++);
    }
    delete _mvoices;
    _mvoices = nullptr;
}

bool SoundLibrary::AddSound(const std::string& name, Sound* sound) {
    std::size_t sz = _mvoices->size();
    if(sz >= static_cast<std::size_t>(_numVoices)) return false;
    if(sound == nullptr) return false;
    int allocated_to = allocate_voice(sound->GetSample());
    if(allocated_to == -1) {
        delete sound;
        return false;
    }

    MapStrPairIntSndIter _iter = _mvoices->find(name);
    if(_iter != _mvoices->end()) {
        delete _iter->second.second;
        _iter->second.second = nullptr;
        _mvoices->erase(_iter);
    }

    std::pair<MapStrPairIntSndIter, bool> inserted = _mvoices->insert(std::make_pair(name, std::make_pair(allocated_to, sound)));
    
    if(inserted.second == false) delete sound;

    return inserted.second;
}

bool SoundLibrary::RemoveSound(const std::string& name) {
    if(Verify(name) == false) return false;
    if(IsPlaying(name)) Stop(name);

    MapStrPairIntSndIter _iter = _mvoices->find(name);
    
    deallocate_voice(_iter->second.first);
    _iter->second.first = -1;

    delete _iter->second.second;
    _iter->second.second = nullptr;
    _mvoices->erase(_iter);
    return true;
}

void SoundLibrary::Play(const std::string& name) {
    if(Verify(name) == false) return;
    voice_start(GetIndexOf(name));
}

bool SoundLibrary::IsPlaying(const std::string& name) const {
    if(Verify(name) == false) return false;
	return !(voice_get_position(GetIndexOf(name)) == -1);
}

void SoundLibrary::Stop(const std::string& name) {
    if(Verify(name) == false) return;
    voice_stop(GetIndexOf(name));
    SetPosition(name, 0);
}

void SoundLibrary::Restart(const std::string& name) {
    if(Verify(name) == false) return;
    SetPosition(name, 0);
}

void SoundLibrary::Pause(const std::string& name) {
    if(Verify(name) == false) return;
    voice_stop(GetIndexOf(name));
}

long SoundLibrary::GetLength(const std::string& name) const {
    if(Verify(name) == false) return -1;
    return (voice_check(GetIndexOf(name))->len);
}

long SoundLibrary::GetLength(const std::string& name) {
    return static_cast<const SoundLibrary&>(*this).GetLength(name);
}

double SoundLibrary::GetLengthInSeconds(const std::string& name) const {
    if(Verify(name) == false) return -1.0;
    long length = GetLength(name);
    int freq = GetFrequency(name);
    return (length / freq);
}

double SoundLibrary::GetLengthInSeconds(const std::string& name) {
    return static_cast<const SoundLibrary&>(*this).GetLengthInSeconds(name);
}

long SoundLibrary::GetPosition(const std::string& name) const {
    if(Verify(name) == false) return -1;
    return voice_get_position(GetIndexOf(name));
}

long SoundLibrary::GetPosition(const std::string& name) {
    return static_cast<const SoundLibrary&>(*this).GetPosition(name);
}

void SoundLibrary::SetPosition(const std::string& name, unsigned long pos) {
    if(Verify(name) == false) return;
    if(pos >= GetSoundAt(name)->GetSample()->len ) pos = GetSoundAt(name)->GetSample()->len;
    voice_set_position(GetIndexOf(name), pos);
}

long SoundLibrary::GetElapsed(const std::string& name) const {
    return GetPosition(name);
}

long SoundLibrary::GetElapsed(const std::string& name) {
    return static_cast<const SoundLibrary&>(*this).GetElapsed(name);
}

double SoundLibrary::GetElapsedInSeconds(const std::string& name) const {
    if(Verify(name) == false) return -1.0;
    if(IsPlaying(name) == false) return -1.0;
    unsigned long curPos = GetPosition(name);
    int freq = GetFrequency(name);
    return (curPos / freq);
}

double SoundLibrary::GetElapsedInSeconds(const std::string& name) {
    return static_cast<const SoundLibrary&>(*this).GetElapsedInSeconds(name);
}

int SoundLibrary::GetPan(const std::string& name) const {
    if(Verify(name) == false) return -1;
    return (voice_get_pan(GetIndexOf(name)));
}

int SoundLibrary::GetPan(const std::string& name) {
    return static_cast<const SoundLibrary&>(*this).GetPan(name);
}

void SoundLibrary::SetPan(const std::string& name, unsigned char pan) {
    if(Verify(name) == false) return;
    voice_set_pan(GetIndexOf(name), pan);
}

void SoundLibrary::SetPanLeft(const std::string& name) {
	if(Verify(name) == false) return;
    voice_set_pan(GetIndexOf(name), Sound::PAN_LEFT);
}

void SoundLibrary::SetPanCenter(const std::string& name) {
	if(Verify(name) == false) return;
    voice_set_pan(GetIndexOf(name), Sound::PAN_CENTER);
}

void SoundLibrary::SetPanRight(const std::string& name) {
	if(Verify(name) == false) return;
    voice_set_pan(GetIndexOf(name), Sound::PAN_RIGHT);
}

void SoundLibrary::SetPanLeftCenter(const std::string& name) {
    if(Verify(name) == false) return;
    voice_set_pan(GetIndexOf(name), Sound::PAN_LEFT_CENTER);
}

void SoundLibrary::SetPanRightCenter(const std::string& name) {
    if(Verify(name) == false) return;
    voice_set_pan(GetIndexOf(name), Sound::PAN_RIGHT_CENTER);
}

void SoundLibrary::StartPanSweep(const std::string& name, int timeperiodMS, Sound::PAN endpos) {
    if(Verify(name) == false) return;
    voice_sweep_pan(GetIndexOf(name), timeperiodMS, static_cast<int>(endpos));
}

void SoundLibrary::StopPanSweep(const std::string& name) {
    if(Verify(name) == false) return;
    voice_stop_pan_sweep(GetIndexOf(name));
}

unsigned char SoundLibrary::GetVolume(const std::string& name) const {
    if(Verify(name) == false) return 0;
    return voice_get_volume(GetIndexOf(name));
}

unsigned char SoundLibrary::GetVolume(const std::string& name) {
    return static_cast<const SoundLibrary&>(*this).GetVolume(name);
}

void SoundLibrary::SetVolume(const std::string& name, unsigned char vol) {
    if(Verify(name) == false) return;
    voice_set_volume(GetIndexOf(name), vol);
}

void SoundLibrary::IncreaseVolume(const std::string& name) {
	if(Verify(name) == false) return;
    int vol = GetVolume(name) + VOLUME_STEP;
    if(vol > 255) vol = 255;
    SetVolume(name, vol);
}

void SoundLibrary::DecreaseVolume(const std::string& name) {
	if(Verify(name) == false) return;
    int vol = GetVolume(name) - VOLUME_STEP;
    if(vol < 0) vol = 0;
    SetVolume(name, vol);
}

void SoundLibrary::StartVolumeRamp(const std::string& name, int timeperiodMS, unsigned char endvol) {
    if(Verify(name) == false) return;
    voice_ramp_volume(GetIndexOf(name), timeperiodMS, endvol);
}

void SoundLibrary::StopVolumeRamp(const std::string& name) {
    if(Verify(name) == false) return;
    voice_stop_volumeramp(GetIndexOf(name));
}

void SoundLibrary::Loop(const std::string& name, SoundLibrary::DIRECTION dir) {
	if(Verify(name) == false) return;
    voice_set_playmode(GetIndexOf(name), dir);
}

long SoundLibrary::GetLoopStartPos(const std::string& name) const {
    if(Verify(name) == false) return -1;
    SAMPLE* smpl = voice_check(GetIndexOf(name));
    return (smpl != nullptr ? smpl->loop_start : -1 );
}

long SoundLibrary::GetLoopStartPos(const std::string& name) {
    return static_cast<const SoundLibrary&>(*this).GetLoopStartPos(name);
}

long SoundLibrary::GetLoopEndPos(const std::string& name) const {
    if(Verify(name) == false) return -1;
    SAMPLE* smpl = voice_check(GetIndexOf(name));
    return (smpl != nullptr ? smpl->loop_end : -1 );
}

long SoundLibrary::GetLoopEndPos(const std::string& name) {
    return static_cast<const SoundLibrary&>(*this).GetLoopEndPos(name);
}

void SoundLibrary::SetLoopStartPos(const std::string& name, long pos) {
    if(Verify(name) == false) return;
    if(pos < 0) pos = 0;
    if(pos > GetLength(name)) pos = GetLength(name);
    voice_check(GetIndexOf(name))->loop_start = pos;
}

void SoundLibrary::SetLoopEndPos(const std::string& name, long pos) {
    if(Verify(name) == false) return;
    if(pos > static_cast<int>(GetLength(name)) || pos < 0) return;
    SAMPLE* smpl = voice_check(GetIndexOf(name));
    if(pos < 0) pos = 0;
    if(pos > static_cast<long>(smpl->len)) pos = smpl->len;
    smpl->loop_end = pos;
}

void SoundLibrary::IncreaseFrequency(const std::string& name) {
	if(Verify(name) == false) return;
    SetFrequency(name, GetFrequency(name) + (GetSoundAt(name)->GetSample()->freq * FREQUENCY_STEP));
}

void SoundLibrary::DecreaseFrequency(const std::string& name) {
	if(Verify(name) == false) return;
    SetFrequency(name, GetFrequency(name) - (GetSoundAt(name)->GetSample()->freq * FREQUENCY_STEP));
}

int SoundLibrary::GetFrequency(const std::string& name) const {
    if(Verify(name) == false) return -1;
    return voice_get_frequency(GetIndexOf(name));
}

int SoundLibrary::GetFrequency(const std::string& name) {
    return static_cast<const SoundLibrary&>(*this).GetFrequency(name);
}

void SoundLibrary::SetFrequency(const std::string& name, int Hz) {
    if(Verify(name) == false) return;
    if(Hz <= 1) Hz = 1;
    voice_set_frequency(GetIndexOf(name), Hz);
}

void SoundLibrary::ResetFrequency(const std::string& name) {
    if(Verify(name) == false) return;
    SetFrequency(name, GetSoundAt(name)->GetSample()->freq);
}

void SoundLibrary::StartFrequencySweep(const std::string& name, int timeperiodMS, int endHz) {
    if(Verify(name) == false) return;
    if(timeperiodMS < 0) timeperiodMS = 0;
    if(endHz < 0) endHz = 0;

    voice_sweep_frequency(GetIndexOf(name), timeperiodMS, endHz);
}

void SoundLibrary::StopFrequencySweep(const std::string& name) {
    if(Verify(name) == false) return;
    voice_stop_frequency_sweep(GetIndexOf(name));
}

long SoundLibrary::GetRemaining(const std::string& name) const {
    if(Verify(name) == false) return -1;
    return GetLength(name) - GetElapsed(name);
}

long SoundLibrary::GetRemaining(const std::string& name) {
    return static_cast<const SoundLibrary&>(*this).GetRemaining(name);
}

double SoundLibrary::GetRemainingInSeconds(const std::string& name) const {
    if(Verify(name) == false) return -1.0;
    if(IsPlaying(name) == false) return -1.0;
    return GetLengthInSeconds(name) - GetElapsedInSeconds(name);
}

double SoundLibrary::GetRemainingInSeconds(const std::string& name) {
    return static_cast<const SoundLibrary&>(*this).GetRemainingInSeconds(name);
}

bool SoundLibrary::Verify(const std::string& name) const {
    return (_mvoices->find(name) != _mvoices->end());
}

int SoundLibrary::GetIndexOf(const std::string& name) const {
    return _mvoices->at(name).first;
}

Sound* SoundLibrary::GetSoundAt(const std::string& name) const {
    return _mvoices->at(name).second;
}


A2DE_END