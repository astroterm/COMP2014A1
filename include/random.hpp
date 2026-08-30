#pragma once

#include <random>


class Random {
public:
    Random() : rd(), gen(rd()) {}
    Random(int seed) : gen(seed) {}

    int range(int start, int end) {
        std::uniform_int_distribution dist(start, end);
        return dist(gen);
    }

private:
    std::random_device rd;
    std::mt19937 gen;
};