#ifndef _CODES_H_
#define _CODES_H_

#include <stdint.h>
#include <vector>
#include <array>

class Code
{
    public:

        Code();
        
        static uint8_t Crc8(
            const std::vector<uint8_t>& buf
        );

        uint8_t Crc8Precomputed(
            const std::vector<uint8_t>& buf
        );
    private:
        static uint8_t _Gen8Bit;
        std::array<uint8_t, 256> _CrcTable;

};

#endif  //  _CODES_H_