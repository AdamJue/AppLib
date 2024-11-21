cmake_minimum_required(VERSION 3.10)

project(AppLib VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

find_package(KernelLib CONFIG REQUIRED)
find_package(ExtendLib CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
        src/AppLib.cpp
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(${PROJECT_NAME} PROPERTIES
            OUTPUT_NAME "${PROJECT_NAME}d"
    )
else ()
    set_target_properties(${PROJECT_NAME} PROPERTIES
            OUTPUT_NAME "${PROJECT_NAME}"
    )
endif ()

target_link_libraries(${PROJECT_NAME} PRIVATE
    KernelLib
    ExtendLib
)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION 1)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE $<$<CONFIG:DEBUG>:DEBUG_MODE>
    PRIVATE $<$<CONFIG:RELEASE>:NDEBUG>
)


if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (CMAKE_HOST_UNIX)
        target_compile_options(${PROJECT_NAME}
                PRIVATE $<$<CONFIG:DEBUG>:-g>
                PRIVATE $<$<CONFIG:RELEASE>:-O3>
        )
    else ()
        target_compile_options(${PROJECT_NAME}
                PRIVATE $<$<CONFIG:RELEASE>:-O3>
        )
    endif ()
endif ()


# 获取DLL文件的路径
get_target_property(KERNEL_LIB_PATH KernelLib LOCATION_DEBUG)
get_target_property(EXTEND_LIB_PATH ExtendLib LOCATION_DEBUG)

# 复制DLL文件到运行目录
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${KERNEL_LIB_PATH}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${EXTEND_LIB_PATH}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)


























