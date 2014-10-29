/**************************************************************************************************
// file:	Engine\Input\CMouse.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the mouse class
 **************************************************************************************************/
#include "CMouse.h"

#include <allegro/gfx.h>
#include <allegro/draw.h>
#include <allegro/mouse.h>

#include "../GFX/CGameWindow.h"
#include "../GFX/CAnimatedSprite.h"

#include "../Math/MiscMath.h"
#include "../a2de_exceptions.h"

A2DE_BEGIN

BITMAP* Mouse::DEFAULT_MOUSE_IMAGE = nullptr;
Mouse* Mouse::_instance = nullptr;
int Mouse::_numButtons = -1;

Mouse* Mouse::CreateMouse() {
	if(_instance != nullptr) return _instance;
	if(Config()) {
		if(_instance == nullptr)
			_instance = new Mouse();
	} else {
		_instance = nullptr;
	}
	return _instance;
}

Mouse* Mouse::CreateMouse(Sprite* image, int focusX, int focusY) {
	if(_instance != nullptr) return _instance;
	if(Config()) {
		if(_instance == nullptr)
			_instance = new Mouse(image, focusX, focusY);
	} else {
		_instance = nullptr;
	}
	return _instance;
}

Mouse* Mouse::CreateMouse(Sprite* image, const a2de::Vector2D& focus_coordinates) {
    return CreateMouse(image, focus_coordinates.GetX(), focus_coordinates.GetY());
}

bool Mouse::Config() {

	_numButtons = install_mouse();
	if(_numButtons < 0) {
        throw InputNotAvailableException("Mouse");
    }
    if(CreateDefaultImage() == false) return false;
	return true;
}

