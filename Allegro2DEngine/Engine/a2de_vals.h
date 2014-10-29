/**************************************************************************************************
// file:	Engine\a2de_vals.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Global header for a2de compiler values.
 **************************************************************************************************/
#ifndef A2DE_VALS
#define A2DE_VALS

#ifdef _DEBUG
#define DEBUGMODE
#endif

#include <allegro/base.h>
#include <allegro/system.h>

#ifdef _DEBUG
#include <allegro/debug.h>
#endif

#if ALLEGRO_VERSION == 4
#  if ALLEGRO_SUB_VERSION < 2
#    error Allegro sub version must be version 4.2 or greater!
#  endif
#  if ALLEGRO_WIP_VERSION < 2
#    error Allegro WIP version must be version 4.2.2 or greater!
#  endif
#elif ALLEGRO_VERSION != 4
#  error Allegro version must be version 4.x!
#endif

#if defined(__cplusplus)
#  define A2DE_BEGIN namespace a2de {
#  define A2DE_END }
#  define A2DE ::a2de::
#else
#  error Allegro 2D Engine does not work in any language other than c++!
#endif

#endif