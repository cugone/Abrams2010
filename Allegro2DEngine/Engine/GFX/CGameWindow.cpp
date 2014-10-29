/**************************************************************************************************
// file:	Engine\GFX\CGameWindow.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the game Windows Form
 **************************************************************************************************/
#include "CGameWindow.h"

#include <allegro/system.h>
#include <allegro/gfx.h>
#include <allegro/draw.h>
#include <allegro/joystick.h>
#include <allegro/platform/alwin.h>

#include "../a2de_exceptions.h"
#include "../Input/CMouse.h"

#include <sstream>

A2DE_BEGIN

GameWindow::GameWindow()
 : _window_mode(a2de::GameWindow::WINDOWMODE_WINDOWED),
   _dimensions(640, 480),
   _depth(32),
   _mouse(nullptr),
   _modes(nullptr),
   _title(""),
   _backbuffer(create_bitmap_ex(_depth, _dimensions.first, _dimensions.second)) {
       if(_backbuffer == nullptr) throw Exception("Backbuffer creation failed.");
}

GameWindow::GameWindow(a2de::GameWindow::WINDOWMODE mode) 
  : _window_mode(mode),
    _dimensions(640, 480),
    _depth(32),
    _mouse(nullptr),
    _modes(nullptr),
    _title(""),
    _backbuffer(create_bitmap_ex(_depth, _dimensions.first, _dimensions.second)) {
        if(_backbuffer == nullptr) throw Exception("Backbuffer creation failed.");
}

GameWindow::GameWindow(a2de::GameWindow::WINDOWMODE mode, int width, int height) 
    : _window_mode(mode),
    _dimensions(width, height),
    _depth(32),
    _mouse(nullptr),
    _modes(nullptr),
    _title(""),
    _backbuffer(create_bitmap_ex(_depth, _dimensions.first, _dimensions.second)) { 

        if(_backbuffer == nullptr) {
            throw Exception("Backbuffer creation failed.");
        }

        if(width < 0) {
            destroy_bitmap(_backbuffer);
            throw InvalidArgumentException("Screen width must be a non-negative integer.");
        }
        if(height < 1) {
            destroy_bitmap(_backbuffer);
            throw InvalidArgumentException("Screen height must be a non-zero positive integer.");
        }
}

/*************************************************************************************/
/* Trim function courtesy of GManNickG via http://stackoverflow.com/a/1798170/421178 */
/*************************************************************************************/
std::string trim(std::string& str, const std::string& whitespace = " \t")
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

GameWindow::GameWindow(a2de::GameWindow::WINDOWMODE mode, int width, int height, const std::string& title) 
    : _window_mode(mode),
    _dimensions(width, height),
    _depth(32),
    _mouse(nullptr),
    _modes(nullptr),
    _title(title),
    _backbuffer(create_bitmap_ex(_depth, _dimensions.first, _dimensions.second)) {

    if(_backbuffer == nullptr) {
        throw Exception("Backbuffer creation failed.");
    }

	if(width < 0) {
        destroy_bitmap(_backbuffer);
        throw InvalidArgumentException("Screen width must be a non-negative integer.");
    }
	if(height < 1) {
        destroy_bitmap(_backbuffer);
        throw InvalidArgumentException("Screen height must be a non-zero positive integer.");
    }

}

GameWindow::~GameWindow() {
    //If Mouse object wasn't properly destroyed _mouse returns a non-NULL value
    //and GetNumButtons is still valid.
    if(_mouse != nullptr && _mouse->GetNumButtons() != -1) {
        delete _mouse;
    }
    _mouse = nullptr;

    if(_backbuffer != nullptr) {
        destroy_bitmap(_backbuffer);
        _backbuffer = nullptr;
    }
	if(_modes != nullptr) {
		destroy_gfx_mode_list(_modes);
		_modes = nullptr;
	}
}

