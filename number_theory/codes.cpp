#include "codes.h"


uint8_t Code::_Gen8Bit = 0x1D;

Code::Code()
{
    for (uint32_t i = 0; i < 256; ++i)
    {
        uint8_t byte = static_cast<uint8_t>(i);
        for (uint8_t j = 0; j < 8; ++j)
        {
            if (byte & 0x80)
            {
                byte <<= 1;
                byte ^= _Gen8Bit;
            }
            else
            {
                byte <<= 1;
            }
        }
        _CrcTable[i] = byte;
    }
}

uint8_t Code::Crc8(
    const std::vector<uint8_t>& buf
)
{
    uint8_t crc = 0;
    for (auto const byte : buf)
    {
        crc ^= byte;
        for (int i = 0; i < sizeof(byte) * 8; ++i)
        {
            if (crc & 0x80)
            {
                crc = ((crc << 1) ^ _Gen8Bit);
            }
            else
            {
                crc <<= 1;
            }
            
        }
    }
    return crc;
}

uint8_t Code::Crc8Precomputed(
    const std::vector<uint8_t>& buf
)
{
    uint8_t crc = 0;
    for (auto const byte : buf)
    {
        auto data = crc ^ byte;
        crc = _CrcTable[data];
    }
    return crc;
}