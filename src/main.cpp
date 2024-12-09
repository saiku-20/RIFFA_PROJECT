#include <stdio.h>
#include <windows.h>
#include "riffa.h"
#include "../include/riffa.h"
//int main(int argc, char** argv) {
//    fpga_t* fpga;
//    int id = 0;  // FPGA ID
//    int fpga_count;
//
//    // 获取系统中FPGA的数量
//    fpga_info_list list;
//    fpga_count = fpga_list(&list);
//    printf("Number of FPGAs: %d\n", list.num_fpgas);
//
//    // 打开FPGA设备
//    fpga = fpga_open(id);
//    if (fpga == NULL) {
//        printf("Could not open FPGA %d\n", id);
//        return -1;
//    }
//
//    printf("FPGA opened successfully!\n");
//
//    // 这里可以添加您的FPGA通信代码
//    
//    // 关闭FPGA
//    fpga_close(fpga);
//    return 0;
//} 