#pragma once
#include <cstdint>

namespace ADATE328 {
    // 寄存器地址定义
    enum RegAddr : uint8_t {
        REG_CTRL     = 0x20,
        REG_STATUS   = 0x21,
        REG_CONFIG   = 0x22
    };

    // 控制寄存器位域定义
    union CtrlReg {
        struct {
            uint16_t enable      : 1;    // [0]
            uint16_t mode        : 2;    // [2:1]
            uint16_t gain        : 3;    // [5:3]
            uint16_t reserved    : 2;    // [7:6]
            uint16_t channel     : 4;    // [11:8]
            uint16_t trigger     : 1;    // [12]
            uint16_t unused      : 3;    // [15:13]
        } bits;
        uint16_t raw;

        // 功能枚举定义
        enum Mode { MODE_NORMAL = 0, MODE_TEST = 1, MODE_CALIB = 2 };
        enum Gain { GAIN_1X = 0, GAIN_2X = 1, GAIN_4X = 2, GAIN_8X = 3 };
    };
} 