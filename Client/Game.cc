#include <Game.hh>

#include <iostream>

#include <Shared/Utilities.hh>

using namespace gardn;

Game::Game() {
    puts("init");
    /*
    uint8_t buf[1024];
    binary::Protocol<0> coder(&buf[0]);
    coder.WriteUint8(123);
    coder.WriteVarUint(123);
    coder.WriteVarInt(-123);
    coder.WriteFloat(0.1);
    utilities::HexDump(&buf[0], 15);
    binary::Protocol<0> coder2(&buf[0]);
    printf("%d %llu %lld %f\n", coder2.ReadUint8(), coder2.ReadVarUint(), coder2.ReadVarInt(), coder2.ReadFloat());

    binary::Protocol<0> coder3(&buf[0]);
    uint8_t a = 123;
    uint64_t b = 129;
    int64_t c = -129;
    float d = 0.9;
    coder3.Code<0>(a);
    coder3.Code<0>(b);
    coder3.Code<0>(c);
    coder3.Code<0>(d);
    utilities::HexDump(&buf[0], 15);
    binary::Protocol<0> coder4(&buf[0]);
    coder4.Code<1>(a);
    coder4.Code<1>(b);
    coder4.Code<1>(c);
    coder4.Code<1>(d);
    printf("%d %llu %lld %f\n", a, b, c, d);
    */
}

void Game::Tick(float delta) {
    renderer.ResetTransform();
    renderer.ClearRect(0,0,renderer.width,renderer.height);
    renderer.FillRect(0,0,150,250);
    renderer.SetFill(0xff123456);
    renderer.SetStroke(0xff654321);
    renderer.BeginPath();
    renderer.Arc(150, 260, 57);
    renderer.Fill();
}