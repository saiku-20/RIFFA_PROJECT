//
// The following value is arbitrarily chosen from the space defined
// by Microsoft as being "for non-Microsoft use"
//
//
// {40d49fb9-6085-4e1d-8753-822be944d7bb}
DEFINE_GUID (GUID_RIFFA_INTERFACE,
   0x40d49fb9, 0x6085, 0x4e1d, 0x87, 0x53, 0x82, 0x2b, 0xe9, 0x44, 0xd7, 0xbb);

// The IOCTL function codes from 0x800 to 0xFFF are for customer use.
#define IOCTL_RIFFA_SEND \
    CTL_CODE(FILE_DEVICE_UNKNOWN, 0x900, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_RIFFA_RECV \
    CTL_CODE(FILE_DEVICE_UNKNOWN, 0x901, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_RIFFA_LIST \
    CTL_CODE(FILE_DEVICE_UNKNOWN, 0x902, METHOD_OUT_DIRECT ,FILE_ANY_ACCESS)
#define IOCTL_RIFFA_RESET \
    CTL_CODE(FILE_DEVICE_UNKNOWN, 0x903, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

// RIFFA设备结构体
typedef struct {
    HANDLE handle;
    UINT32 fpga_id;
    UINT32 chnl_id;
    BOOL initialized;
} RIFFA_DEVICE;

// 驱动接口函数
#ifdef __cplusplus
extern "C" {
#endif

RIFFA_DEVICE* RIFFA_Open(UINT32 fpga_id, UINT32 chnl_id);
BOOL RIFFA_Send(RIFFA_DEVICE* device, void* data, size_t len, UINT32 timeout);
BOOL RIFFA_Recv(RIFFA_DEVICE* device, void* data, size_t len, UINT32 timeout);
void RIFFA_Close(RIFFA_DEVICE* device);

#ifdef __cplusplus
}
#endif