bool Mouse::CreateDefaultImage() {
    if(DEFAULT_MOUSE_IMAGE != nullptr) return false;

    const int DEPTH = 32;
    const int WIDTH = 11;
    const int HEIGHT = 19;
    DEFAULT_MOUSE_IMAGE = create_bitmap_ex(DEPTH, WIDTH, HEIGHT);
    if(DEFAULT_MOUSE_IMAGE == nullptr) return false;

    const int BLACK = 0x000000;
    const int WHITE = 0xFFFFFF;
    const int PINK = 0xFF00FF;
    
    //Color bitmap to transparent
    clear_to_color(DEFAULT_MOUSE_IMAGE, PINK);
    
    //Only color areas that are NOT transparent.
    //Each block is a row of pixels.

    /************************************************************************
     * SHOULD PRODUCE THIS RESULT   * = BLACK; 0 = WHITE; - = PINK          *
     * *----------                                                          *
     * **---------                                                          *
     * *0*--------                                                          *
     * *00*-------                                                          *
     * *000*------                                                          *
     * *0000*-----                                                          *
     * *00000*----                                                          *
     * *000000*---                                                          *
     * *0000000*--                                                          *
     * *00000000*-                                                          *
     * *00000*****                                                          *
     * *00*00*----                                                          *
     * *0*-*00*---                                                          *
     * **--*00*---                                                          *
     * *----*00*--                                                          *
     * -----*00*--                                                          *
     * ------*00*-                                                          *
     * ------*00*-                                                          *
     * -------**--                                                          *
     ************************************************************************/

    ((long *)DEFAULT_MOUSE_IMAGE->line[0])[0] = BLACK;
    //((long *)_defaultImage->line[0])[1] = PINK;
    //((long *)_defaultImage->line[0])[2] = PINK;
    //((long *)_defaultImage->line[0])[3] = PINK;
    //((long *)_defaultImage->line[0])[4] = PINK;
    //((long *)_defaultImage->line[0])[5] = PINK;
    //((long *)_defaultImage->line[0])[6] = PINK;
    //((long *)_defaultImage->line[0])[7] = PINK;
    //((long *)_defaultImage->line[0])[8] = PINK;
    //((long *)_defaultImage->line[0])[9] = PINK;
    //((long *)_defaultImage->line[0])[10] = PINK;

    ((long *)DEFAULT_MOUSE_IMAGE->line[1])[0] = BLACK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[1])[1] = BLACK;
    //((long *)_defaultImage->line[1])[2] = PINK;
    //((long *)_defaultImage->line[1])[3] = PINK;
    //((long *)_defaultImage->line[1])[4] = PINK;
    //((long *)_defaultImage->line[1])[5] = PINK;
    //((long *)_defaultImage->line[1])[6] = PINK;
    //((long *)_defaultImage->line[1])[7] = PINK;
    //((long *)_defaultImage->line[1])[8] = PINK;
    //((long *)_defaultImage->line[1])[9] = PINK;
    //((long *)_defaultImage->line[1])[10] = PINK;


    ((long *)DEFAULT_MOUSE_IMAGE->line[2])[0] = BLACK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[2])[1] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[2])[2] = BLACK;
    //((long *)_defaultImage->line[2])[3] = PINK;
    //((long *)_defaultImage->line[2])[4] = PINK;
    //((long *)_defaultImage->line[2])[5] = PINK;
    //((long *)_defaultImage->line[2])[6] = PINK;
    //((long *)_defaultImage->line[2])[7] = PINK;
    //((long *)_defaultImage->line[2])[8] = PINK;
    //((long *)_defaultImage->line[2])[9] = PINK;
    //((long *)_defaultImage->line[2])[10] = PINK;

    ((long *)DEFAULT_MOUSE_IMAGE->line[3])[0] = BLACK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[3])[1] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[3])[2] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[3])[3] = BLACK;
    //((long *)_defaultImage->line[3])[4] = PINK;
    //((long *)_defaultImage->line[3])[5] = PINK;
    //((long *)_defaultImage->line[3])[6] = PINK;
    //((long *)_defaultImage->line[3])[7] = PINK;
    //((long *)_defaultImage->line[3])[8] = PINK;
    //((long *)_defaultImage->line[3])[9] = PINK;
    //((long *)_defaultImage->line[3])[10] = PINK;

    ((long *)DEFAULT_MOUSE_IMAGE->line[4])[0] = BLACK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[4])[1] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[4])[2] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[4])[3] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[4])[4] = BLACK;
    //((long *)_defaultImage->line[4])[5] = PINK;
    //((long *)_defaultImage->line[4])[6] = PINK;
    //((long *)_defaultImage->line[4])[7] = PINK;
    //((long *)_defaultImage->line[4])[8] = PINK;
    //((long *)_defaultImage->line[4])[9] = PINK;
    //((long *)_defaultImage->line[4])[10] = PINK;

    ((long *)DEFAULT_MOUSE_IMAGE->line[5])[0] = BLACK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[5])[1] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[5])[2] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[5])[3] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[5])[4] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[5])[5] = BLACK;
    //((long *)_defaultImage->line[5])[6] = PINK;
    //((long *)_defaultImage->line[5])[7] = PINK;
    //((long *)_defaultImage->line[5])[8] = PINK;
    //((long *)_defaultImage->line[5])[9] = PINK;
    //((long *)_defaultImage->line[5])[10] = PINK;

    ((long *)DEFAULT_MOUSE_IMAGE->line[6])[0] = BLACK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[6])[1] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[6])[2] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[6])[3] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[6])[4] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[6])[5] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[6])[6] = BLACK;
    //((long *)_defaultImage->line[6])[7] = PINK;
    //((long *)_defaultImage->line[6])[8] = PINK;
    //((long *)_defaultImage->line[6])[9] = PINK;
    //((long *)_defaultImage->line[6])[10] = PINK;

    ((long *)DEFAULT_MOUSE_IMAGE->line[7])[0] = BLACK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[7])[1] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[7])[2] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[7])[3] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[7])[4] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[7])[5] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[7])[6] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[7])[7] = BLACK;
    //((long *)_defaultImage->line[7])[8] = PINK;
    //((long *)_defaultImage->line[7])[9] = PINK;
    //((long *)_defaultImage->line[7])[10] = PINK;

    ((long *)DEFAULT_MOUSE_IMAGE->line[8])[0] = BLACK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[8])[1] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[8])[2] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[8])[3] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[8])[4] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[8])[5] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[8])[6] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[8])[7] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[8])[8] = BLACK;
    //((long *)_defaultImage->line[8])[9] = PINK;
    //((long *)_defaultImage->line[8])[10] = PINK;

    ((long *)DEFAULT_MOUSE_IMAGE->line[9])[0] = BLACK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[9])[1] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[9])[2] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[9])[3] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[9])[4] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[9])[5] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[9])[6] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[9])[7] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[9])[8] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[9])[9] = BLACK;
    //((long *)_defaultImage->line[9])[10] = PINK;

    ((long *)DEFAULT_MOUSE_IMAGE->line[10])[0] = BLACK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[10])[1] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[10])[2] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[10])[3] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[10])[4] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[10])[5] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[10])[6] = BLACK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[10])[7] = BLACK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[10])[8] = BLACK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[10])[9] = BLACK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[10])[10] = BLACK;

    ((long *)DEFAULT_MOUSE_IMAGE->line[11])[0] = BLACK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[11])[1] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[11])[2] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[11])[3] = BLACK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[11])[4] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[11])[5] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[11])[6] = BLACK;
    //((long *)_defaultImage->line[11])[7] = PINK;
    //((long *)_defaultImage->line[11])[8] = PINK;
    //((long *)_defaultImage->line[11])[9] = PINK;
    //((long *)_defaultImage->line[11])[10] = PINK;

    ((long *)DEFAULT_MOUSE_IMAGE->line[12])[0] = BLACK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[12])[1] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[12])[2] = BLACK;
    //((long *)_defaultImage->line[12])[3] = PINK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[12])[4] = BLACK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[12])[5] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[12])[6] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[12])[7] = BLACK;
    //((long *)_defaultImage->line[12])[8] = PINK;
    //((long *)_defaultImage->line[12])[9] = PINK;
    //((long *)_defaultImage->line[12])[10] = PINK;

    ((long *)DEFAULT_MOUSE_IMAGE->line[13])[0] = BLACK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[13])[1] = BLACK;
    //((long *)_defaultImage->line[13])[2] = PINK;
    //((long *)_defaultImage->line[13])[3] = PINK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[13])[4] = BLACK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[13])[5] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[13])[6] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[13])[7] = BLACK;
    //((long *)_defaultImage->line[13])[8] = PINK;
    //((long *)_defaultImage->line[13])[9] = PINK;
    //((long *)_defaultImage->line[13])[10] = PINK;

    ((long *)DEFAULT_MOUSE_IMAGE->line[14])[0] = BLACK;
    //((long *)_defaultImage->line[14])[1] = PINK;
    //((long *)_defaultImage->line[14])[2] = PINK;
    //((long *)_defaultImage->line[14])[3] = PINK;
    //((long *)_defaultImage->line[14])[4] = PINK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[14])[5] = BLACK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[14])[6] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[14])[7] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[14])[8] = BLACK;
    //((long *)_defaultImage->line[14])[9] = PINK;
    //((long *)_defaultImage->line[14])[10] = PINK;

    //((long *)_defaultImage->line[15])[0] = PINK;
    //((long *)_defaultImage->line[15])[1] = PINK;
    //((long *)_defaultImage->line[15])[2] = PINK;
    //((long *)_defaultImage->line[15])[3] = PINK;
    //((long *)_defaultImage->line[15])[4] = PINK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[15])[5] = BLACK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[15])[6] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[15])[7] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[15])[8] = BLACK;
    //((long *)_defaultImage->line[15])[9] = PINK;
    //((long *)_defaultImage->line[15])[10] = PINK;

    //((long *)_defaultImage->line[16])[0] = PINK;
    //((long *)_defaultImage->line[16])[1] = PINK;
    //((long *)_defaultImage->line[16])[2] = PINK;
    //((long *)_defaultImage->line[16])[3] = PINK;
    //((long *)_defaultImage->line[16])[4] = PINK;
    //((long *)_defaultImage->line[16])[5] = PINK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[16])[6] = BLACK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[16])[7] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[16])[8] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[16])[9] = BLACK;
    //((long *)_defaultImage->line[16])[10] = PINK;

    //((long *)_defaultImage->line[17])[0] = PINK;
    //((long *)_defaultImage->line[17])[1] = PINK;
    //((long *)_defaultImage->line[17])[2] = PINK;
    //((long *)_defaultImage->line[17])[3] = PINK;
    //((long *)_defaultImage->line[17])[4] = PINK;
    //((long *)_defaultImage->line[17])[5] = PINK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[17])[6] = BLACK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[17])[7] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[17])[8] = WHITE;
    ((long *)DEFAULT_MOUSE_IMAGE->line[17])[9] = BLACK;
    //((long *)_defaultImage->line[17])[10] = PINK;

    //((long *)_defaultImage->line[18])[0] = PINK;
    //((long *)_defaultImage->line[18])[1] = PINK;
    //((long *)_defaultImage->line[18])[2] = PINK;
    //((long *)_defaultImage->line[18])[3] = PINK;
    //((long *)_defaultImage->line[18])[4] = PINK;
    //((long *)_defaultImage->line[18])[5] = PINK;
    //((long *)_defaultImage->line[18])[6] = PINK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[18])[7] = BLACK;
    ((long *)DEFAULT_MOUSE_IMAGE->line[18])[8] = BLACK;
    //((long *)_defaultImage->line[18])[9] = PINK;
    //((long *)_defaultImage->line[18])[10] = PINK;


    return true;
}

