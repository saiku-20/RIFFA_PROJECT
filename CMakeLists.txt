cmake_minimum_required(VERSION 3.10)
project(RIFFA_Project)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 设置库文件和头文件目录
set(RIFFA_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(RIFFA_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# 收集源文件
set(RIFFA_SOURCES
    src/main.cpp
    #src/riffa_driver.cpp
    #src/riffa_utils.cpp
)

# 更新可执行文件定义
add_executable(riffa_test ${RIFFA_SOURCES})

# 添加包含目录
target_include_directories(riffa_test 
    PRIVATE 
        ${RIFFA_INCLUDE_DIR}
)

# 链接RIFFA库
target_link_libraries(riffa_test 
    PRIVATE 
        ${RIFFA_LIB_DIR}/riffa.lib
)

# 设置VS的启动项目
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT riffa_test)

# 复制DLL到输出目录
add_custom_command(TARGET riffa_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${RIFFA_LIB_DIR}/riffa.dll"
    $<TARGET_FILE_DIR:riffa_test>
)

# 为VS设置工作目录
set_target_properties(riffa_test PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
) 