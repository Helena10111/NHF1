#include "../string/string.h"
#include <stdarg.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../../debugmalloc.h"

typedef struct IngredientList {
    String name;
        struct IngredientList* next;
} IngredientList;
typedef struct IngredientQList {
    String name;
    String unit;
    int quantity;
        struct IngredientQList* next;
} IngredientQList;
typedef struct InstructionList {
    String text;
        struct InstructionList* next;
} InstructionList;
typedef struct RecipeList {
    String name;
    InstructionList* instructions;
    IngredientQList* ingredients;
    struct RecipeList* next;
} RecipeList;
typedef struct RecipeListFound {
    RecipeList* ptr;
    struct RecipeListFound* next;
} RecipeListFound;
typedef struct StrList {
    String item;
    int length;
        struct StrList* next;
} StrList;


/**
 * IngredientList függvények
 */
bool isIngredientInArray( IngredientList* list, String name )
{
    if ( list == NULL ) return false;

    IngredientList* current = list;
    while ( current != NULL )
    {
        if ( strcompare( current->name, name ) ) return true;
        current = current->next;
    }

    return false;
}
void freeIngredientList( IngredientList* list )
{
    if ( list == NULL ) return;

    IngredientList* current = list;
    while( current != NULL )
    {
        IngredientList* toFree = current;
        current = current->next;

        free( toFree->name );
        free( toFree );
    }
}
int ingredientListLength( IngredientList* list )
{
    if ( list == NULL ) return 0;

    int counter = 0;
    IngredientList* current = list;
    while ( current != NULL )
    {
        counter++;
        current = current->next;
    }

    return counter;
}
IngredientList* findIngredientByName( IngredientList* ingredients, String name )
{
    if ( ingredients == NULL ) return NULL;

    IngredientList* current = ingredients;
    while ( current != NULL )
    {
        if ( strcompare(current->name, name) ) return current;
        current = current->next;
    }

    return NULL;
}
IngredientList* findIngredientById( IngredientList* ingredients, int id )
{
    if ( ingredients == NULL ) return NULL;

    int counter = 0;
    IngredientList* current = ingredients;
    while ( current != NULL )
    {
        if ( counter == id ) return current;
        counter++;
        current = current->next;
    }

    return NULL;
}
IngredientList* deleteIngredient( IngredientList* list, IngredientList* item )
{
    if ( list == NULL ) return NULL;

    if ( strcompare( list->name, item->name ) )
    {
        IngredientList* returnList = list->next;

        //free( item->name );
        free( item );

        return returnList;
    }

    IngredientList* prev = list;
    IngredientList* current = list->next;
    while ( current != NULL )
    {
        if ( strcompare( current->name, item->name ) )
        {
            prev->next = current->next;

            //free( current->name );
            free( current );

            break;
        }

        prev = prev->next;
        current = current->next;
    }

    return list;
}
IngredientList* lastIngredient( IngredientList* start )
{
    if ( start == NULL ) return NULL;

    IngredientList* current = start;
    while ( current != NULL )
    {
        if ( current->next == NULL ) return current;
        current = current->next;
    }

    return NULL;
}
IngredientList* insertIngredient( IngredientList* list, String name )
{
    IngredientList* newIngredient = malloc( sizeof(IngredientList) );
                    newIngredient->name = name;
                    newIngredient->next = NULL;

    if ( list == NULL ) return newIngredient;

    lastIngredient( list )->next = newIngredient;
    return list;
}


/**
 * IngredientQuantityList függvények
 */
