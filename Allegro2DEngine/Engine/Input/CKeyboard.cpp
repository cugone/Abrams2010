/**************************************************************************************************
// file:	Engine\Input\CKeyboard.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the keyboard class
 **************************************************************************************************/
#include "CKeyboard.h"

A2DE_BEGIN

Keyboard* Keyboard::_instance = nullptr;

bool Keyboard::Config() {
	return (install_keyboard() >= 0);
}

Keyboard* Keyboard::CreateKeyboard() {
	if(_instance != nullptr) return _instance;
    if(Config() == false) return nullptr;
	if(_instance == nullptr) _instance = new Keyboard();
	return _instance;
}

Keyboard::Keyboard() {
    clear_keybuf();
    _prevKey.reset();
    _curKey.reset();
}
Keyboard::~Keyboard() {
    clear_keybuf();
    _prevKey.reset();
    _curKey.reset();
	remove_keyboard();
}

bool Keyboard::KeyDown(int scancode) {
    return (!_prevKey.test(scancode) && _curKey.test(scancode));
}
bool Keyboard::KeyPress(int scancode) {
    return (_prevKey.test(scancode) && _curKey.test(scancode));
}
bool Keyboard::KeyUp(int scancode) {
    return (_prevKey.test(scancode) && !_curKey.test(scancode));
}
bool Keyboard::IsKeyPressed() {
	return (_prevKey.test(0) && _curKey.test(0));
}

int Keyboard::GetNextKeyByScancode() {
    if(keypressed()) {
        int result = (readkey() >> 0x08);
        clear_keybuf();
        return result;
    }
    return 0;
}
int Keyboard::GetNextKeyByAscii() {
    if(keypressed()) {
        int result = (readkey() & 0xFF);
        clear_keybuf();
        return result;
    }
    return 0;
}

void Keyboard::Update() {
    poll_keyboard();
	_prevKey.set(0, _curKey.at(0));
	_curKey.reset(0);
    for(size_t i = 1; i < KEY_MAX; ++i) {
        _prevKey.set(i, _curKey.at(i));
        (key[i] == 0 ? _curKey.reset(i) : _curKey.set(i));
    }
    if(_curKey.any()) _curKey.set(0);

}

A2DE_END