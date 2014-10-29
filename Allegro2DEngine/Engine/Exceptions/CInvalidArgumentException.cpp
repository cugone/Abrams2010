/**************************************************************************************************
// file:	Engine\Exceptions\CInvalidArgumentException.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the invalid argument exception class
 **************************************************************************************************/
#include "CInvalidArgumentException.h"

A2DE_BEGIN

InvalidArgumentException::InvalidArgumentException(const std::string& message) : std::invalid_argument(message), _message(message) {
    /* DO NOTHING */
}

a2de::InvalidArgumentException::~InvalidArgumentException() {
    /* DO NOTHING */
}

a2de::InvalidArgumentException::InvalidArgumentException(const char* message) : std::invalid_argument(message), _message(message) {
    /* DO NOTHING */
}

std::string a2de::InvalidArgumentException::GetMessage() const {
    return _message;
}

std::string InvalidArgumentException::GetMessage() {
    return static_cast<const InvalidArgumentException&>(*this).GetMessage();
}

const char* a2de::InvalidArgumentException::what() const {
    return _message.c_str();
}

A2DE_END