Mouse::Mouse()
     : _position(mouse_x, mouse_y, mouse_z), _mickeys(0.0, 0.0, 0.0), _focus(0.0, 0.0), _image(nullptr), _prevbuttons(false), _curbuttons(false), _dirtyImage(false), _isVisible(false) {

    _image = Sprite::CreateSprite("A2DE_DefaultMouse", DEFAULT_MOUSE_IMAGE);
    DEFAULT_MOUSE_IMAGE = nullptr;

    set_mouse_sprite(_image->GetImage());
    set_mouse_sprite_focus(_focus.GetX(), _focus.GetY());

    int _mX = _mickeys.GetX();
    int _mY = _mickeys.GetY();

    get_mouse_mickeys(&_mX, &_mY);
    int mX = _mX;
    int mY = _mY;
    int mZ = _position.GetZ() - _mickeys.GetZ();
    _mickeys = Vector3D(mX, mY, mZ);

}

Mouse::Mouse(Sprite* image, int focusX, int focusY)
     : _position(mouse_x, mouse_y, mouse_z), _mickeys(0.0, 0.0, 0.0), _focus(focusX, focusY), _image(nullptr), _prevbuttons(false), _curbuttons(false), _dirtyImage(false), _isVisible(false) {

	if(image == nullptr) {
		focusX = 0;
		focusY = 0;
        _image = Sprite::CreateSprite("A2DE_DefaultMouse", DEFAULT_MOUSE_IMAGE);
        DEFAULT_MOUSE_IMAGE = nullptr;
        set_mouse_sprite(_image->GetImage());
	} else {
		if(focusX < 0 || focusX > image->GetWidth()) focusX = 0;
		if(focusY < 0 || focusY > image->GetHeight()) focusY = 0;
	}

	SetImage(image, focusX, focusY);

	set_mouse_sprite(_image->GetImage());
	set_mouse_sprite_focus(_focus.GetX(), _focus.GetY());

    int _mX = _mickeys.GetX();
    int _mY = _mickeys.GetY();

    get_mouse_mickeys(&_mX, &_mY);
    int mX = _mX;
    int mY = _mY;
    int mZ = _position.GetZ() - _mickeys.GetZ();
    _mickeys = Vector3D(mX, mY, mZ);
}

