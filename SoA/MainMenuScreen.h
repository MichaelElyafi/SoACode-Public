// 
//  MainMenuScreen.h
//  Seed Of Andromeda
//
//  Created by Ben Arnold on 17 Oct 2014
//  Copyright 2014 Regrowth Studios
//  All Rights Reserved
//  
//  This file provides the main menu screen
//  implementation. This screen encompasses the
//  gamestate for the main menu, as well as interaction
//  with the user interface.
//

#pragma once

#ifndef MAINMENUSCREEN_H_
#define MAINMENUSCREEN_H_

#include <Vorb/AwesomiumInterface.h>
#include <Vorb/IGameScreen.h>
#include <Vorb/Random.h>
#include <Vorb/VorbPreDecl.inl>

#include "MainMenuAPI.h"
#include "LoadMonitor.h"
#include "MainMenuRenderPipeline.h"

class App;
struct TerrainMeshMessage;
DECL_VSOUND(class, Engine)
class AmbienceLibrary;
class AmbiencePlayer;

class MainMenuScreen : public IAppScreen<App>
{
    friend class MainMenuAPI; ///< MainMenuAPI needs to talk directly to the MainMenuScreen
public:
    CTOR_APP_SCREEN_DECL(MainMenuScreen, App);

    virtual i32 getNextScreen() const;
    virtual i32 getPreviousScreen() const;

    virtual void build();
    virtual void destroy(const GameTime& gameTime);

    virtual void onEntry(const GameTime& gameTime);
    virtual void onExit(const GameTime& gameTime);

    virtual void onEvent(const SDL_Event& e);
    virtual void update(const GameTime& gameTime);
    virtual void draw(const GameTime& gameTime);

    // Getters
    CinematicCamera& getCamera() { return _camera; }
    vio::IOManager& getIOManager() { return _ioManager; }

private:

    /// Initializes the rendering
    void initRenderPipeline();

    /// Loads a save file and prepares to play the game
    /// @param fileName: The name of the save file
    void loadGame(const nString& fileName);

    /// Makes a new save file and prepares to play the game
    /// @param fileName: The name of the save file
    void newGame(const nString& fileName);

    /// The function that runs on the update thread. It handles
    /// loading the planet in the background.
    void updateThreadFunc();

    /// Updates the dynamic clipping plane for the world camera
    void updateWorldCameraClip();

    vui::AwesomiumInterface<MainMenuAPI> _awesomiumInterface; ///< The user interface
    
    vio::IOManager _ioManager; ///< Helper class for IO operations

    CinematicCamera _camera; ///< The camera that looks at the planet from space

    std::thread* _updateThread; ///< The thread that updates the planet. Runs updateThreadFunc()
    volatile bool _threadRunning; ///< True when the thread should be running

    MainMenuRenderPipeline _renderPipeline; ///< This handles all rendering for the main menu

    // TODO: Remove to a client state
    vsound::Engine* m_engine;
    AmbienceLibrary* m_ambLibrary;
    AmbiencePlayer* m_ambPlayer;
};

#endif // MAINMENUSCREEN_H_