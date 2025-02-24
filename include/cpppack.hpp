#ifndef CPP_NW_PACK_HPP
#define CPP_NW_PACK_HPP

#include <cstdint>
#include <cstddef>
#include <iostream>

static inline
void packu8(void* buffer, uint8_t x) {
    auto p = (unsigned char*) buffer;
    p[0] = (unsigned char)(x >> (8 * (sizeof(x) - 1 - 0)));
}

static inline
void packu16(void* buffer, uint16_t x) {
    auto p = (unsigned char*) buffer;
    p[0] = (unsigned char)(x >> (8 * (sizeof(x) - 1 - 0)));
    p[1] = (unsigned char)(x >> (8 * (sizeof(x) - 1 - 1)));
}

static inline
void packu32(void* buffer, uint32_t x) {
    auto p = (unsigned char*) buffer;
    p[0] = (unsigned char)(x >> (8 * (sizeof(x) - 1 - 0)));
    p[1] = (unsigned char)(x >> (8 * (sizeof(x) - 1 - 1)));
    p[2] = (unsigned char)(x >> (8 * (sizeof(x) - 1 - 2)));
    p[3] = (unsigned char)(x >> (8 * (sizeof(x) - 1 - 3)));
}

static inline
void packu64(void* buffer, uint64_t x) {
    auto p = (unsigned char*) buffer;
    p[0] = (unsigned char)(x >> (8 * (sizeof(x) - 1 - 0)));
    p[1] = (unsigned char)(x >> (8 * (sizeof(x) - 1 - 1)));
    p[2] = (unsigned char)(x >> (8 * (sizeof(x) - 1 - 2)));
    p[3] = (unsigned char)(x >> (8 * (sizeof(x) - 1 - 3)));
    p[4] = (unsigned char)(x >> (8 * (sizeof(x) - 1 - 4)));
    p[5] = (unsigned char)(x >> (8 * (sizeof(x) - 1 - 5)));
    p[6] = (unsigned char)(x >> (8 * (sizeof(x) - 1 - 6)));
    p[7] = (unsigned char)(x >> (8 * (sizeof(x) - 1 - 7)));
}

static inline
void packu8le(void* buffer, uint8_t x) {
    auto p = (unsigned char*) buffer;
    p[0] = (unsigned char)(x >> (8 * 0));
}

static inline
void packu16le(void* buffer, uint16_t x) {
    auto p = (unsigned char*) buffer;
    p[0] = (unsigned char)(x >> (8 * 0));
    p[1] = (unsigned char)(x >> (8 * 1));
}

static inline
void packu32le(void* buffer, uint32_t x) {
    auto p = (unsigned char*) buffer;
    p[0] = (unsigned char)(x >> (8 * 0));
    p[1] = (unsigned char)(x >> (8 * 1));
    p[2] = (unsigned char)(x >> (8 * 2));
    p[3] = (unsigned char)(x >> (8 * 3));
}

static inline
void packu64le(void* buffer, uint64_t x) {
    auto p = (unsigned char*) buffer;
    p[0] = (unsigned char)(x >> (8 * 0));
    p[1] = (unsigned char)(x >> (8 * 1));
    p[2] = (unsigned char)(x >> (8 * 2));
    p[3] = (unsigned char)(x >> (8 * 3));
    p[4] = (unsigned char)(x >> (8 * 4));
    p[5] = (unsigned char)(x >> (8 * 5));
    p[6] = (unsigned char)(x >> (8 * 6));
    p[7] = (unsigned char)(x >> (8 * 7));
}

#endif /* CPP_NW_PACK_HPP */
