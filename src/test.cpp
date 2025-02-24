#include "pack.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <iomanip>

#define ETRACE(X) TRACE(X, "", "\n", std::cerr)
#define ETRACENNL(X) TRACE(X, "", "", std::cerr)

#define TRACE(X, HEAD, TAIL, OUT) [&](){ \
    std::cerr << HEAD #X ":0x" \
        << std::hex << std::setw(sizeof(X) * 2) << std::setfill('0') \
        << (size_t)(X) \
        << TAIL; \
        }()

namespace byte {
static inline
constexpr uint16_t swap16(uint16_t x) {
    return (x << 8) | (x >> 8);
}
static_assert(0xDEAD == swap16(0xADDE));
static inline
constexpr uint32_t swap32(uint32_t x) {
    return ((uint32_t)swap16(x & 0xffff) << 16) | swap16(x >> 16);
}
static_assert(0xDEADBEEF == swap32(0xEFBEADDE));
static inline
constexpr uint64_t swap64(uint64_t x) {
    return ((uint64_t)swap32(x & 0xffffffff) << 32) | swap32(x >> 32);
}
static_assert(0xDEADBEEF01020309 == swap64(0x09030201EFBEADDE));
}
namespace fn_test {
void unpack_unsigned(void) {
    constexpr size_t BUFFER_MAX_SIZE = 21600;
    unsigned char buffer[BUFFER_MAX_SIZE] = { 0 };
    for (size_t i = 0; i < BUFFER_MAX_SIZE; ++i) {
        buffer[i] = i % 256;
    }
    uint8_t u8_array[256];
    for (size_t i = 0; i < 256; ++i) {
        u8_array[i] = unpacku8(buffer + i);
    }
    for (size_t i = 0; i < 256; ++i) {
        assert(u8_array[i] == i);
    }

    uint16_t u16_array[256];
    for (size_t i = 0; i < 256; ++i) {
        u16_array[i] = unpacku16(buffer + i);
    }
    uint16_t expected16 = 0;
    for (size_t i = 0; i < 256; ++i) {
        expected16 = (expected16 << 8) | ((i + 1) & 0xff);

        assert(u16_array[i] == expected16);
    }

    uint32_t u32_array[256];
    for (size_t i = 0; i < 256; ++i) {
        u32_array[i] = unpacku32(buffer + i);
    }
    uint32_t expected32 = 0x0102;
    for (size_t i = 0; i < 256; ++i) {
        expected32 = (expected32 << 8) | ((i + 3) & 0xff);
        assert(u32_array[i] == expected32);
    }

    uint64_t u64_array[256];
    for (size_t i = 0; i < 256; ++i) {
        u64_array[i] = unpacku64(buffer + i);
    }
    uint64_t expected64 = 0x010203040506;
    for (size_t i = 0; i < 256; ++i) {
        expected64 = (expected64 << 8) | ((i + 7) & 0xff);
        assert(u64_array[i] == expected64);
    }
}
void unpack_unsigned_little_endian(void) {
    constexpr size_t BUFFER_MAX_SIZE = 21600;
    unsigned char buffer[BUFFER_MAX_SIZE] = { 0 };
    for (size_t i = 0; i < BUFFER_MAX_SIZE; ++i) {
        buffer[i] = i % 256;
    }
    uint8_t u8_array[256];
    for (size_t i = 0; i < 256; ++i) {
        u8_array[i] = unpacku8le(buffer + i);
    }
    for (size_t i = 0; i < 256; ++i) {
        assert(u8_array[i] == i);
    }
    uint16_t u16_array[256];
    for (size_t i = 0; i < 256; ++i) {
        u16_array[i] = unpacku16le(buffer + i);
    }
    uint16_t expected16 = 0;
    for (size_t i = 0; i < 256; ++i) {
        expected16 = (expected16 << 8) | ((i + 1) & 0xff);
        assert(u16_array[i] == byte::swap16(expected16));
    }

    uint32_t u32_array[256];
    for (size_t i = 0; i < 256; ++i) {
        u32_array[i] = unpacku32le(buffer + i);
    }
    uint32_t expected32 = 0x0102;
    for (size_t i = 0; i < 256; ++i) {
        expected32 = (expected32 << 8) | ((i + 3) & 0xff);

        assert(u32_array[i] == byte::swap32(expected32));
    }

    uint64_t u64_array[256];
    for (size_t i = 0; i < 256; ++i) {
        u64_array[i] = unpacku64le(buffer + i);
    }
    uint64_t expected64 = 0x010203040506;
    for (size_t i = 0; i < 256; ++i) {
        expected64 = (expected64 << 8) | ((i + 7) & 0xff);
        
        assert(u64_array[i] == byte::swap64(expected64));
    }

}
void unpack_unsigned_type_generic(void) {
    constexpr size_t BUFFER_MAX_SIZE = 21600;
    unsigned char buffer[BUFFER_MAX_SIZE] = { 0 };
    for (size_t i = 0; i < BUFFER_MAX_SIZE; ++i) {
        buffer[i] = i % 256;
    }
    uint8_t u8_array[256] = { 0 };
    uint8_t* u8_ptr = u8_array;

    for (size_t i = 0; i < 256; ++i) {
        u8_ptr = tgunpacku(buffer + i, u8_ptr);
    }
    for (size_t i = 0; i < 256; ++i) {
        assert(u8_array[i] == i);
    }

    uint16_t u16_array[256];
    uint16_t* u16_ptr = u16_array;
    for (size_t i = 0; i < 256; ++i) {
        u16_ptr = tgunpacku(buffer + i, u16_ptr);
    }
    uint16_t expected16 = 0;
    for (size_t i = 0; i < 256; ++i) {
        expected16 = (expected16 << 8) | ((i + 1) & 0xff);
        assert(u16_array[i] == expected16);
    }

    uint32_t u32_array[256];
    uint32_t* u32_ptr = u32_array;
    for (size_t i = 0; i < 256; ++i) {
        u32_ptr = tgunpacku(buffer + i, u32_ptr);
    }
    uint32_t expected32 = 0x0102;
    for (size_t i = 0; i < 256; ++i) {
        expected32 = (expected32 << 8) | ((i + 3) & 0xff);
        assert(u32_array[i] == expected32);
    }

    uint64_t u64_array[256];
    uint64_t* u64_ptr = u64_array;
    for (size_t i = 0; i < 256; ++i) {
        u64_ptr = tgunpacku(buffer + i, u64_ptr);
    }
    uint64_t expected64 = 0x010203040506;
    for (size_t i = 0; i < 256; ++i) {
        expected64 = (expected64 << 8) | ((i + 7) & 0xff);
        assert(u64_array[i] == expected64);
    }
}
void unpack_unsigned_little_endian_type_generic(void) {
    constexpr size_t BUFFER_MAX_SIZE = 21600;
    unsigned char buffer[BUFFER_MAX_SIZE] = { 0 };
    for (size_t i = 0; i < BUFFER_MAX_SIZE; ++i) {
        buffer[i] = i % 256;
    }
    uint8_t u8_array[256] = { 0 };
    uint8_t* u8_ptr = u8_array;

    for (size_t i = 0; i < 256; ++i) {
        u8_ptr = tgunpackule(buffer + i, u8_ptr);
    }
    for (size_t i = 0; i < 256; ++i) {
        assert(u8_array[i] == i);
    }

    uint16_t u16_array[256];
    uint16_t* u16_ptr = u16_array;
    for (size_t i = 0; i < 256; ++i) {
        u16_ptr = tgunpackule(buffer + i, u16_ptr);
    }
    uint16_t expected16 = 0;
    for (size_t i = 0; i < 256; ++i) {
        expected16 = (expected16 << 8) | ((i + 1) & 0xff);
        assert(u16_array[i] == byte::swap16(expected16));
    }

    uint32_t u32_array[256];
    uint32_t* u32_ptr = u32_array;
    for (size_t i = 0; i < 256; ++i) {
        u32_ptr = tgunpackule(buffer + i, u32_ptr);
    }
    uint32_t expected32 = 0x0102;
    for (size_t i = 0; i < 256; ++i) {
        expected32 = (expected32 << 8) | ((i + 3) & 0xff);
        assert(u32_array[i] == byte::swap32(expected32));
    }

    uint64_t u64_array[256];
    uint64_t* u64_ptr = u64_array;
    for (size_t i = 0; i < 256; ++i) {
        u64_ptr = tgunpackule(buffer + i, u64_ptr);
    }
    uint64_t expected64 = 0x010203040506;
    for (size_t i = 0; i < 256; ++i) {
        expected64 = (expected64 << 8) | ((i + 7) & 0xff);
        assert(u64_array[i] == byte::swap64(expected64));
    }
}
} /* namespace fn_test */

int main(void) {
    fn_test::unpack_unsigned();
    fn_test::unpack_unsigned_little_endian();
    fn_test::unpack_unsigned_type_generic();
    fn_test::unpack_unsigned_little_endian_type_generic();
	std::cout << "ok" << std::endl;
	return 0;
}