bool isIngredientQInArray( IngredientQList* list, String name )
{
    if ( list == NULL ) return false;

    IngredientQList* current = list;
    while ( current != NULL )
    {
        if ( strcompare(current->name, name) ) return true;
        current = current->next;
    }

    return false;
}
void freeIngredientQList( IngredientQList* list )
{
    if ( list == NULL ) return;

    IngredientQList* current = list;
    while ( current != NULL )
    {
        IngredientQList* toFree = current;
        current = current->next;

        // free( toFree->name );
        //free( toFree->unit );
        free( toFree );
    }
}
IngredientQList* findQIngredientByName( IngredientQList* list, String _name )
{
    if ( list == NULL ) return NULL;

    IngredientQList* current = list;
    while ( current != NULL )
    {
        if ( strcompare( current->name, _name ) ) return current;
        current = current->next;
    }

    return NULL;
}
IngredientQList* findQIngredientById( IngredientQList* list, int id )
{
    if ( list == NULL ) return NULL;

    int counter = 0;
    IngredientQList* current = list;
    while ( current != NULL )
    {
        if ( counter == id ) return current;
        counter++;
        current = current->next;
    }

    return NULL;
}
IngredientQList* lastQIngredient( IngredientQList* list )
{
    if ( list == NULL ) return NULL;

    IngredientQList* current = list;
    while ( current != NULL )
    {
        if ( current->next == NULL ) return current;
        current = current->next;
    }
    return NULL;
}
IngredientQList* insertQIngreient( IngredientQList* list, String name, String unit, int quantity )
{
    IngredientQList* newItem = malloc( sizeof(IngredientQList) );
                     newItem->name = name;
                     newItem->unit = unit;
                     newItem->quantity = quantity;
                     newItem->next = NULL;

    if ( list == NULL ) return newItem;

    lastQIngredient( list )->next = newItem;
    return list;
}
IngredientQList* deleteQIngredient( IngredientQList* list, IngredientQList* item )
{
    if ( list == NULL ) return NULL;

    if ( strcompare( list->name, item->name ) )
    {
        IngredientQList* returnList = list->next;

        //free( item->name );
        //free( item->unit );
        free( item );

        return returnList;
    }

    IngredientQList* prev = list;
    IngredientQList* current = list->next;
    while ( current != NULL )
    {
        if ( strcompare(current->name, item->name) )
        {
            prev->next = current->next;

            //free( current->name );
            //free( current->unit );
            free( current );

            break;
        }

        prev = prev->next;
        current = current->next;
    }

    return list;
}


/**
 * InstructionList függvények
 */
void freeInstructionList( InstructionList* list )
{
    if ( list == NULL ) return;

    InstructionList* current = list;
    while ( current != NULL )
    {
        InstructionList* toFree = current;
        current = current->next;

        //free( toFree->text );
        free( toFree );
    }
}
InstructionList* lastInstruction( InstructionList* list )
{
    if ( list == NULL ) return NULL;

    InstructionList* current = list;
    while ( current != NULL )
    {
        if ( current->next == NULL ) return current;
        current = current->next;
    }

    return NULL;
}
InstructionList* insertInstruction( InstructionList* list, String text )
{
    InstructionList* newItem = malloc( sizeof(InstructionList) );
                     newItem->text = text;
                     newItem->next = NULL;

    if ( list == NULL ) return newItem;

    lastInstruction( list )->next = newItem;
    return list;
}


/**
 * RecipeList függvények
 */