Mouse::~Mouse() {

    set_mouse_sprite(nullptr);
    show_mouse(nullptr);
    if(_image) {
		delete _image;
        _image = nullptr;
    }
    DEFAULT_MOUSE_IMAGE = nullptr;
	_numButtons = -1;
	remove_mouse();
}

Sprite* Mouse::GetSprite() const {
	return _image;
}

int Mouse::GetX() const {
    return _position.GetX();
}
int Mouse::GetY() const {
    return _position.GetY();
}
int Mouse::GetZ() const {
    return _position.GetZ();
}

int Mouse::GetMickeyX() const {
    return _mickeys.GetX();
}
int Mouse::GetMickeyY() const {
    return _mickeys.GetY();
}
int Mouse::GetMickeyZ() const {
	return _mickeys.GetZ();
}

int Mouse::GetFocusX() const {
	return _focus.GetX();
}
int Mouse::GetFocusY() const {
	return _focus.GetY();
}

int Mouse::GetNumButtons() const {
	return _numButtons;
}

bool Mouse::ImageHasChanged() const {
	return _dirtyImage;
}

void Mouse::SetX(int x) {
    SetPosition(x, GetY(), GetZ());
}
void Mouse::SetY(int y) {
    SetPosition(GetX(), y, GetZ());
}
void Mouse::SetZ(int z) {
    SetPosition(GetX(), GetY(), z);
}

void Mouse::SetPosition(int x, int y) {
    SetPosition(x, y, GetZ());
}

void Mouse::SetPosition(int x, int y, int z) {
    int old_z = _position.GetZ();
    int new_Z = z;
    position_mouse_z(z);
    _position = Vector3D(x, y, z);
    int mX = _mickeys.GetX();
    int mY = _mickeys.GetY();
    _mickeys = Vector3D(mX, mY, old_z - new_Z);
}

