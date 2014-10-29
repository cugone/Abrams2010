/**************************************************************************************************
// file:	Engine\Games\ADTGame.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the adt game class
 **************************************************************************************************/
#include "ADTGame.h"

#include "../a2de_exceptions.h"

A2DE_BEGIN

Game::Game(a2de::GameWindow* window) : _FRAME_RATE(1.0 / 60.0), _MAX_FRAME_TIME(_FRAME_RATE * 2.0), _deltaTime(_FRAME_RATE), _gameTime(), _gameWindow(nullptr), _isQuitting(false) {
    try {
        init(window);
    } catch(...) {
        throw;
    }
}

Game::Game(double frame_rate, double max_frame_time, a2de::GameWindow* window) : _FRAME_RATE(1.0 / frame_rate), _MAX_FRAME_TIME(max_frame_time), _deltaTime(_FRAME_RATE), _gameTime(), _gameWindow(nullptr), _isQuitting(false) {
    try {
        init(window);
    } catch(...) {
        throw;
    }
}

Game::~Game() {
    deinit();
}

void Game::init(a2de::GameWindow* window) {
    try {
        if(window == nullptr) throw a2de::Exception("GameWindow must not be null.");
        _gameWindow = window;
        _gameWindow->ShowWindow();
    } catch(...) {
        deinit();
        throw;
    }
}

void Game::deinit() {
    delete _gameWindow;
    _gameWindow = nullptr;
}

void Game::MainLoop() {
    _gameTime.Start();
    clock_t currentTime = clock();
    double accumulator = _deltaTime;
    while(!_isQuitting) {
        clock_t newTime = clock();
        double frameTime = difftime(newTime, currentTime) / CLOCKS_PER_SEC;
        if(frameTime > _MAX_FRAME_TIME) frameTime = _MAX_FRAME_TIME;
        currentTime = newTime;
        accumulator += frameTime;
        while(accumulator >= _deltaTime) {
            this->Processing(_gameTime, _deltaTime);
            accumulator -= _deltaTime;
        }
        this->Render(_gameTime, _deltaTime);
    }
    _gameTime.Stop();
}

void Game::Run(int argc, char** argv) {
    if(this->Initialize(argc, argv)) MainLoop();
    this->CleanUp();
}

bool Game::Initialize(int /*argc*/, char** /*argv*/) {
    return true;
}

void Game::Processing(a2de::StopWatch& /*gameTime*/, double /*deltaTime*/) {

}

void Game::Render(a2de::StopWatch& /*gameTime*/, double /*deltaTime*/) {

}

void Game::CleanUp() {

}

a2de::GameWindow* Game::GetWindow() const {
    return _gameWindow;
}

a2de::GameWindow* Game::GetWindow() {
    return static_cast<const Game&>(*this).GetWindow();
}

bool Game::IsQuitting() const {
    return _isQuitting;
}

bool Game::IsQuitting() {
    return static_cast<const Game&>(*this).IsQuitting();
}

void Game::Quit() {
    _isQuitting = true;
}

const a2de::StopWatch& Game::GetGameTime() const {
    return _gameTime;
}

a2de::StopWatch& Game::GetGameTime() {
    return const_cast<a2de::StopWatch&>(static_cast<const Game&>(*this).GetGameTime());
}


A2DE_END