void freeRecipeList( RecipeList* list )
{
    if ( list == NULL ) return;

    RecipeList* current = list;
    while( current != NULL )
    {
        RecipeList* toFree = current;
        current = current->next;

        //free( toFree->name );
        freeInstructionList( toFree->instructions );
        freeIngredientQList( toFree->ingredients );
        free( toFree );
    }
}
int recipeListLength( RecipeList* list )
{
    if ( list == NULL ) return 0;

    int counter = 0;
    RecipeList* current = list;
    while ( current != NULL )
    {
        counter++;
        current = current->next;
    }

    return counter;
}
RecipeList* isRecipeInArray( RecipeList* list, RecipeList* item )
{
    if ( list == NULL ) return NULL;

    RecipeList* current = list;
    while ( current != NULL )
    {
        if ( strcompare(current->name, item->name) ) return current;
        current = current->next;
    }

    return NULL;
}
RecipeList* lastRecipe( RecipeList* list )
{
    if ( list == NULL ) return NULL;

    RecipeList* current = list;
    while ( current != NULL )
    {
        if ( current->next == NULL ) return current;
        current = current->next;
    }

    return NULL;
}
RecipeList* insertRecipe( RecipeList* list, String name, InstructionList* instructionList, IngredientQList* ingredientQList )
{
    RecipeList* new = malloc(sizeof(RecipeList));
                new->name = strcopy( name );
                new->ingredients = ingredientQList;
                new->instructions = instructionList;
                new->next = NULL;

    if ( list == NULL ) return new;

    lastRecipe( list )->next = new;
    return list;
}
RecipeList* insertRecipeList( RecipeList* list, RecipeList* new )
{
    if ( list == NULL ) return new;

    lastRecipe(list)->next = new;
    return list;
}
RecipeList* findRecipeById( RecipeList* list, int id )
{
    if ( list == NULL ) return NULL;

    RecipeList* current = list;
    int counter = 0;
    while ( current != NULL )
    {
        if ( counter == id ) return current;
        counter++;
        current = current->next;
    }

    return NULL;
}
RecipeList* findRecipeByName( RecipeList* list, String name )
{
    if ( list == NULL ) return NULL;

    RecipeList* current = list;
    while ( current != NULL )
    {
        if ( strcompare(current->name, name) ) return current;
        current = current->next;
    }

    return NULL;
}
RecipeList* deleteRecipe( RecipeList* list, RecipeList* item )
{
    if ( list == NULL ) return NULL;

    if ( list == item )
    {
        RecipeList* returnList = list->next;

        free(list->name);
        freeInstructionList(list->instructions);
        freeIngredientQList(list->ingredients);

        return returnList;
    }

    RecipeList* prev = list;
    RecipeList* current = list->next;
    while ( current != NULL )
    {
        if ( current == item )
        {
            prev->next = current->next;

            free(current->name);
            freeInstructionList(current->instructions);
            freeIngredientQList(current->ingredients);

            break;
        }
        prev = prev->next;
        current = current->next;
    }

    return list;
}
RecipeList* randomRecipe( RecipeList* list )
{
    srand(time(NULL));
    int num = (rand() % ((recipeListLength(list)-1) - 0 + 1)) + 0;

    return findRecipeById(list, num);
}

RecipeListFound* lastRecipeFound( RecipeListFound* list )
{
    if ( list == NULL ) return NULL;

    RecipeListFound* current = list;
    while ( current != NULL )
    {
        if ( current->next == NULL ) return current;
        current = current->next;
    }
}
RecipeListFound* insertRecipeFound( RecipeListFound* list, RecipeList* ptr )
{
    RecipeListFound* new = malloc(sizeof(RecipeListFound));
                     new->ptr = ptr;
                     new->next = NULL;

    if ( list == NULL ) return new;

    lastRecipeFound(list)->next = new;
    return list;
}
RecipeListFound* findRecipesByName( RecipeList* list, String needle )
{
    if ( list == NULL ) return NULL;

    RecipeListFound* returnList = NULL;

    RecipeList* current = list;
    while ( current != NULL )
    {
        //String hay = strToLower(current->name);
        //String ned = strToLower(needle);

        if ( substr(current->name, needle) )
        //if ( substr(hay, ned) )
        {
            returnList = insertRecipeFound(returnList, current);
        }
        //free(hay);
        //free(ned);

        current = current->next;
    }

    return returnList;
}
RecipeListFound* findRecipesByIngredient( RecipeList* list, String ingredient )
{
    if ( list == NULL ) return NULL;

    RecipeListFound* returnList = NULL;

    RecipeList* current = list;
    while ( current != NULL )
    {
        IngredientQList* ings = current->ingredients;
        bool checkIngr = true;
        while ( checkIngr && ings != NULL )
        {
            if ( strcompare(ings->name, ingredient) )
            {
                returnList = insertRecipeFound(returnList, current);
                checkIngr = false;
            }
            ings = ings->next;
        }

        current = current->next;
    }

    return returnList;
}
RecipeListFound* findRecipesByMoreIngredient( RecipeList* list, IngredientList* ingredients )
{
    if ( list == NULL ) return NULL;

    RecipeListFound* returnList = NULL;

    RecipeList* current = list;
    while ( current != NULL )
    {
        IngredientList* ingredient = ingredients;
        int ingCounter = 0;
        while ( ingredient != NULL )
        {
            IngredientQList* ings = current->ingredients;
            while ( ings != NULL )
            {
                if ( strcompare(ings->name, ingredient->name) )
                {
                    ingCounter++;
                    break;
                }
                ings = ings->next;
            }
            ingredient = ingredient->next;
        }

        if ( ingCounter == ingredientListLength(ingredients) )
        {
            returnList = insertRecipeFound(returnList, current);
        }

        current = current->next;
    }

    return returnList;
}


