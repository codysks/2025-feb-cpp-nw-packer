#ifndef FEB_2025_CPP_NW_PACKER_HPP
#define FEB_2025_CPP_NW_PACKER_HPP

#include <cstdint>
#include <cstddef>
#include <iostream>

[[nodiscard]]
static inline
uint8_t unpacku8(void const* buffer) {
    auto p = (unsigned char const*) buffer;
    uint8_t ret =
        (decltype(ret))p[0] << (8 * (sizeof(ret) - 1 - 0));
    return ret;
}
[[nodiscard]]
static inline
uint16_t unpacku16(void const* buffer) {
    auto p = (unsigned char const*) buffer;
    uint16_t ret =
        (decltype(ret))p[0] << (8 * (sizeof(ret) - 1 - 0)) |
        (decltype(ret))p[1] << (8 * (sizeof(ret) - 1 - 1));
    return ret;
}
[[nodiscard]]
static inline
uint32_t unpacku32(void const* buffer) {
    auto p = (unsigned char const*) buffer;
    uint32_t ret =
        (decltype(ret))p[0] << (8 * (sizeof(ret) - 1 - 0)) |
        (decltype(ret))p[1] << (8 * (sizeof(ret) - 1 - 1)) |
        (decltype(ret))p[2] << (8 * (sizeof(ret) - 1 - 2)) |
        (decltype(ret))p[3] << (8 * (sizeof(ret) - 1 - 3));
    return ret;
}
[[nodiscard]]
static inline
uint64_t unpacku64(void const* buffer) {
    auto p = (unsigned char const*) buffer;
    uint64_t ret =
        (decltype(ret))p[0] << (8 * (sizeof(ret) - 1 - 0)) |
        (decltype(ret))p[1] << (8 * (sizeof(ret) - 1 - 1)) |
        (decltype(ret))p[2] << (8 * (sizeof(ret) - 1 - 2)) |
        (decltype(ret))p[3] << (8 * (sizeof(ret) - 1 - 3)) |
        (decltype(ret))p[4] << (8 * (sizeof(ret) - 1 - 4)) |
        (decltype(ret))p[5] << (8 * (sizeof(ret) - 1 - 5)) |
        (decltype(ret))p[6] << (8 * (sizeof(ret) - 1 - 6)) |
        (decltype(ret))p[7] << (8 * (sizeof(ret) - 1 - 7));
    return ret;
}

[[nodiscard]]
static inline
uint8_t unpacku8le(void const* buffer) {
    auto p = (unsigned char const*) buffer;
    uint8_t ret =
        (decltype(ret))p[0] << (8 *  0);
    return ret;
}

[[nodiscard]]
static inline
uint16_t unpacku16le(void const* buffer) {
    auto p = (unsigned char const*) buffer;
    uint16_t ret =
        (decltype(ret))p[0] << (8 *  0) |
        (decltype(ret))p[1] << (8 *  1);
    return ret;
}


[[nodiscard]]
static inline
uint32_t unpacku32le(void const* buffer) {
    auto p = (unsigned char const*) buffer;
    uint32_t ret =
        (decltype(ret))p[0] << (8 *  0) |
        (decltype(ret))p[1] << (8 *  1) |
        (decltype(ret))p[2] << (8 *  2) |
        (decltype(ret))p[3] << (8 *  3);
    return ret;
}

[[nodiscard]]
static inline
uint64_t unpacku64le(void const* buffer) {
    auto p = (unsigned char const*) buffer;
    uint64_t ret =
        (decltype(ret))p[0] << (8 *  0) |
        (decltype(ret))p[1] << (8 *  1) |
        (decltype(ret))p[2] << (8 *  2) |
        (decltype(ret))p[3] << (8 *  3) |
        (decltype(ret))p[4] << (8 *  4) |
        (decltype(ret))p[5] << (8 *  5) |
        (decltype(ret))p[6] << (8 *  6) |
        (decltype(ret))p[7] << (8 *  7);
    return ret;
}


#if __cplusplus < 201700L
template <typename T, size_t sz>
struct C11TgUnpackDispatch;
template <typename T>
struct C11TgUnpackDispatch<T, 1u> {
    static inline uint8_t unpack(void const* buffer) { return unpacku8(buffer); };
};
template <typename T>
struct C11TgUnpackDispatch<T, 2u> {
    static inline uint16_t unpack(void const* buffer) { return unpacku16(buffer); };
};
template <typename T>
struct C11TgUnpackDispatch<T, 4u> {
    static inline uint32_t unpack(void const* buffer) { return unpacku32(buffer); };
};
template <typename T>
struct C11TgUnpackDispatch<T, 8u> {
    static inline uint64_t unpack(void const* buffer) { return unpacku64(buffer); };
};
#endif

