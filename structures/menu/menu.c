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


Menu* lastMenu( Menu* menuList )
{
    if ( menuList == NULL ) return NULL;

    Menu* current = menuList;
    while ( current != NULL )
    {
        if ( current->next == NULL ) return current;
        current = current->next;
    }
}
Menu* insertMenu( Menu* menuList, int id, String path, MenuList* nav, Menu* prev, StrList* strlist, MenuType type )
{
    Menu* newItem = malloc( sizeof(Menu) );
          newItem->id = id;
          newItem->path = strcopy(path);
          newItem->nav = nav;
          newItem->prev = prev;
          newItem->list = strlist;
          newItem->type = type;
          newItem->next = NULL;

    if ( menuList == NULL ) return newItem;

    lastMenu( menuList )->next = newItem;
    return menuList;
}
Menu* findMenuById( Menu* menuList, int id )
{
    if ( menuList == NULL ) return NULL;

    Menu* current = menuList;
    while ( current != NULL )
    {
        if ( current->id == id ) return current;
        current = current->next;
    }

    return NULL;
}

void freeMenuList( MenuList* list )
{
    if ( list == NULL ) return;

    MenuList* current = list;
    while ( current != NULL )
    {
        MenuList* toFree = current;
        current = current->next;

        free(toFree->name);
        free(toFree);
    }
}
MenuList* lastMenuList( MenuList* list )
{
    if ( list == NULL ) return NULL;

    MenuList* current = list;
    while( current != NULL )
    {
        if ( current->next == NULL ) return current;
        current = current->next;
    }
}
MenuList* insertMenuList( MenuList* list, String name, int id )
{
    MenuList* newItem = malloc(sizeof(MenuList));
              newItem->name = strcopy(name);
              newItem->id = id;
              newItem->next = NULL;

    if ( list == NULL ) return newItem;

    lastMenuList( list )->next = newItem;
    return list;
}
MenuList* createMenuList( int args, ... )
{
    va_list     argumentList;
    int         idCount = 0;
    MenuList*   menuList = NULL;

    va_start( argumentList, args );
    for ( ; idCount < args; ++idCount )
    {
        menuList = insertMenuList( menuList, va_arg( argumentList, String ), idCount );
    }
    va_end( argumentList );

    return menuList;
}
int menulistLength( MenuList* menuList )
{
    if ( menuList == NULL ) return 0;

    int counter = 0;
    MenuList* current = menuList;
    while ( current != NULL )
    {
        counter++;
        current = current->next;
    }

    return counter;
}
void printTitlePath( Menu* menu )
{
    if ( menu == NULL ) return;
    printTitlePath( menu->prev );
    printf( "%s ", menu->path );

    printf("> ");
}

void freeMenu( Menu* menu )
{
    if ( menu == NULL ) return;

    Menu* current = menu;
    while ( current != NULL )
    {
        Menu* toFree = current;
        current = current->next;

        free( toFree->path );
        freeMenuList( toFree->nav );
        if ( toFree->list != NULL ) freeStrList( toFree->list );
        free( toFree );
    }
}

Navigation  getNavKey()
{
    int char1, char2;
    char1 = getch();

    if ( char1 == 0xE0 )
    {
        char2 = getch();
        switch ( char2 )
        {
            case UP: return UP;
            case DOWN: return DOWN;
            case LEFT: return LEFT;
            case RIGHT: return RIGHT;
        }
    }
    else if ( char1 == ENTER )
    {
        return ENTER;
    }
    else if ( char1 == ESCAPE )
    {
        return ESCAPE;
    }
}


