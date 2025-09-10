#ifndef HEADER_H
#define HEADER_H

#include <cstdint>
#include <cstring>

struct Header
{
    int32_t numRows;
};

inline void serializeHeader(const Header &h, char *dest)
{
    std::memcpy(dest, &h.numRows, sizeof(h.numRows));
}

inline void deserializeHeader(const char *src, Header &h)
{
    std::memcpy(&h.numRows, src, sizeof(h.numRows));
}

#endif
