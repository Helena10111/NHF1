cmake_minimum_required(VERSION 3.17)
project(Receptkonyv C)

set(PROJECT_HEADERS
        structures/resources/components/components.h
        structures/menu/menu.h
        structures/resources/string/string.h
        debugmalloc.h
        structures/io/file_operations.h
        )

set(PROJECT_SOURCES
        main.c
        structures/io/file_operations.c
        structures/resources/components/components.c
        structures/menu/menu.c
        structures/resources/string/string.c
        debugmalloc.h
        )

set(CMAKE_C_STANDARD 99)

add_executable(Receptkonyv ${PROJECT_SOURCES} ${PROJECT_HEADERS})