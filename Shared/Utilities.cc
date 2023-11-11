#include <Shared/Utilities.hh>

#include <cmath>
#include <chrono>
#include <iostream>

using namespace utilities;

void utilities::HexDump(uint8_t const *start, uint64_t size) {
    uint8_t const *end = start + size;
    while (start != end)
        printf("%02X ", *start++);
    puts("");
}

void utilities::HexDump(char const *start, uint64_t size) {
    char const *end = start + size;
    while (start != end)
        printf("%02X ", *start++);
    puts("");
}

uint64_t utilities::GetTime() {
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

Vector::Vector() {
    x = y = 0;
}

Vector::Vector(float _x, float _y) {
    x = _x; y = _y;
}

Vector *Vector::operator=(Vector *v) {
    x = v->x;
    y = v->y;
    return this;
}

Vector &Vector::operator+=(Vector &v) {
    x += v.x;
    y += v.y;
    return *this;
}

Vector &Vector::operator-=(Vector &v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

Vector &Vector::operator*=(float v) {
    x *= v;
    y *= v;
    return *this;
}

bool Vector::operator>(float v) {
    return x * x + y * y > v * v;
}

bool Vector::operator<(float v) {
    return x * x + y * y < v * v;
}

Vector Vector::FromPolar(float r, float t) {
    return Vector(r * cosf(t), r * sinf(t));
}