void Mouse::SetFocus(int x, int y) {
	_focus = Vector2D(x, y);
	set_mouse_sprite_focus(_focus.GetX(), _focus.GetY());
}

void Mouse::Update() {
    poll_mouse();

    SetPosition(mouse_x, mouse_y, mouse_z);

    int mX = _mickeys.GetX();
    int mY = _mickeys.GetY();
    int mZ = _mickeys.GetZ();
    get_mouse_mickeys(&mX, &mY);
    _mickeys = Vector3D(mX, mY, mZ);

    _prevbuttons = _curbuttons;
    _curbuttons.reset();

    //Intentional unrolled loop!
    if((mouse_b & MOUSEBUTTON_BUTTON1) != 0) _curbuttons.set(GetButtonIndex(MOUSEBUTTON_BUTTON1));
    if((mouse_b & MOUSEBUTTON_BUTTON2) != 0) _curbuttons.set(GetButtonIndex(MOUSEBUTTON_BUTTON2));
    if((mouse_b & MOUSEBUTTON_BUTTON3) != 0) _curbuttons.set(GetButtonIndex(MOUSEBUTTON_BUTTON3));
    if((mouse_b & MOUSEBUTTON_BUTTON4) != 0) _curbuttons.set(GetButtonIndex(MOUSEBUTTON_BUTTON4));
    if((mouse_b & MOUSEBUTTON_BUTTON5) != 0) _curbuttons.set(GetButtonIndex(MOUSEBUTTON_BUTTON5));
    if((mouse_b & MOUSEBUTTON_BUTTON6) != 0) _curbuttons.set(GetButtonIndex(MOUSEBUTTON_BUTTON6));
    if((mouse_b & MOUSEBUTTON_BUTTON7) != 0) _curbuttons.set(GetButtonIndex(MOUSEBUTTON_BUTTON7));
    if((mouse_b & MOUSEBUTTON_BUTTON8) != 0) _curbuttons.set(GetButtonIndex(MOUSEBUTTON_BUTTON8));
    if((mouse_b & MOUSEBUTTON_BUTTON9) != 0) _curbuttons.set(GetButtonIndex(MOUSEBUTTON_BUTTON9));
    if((mouse_b & MOUSEBUTTON_BUTTON10) != 0) _curbuttons.set(GetButtonIndex(MOUSEBUTTON_BUTTON10));
    if((mouse_b & MOUSEBUTTON_BUTTON11) != 0) _curbuttons.set(GetButtonIndex(MOUSEBUTTON_BUTTON11));
    if((mouse_b & MOUSEBUTTON_BUTTON12) != 0) _curbuttons.set(GetButtonIndex(MOUSEBUTTON_BUTTON12));
    if((mouse_b & MOUSEBUTTON_BUTTON13) != 0) _curbuttons.set(GetButtonIndex(MOUSEBUTTON_BUTTON13));
    if((mouse_b & MOUSEBUTTON_BUTTON14) != 0) _curbuttons.set(GetButtonIndex(MOUSEBUTTON_BUTTON14));
    if((mouse_b & MOUSEBUTTON_BUTTON15) != 0) _curbuttons.set(GetButtonIndex(MOUSEBUTTON_BUTTON15));
    if((mouse_b & MOUSEBUTTON_BUTTON16) != 0) _curbuttons.set(GetButtonIndex(MOUSEBUTTON_BUTTON16));

    if(_curbuttons.any()) _curbuttons.set(MOUSEBUTTON_ANY);

    if(_image) {
        set_mouse_sprite(_image->GetImage());
    } else {
        set_mouse_sprite(nullptr);
    }
    set_mouse_sprite_focus(_focus.GetX(), _focus.GetY());
}

