/**************************************************************************************************
// file:	Engine\GFX\CSpriteHandler.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the sprite handler class
 **************************************************************************************************/
#include "CSpriteHandler.h"

#include <allegro/matrix.h>
#include <allegro/draw.h>
#include <allegro/color.h>
#include <allegro/3dmaths.h>

#include "CColor.h"
#include "CSprite.h"
#include "../Math/MiscMath.h"
#include "../Math/CShape.h"
#include "../Math/CRectangle.h"
#include <algorithm>
#include "CGameWindow.h"


A2DE_BEGIN

/************************************************************************/
/* DO NOT DEFINE CONSTRUCTORS, DESTRUCTOR, ASSIGNMENT OPERATOR!         */
/************************************************************************/

void SpriteHandler::Draw(BITMAP* dest, Shape* object) {
    if(object == nullptr || dest == nullptr) return;
    object->Draw(dest, object->GetColor(), object->IsFilled());
}

void SpriteHandler::Draw(BITMAP* dest, BITMAP* source, int x, int y, a2de::Color tintColor, unsigned char tintIntensity, unsigned char alpha, bool hasAlphaChannel) {
    if(source == nullptr || dest == nullptr) return;

    /* DO NOTHING
     * Alpha transparency is set to 0. If the bitmap is completely transparent, there's no need to draw anything or perform a complex tinting/alpha operation.
     */
    if(alpha == 0) return;

	if(alpha != 255 && tintIntensity != 0) { //Not fully opaque with a tinting color.
		BITMAP* tempBMP = create_bitmap_ex(32, source->w, source->h);
		clear_bitmap(tempBMP);

        //Copy source to include transparent pixels.
        blit(source, tempBMP, 0, 0, 0, 0, tempBMP->w, tempBMP->h);

		set_trans_blender(getr(tintColor), getg(tintColor), getb(tintColor), alpha);
		draw_lit_sprite(tempBMP, source, 0, 0, tintIntensity);
        if(hasAlphaChannel) set_alpha_blender();
		draw_trans_sprite(dest, tempBMP, x, y);

		destroy_bitmap(tempBMP);
		tempBMP = nullptr;
	} else if(alpha != 255 && tintIntensity == 0) { //Not fully opaque and no tinting color.
		set_trans_blender(255, 255, 255, alpha);
        if(hasAlphaChannel) set_alpha_blender();
		draw_trans_sprite(dest, source, x, y);
    } else if(tintIntensity != 0 && alpha == 255) { //Fully opaque with a tinting color.
		set_trans_blender(getr(tintColor), getg(tintColor), getb(tintColor), 255);
        if(hasAlphaChannel) set_alpha_blender();
		draw_lit_sprite(dest, source, x, y, tintIntensity);
	} else { //Default draw operation. Fully opaque and no tinting color.
        set_trans_blender(255, 255, 255, 255);
        if(hasAlphaChannel) set_alpha_blender();
		draw_trans_sprite(dest, source, x, y);
	}
}
void SpriteHandler::Draw(BITMAP* dest, Sprite* sprite) {
    if(sprite == nullptr || dest == nullptr) return;
    Draw(dest, sprite->GetImage(), a2de::Math::ToScreenScale(sprite->GetX()), a2de::Math::ToScreenScale(sprite->GetY()), sprite->GetTint(), sprite->GetTintIntensity(), sprite->GetAlpha(), sprite->HasAlphaChannel());
}

void SpriteHandler::DrawFlip(BITMAP* dest, Sprite* sprite, SpriteHandler::SPRITEAXIS axis) {
    if(sprite == nullptr || dest == nullptr) return;
    BITMAP* tempBMP = nullptr;
    if(sprite->GetAlpha() < 255 || sprite->GetTintIntensity() > 0) {
        tempBMP = create_bitmap(sprite->GetWidth(), sprite->GetHeight());
        clear_to_color(tempBMP, Color::MAGENTA());
    }
    switch(axis) {
        case SpriteHandler::AXIS_HORIZONTAL:
            draw_sprite_v_flip((tempBMP != nullptr ? tempBMP : dest), sprite->GetImage(), (tempBMP != nullptr ? 0 : a2de::Math::ToScreenScale(sprite->GetX())), (tempBMP != nullptr ? 0 : a2de::Math::ToScreenScale(sprite->GetY())));
            break;
        case SpriteHandler::AXIS_VERTICAL:
            draw_sprite_h_flip((tempBMP != nullptr ? tempBMP : dest), sprite->GetImage(), (tempBMP != nullptr ? 0 : a2de::Math::ToScreenScale(sprite->GetX())), (tempBMP != nullptr ? 0 : a2de::Math::ToScreenScale(sprite->GetY())));
            break;
        case SpriteHandler::AXIS_BOTH:
            draw_sprite_vh_flip((tempBMP != nullptr ? tempBMP : dest), sprite->GetImage(), (tempBMP != nullptr ? 0 : a2de::Math::ToScreenScale(sprite->GetX())), (tempBMP != nullptr ? 0 : a2de::Math::ToScreenScale(sprite->GetY())));
            break;
    }
    if(tempBMP) {
        Draw(dest, tempBMP, a2de::Math::ToScreenScale(sprite->GetX()), a2de::Math::ToScreenScale(sprite->GetY()), sprite->GetTint(), sprite->GetTintIntensity(), sprite->GetAlpha(), sprite->HasAlphaChannel());
    }
    if(tempBMP) {
        destroy_bitmap(tempBMP);
        tempBMP = nullptr;
    }
}

