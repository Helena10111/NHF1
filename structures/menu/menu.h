#ifndef RECEPTKONYV_MENU_H
#define RECEPTKONYV_MENU_H

#include "../resources/components/components.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../debugmalloc.h"

typedef enum Navigation {
    UP = 72,
    DOWN = 80,
    LEFT = 75,
    RIGHT = 77,
    ENTER = 13,
    ESCAPE = 27
} Navigation;
typedef enum MenuType {
    DISPLAY,
    INPUT_CHECKBOX,
    INPUT_RADIO,
    INPUT_TYPE,
    INPUT_RECIPE,
    OUTPUT_LIST,
    OUTPUT_UNORDERED
} MenuType;
typedef struct MenuList {
    int    id;
    String name;
        struct MenuList* next;
} MenuList;
typedef struct Menu {
    int id;
    String path;
    MenuType type;

    MenuList* nav;
    struct Menu* prev;
    StrList* list;

    struct Menu* next;
} Menu;
typedef struct Response {
    int code;
    String name;
    StrList* list;
    void* ptr;
} Response;

Menu* lastMenu( Menu* menuList );
Menu* insertMenu( Menu* menuList, int id, String path, MenuList* nav, Menu* prev, StrList* strlist, MenuType type );
Menu* findMenuById( Menu* menuList, int id );

MenuList* lastMenuList( MenuList* list );
MenuList* insertMenuList( MenuList* list, String name );
MenuList* createMenuList( int args, ... );

Response display( Menu* menu );

void freeMenu( Menu* menu );

#endif //RECEPTKONYV_MENU_H