Response display( Menu* menu )
{
    int cursor = 0;
    int navCount = menulistLength( menu->nav );
    bool ordered = true;

    if ( menu->prev != NULL ) navCount += 1;

    if ( menu->type == INPUT_RADIO && menu->list != NULL )
    {
        navCount += strlistLength( menu->list );
        cursor = navCount-1;
    }

    if ( menu->type == OUTPUT_UNORDERED && menu->list != NULL )
    {
        ordered = false;
        menu->type = OUTPUT_LIST;
    }

    Response response;

    while ( true )
    {
        system( "cls" ); // Console clear

        printf( "  ____                     _   _                         \n"
                " |  _ \\ ___  ___ ___ _ __ | |_| | _____  _ __  _   ___   __\n"
                " | |_) / _ \\/ __/ _ \\ '_ \\| __| |/ / _ \\| '_ \\| | | \\ \\ / /\n"
                " |  _ <  __/ (_|  __/ |_) | |_|   < (_) | | | | |_| |\\ V / \n"
                " |_| \\_\\___|\\___\\___| .__/ \\__|_|\\_\\___/|_| |_|\\__, | \\_/  \n"
                "                    |_|                        |___/\n\n" );

        printf( " " );
        if ( menu->prev != NULL )
        {
            printTitlePath( menu->prev );
        }
        printf( "%s\n\n", menu->path );

        MenuList* current = menu->nav;
        while ( current != NULL )
        {
            printf( " [%c] %s\n", current->id == cursor ? 45 : 32, current->name );
            current = current->next;
        }

        if ( menu->prev != NULL )
        {
            printf( " [%c] Vissza\n", cursor == navCount-1 ? 45 : 32 );
        }

        switch ( menu->type )
        {
            case OUTPUT_LIST:
            {
                if ( menu->list == NULL ) printf( "\n Nincs megjelen\xA1thet\x8B eredm\x82ny." );
                else
                {
                    StrList* moving = menu->list;
                    int listOrder = 1;
                    printf("\n");
                    while ( moving != NULL )
                    {
                        if ( ordered )
                        {
                            printf( "  %d. %s\n", listOrder, moving->item );
                            listOrder++;
                        }
                        else
                        {
                            if ( moving->length == 0 ) printf("  ");
                            printf( " %s\n", moving->item );
                        }
                        moving = moving->next;
                    }
                }

                break;
            }
            case INPUT_TYPE:
            {
                if ( menu->list != NULL )
                {
                    printf( "\n Add meg a k\x94vetkez\x8B adatot/adatokat: \n" );

                    StrList* currentStr = menu->list;
                    StrList* start = NULL;
                    while ( currentStr != NULL )
                    {
                        String new = malloc( (currentStr->length+1) * sizeof(char) );
                        printf( "    %s (Max. %d): ", currentStr->item, currentStr->length );

                        fgets( new, currentStr->length+1, stdin );
                        new[strlength(new)-1] = '\0';
                        new = realloc( new, (strlength(new)+1) * sizeof(char) );

                        start = insertStr( start, new, 0 );
                        currentStr = currentStr->next;
                    }

                    response.list = start;
                    return response;
                }

                break;
            }
            case INPUT_RECIPE:
            {
                RecipeList* newList = malloc(sizeof(RecipeList));
                            newList->instructions = NULL;
                            newList->ingredients = NULL;
                            newList->next = NULL;

                printf( "\n Add meg a k\x94vetkez\x8B adatot/adatokat: \n" );

                String recipeName = NULL;
                do
                {
                    free(recipeName);
                    recipeName = malloc(101*sizeof(char));
                    printf("    Recept neve (Max. 100): ");
                    fgets( recipeName, 101, stdin );

                    recipeName[strlength(recipeName)-1] = '\0';
                    recipeName = realloc( recipeName, (strlength(recipeName)+1) * sizeof(char));
                }
                while ( strlength(recipeName) < 1 );
                newList->name = recipeName;

                printf("    Instrukci\xA2k megad\xA0sa (Soronk\x82nt max. 500 karakter, kil\x82p\x82shez g\x82peld be a k\x94vetkez\x8B karaktert: !):\n");

                String buffer = NULL;
                int counter = 1;
                do
                {
                    free(buffer);
                    buffer = malloc(500*sizeof(char));
                    printf("        %d. ", counter);
                    fgets( buffer, 501, stdin );
                    buffer[strlength(buffer)-1] = '\0';
                    buffer = realloc(buffer, (strlength(buffer)+1) );
                    if ( strcompare(buffer, "!") ) break;

                    newList->instructions = insertInstruction( newList->instructions, strcopy(buffer) );
                    counter++;
                }
                while( !strcompare(buffer, "!") );

                printf("    Hozz\xA0val\xA2k lista hozz\xA0\aad\xA0s/m\xA2\ados\xA1t\xA0s: ");
                if ( menu->list == NULL )
                {
                    printf("\n        Nincs hozz\xA0\aadott \x94sszetev\x8B! Folytatod? (i/n): ");
                    String buff = malloc(2*sizeof(char));
                    fgets(buff, 2, stdin);

                    if ( strcompare(buff, "i") )
                    {
                        response.ptr = newList;
                        response.code = 1;
                        free(buff);
                        return response;
                    }
                    else
                    {
                        freeRecipeList( newList );
                        response.ptr = NULL;
                        response.code = -1;
                        free(buff);
                        return response;
                    }
                }
                else
                {
                    counter = 1;
                    StrList* currentStr = menu->list;
                    while ( currentStr != NULL )
                    {
                        printf("\n        %d. %s", counter, currentStr->item );
                        counter++;
                        currentStr = currentStr->next;
                    }
                }

                printf("\n    V\xA0lassz a list\xA0\ab\xA2l egy sz\xA0mot, ha nincs benne, add hozz\xA0 a hozz\xA0val\xA2k me\x81pontban (kil\x82p\x82shez g\x82peld be a k\x94vetkez\x8B karaktert: !): ");
                buffer = NULL;
                int newCounter = 1;
                do
                {
                    free(buffer);
                    //buffer = malloc((floor(log10(abs(counter)))+1)*sizeof(char));
                    buffer = malloc(101*sizeof(char));

                    printf("\n        Hozz\xA0val\xA2 azonos\xA1t\xA2ja (sz\xA0m): ");
                    fgets(buffer, 101, stdin);

                    char* ptr;
                    long number = strtol(buffer, &ptr, 10);

                    buffer[strlength(buffer)-1] = '\0';
                    //buffer = realloc( buffer, (strlength(buffer)+1) * sizeof(char));
                    if ( strcompare(buffer, "!") ) break;

                    StrList* selectedIngredient = findStrListById( menu->list, (int)(number-1));

                    if ( number < 1 || number > (counter) || selectedIngredient == NULL )
                    {
                        printf("    Nincs ilyen alapanyag!");
                        continue;
                    }

                    String quantity = malloc(101*sizeof(char));
                    printf("        Hozz\xA0val\xA2 mennyis\x82ge (sz\xA0m): ");
                    fgets(buffer, 101, stdin);

                    int quantityNum = (int)strtol(buffer, &ptr, 10);

                    String unit = malloc(51*sizeof(char));
                    printf("        Hozz\xA0val\xA2 m\x82rt\x82kegys\x82ge (Max. 50): ");
                    fgets(unit, 51, stdin);
                    unit[strlength(unit)-1] = '\0';
                    unit = realloc(unit, (strlength(unit)+1) );

                    if ( isIngredientQInArray( newList->ingredients, selectedIngredient->item ) )
                    {
                        findQIngredientByName( newList->ingredients, selectedIngredient->item)->unit = unit;
                        findQIngredientByName( newList->ingredients, selectedIngredient->item)->quantity = quantityNum;
                    }
                    else
                    {
                        newList->ingredients = insertQIngreient(newList->ingredients, selectedIngredient->item, unit, quantityNum );
                    }

                    printf("    Hozz\xA0\aadva list\xA0hoz");
                }
                while( !strcompare(buffer, "!") );

                response.ptr = newList;
                response.code = 1;
                return response;
            }
            case INPUT_RADIO:
            {
                if ( menu->list == NULL ) printf( "\n Nincs megjelen\xA1thet\x8B eredm\x82ny." );
                else
                {
                    int mct = 0;
                    printf( "\n V\xA0lassz egyet az al\xA0\abbi list\xA0\ab\xA2l: \n" );

                    StrList * currentLs = menu->list;
                    while ( currentLs != NULL )
                    {
                        printf( " [%c] %s\n", mct == cursor ? 45 : 32, currentLs->item );
                        currentLs = currentLs->next;
                        mct++;
                    }
                }
            }
        }

        // Válasz bekérése
        switch ( getNavKey() )
        {
            case UP:
            {
                if ( navCount > 1 )
                {
                    if ( (cursor-1) < 0 ) cursor = navCount-1;
                    else cursor--;
                }

                break;
            }
            case DOWN:
            {
                if ( navCount > 1 )
                {
                    if ( (cursor+1) == navCount ) cursor = 0;
                    else cursor++;
                }

                break;
            }
            case ENTER:
            {
                if ( cursor == navCount-1 ) response.code = -1;
                else response.code = cursor;

                return response;
            }
        }
    }
}