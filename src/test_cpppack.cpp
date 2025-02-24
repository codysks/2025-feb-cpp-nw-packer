#include "cpppack.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <cstring>

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

void pack_unsigned(void) {
    uint8_t u8__1 = 0x01;
    uint16_t u16__1 = 0x0203;
    uint32_t u32__1 = 0x04050607;
    uint64_t u64__1 = 0x08090a0b0c0d0e0f;

    unsigned char check_buffer[21600] = { 0 };
    packu64(check_buffer, u64__1);
    packu32(check_buffer + 10, u32__1);
    packu16(check_buffer + 20, u16__1);
    packu8(check_buffer + 30, u8__1);
    assert(!memcmp(check_buffer,
    "\010\011\012\013\014\015\016\017\000\000"
    "\004\005\006\007\000\000\000\000\000\000"
    "\002\003\000\000\000\000\000\000\000\000"
    "\001\000\000\000\000\000\000\000\000\000"
    , 40));
}
} /* namespace fn_test */
int main(void) {
	fn_test::pack_unsigned();

	return 0;

}
