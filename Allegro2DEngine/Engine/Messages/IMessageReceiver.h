/**************************************************************************************************
// file:	Engine\Messages\IMessageReceiver.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the IMessageReceiver interface
 **************************************************************************************************/
#ifndef A2DE_IMESSAGERECEIVER_H
#define A2DE_IMESSAGERECEIVER_H

#include "../a2de_vals.h"

A2DE_BEGIN

class Message;

class IMessageReceiver {
public:
    virtual void ReceiveMessage(Message* msg) = 0;
    virtual ~IMessageReceiver() { /* DO NOTHING */ }
};

A2DE_END

#endif