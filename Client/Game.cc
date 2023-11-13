#include <Client/Game.hh>

#include <iostream>

#include <Shared/Utilities.hh>

using namespace gardn;

Game::Game() {
    puts("init");
    socket.Connect("ws://127.0.0.1:1234");
}

void Game::Tick(float delta) {
    renderer.ResetTransform();
    if (camera_id != NULL_ENTITY && playing) {
        renderer.Translate(renderer.width / 2, renderer.height / 2);
    }    
}