int Mouse::GetButtonIndex(Mouse::BUTTONS button) {
    switch(button) {
    case MOUSEBUTTON_ANY:
        return 0;
    case MOUSEBUTTON_BUTTON1:
        return 1;
    case MOUSEBUTTON_BUTTON2:
        return 2;
    case MOUSEBUTTON_BUTTON3:
        return 3;
    case MOUSEBUTTON_BUTTON4:
        return 4;
    case MOUSEBUTTON_BUTTON5:
        return 5;
    case MOUSEBUTTON_BUTTON6:
        return 6;
    case MOUSEBUTTON_BUTTON7:
        return 7;
    case MOUSEBUTTON_BUTTON8:
        return 8;
    case MOUSEBUTTON_BUTTON9:
        return 9;
    case MOUSEBUTTON_BUTTON10:
        return 10;
    case MOUSEBUTTON_BUTTON11:
        return 11;
    case MOUSEBUTTON_BUTTON12:
        return 12;
    case MOUSEBUTTON_BUTTON13:
        return 13;
    case MOUSEBUTTON_BUTTON14:
        return 14;
    case MOUSEBUTTON_BUTTON15:
        return 15;
    case MOUSEBUTTON_BUTTON16:
        return 16;
    default:
        return -1;
    }
}
bool Mouse::ButtonDown(Mouse::BUTTONS button) {
    int curButton = GetButtonIndex(button);
    if(curButton < 0) return false;
    return (!_prevbuttons.test(curButton) && _curbuttons.test(curButton));
}
bool Mouse::ButtonPress(Mouse::BUTTONS button) {
    int curButton = GetButtonIndex(button);
    if(curButton < 0) return false;
    return (_prevbuttons.test(curButton) && _curbuttons.test(curButton));
}
bool Mouse::ButtonUp(Mouse::BUTTONS button) {
    int curButton = GetButtonIndex(button);
    if(curButton < 0) return false;
    return (_prevbuttons.test(curButton) && !_curbuttons.test(curButton));
}
bool Mouse::IsButtonPressed() {
    return (!_prevbuttons.test(0) && _curbuttons.test(0));
}

void Mouse::SetImage(Sprite* image, int focusX, int focusY) {
    if(_image) {
        set_mouse_sprite(nullptr);
        set_mouse_sprite_focus(0, 0);
        show_mouse(nullptr);
        delete _image;
        _image = nullptr;
    }
    if(image) {
        _image = Sprite::CreateSprite(*image);
    } else {
        CreateDefaultImage();
        _image = Sprite::CreateSprite("A2DE_DefaultMouse", DEFAULT_MOUSE_IMAGE);
        DEFAULT_MOUSE_IMAGE = nullptr;
        focusX = 0;
        focusY = 0;
    }
    _focus = Vector2D(focusX, focusY);
    _dirtyImage = true;
}

bool Mouse::IsVisible() {
    return _isVisible;
}
void Mouse::SetVisible(bool visible) {
    _isVisible = visible;
}

void Mouse::Show(BITMAP* dest) {
    if(dest) {
        if(_image == nullptr) {
            show_mouse(dest);
        } else {
            show_mouse(nullptr);
            draw_sprite(dest, _image->GetImage(), GetX() + -_focus.GetX(), GetY() + -_focus.GetY());
        }
    } else {
        show_mouse(nullptr);
    }
}
void Mouse::Show(const GameWindow& dest) {
    Show(dest.GetBackBuffer());
}
void Mouse::Hide() {
    Show(nullptr);
}

void Mouse::SetImageToDefault() {
    SetImage(nullptr, 0, 0);
}

a2de::Vector3D Mouse::GetPosition3d() const {
    return _position;
}

a2de::Vector3D Mouse::GetPosition3d() {
    return static_cast<const Mouse&>(*this).GetPosition3d();
}

a2de::Vector2D Mouse::GetPosition2d() const {
    return _position;
}

a2de::Vector2D Mouse::GetPosition2d() {
    return static_cast<const Mouse&>(*this).GetPosition2d();
}

void Mouse::SetPosition(const a2de::Vector2D& pos) {
    SetPosition(pos.GetX(), pos.GetY(), GetZ());
}

void Mouse::SetPosition(const a2de::Vector3D& pos) {
    SetPosition(pos.GetX(), pos.GetY(), pos.GetZ());
}

a2de::Vector3D Mouse::GetMickeys3d() const {
    return _mickeys;
}

a2de::Vector3D Mouse::GetMickeys3d() {
    return static_cast<const Mouse&>(*this).GetMickeys3d();
}

a2de::Vector2D Mouse::GetMickeys2d() const {
    return Vector2D(_mickeys);
}

a2de::Vector2D Mouse::GetMickeys2d() {
    return static_cast<const Mouse&>(*this).GetMickeys2d();
}

a2de::Vector2D Mouse::GetFocus() const {
    return _focus;
}

a2de::Vector2D Mouse::GetFocus() {
    return static_cast<const Mouse&>(*this).GetFocus();
}


A2DE_END