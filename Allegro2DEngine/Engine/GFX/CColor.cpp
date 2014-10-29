/**************************************************************************************************
// file:	Engine\GFX\CColor.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the color class
 **************************************************************************************************/
#include "CColor.h"
#include <algorithm>
#include <allegro/color.h>

A2DE_BEGIN

    
Color::Color(unsigned char r, unsigned char g, unsigned char b) : _value(makecol(r, g, b)) { /* DO NOTHING */ }

Color::Color(const Color& other) : _value(other._value) { /* DO NOTHING */ }

Color::Color(int value) : _value(0) {
    value = std::min(std::max(0x000000, value), 0xFFFFFF);
    int r = getr(value);
    int g = getg(value);
    int b = getb(value);
    _value = makecol(r, g, b);
}

Color::Color() : _value(0) { }

Color::~Color() {
    _value = -1;
}

Color& Color::operator=(const Color& rhs) {
    if(this == &rhs) return *this;

    this->_value = rhs._value;

    return *this;
}

Color::operator int() const{
    return _value;
}

Color::operator int() {
    return static_cast<const Color&>(*this).operator int();
}

void Color::SetRed(unsigned char r) {
    _value = makecol(r, GetGreen(), GetBlue());
}

unsigned char Color::GetRed() const {
    return getr(_value);
}

unsigned char Color::GetRed() {
    return static_cast<const Color&>(*this).GetRed();
}

void Color::SetGreen(unsigned char g) {
    _value = makecol(GetRed(), g, GetBlue());
}

unsigned char Color::GetGreen() const {
    return getg(_value);
}

unsigned char Color::GetGreen() {
    return static_cast<const Color&>(*this).GetGreen();
}

void Color::SetBlue(unsigned char b) {
    _value = makecol(GetRed(), GetGreen(), b);
}

unsigned char Color::GetBlue() const {
    return getb(_value);
}

unsigned char Color::GetBlue() {
    return static_cast<const Color&>(*this).GetBlue();
}

bool Color::operator==(const Color& rhs) const {
    return (this->_value == rhs._value);
}

bool Color::operator==(const Color& rhs) {
    return static_cast<const Color&>(*this).operator==(rhs);
}

bool operator==(int lhs, const Color& rhs) {
    return Color(lhs) == rhs;
}

bool Color::operator!=(const Color& rhs) const {
    return !(this->_value == rhs._value);
}

bool Color::operator!=(const Color& rhs) {
    return static_cast<const Color&>(*this).operator!=(rhs);
}

bool operator!=(int lhs, const Color& rhs) {
    return rhs.operator!=(lhs);
}

bool Color::operator<(const Color& rhs) const {
    return this->_value < rhs._value;
}

bool Color::operator<(const Color& rhs) {
    return static_cast<const Color&>(*this).operator<(rhs);
}

bool operator<(int lhs, const Color& rhs) {
    return Color(lhs) < rhs;
}

bool Color::operator<=(const Color& rhs) const {
    return !(rhs._value < this->_value);
}

bool Color::operator<=(const Color& rhs) {
    return static_cast<const Color&>(*this).operator<=(rhs);
}

bool operator<=(int lhs, const Color& rhs) {
    return !(rhs < Color(lhs));
}

bool Color::operator>(const Color& rhs) const {
    return rhs._value < this->_value;
}

bool Color::operator>(const Color& rhs) {
    return static_cast<const Color&>(*this).operator>(rhs);
}

bool operator>(int lhs, const Color& rhs) {
    return rhs > Color(lhs);
}

bool Color::operator>=(const Color& rhs) const {
    return !(this->_value < rhs._value);
}

bool Color::operator>=(const Color& rhs) {
    return static_cast<const Color&>(*this).operator>=(rhs);
}

bool operator>=(int lhs, const Color& rhs) {
    return rhs >= Color(lhs);
}


const Color Color::WHITE() {
    return Color(0xFF, 0xFF, 0xFF);
}

const Color Color::SILVER() {
    return Color(0xC0, 0xC0, 0xC0);
}

const Color Color::LIGHT_GREY() {
    return SILVER();
}

const Color Color::LIGHT_GRAY() {
    return LIGHT_GREY();
}

const Color Color::GREY() {
    return Color(0x80, 0x80, 0x80);
}

const Color Color::DARK_GREY() {
    return GREY();
}

const Color Color::DARK_GRAY() {
    return GREY();
}

const Color Color::GRAY() {
    return GREY();
}

const Color Color::BLACK() {
    return Color(0x00, 0x00, 0x00);
}

const Color Color::RED() {
    return Color(0xFF, 0x00, 0x00);
}

const Color Color::MAROON() {
    return Color(0x80, 0x00, 0x00);
}

const Color Color::YELLOW() {
    return Color(0xFF, 0xFF, 0x00);
}

const Color Color::OLIVE() {
    return Color(0x80, 0x80, 0x00);
}

const Color Color::LIME() {
    return Color(0x00, 0xFF, 0x00);
}

const Color Color::GREEN() {
    return Color(0x00, 0x80, 0x00);
}

const Color Color::CYAN() {
    return Color(0x00, 0xFF, 0xFF);
}

const Color Color::AQUA() {
    return CYAN();
}

const Color Color::TEAL() {
    return Color(0x00, 0x80, 0x80);
}

const Color Color::BLUE() {
    return Color(0x00, 0x00, 0xFF);
}

const Color Color::NAVY_BLUE() {
    return Color(0x00, 0x00, 0x80);
}

const Color Color::MAGENTA() {
    return Color(0xFF, 0x00, 0xFF);
}

const Color Color::FUCHSIA() {
    return MAGENTA();
}

const Color Color::PURPLE() {
    return Color(0x80, 0x00, 0x80);
}

const Color Color::ORANGE() {
    return Color(0xFF, 0xA5, 0x00);
}

const Color Color::HOT_PINK() {
    return Color(0xFF, 0x00, 0x80);
}

const Color Color::LIME_GREEN() {
    return Color(0x80, 0xFF, 0x00);
}

const Color Color::SEAFOAM_GREEN() {
    return Color(0x00, 0xFF, 0x80);
}

const Color Color::VIOLET() {
    return Color(0x80, 0x00, 0xFF);
}

const Color Color::SKY_BLUE() {
    return Color(0x00, 0x80, 0xFF);
}

const Color Color::BROWN() {
    return Color(0x80, 0x40, 0x00);
}

const Color Color::PINK() {
    return MAGENTA();
}


A2DE_END