template <typename T>
[[nodiscard]]
static inline
T tgunpacku(void const* buffer) {
#if __cplusplus >= 201700L
         if constexpr(sizeof(T) == 4) { return unpacku32(buffer); }
    else if constexpr(sizeof(T) == 8) { return unpacku64(buffer); }
    else if constexpr(sizeof(T) == 2) { return unpacku16(buffer); }
    else if constexpr(sizeof(T) == 1) { return unpacku8(buffer); }
    else { static_assert(false, "Unimplemented byte size"); }
#else
    return C11TgUnpackDispatch<T, sizeof(T)>::unpack(buffer);
#endif
}



template <typename T>
static inline
T* tgunpacku(void const* buffer, T* x) {
    *x = tgunpacku<T>(buffer);
    return x + 1;
}

#if __cplusplus < 201700L
template <typename T, size_t sz>
struct C11TgUnpackDispatchLe;
template <typename T>
struct C11TgUnpackDispatchLe<T, 1u> {
    static inline uint8_t unpack(void const* buffer) { return unpacku8le(buffer); };
};
template <typename T>
struct C11TgUnpackDispatchLe<T, 2u> {
    static inline uint16_t unpack(void const* buffer) { return unpacku16le(buffer); };
};
template <typename T>
struct C11TgUnpackDispatchLe<T, 4u> {
    static inline uint32_t unpack(void const* buffer) { return unpacku32le(buffer); };
};
template <typename T>
struct C11TgUnpackDispatchLe<T, 8u> {
    static inline uint64_t unpack(void const* buffer) { return unpacku64le(buffer); };
};
#endif

template <typename T>
[[nodiscard]]
static inline
T tgunpackule(void const* buffer) {
#if __cplusplus >= 201700L
         if constexpr(sizeof(T) == 4) { return unpacku32le(buffer); }
    else if constexpr(sizeof(T) == 8) { return unpacku64le(buffer); }
    else if constexpr(sizeof(T) == 2) { return unpacku16le(buffer); }
    else if constexpr(sizeof(T) == 1) { return unpacku8le(buffer); }
    else { static_assert(false, "Unimplemented byte size"); }
#else
    return C11TgUnpackDispatchLe<T, sizeof(T)>::unpack(buffer);
#endif
}

template <typename T>
static inline
T* tgunpackule(void const* buffer, T* x) {
    *x = tgunpackule<T>(buffer);
    return x + 1;
}

static inline
constexpr size_t size_of_all_args(void) {
    return 0;
}
template<typename T1, typename... TOther>
static inline constexpr
size_t size_of_all_args(T1 arg1, TOther... argother);
template<typename T1, typename... TOther>
static inline constexpr
size_t size_of_all_args(T1* arg1, TOther... argother);

template<typename T1, typename... TOther>
static inline constexpr
size_t size_of_all_args(T1 arg1, TOther... argother) {
    return sizeof(arg1) + size_of_all_args(argother...);
}
template<typename T1, typename... TOther>
static inline constexpr
size_t size_of_all_args(T1* arg1, TOther... argother) {
    return sizeof(*arg1) + size_of_all_args(argother...);
}

namespace vrdc {
[[deprecated("vrdc_unpack() must be called with atleast 2 parameters (buffer and unpack site)")]]
static inline
void vrdc_unpack([[maybe_unused]]void const* buffer) {
    (void)0;
}

template<typename T1, typename... TOther>
void vrdc_unpack(void const* buffer, T1* arg1, TOther... argother);

template<typename T1, typename... TOther>
static inline
void vrdc_unpack(void const* buffer, T1* arg1, TOther... argother) {
    auto p = (unsigned char const*) buffer;
    tgunpacku(p, arg1);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    vrdc_unpack(p + sizeof(*arg1), argother...);
#pragma GCC diagnostic pop
}

template<typename T1, typename... TOther>
static inline
size_t vrdc_unpack_get_written_bytes(void const* buffer, T1* arg1, TOther... argother) {
    vrdc_unpack(buffer, arg1, argother...);
    return size_of_all_args(arg1, argother...);
}

} // namespace vrdc

#endif /* FEB_2025_CPP_NW_PACKER_HPP */

