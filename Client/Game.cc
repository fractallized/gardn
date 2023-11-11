#include <Game.hh>

#include <iostream>

using namespace gardn;

Game::Game() {
    puts("init");
}

void Game::Tick(float delta) {
    renderer.SetTransform(1,0,0,1,0,0);
    renderer.ClearRect(0,0,150,250);
    renderer.FillRect(0,0,150,250);
}