void SpriteHandler::DrawRotate(BITMAP* dest, Sprite* sprite) {
    if(sprite == nullptr || dest == nullptr) return;
    BITMAP* tempBMP = nullptr;
    if(sprite->GetAlpha() < 255 || sprite->GetTintIntensity() > 0) {
        tempBMP = create_bitmap(sprite->GetWidth(), sprite->GetHeight());
        clear_to_color(tempBMP, Color::MAGENTA());
    }
    if(tempBMP) {
        Draw(tempBMP, sprite->GetImage(), 0, 0, sprite->GetTint(), sprite->GetTintIntensity(), sprite->GetAlpha(), sprite->HasAlphaChannel());
    }
    rotate_sprite(dest, (tempBMP != nullptr ? tempBMP : sprite->GetImage()), a2de::Math::ToScreenScale(sprite->GetX()), a2de::Math::ToScreenScale(sprite->GetY()), Math::RadianToFixed(sprite->GetAngle()));

    if(tempBMP) {
        destroy_bitmap(tempBMP);
        tempBMP = nullptr;
    }
}

void SpriteHandler::DrawRotateScale(BITMAP* dest, Sprite* sprite) {
    if(sprite == nullptr || dest == nullptr) return;
	rotate_scaled_sprite(dest, sprite->GetImage(), a2de::Math::ToScreenScale(sprite->GetX()), a2de::Math::ToScreenScale(sprite->GetY()), Math::RadianToFixed(sprite->GetAngle()), sprite->GetScaleAsFixed());
}

void SpriteHandler::DrawRotateFlip(BITMAP* dest, Sprite* sprite, SpriteHandler::SPRITEAXIS axis) {
    if(sprite == nullptr || dest == nullptr) return;
	switch(axis) {
		case SpriteHandler::AXIS_HORIZONTAL:
			rotate_sprite_v_flip(dest, sprite->GetImage(), a2de::Math::ToScreenScale(sprite->GetX()), a2de::Math::ToScreenScale(sprite->GetY()), Math::RadianToFixed(sprite->GetAngle()));
			break;
		case SpriteHandler::AXIS_VERTICAL:
			rotate_sprite_v_flip(dest, sprite->GetImage(), a2de::Math::ToScreenScale(sprite->GetX()), a2de::Math::ToScreenScale(sprite->GetY()), (Math::RadianToFixed(sprite->GetAngle()) + itofix(128)));
			break;
		case SpriteHandler::AXIS_BOTH:
			rotate_sprite(dest, sprite->GetImage(), a2de::Math::ToScreenScale(sprite->GetX()), a2de::Math::ToScreenScale(sprite->GetY()), (Math::RadianToFixed(sprite->GetAngle()) + itofix(128)));
			break;
	}
}

void SpriteHandler::DrawRotateScaleFlip(BITMAP* dest, Sprite* sprite, SpriteHandler::SPRITEAXIS axis) {
    if(sprite == nullptr || dest == nullptr) return;
	switch(axis) {
		case SpriteHandler::AXIS_HORIZONTAL:
			rotate_scaled_sprite_v_flip(dest, sprite->GetImage(), a2de::Math::ToScreenScale(sprite->GetX()), a2de::Math::ToScreenScale(sprite->GetY()), (Math::RadianToFixed(sprite->GetAngle()) + itofix(128)), sprite->GetScaleAsFixed());
			break;
		case SpriteHandler::AXIS_VERTICAL:
			rotate_scaled_sprite_v_flip(dest, sprite->GetImage(), a2de::Math::ToScreenScale(sprite->GetX()), a2de::Math::ToScreenScale(sprite->GetY()), Math::RadianToFixed(sprite->GetAngle()), sprite->GetScaleAsFixed());
			break;
		case SpriteHandler::AXIS_BOTH:
			rotate_scaled_sprite(dest, sprite->GetImage(), a2de::Math::ToScreenScale(sprite->GetX()), a2de::Math::ToScreenScale(sprite->GetY()), (Math::RadianToFixed(sprite->GetAngle()) + itofix(128)), sprite->GetScaleAsFixed());
			break;
	}
}

void SpriteHandler::DrawScale(BITMAP* dest, Sprite* sprite) {
    if(sprite == nullptr || dest == nullptr) return;
    stretch_sprite(dest, sprite->GetImage(), a2de::Math::ToScreenScale(sprite->GetX()), a2de::Math::ToScreenScale(sprite->GetY()), a2de::Math::ToScreenScale(sprite->GetWidth()) * sprite->GetScaleX(), a2de::Math::ToScreenScale(sprite->GetHeight()) * sprite->GetScaleY());
}

