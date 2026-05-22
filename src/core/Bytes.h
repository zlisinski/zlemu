#pragma once

#include <type_traits>

#include "Zlemu.h"

namespace Bytes
{
    constexpr uint16_t Make16Bit(uint8_t high, uint8_t low)
    {
        return (high << 8) | low;
    }

    constexpr uint32_t Make24Bit(uint8_t bank, uint16_t offset)
    {
        return (bank << 16) | offset;
    }

    constexpr uint32_t Make24Bit(uint8_t high, uint8_t mid, uint8_t low)
    {
        return (high << 16) | (mid << 8) | low;
    }

    template <uint8_t N, typename T>
    constexpr uint8_t GetByte(T value)
    {
        static_assert(std::is_integral<T>::value, "value must be integral type.");
        static_assert(N < sizeof(T), "N must be less than sizeof(T)");
        using U = std::make_unsigned_t<T>;

        // Return type is uint8_t, so there is no need to mask off other bytes.
        return static_cast<U>(value) >> (8 * N);
    }

    template <uint8_t N, typename T>
    constexpr uint8_t GetBit(T value)
    {
        static_assert(std::is_integral<T>::value, "value must be integral type.");
        static_assert(N < sizeof(T) * 8, "N must be less than sizeof(T) * 8");
        using U = std::make_unsigned_t<T>;

        return (static_cast<U>(value) >> N) & 0x01;
    }

    template <uint8_t N, typename T>
    constexpr bool TestBit(T value)
    {
        static_assert(std::is_integral<T>::value, "value must be integral type.");
        static_assert(N < sizeof(T) * 8, "N must be less than sizeof(T) * 8");
        using U = std::make_unsigned_t<T>;

        return static_cast<U>(value) & (U(1) << N);
    }

    template <uint8_t N, typename T>
    constexpr void SetBit(T &value)
    {
        static_assert(std::is_integral<T>::value, "value must be integral type.");
        static_assert(N < sizeof(T) * 8, "N must be less than sizeof(T) * 8");
        using U = std::make_unsigned_t<T>;

        value = static_cast<T>(static_cast<U>(value) | (U(1) << N));
    }

    template <uint8_t N, typename T>
    constexpr void ClearBit(T &value)
    {
        static_assert(std::is_integral<T>::value, "value must be integral type.");
        static_assert(N < sizeof(T) * 8, "N must be less than sizeof(T) * 8");
        using U = std::make_unsigned_t<T>;

        value = static_cast<T>(static_cast<U>(value) & ~(U(1) << N));
    }

    template <uint8_t BitSize, typename T>
    constexpr std::make_signed_t<T> SignExtend(T value)
    {
        static_assert(std::is_integral<T>::value, "value must be integral type.");
        static_assert(BitSize < sizeof(T) * 8, "BitSize must be less than sizeof(T) * 8");

        constexpr int bits = (sizeof(T) * 8) - BitSize;

        return static_cast<std::make_signed_t<T>>(value << bits) >> bits;
    }
}