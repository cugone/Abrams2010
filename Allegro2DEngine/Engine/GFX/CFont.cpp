/**************************************************************************************************
// file:	Engine\GFX\CFont.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the font class
 **************************************************************************************************/
#include "CFont.h"
#include "../a2de_exceptions.h"

A2DE_BEGIN

Font::Font(std::string file) : _file(file), _font(load_bitmap_font(_file.c_str(), nullptr, nullptr)), _height(0) {
	if(_font) _height = text_height(_font);
}

Font* Font::CreateFont(std::string file) {
	if(exists(file.c_str()) == false) {
        throw FileNotFoundException(file);
    }
    if(std::string(get_extension(file.c_str())).compare("bmp") != 0) {
        throw TypeNotSupportedException("Non-.bmp");
    }
	return (new Font(file));
}
Font::~Font() {
    //If _font is a synonym to Allegro's font object do not destroy it!
	if(_font != font) destroy_font(_font);
    _font = nullptr;
	_file.clear();
	_height = 0;
}
FONT* Font::GetFont() const {
	return _font;
}
std::string Font::GetFilename() const {
	return _file;
}

unsigned int Font::GetHeight() const {
	return _height;
}
unsigned int Font::GetHeight(FONT* fontobj) {
	return text_height(fontobj);
}
unsigned long Font::GetLength(std::string text) {
	return (text_length(_font, text.c_str()));
}

unsigned long Font::GetLength(FONT* fontobj, std::string text) {
	return (text_length(fontobj, text.c_str()));
}

void Font::AdjustFont(std::string file) {
    if(exists(file.c_str()) == false) {
        throw FileNotFoundException(file);
    }

	_file = file;
    if(_font != font) destroy_font(_font);
    _font = nullptr;
	_font = load_bitmap_font(file.c_str(), nullptr, nullptr);
    _height = 0;
    if(_font) {
        _height = text_height(_font);
    }
}

A2DE_END