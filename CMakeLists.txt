cmake_minimum_required(VERSION 3.5)

project(ip_filter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ip_filter main.cpp)

install(TARGETS ip_filter
    RUNTIME DESTINATION bin)


if (MSVC)                                                             
    target_compile_options(ip_filter PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

#set_target_properties(ip_filter PROPERTIES COMPILE_FLAGS "-fsanitize=address -fno-omit-frame-pointer")
#set_target_properties(ip_filter PROPERTIES LINK_FLAGS "-fsanitize=address -fno-omit-frame-pointer")
