#include "mtsSLCB.h"
#define PinNums 64
#define slcb 0x2
#define c_wr_pin_en 0x08
#define c_rd_pcb_version 0x00
#define c_rd_fpga_version 0x01
enum FPGA_TYPE{
    PCIE,
    UTBS,
    ROUTER,
    FAILBUS,
    SLCB
};
using namespace std;
typedef uint16_t UINT16;
typedef uint32_t UINT32;
typedef uint8_t UINT8;
namespace mtsSLCB{
    int Read_Version_PCB(UINT16 slot, UINT32& pcb_version){
        UINT32 PC_DATA_L = 0;
        UINT32 PC_DATA_H = 0;
        InPut_TBurst(slot,slcb,c_rd_pcb_version,PC_DATA_L,PC_DATA_H);
        pcb_version = PC_DATA_L;
        return 0;
    }
    int Read_Version_FPGA(UINT16 slot, UINT32& fpga_version){
        UINT32 PC_DATA_L = 0;
        UINT32 PC_DATA_H = 0;
        InPut_TBurst(slot,slcb,c_rd_fpga_version,PC_DATA_L,PC_DATA_H);
        fpga_version = PC_DATA_L;
        return 0;
    }
    int WritePinEn(UINT16* slotlist,UINT32 slotlistlength,UINT16** pinList,UINT32* pinListLength){
        UINT16 PinEn = 0;
        UINT16 SlotEn = 0;
        UINT32 PC_DATA_L = 0;
        UINT32 PC_DATA_H = 0;
        //UINT32 channelListLength = 0;
        //UINT32 channelListTotal = 0;
        UINT64 pinData64Bit = 0;
        for(j=0;j<slotlistlength;j++){
            SlotEn = slotlist[j];
            for(i=0;i<pinListLength[j];i++){   
                PinEn = 1<<pinList[j][i];
                pinData64Bit = pinData64Bit | PinEn;
            }
            PC_DATA_L = pinData64Bit & 0xFFFFFFFF;
            PC_DATA_H = pinData64Bit >> 32;
            OutPut_TBurst(SlotEn,slcb,c_wr_pin_en,PC_DATA_L,PC_DATA_H);
            pinData64Bit = 0;
        }
        return 0;
    }

    int ReadPinEn(UINT16* slotlist,UINT32 slotlistlength,UINT16* pinList,UINT32* pinListLength){
        return 0;
    }
}
int Input_TBurst(UINT16 slot,UINT8 BoardChoose,UINT8 cmd,UINT32& data_l,UINT32& data_h){
    
    UINT32 rcvdata[2] = {0};
    UINT32 sendBuffer[4] ={0};

    UINT32 _preamble24bits = 0XFFFFFF & 0x5555d5;
    UINT8 _sequenceNumber8bits = 0XFF & 1;
    UINT8 _reserve2bits = 0;
    UINT8 _crc1bits = 0;
    UINT32 _WrRdLength25bits = 0;
    UINT8 _WrRdCmd4bits = 0XF & 0X2; //READ

    UINT8 _sysboardChoose5bits = 0x1F & BoardChoose;
    UINT8 _fpgaChoose6bits = 0;
    UINT8 _reserve6bits = 0;
    UINT32 _slotChoose24bits = 0xFFFFFF & slot ;
    UINT16 _slotChoose15bits = 0x7FFF & 0;
    UINT8 _opcAdd8bits = cmd;

    // First 64-bit frame (sendBuffer[0] for high 32 bits, sendBuffer[1] for low 32 bits)
    // High 32 bits: preamble(24) + sequence(8)
    sendBuffer[1] = (_preamble24bits << 8) | _sequenceNumber8bits;
    
    // Low 32 bits: reserve(2) + crc(1) + WrRdLength(25) + WrRdCmd(4)
    sendBuffer[0] = (_reserve2bits << 30) | 
                    (_crc1bits << 29) |
                    (_WrRdLength25bits << 4) |
                    _WrRdCmd4bits;
    
    // Second 64-bit frame (sendBuffer[2] for high 32 bits, sendBuffer[3] for low 32 bits)
    // High 32 bits: sysboardChoose(5) + fpgaChoose(6) + reserve(6) + slotChoose(15)
    sendBuffer[3] = (_sysboardChoose5bits << 27) |
                    (_fpgaChoose6bits << 21) |
                    (_reserve6bits << 15) |
                    _slotChoose15bits;
    
    // Low 32 bits: slotChoose24bits(24) + opcAdd(8)
    sendBuffer[2] = (_slotChoose24bits << 8) |
                    _opcAdd8bits;  // Placing in highest 8 bits of the word
    mtsComm::Instance()->SetTransfrom(PIO,true);

    sendNums = mtsComm::Instance()->Output(sendBuffer,4,timeout);
    rcvNums = mtsComm::Instance()->Input(rcvData,2,timeout);
    data_l = rcvdata[0];
    data_h = rcvdata[1];
    return 0;
}
int Output_TBurst(UINT16 slot,UINT8 BoardChoose,UINT8 cmd,UINT32 data_l,UINT32 data_h){
    UINT32 sendBuffer[4] ={0};

    UINT32 _preamble24bits = 0XFFFFFF & 0x5555d5;
    UINT8 _sequenceNumber8bits = 0XFF & 1;
    UINT8 _reserve2bits = 0;
    UINT8 _crc1bits = 0;
    UINT32 _WrRdLength25bits = 0;
    UINT8 _WrRdCmd4bits = 0XF & 0X1; //WRITE

    UINT8 _sysboardChoose5bits = 0x1F & BoardChoose;
    UINT8 _fpgaChoose6bits = 0;
    UINT8 _reserve6bits = 0;
    UINT32 _slotChoose24bits = 0xFFFFFF & slot ;
    UINT16 _slotChoose15bits = 0x7FFF & 0;
    UINT8 _opcAdd8bits = cmd;

    // First 64-bit frame (sendBuffer[0] for high 32 bits, sendBuffer[1] for low 32 bits)
    // High 32 bits: preamble(24) + sequence(8)
    sendBuffer[1] = (_preamble24bits << 8) | _sequenceNumber8bits;
    
    // Low 32 bits: reserve(2) + crc(1) + WrRdLength(25) + WrRdCmd(4)
    sendBuffer[0] = (_reserve2bits << 30) | 
                    (_crc1bits << 29) |
                    (_WrRdLength25bits << 4) |
                    _WrRdCmd4bits;
    
    // Second 64-bit frame (sendBuffer[2] for high 32 bits, sendBuffer[3] for low 32 bits)
    // High 32 bits: sysboardChoose(5) + fpgaChoose(6) + reserve(6) + slotChoose(15)
    sendBuffer[3] = (_sysboardChoose5bits << 27) |
                    (_fpgaChoose6bits << 21) |
                    (_reserve6bits << 15) |
                    _slotChoose15bits;
    
    // Low 32 bits: slotChoose24bits(24) + opcAdd(8)
    sendBuffer[2] = (_slotChoose24bits << 8) |
                    _opcAdd8bits;  // Placing in highest 8 bits of the word
    

    return 0;
}   
int main(){
    return 0;
}

