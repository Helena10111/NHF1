#include "structures/resources/string/string.h" /* Saját string kezelés */
#include "structures/io/file_operations.h"      /* Fájlba írás és olvasás */
#include "structures/menu/menu.h"               /* Menü */
#include <stdlib.h>
#include "debugmalloc.h"                        /* Debugmalloc */
#include <stdio.h>
#include <stdbool.h>


int main()
{
    printf( "Program bet\x94lt\x82se folyamatban..." );

    /**
     * Adatszerkezetek felépítése
     */
    RecipeList*         recipeBook = NULL;
    IngredientList*     ingredients = NULL;
    IngredientQList*    pantry = NULL;

    /**
     * Mentett értékek beolvasása fájlból
     */
    //TODO: Fájlból beolvas
    ingredients = readIngredientlistFile();
    pantry = readPantrylistFile();
    recipeBook = readRecipeFile();

    /**
     * Menü felépítése
     */
    StrList* IngredientOutputList = fromIngredients( ingredients );
    StrList* PantryOutputList = fromQIngredints( pantry );

    Menu* appMenu = NULL;
        // mainMenu - Főmenü
        appMenu = insertMenu( appMenu, 10, "F\x8Bmen\x81", createMenuList(5, "Alapanyagok", "Kamra", "Receptek", "Keres\x82s", "Kil\x82p\x82s"), NULL, NULL, DISPLAY );

        // ingredientMenu - Hozzávalók menüválasztó
        appMenu = insertMenu( appMenu, 20, "Alapanyagok", createMenuList(3, "Alapanyagok list\xA0z\xA0sa", "Alapanyag hozz\xA0\aad\xA0sa", "Alapanyag t\x94rl\x82se"), findMenuById(appMenu, 10), NULL, DISPLAY  );
        // ingredientListMenu - Hozzávalók kilistázása
        appMenu = insertMenu( appMenu, 21, "Alapanyagok list\xA0z\xA0sa", NULL, findMenuById(appMenu, 20), IngredientOutputList, OUTPUT_LIST  );
        // ingredientNewMenu - Új hozzávaló hozzáadása
        StrList* NewIngredientMenu = insertStr( NULL, "Alapanyag neve", 100 );
        appMenu = insertMenu( appMenu, 22, "Alapanyag hozz\xA0\aad\xA0sa", NULL, findMenuById(appMenu, 20), NewIngredientMenu, INPUT_TYPE );
        // ingredientDeleteMenu - Hozzávaló törlése
        appMenu = insertMenu( appMenu, 23, "Alapanyag t\x94rl\x82se", NULL, findMenuById(appMenu, 20), IngredientOutputList, INPUT_RADIO );

        // pantryMenu - Kamra menüválasztó
        appMenu = insertMenu( appMenu, 30, "Kamra", createMenuList(3, "Hozz\xA0\aadott alapanyagok megtekint\x82se", "Alapanyag hozz\xA0\aad\xA0sa/m\xA2\ados\xA1t\xA0sa", "Alapanyag t\x94rl\x82se"), findMenuById(appMenu, 10), NULL, DISPLAY );
        // pantryListMenu - Kamra kilistázása
        appMenu = insertMenu( appMenu, 31, "Hozz\xA0\aadott alapanyagok megtekint\x82se", NULL, findMenuById(appMenu, 30), PantryOutputList, OUTPUT_LIST );
        // pantryNewSelectMenu - Kamra új eleme hozzáadása kiválasztó
        appMenu = insertMenu( appMenu, 321, "Alapanyag hozz\xA0\aad\xA0sa", NULL, findMenuById(appMenu, 30), IngredientOutputList, INPUT_RADIO );
        // pantryNewAddMenu - Új kamraelem adatainak megadása
        StrList* NewPantryMenu = insertStr( NULL, "Kiv\xA0lasztott alapanyag mennyis\x82ge", 100 );
                 NewPantryMenu = insertStr( NewPantryMenu, "Kiv\xA0lasztott alapanyag m\x82rt\x82kegys\x82ge", 20 );
        appMenu = insertMenu( appMenu, 322, "<alapanyag neve>", NULL, findMenuById(appMenu, 321), NewPantryMenu, INPUT_TYPE );
        // pantryDeleteMenu - Kamraelem törlése
        appMenu = insertMenu( appMenu, 33, "Alapanyag t\x94rl\x82se", NULL, findMenuById(appMenu, 30), PantryOutputList, INPUT_RADIO );

        // recipeMenu - Recept menüválasztó
        appMenu = insertMenu( appMenu, 40, "Receptk\x94nyv", createMenuList( 3, "Recept megtekint\x82se", "Recept hozz\xA0\aad\xA0sa/m\xA2\ados\xA1t\xA0sa", "Recept t\x94rl\x82se" ) , findMenuById(appMenu, 10), NULL, DISPLAY );
        // recipeListSelectMenu - Recept kilistázása receptválasztó
        appMenu = insertMenu( appMenu, 41, "Recept megtekint\x82se", NULL, findMenuById(appMenu, 40), NULL, INPUT_RADIO );
        // recipeShowMenu - Recept hosszas kiírása
        appMenu = insertMenu( appMenu, 42, "", NULL, findMenuById(appMenu, 41), NULL, OUTPUT_UNORDERED );
        // recipeNewMenu - Recept hozzáadása
        appMenu = insertMenu( appMenu, 43, "Recept hozz\xA0\aad\xA0sa/m\xA2\ados\xA1t\xA0sa", NULL, findMenuById(appMenu, 40), NULL, INPUT_RECIPE );
        // recipeModifyMenu - Recept módosítása
        //appMenu = insertMenu( appMenu, 44, "NOT IMPLEMENTED YET", NULL, findMenuById(appMenu, 40), NULL, OUTPUT_LIST );
        // recipeDeleteMenu - Recept törlése
        appMenu = insertMenu( appMenu, 46, "Recept t\xA2rl\x82se", NULL, findMenuById(appMenu, 40), NULL, INPUT_RADIO );

        // searchMenu - Keresés menü
        appMenu = insertMenu( appMenu, 50, "Keres\x82s", createMenuList( 4, "\x90tel neve alapj\xA0n", "Nincs \x94tletem", "Enn\x82k egy kis...", "El kell haszn\xA0lni" ), findMenuById(appMenu, 10), NULL, DISPLAY );
        // searchEnterMenu - Keresés név alapján begépelés
        StrList* SearchEnterMenu = insertStr( NULL, "Keresett \x82tel neve, vagy egy r\x82szlet", 100 );
        appMenu = insertMenu( appMenu, 51, "Keres\x82s n\x82v alapj\xA0n", NULL, findMenuById(appMenu, 50), SearchEnterMenu, INPUT_TYPE );
        // searchListEnterMenu - Keresés név alapján kiíró
        appMenu = insertMenu( appMenu, 511, "Tal\xA0latok", NULL, findMenuById(appMenu, 50), NULL, INPUT_RADIO );
        // searchDisplayRecipe - Keresés menü recept kiírása
        appMenu = insertMenu( appMenu, 522, "<recept neve>", NULL, findMenuById(appMenu, 50), NULL, OUTPUT_UNORDERED );
        // searchMenu - Random
        appMenu = insertMenu( appMenu, 53, "<recept neve>", NULL, findMenuById(appMenu, 50), NULL, OUTPUT_UNORDERED );
        // searchMenu - ennék egy kis választó
        appMenu = insertMenu( appMenu, 54, "Enn\x82k egy kis...", NULL, findMenuById(appMenu, 50), IngredientOutputList, INPUT_RADIO );
        // searchMenu  - el kell használni választó
        appMenu = insertMenu( appMenu, 55, "El kell haszn\xA0lni", NULL, findMenuById(appMenu, 50), IngredientOutputList, INPUT_RADIO );


    /**
     * Menü kezelése
     */
    Menu* currentMenu = appMenu;
    Response response;
    bool running = true;

    while ( running )
    {
        response = display( currentMenu );

        switch ( currentMenu->id )
        {
            case 10:
            {
                switch ( response.code )
                {
                    // Alapanyagok
                    case 0:
                    {
                        currentMenu = findMenuById(appMenu, 20);
                        break;
                    }
                        //Kamra
                    case 1:
                    {
                        currentMenu = findMenuById(appMenu, 30);
                        break;
                    }
                        // Receptek
                    case 2:
                    {
                        currentMenu = findMenuById(appMenu, 40);
                        break;
                    }
                    case 3:
                    {
                        currentMenu = findMenuById(appMenu, 50);
                        break;
                    }
                        // Kilépés
                    case -1:
                    {
                        running = false;
                        break;
                    }
                }
                break;
            }   // mainMenu - Főmenü

            case 20:
            {
                switch ( response.code )
                {
                    // Alapanyagok listázása
                    case 0:
                    {
                        currentMenu = findMenuById(appMenu, 21);
                        break;
                    }
                        // Új alapanyag hozzáadása
                    case 1:
                    {
                        currentMenu = findMenuById(appMenu, 22);
                        break;
                    }
                        // Alapanyag törlése
                    case 2:
                    {
                        currentMenu = findMenuById(appMenu, 23);
                        break;
                    }
                        // Visszalépés
                    case -1:
                    {
                        currentMenu = currentMenu->prev;
                        break;
                    }
                }
                break;
            }   // ingredientMenu - Hozzávalók menüválasztó
            case 21:
            {
                currentMenu = currentMenu->prev;
                break;
            }   // ingredientListMenu - Hozzávalók kilistázása
            case 22:
            {
                currentMenu = currentMenu->prev;
                if ( response.list != NULL && strlength( response.list->item ) > 0 )
                {
                    if ( !isIngredientInArray( ingredients, response.list->item ) )
                    {
                        ingredients = insertIngredient( ingredients, response.list->item );

                        if ( IngredientOutputList != NULL ) freeStrList( IngredientOutputList );
                        IngredientOutputList = fromIngredients( ingredients );

                        findMenuById(appMenu, 21)->list = IngredientOutputList;
                        findMenuById(appMenu, 23)->list = IngredientOutputList;
                        findMenuById(appMenu, 321)->list = IngredientOutputList;
                        findMenuById(appMenu, 54)->list = IngredientOutputList;
                    }
                }

                break;
            }   // ingredientNewMenu - Új hozzávaló hozzáadása
            case 23:
            {
                currentMenu = currentMenu->prev;

                if ( response.code != -1 )
                {
                    IngredientList* selected = findIngredientById( ingredients, response.code );

                    if ( selected != NULL )
                    {
                        IngredientQList* findSelected = findQIngredientByName( pantry, selected->name );
                        if ( findSelected != NULL )
                        {
                            pantry = deleteQIngredient( pantry, findSelected );
                        }

                        ingredients = deleteIngredient( ingredients, selected );

                        if ( IngredientOutputList != NULL ) freeStrList( IngredientOutputList );
                        if ( PantryOutputList != NULL ) freeStrList( PantryOutputList );

                        IngredientOutputList = fromIngredients(ingredients);
                        PantryOutputList = fromQIngredints(pantry);

                        findMenuById(appMenu, 21)->list = IngredientOutputList;
                        findMenuById(appMenu, 23)->list = IngredientOutputList;
                        findMenuById(appMenu, 321)->list = IngredientOutputList;
                        findMenuById(appMenu, 54)->list = IngredientOutputList;

                        findMenuById(appMenu, 31)->list = PantryOutputList;
                        findMenuById(appMenu, 33)->list = PantryOutputList;
                    }
                }
                break;
            }   // ingredientDeleteMenu - Hozzávaló törlése

            case 30:
            {
                switch ( response.code )
                {
                    // Alapanyagok megtekintése
                    case 0:
                    {
                        currentMenu = findMenuById(appMenu, 31);
                        break;
                    }
                        // Alapanyag hozzáadása választó
                    case 1:
                    {
                        currentMenu = findMenuById(appMenu, 321);
                        break;
                    }
                        // Alapanyag törlése
                    case 2:
                    {
                        currentMenu = findMenuById(appMenu, 33);
                        break;
                    }
                        // Visszalépés
                    case -1:
                    {
                        currentMenu = currentMenu->prev;
                        break;
                    }
                }
                break;
            }   // pantryMenu - Kamra menüválasztó
            case 31:
            {
                currentMenu = currentMenu->prev;
                break;
            }   // pantryListMenu - Kamra kilistázása
            case 321:
            {
                currentMenu = currentMenu->prev;
                if ( response.code != -1 )
                {
                    IngredientList* selected = findIngredientById( ingredients, response.code );
                    if ( selected != NULL )
                    {
                        Menu* toOpen = findMenuById(appMenu, 322);
                              toOpen->path = selected->name;

                        Response resp = display( toOpen );
                        if ( resp.code != -1 && (resp.list != NULL && strlength(resp.list->item) > 0) && (resp.list->next != NULL && strlength(resp.list->next->item) > 0) )
                        {
                            char* ptr;
                            long number = strtol(resp.list->item, &ptr, 10);

                            if ( isIngredientQInArray( pantry, selected->name ) )
                            {
                                IngredientQList* toModify = findQIngredientByName( pantry, selected->name );

                                if ( strlength( resp.list->item ) > 0 )
                                {
                                    toModify->quantity = (int)number;
                                }

                                if ( strlength(resp.list->next->item) > 0 )
                                {
                                    toModify->unit = strcopy(resp.list->next->item);
                                }
                            }
                            else
                            {
                                pantry = insertQIngreient( pantry, selected->name, resp.list->next->item, (int)number );
                            }

                            if ( PantryOutputList != NULL ) freeStrList( PantryOutputList );
                            PantryOutputList = fromQIngredints(pantry);

                            findMenuById(appMenu, 31)->list = PantryOutputList;
                            findMenuById(appMenu, 33)->list = PantryOutputList;
                        }
                    }
                }

                break;
            }  // pantryNewSelectMenu - Kamra új eleme hozzáadása kiválasztó & pantryNewAddMenu - Új kamraelem adatainak megadása
            case 33:
            {
                currentMenu = currentMenu->prev;

                if ( response.code != -1 )
                {
                    IngredientQList* selected = findQIngredientById( pantry, response.code );

                    if ( selected != NULL )
                    {
                        pantry = deleteQIngredient( pantry, selected );

                        if ( PantryOutputList != NULL ) freeStrList( PantryOutputList );
                        PantryOutputList = fromQIngredints( pantry );

                        findMenuById(appMenu, 31)->list = PantryOutputList;
                        findMenuById(appMenu, 33)->list = PantryOutputList;
                    }
                }

                break;
            }   // pantryDeleteMenu - Kamraelem törlése

            case 40:
            {
                switch (response.code)
                {
                    case 0:
                    {
                        Menu* recipeMenuSelect = findMenuById(appMenu, 41);
                        StrList* recipeStrList = NULL;

                        RecipeList* recipeStrListCurrent = recipeBook;
                        while ( recipeStrListCurrent != NULL )
                        {
                            recipeStrList = insertStr(recipeStrList, recipeStrListCurrent->name, 0);
                            recipeStrListCurrent = recipeStrListCurrent->next;
                        }

                        if ( recipeMenuSelect->list != NULL ) freeStrList(recipeMenuSelect->list);
                        recipeMenuSelect->list = recipeStrList;
                        currentMenu = recipeMenuSelect;
                        break;
                    }
                    case 1:
                    {
                        Menu* selected = findMenuById(appMenu, 43);

                        if ( selected->list != NULL ) freeStrList(selected->list);
                        selected->list = fromIngredients(ingredients);

                        currentMenu = selected;
                        break;
                    }
                    case 2:
                    {
                        Menu* recipeMenuSelect = findMenuById(appMenu, 46);
                        StrList* recipeStrList = NULL;

                        RecipeList* recipeStrListCurrent = recipeBook;
                        while ( recipeStrListCurrent != NULL )
                        {
                            recipeStrList = insertStr(recipeStrList, recipeStrListCurrent->name, 0);
                            recipeStrListCurrent = recipeStrListCurrent->next;
                        }

                        if ( recipeMenuSelect->list != NULL ) freeStrList(recipeMenuSelect->list);
                        recipeMenuSelect->list = recipeStrList;
                        currentMenu = recipeMenuSelect;
                        break;
                    }
                    case -1:
                    {
                        currentMenu = currentMenu->prev;
                        break;
                    }
                }
                break;
            }   // recipeMenu - Recept menüválasztó
            case 41:
            {
                if ( response.code != -1 )
                {
                    RecipeList* selected = findRecipeById( recipeBook, response.code );

                    if ( selected != NULL )
                    {
                        Menu* toShowMenu = findMenuById(appMenu, 42);
                              toShowMenu->type = OUTPUT_UNORDERED;
                        StrList* recipeShowStrList = NULL;

                        toShowMenu->path = selected->name;

                        free( toShowMenu->list );

                        recipeShowStrList = insertStr( recipeShowStrList, "+------------+\n | Hozz\xA0val\xA2k |\n +------------+\n", 1 );
                        StrList* recipeQIngredientsList = fromQIngredints( selected->ingredients );
                        if ( recipeQIngredientsList != NULL )
                        {
                            recipeShowStrList->next = fromQIngredints( selected->ingredients );
                        }
                        else
                        {
                            recipeShowStrList = insertStr(recipeShowStrList, "Nincs megjelen\xA1thet\x8B adat.", 0);
                        }
                        recipeShowStrList = insertStr( recipeShowStrList, "\n", 1 );

                        recipeShowStrList = insertStr( recipeShowStrList, "+-------------+\n | Instrukci\xA2k |\n +-------------+\n", 1 );
                        lastStr( recipeShowStrList )->next = fromInstructions( selected->instructions );

                        toShowMenu->list = recipeShowStrList;
                        currentMenu = toShowMenu;
                    }
                }
                else
                {
                    currentMenu = currentMenu->prev;
                }

                break;
            }   // recipeListSelectMenu - Recept kilistázása receptválasztó
            case 42:
            {
                currentMenu = currentMenu->prev;
                break;
            }   // recipeShowMenu - Recept hosszas kiírása
            case 43:
            {
                currentMenu = currentMenu->prev;

                if ( response.ptr != NULL )
                {
                    RecipeList* searchForAlready = isRecipeInArray( recipeBook, response.ptr );
                    if ( searchForAlready == NULL )
                    {
                        recipeBook = insertRecipeList( recipeBook, response.ptr );
                    }
                    else
                    {
                        searchForAlready->instructions = ((struct RecipeList*)response.ptr)->instructions;
                        searchForAlready->ingredients = ((struct RecipeList*)response.ptr)->ingredients;
                    }
                }

                break;
            }   // recipeNewList - Recept hozzáadása
            case 46:
            {
                currentMenu = currentMenu->prev;

                if ( response.code != -1 )
                {
                    RecipeList* selected = findRecipeById( recipeBook, response.code );

                    if ( selected != NULL )
                    {
                        recipeBook = deleteRecipe(recipeBook, selected);
                    }
                }

                break;
            }   // recipeDeleteMenu - Recept törlése

            case 50:
            {
                switch (response.code)
                {
                    case 0:
                    {
                        currentMenu = findMenuById(appMenu, 51);
                        break;
                    }
                    case 1:
                    {
                        Menu* toShowMenu = findMenuById(appMenu, 53);
                        if ( recipeBook != NULL )
                        {
                            RecipeList* selected = randomRecipe(recipeBook);
                            toShowMenu->type = OUTPUT_UNORDERED;
                            StrList* recipeShowStrList = NULL;

                            toShowMenu->path = selected->name;

                            free( toShowMenu->list );

                            recipeShowStrList = fromRecipeToDisplay(selected);

                            toShowMenu->list = recipeShowStrList;
                            currentMenu = toShowMenu;

                        }
                        else
                        {
                            toShowMenu->type = OUTPUT_LIST;
                            StrList* recipeShowStrList = NULL;
                            toShowMenu->path = "Nincs tal\xA0lat";
                        }
                        currentMenu = toShowMenu;

                        break;
                    }
                    case 2:
                    {
                        currentMenu = findMenuById(appMenu, 54);
                        break;
                    }
                    case 3:
                    {
                        currentMenu = findMenuById(appMenu, 55);
                        break;
                    }
                    case -1:
                    {
                        currentMenu = currentMenu->prev;
                        break;
                    }
                }
                break;
            }   // searchMenu - Keresés menü
            case 51:
            {
                if ( response.code != -1 )
                {
                    if ( response.list != NULL && strlen(response.list->item) > 0 )
                    {
                        RecipeListFound* founds = findRecipesByName( recipeBook, response.list->item );
                        Menu* toOpen = findMenuById(appMenu, 511);

                        if ( toOpen->list != NULL ) freeStrList(toOpen->list);
                        toOpen->list = fromRecipeFound(founds);
                        currentMenu = toOpen;
                    }
                }
                else
                {
                    currentMenu = currentMenu->prev;
                }

                break;
            }   // searchEnterMenu - Keresés név alapján beíró menü
            case 511:
            {
                if ( response.code != -1 )
                {
                    RecipeList* selected = findRecipeByName(recipeBook, (findStrListById(currentMenu->list, response.code))->item);
                    if ( selected != NULL )
                    {
                        Menu* toShowMenu = findMenuById(appMenu, 522);
                        toShowMenu->type = OUTPUT_UNORDERED;
                        StrList* recipeShowStrList = NULL;

                        toShowMenu->path = selected->name;

                        free( toShowMenu->list );

                        recipeShowStrList = fromRecipeToDisplay(selected);

                        toShowMenu->list = recipeShowStrList;
                        currentMenu = toShowMenu;
                    }
                }
                else
                {
                    currentMenu = currentMenu->prev;
                }

                break;
            }  // Keresés név alapján választó és megjelenítő
            case 522:
            {
                currentMenu = currentMenu->prev;
                break;
            }  // Név alapján keresés
            case 53:
            {
                currentMenu = currentMenu->prev;
                break;
            }   // random keresés
            case 54:
            {
                if ( response.code != -1 )
                {
                    String selected = findStrListById(currentMenu->list, response.code)->item;
                    if ( response.list != NULL && selected != NULL && strlen(selected) > 0 )
                    {
                        RecipeListFound* founds = findRecipesByIngredient( recipeBook, selected );
                        printf("%s", findStrListById(currentMenu->list, response.code)->item);
                        Menu* toOpen = findMenuById(appMenu, 511);

                        if ( toOpen->list != NULL ) freeStrList(toOpen->list);
                        toOpen->list = fromRecipeFound(founds);
                        currentMenu = toOpen;
                    }
                }
                else
                {
                    currentMenu = currentMenu->prev;
                }

                break;
            }   // keresés egy összetevő alapján
            case 55:
            {
                break;
            }   // Keresés több összetevő alapján
        }
    }

    /**
     * Változtatások mentése fájlba
     */
    //TODO: Fájlba mentés
    writeIngredientlistFile( ingredients );
    writePantrylistFile( pantry );
    writeRecipeFile( recipeBook );

    /**
     * Memória felszabadítása
     */
    //TODO: FELSZABADÍTÁS
    freeMenu( appMenu ); // Menü felszabadítása
    freeIngredientList( ingredients ); // Hozzávalólista felszabadítása
    freeIngredientQList( pantry ); // Kamralista felszabadítása
    freeRecipeList( recipeBook ); // Recepteklista felszabadítása

    return 0;
}