void SpriteHandler::DrawRotateWorldSpace(BITMAP* dest, Sprite* sprite, int x, int y, int radius) {
    if(sprite == nullptr || dest == nullptr) return;
    pivot_sprite(dest, sprite->GetImage(), a2de::Math::ToScreenScale(x), a2de::Math::ToScreenScale(y), a2de::Math::ToScreenScale(sprite->GetCenterX()) + a2de::Math::ToScreenScale(radius), a2de::Math::ToScreenScale(sprite->GetCenterY()) + a2de::Math::ToScreenScale(radius), Math::RadianToFixed(sprite->GetAngle()));
}

void SpriteHandler::DrawRotateWorldSpaceScale(BITMAP* dest, Sprite* sprite, int x, int y, int radius) {
    if(sprite == nullptr || dest == nullptr) return;
    pivot_scaled_sprite(dest, sprite->GetImage(), a2de::Math::ToScreenScale(x), a2de::Math::ToScreenScale(y), a2de::Math::ToScreenScale(sprite->GetCenterX()) + a2de::Math::ToScreenScale(radius), a2de::Math::ToScreenScale(sprite->GetCenterY()) + a2de::Math::ToScreenScale(radius), Math::RadianToFixed(sprite->GetAngle()), sprite->GetScaleAsFixed());
}
void SpriteHandler::DrawRotateWorldSpaceFlip(BITMAP* dest, Sprite* sprite, int /*x*/, int /*y*/, int radius, SpriteHandler::SPRITEAXIS axis) {
    if(sprite == nullptr || dest == nullptr) return;
    switch(axis) {
    case SpriteHandler::AXIS_HORIZONTAL:
        rotate_sprite_v_flip(dest, sprite->GetImage(), a2de::Math::ToScreenScale(sprite->GetX()) + a2de::Math::ToScreenScale(radius), a2de::Math::ToScreenScale(sprite->GetY()) + a2de::Math::ToScreenScale(radius), Math::RadianToFixed(sprite->GetAngle()));
        break;
    case SpriteHandler::AXIS_VERTICAL:
        rotate_sprite_v_flip(dest, sprite->GetImage(), a2de::Math::ToScreenScale(sprite->GetX()) + a2de::Math::ToScreenScale(radius), a2de::Math::ToScreenScale(sprite->GetY()) + a2de::Math::ToScreenScale(radius), (Math::RadianToFixed(sprite->GetAngle()) + itofix(128)));
        break;
    case SpriteHandler::AXIS_BOTH:
        rotate_sprite(dest, sprite->GetImage(), a2de::Math::ToScreenScale(sprite->GetX()) + a2de::Math::ToScreenScale(radius), a2de::Math::ToScreenScale(sprite->GetY()) + a2de::Math::ToScreenScale(radius), (Math::RadianToFixed(sprite->GetAngle()) + itofix(128)));
        break;
    }
}

void SpriteHandler::DrawRotateWorldSpaceScaleFlip(BITMAP* dest, Sprite* sprite, int x, int y, int radius, SpriteHandler::SPRITEAXIS axis) {
    if(sprite == nullptr || dest == nullptr) return;
    switch(axis) {
    case SpriteHandler::AXIS_HORIZONTAL:
        pivot_scaled_sprite_v_flip(dest, sprite->GetImage(), a2de::Math::ToScreenScale(x), a2de::Math::ToScreenScale(y), a2de::Math::ToScreenScale(sprite->GetCenterX()) + a2de::Math::ToScreenScale(radius), a2de::Math::ToScreenScale(sprite->GetCenterY()) + a2de::Math::ToScreenScale(radius), (Math::RadianToFixed(sprite->GetAngle()) + itofix(128)), sprite->GetScaleAsFixed());
        break;
    case SpriteHandler::AXIS_VERTICAL:
        pivot_scaled_sprite_v_flip(dest, sprite->GetImage(), a2de::Math::ToScreenScale(x), a2de::Math::ToScreenScale(y), a2de::Math::ToScreenScale(sprite->GetCenterX()) + a2de::Math::ToScreenScale(radius), a2de::Math::ToScreenScale(sprite->GetCenterY()) + a2de::Math::ToScreenScale(radius), Math::RadianToFixed(sprite->GetAngle()), sprite->GetScaleAsFixed());
        break;
    case SpriteHandler::AXIS_BOTH:
        pivot_scaled_sprite(dest, sprite->GetImage(), a2de::Math::ToScreenScale(x), a2de::Math::ToScreenScale(y), a2de::Math::ToScreenScale(sprite->GetCenterX()) + a2de::Math::ToScreenScale(radius), a2de::Math::ToScreenScale(sprite->GetCenterY()) + a2de::Math::ToScreenScale(radius), (sprite->GetAngle() + itofix(128)), sprite->GetScaleAsFixed());
        break;
    }
}

A2DE_END