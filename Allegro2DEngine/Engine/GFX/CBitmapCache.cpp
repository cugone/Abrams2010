/**************************************************************************************************
// file:	Engine\GFX\CBitmapCache.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the bitmap cache class
 **************************************************************************************************/
#include "CBitmapCache.h"

#include <algorithm>
#include <map>

A2DE_BEGIN

//filename or name of bitmap, reference count, memory location...
typedef std::map<std::string, std::pair<long, BITMAP*> > MapStrBmp;
typedef MapStrBmp::iterator MapStrBmpIter;

MapStrBmp BitmapCache::_cache;

BITMAP* BitmapCache::GetBitmap(const std::string& filename) {
    //Return NULL if a bad filename was passed.
    if(filename.empty()) return nullptr;
    if(exists(filename.c_str()) == false) return nullptr;

    //Reduce incorrect results by forcing slash equality.
    std::string f(filename);
    f = fix_filename_slashes(&f[0]);

    //Clean the cache if it's dirty.
    CleanCache();

    //Search for requested BITMAP.
    MapStrBmpIter _iter = _cache.find(f);

    //If found, return it.
    if(_iter != _cache.end()) {
        _iter->second.first++;
        return _iter->second.second;
    }

    //Otherwise, create it, store it, then return it.
    BITMAP* result = load_bitmap(f.c_str(), nullptr);
    if(result == nullptr) return nullptr;
    _cache.insert(std::make_pair(f, std::make_pair(static_cast<long>(1), result)));
    return result;
}

void BitmapCache::StoreBitmap(const std::string& name, BITMAP* bmp) {
    if(name.empty() || bmp == nullptr) return;

    CleanCache();
    std::string n(name);
    n = fix_filename_slashes(&n[0]);
    MapStrBmpIter _iter = _cache.find(n);
    //Bitmap already exists in cache, do not store it.
    if(_iter != _cache.end()) {
        return;
    }
    _cache.insert(std::make_pair(n, std::make_pair(static_cast<long>(0), bmp)));
}

BITMAP* BitmapCache::RetrieveBitmap(const std::string& name) {
    if(name.empty()) return nullptr;

    std::string n(name);
    n = fix_filename_slashes(&n[0]);
    MapStrBmpIter _iter = _cache.find(n);
    if(_iter != _cache.end()) {
        _iter->second.first++;
        return _iter->second.second;
    }
    return nullptr;
}

void BitmapCache::DecrementRefCount(const std::string& name) {
    if(name.empty()) return;

    std::string n(name);
    n = fix_filename_slashes(&n[0]);
    MapStrBmpIter _iter = _cache.find(n);

    if(_iter != _cache.end()) {
        _iter->second.first--;
        CleanCache();
    }
}

void BitmapCache::IncrementRefCount(const std::string& name) {
    if(name.empty()) return;

    std::string n(name);
    n = fix_filename_slashes(&n[0]);
    MapStrBmpIter _iter = _cache.find(n);

    if(_iter != _cache.end()) {
        _iter->second.first++;
    }
}
void BitmapCache::CleanCache() {

    //Clean the cache of any bitmaps that are no longer referenced.
    for(MapStrBmpIter _iter = _cache.begin(); _iter != _cache.end(); /* DO NOTHING */ ) {
        if(_iter->second.first > 0) {
            ++_iter;
            continue;
        }
        destroy_bitmap(_iter->second.second);
        _iter->second.second = nullptr;
        _cache.erase(_iter++);
    }
}

A2DE_END