bool GameWindow::IsWindowed() const {
    return _window_mode == a2de::GameWindow::WINDOWMODE_WINDOWED;
}
int GameWindow::GetWidth() const {
    return _dimensions.first;
}
int GameWindow::GetHeight() const {
    return _dimensions.second;
}
int GameWindow::GetDepth() const {
    return _depth;
}
BITMAP* GameWindow::GetBackBuffer() const {
    return _backbuffer;
}

void GameWindow::SetResolution() {
	_resolution = set_gfx_mode((IsWindowed() ? GFX_DIRECTX_WIN : GFX_DIRECTX_ACCEL) , _dimensions.first, _dimensions.second, 0, 0);
    if(_resolution != 0 ) {
        std::ostringstream ss;
        ss << "Resolution " << _dimensions.first << 'x' << _dimensions.second << " not supported by output device.";
        throw Exception(ss.str());
    }
}

bool GameWindow::RequestResolution(int width, int height) {
    _resolution = set_gfx_mode((IsWindowed() ? GFX_DIRECTX_WIN : GFX_DIRECTX_ACCEL) , width, height, 0, 0);
    if(_resolution != 0) {
        _resolution = set_gfx_mode((IsWindowed() ? GFX_DIRECTX_WIN : GFX_DIRECTX_ACCEL) , _dimensions.first, _dimensions.second, 0, 0);
        return false;
    }

    destroy_bitmap(_backbuffer);
    _backbuffer = create_bitmap_ex(_depth, width, height);
    if(_backbuffer == nullptr) {
        _resolution = set_gfx_mode((IsWindowed() ? GFX_DIRECTX_WIN : GFX_DIRECTX_ACCEL) , _dimensions.first, _dimensions.second, 0, 0);
        destroy_bitmap(_backbuffer);
        _backbuffer = create_bitmap_ex(_depth, _dimensions.first, _dimensions.second);
        return false;
    }

    _dimensions.first = width;
    _dimensions.second = height;
    return true;
}

void GameWindow::RegisterMouse(Mouse* mouse) {
	if(_mouse != nullptr || mouse == nullptr) return;
	_mouse = mouse;
	_mouse->SetVisible(true);
}
void GameWindow::UnRegisterMouse() {
    _mouse->SetVisible(false);
	_mouse = nullptr;
}

void GameWindow::ShowWindow() {
	set_color_depth(_depth);
	try {
		SetResolution();
	} catch(Exception& /*e*/) {
        throw;
	}

    //Trim extra space in user-supplied title.
    _title = trim(_title);
    _title.append("   Created using the Abrams 2D Engine (c) Casey Ugone");
    //Trim extra space from copyright if trimmed user-supplied title is already empty.
    _title = trim(_title);
    set_window_title(_title.c_str());

}
void GameWindow::StartRender() {
	if(_mouse) {
        _mouse->Hide();
    }
    clear_bitmap(_backbuffer);
    acquire_screen();
}

void GameWindow::EndRender() {
    if(_mouse) {
        if(_mouse->IsVisible()) {
            _mouse->Show(_backbuffer);
        } else {
            _mouse->Show(nullptr);
        }
    }
    blit(_backbuffer, screen, 0, 0, 0, 0, _dimensions.first, _dimensions.second);
    release_screen();
}

bool GameWindow::EnumerateResolutions() {
	if(IsWindowed()) {
		_modes = get_gfx_mode_list(GFX_DIRECTX_WIN);
	} else {
		_modes = get_gfx_mode_list(GFX_DIRECTX_ACCEL);
	}
	if(_modes == nullptr) return false;
	return true;
}
void GameWindow::DenumerateResolutions() {
	if(_modes != nullptr) {
		destroy_gfx_mode_list(_modes);
		_modes = nullptr;
	}
}
int GameWindow::GetNumResolutions() const {
	if(_modes != nullptr) return _modes->num_modes;
    return 0;
}
GFX_MODE* GameWindow::GetResolutions() const {
	if(_modes != nullptr) return _modes->mode;
    return nullptr;
}


A2DE_END