/**
 * StrList függvények
 */
void freeStrList( StrList* list )
{
    if ( list == NULL ) return;

    StrList* current = list;
    while ( current != NULL )
    {
        StrList* toFree = current;
        current = current->next;

        //if ( strlength(toFree->item) > 0 ) free(toFree->item);

        if ( toFree->length >= 0 && toFree->length <= 2 ) free( toFree );
    }
}
int strlistLength( StrList* list )
{
    if ( list == NULL ) return 0;

    StrList* current = list;
    int counter = 0;
    while ( current != NULL )
    {
        counter++;
        current = current->next;
    }

    return counter;
}
StrList* lastStr( StrList* list )
{
    if ( list == NULL ) return list;

    StrList* current = list;
    while ( current != NULL )
    {
        if ( current->next == NULL ) return current;
        current = current->next;
    }
}
StrList* findStrListById( StrList* list, int id )
{
    if ( list == NULL ) return NULL;

    int counter = 0;
    StrList* current = list;
    while ( current != NULL )
    {
        if ( counter == id ) return current;
        counter++;
        current = current->next;
    }

    return NULL;
}
StrList* insertStr( StrList* list, String item, int length )
{
    StrList* newItem = malloc( sizeof(StrList) );
             newItem->item = item;
             newItem->length = length;
             newItem->next = NULL;

    if ( list == NULL ) return newItem;

    lastStr( list )->next = newItem;
    return list;
}
StrList* fromIngredients( IngredientList* list )
{
    if ( list == NULL ) return NULL;

    StrList* response = NULL;
    IngredientList* current = list;
    while ( current != NULL )
    {
        response = insertStr( response, current->name, 0 );
        current = current->next;
    }

    return response;
}
StrList* fromQIngredints( IngredientQList* list )
{
    if ( list == NULL ) return NULL;

    StrList * start = NULL;
    StrList * last = start;
    IngredientQList* current = list;

    while ( current != NULL )
    {
        StrList* new = malloc( sizeof(StrList) );
        new->next = NULL;
        new->length = 0;
        new->item = malloc( (strlength(current->name) + (floor(log10(abs(current->quantity)))) + strlength(current->unit) + 5 + 2 ) * sizeof(char) );
        new->item = strcopy( current->name );
        strcat( new->item, " " );
        strcat( new->item, "-> " );

        String buffer = malloc( (floor(log10(abs(current->quantity)))+2) * sizeof(char) );
        itoa( current->quantity, buffer, 10 );
        strcat( new->item, buffer );

        strcat( new->item, current->unit );

        free(buffer); // TODO: megfigyelni

        if ( start == NULL )
        {
            start = new;
            last = new;
        }
        else
        {
            last->next = new;
            last = new;
        }

        current = current->next;
    }

    return start;
}
StrList* fromInstructions( InstructionList* list )
{
    if ( list == NULL ) return NULL;

    StrList* start = NULL;
    InstructionList* current = list;
    int counter = 1;

    while ( current != NULL )
    {
        String str = malloc( (strlength(current->text) + (floor(log10(abs(counter)))) + 3 ) * sizeof(char) );
        if (str == NULL) continue; // DEBUG

        sprintf( str, "%d. %s", counter, current->text );

        start = insertStr( start, str, 0 );

        counter++;
        current = current->next;
    }

    return start;
}
StrList* fromRecipeFound( RecipeListFound* list )
{
    if ( list == NULL ) return NULL;

    StrList* response = NULL;
    RecipeListFound* current = list;
    while ( current != NULL )
    {
        response = insertStr( response, current->ptr->name, 0 );
        current = current->next;
    }

    return response;
}
StrList* fromRecipeToDisplay( RecipeList* selected )
{
    StrList* recipeShowStrList = NULL;

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

    return recipeShowStrList;
}