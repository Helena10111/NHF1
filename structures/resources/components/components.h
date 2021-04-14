#ifndef RECEPTKONYV_COMPONENTS_H
#define RECEPTKONYV_COMPONENTS_H

#include "../string/string.h"
#include <stdarg.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
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
typedef struct StrList {
    String item;
    int length;
    struct StrList* next;
} StrList;
typedef struct RecipeListFound {
    RecipeList* ptr;
    struct RecipeListFound* next;
} RecipeListFound;

/**
 * IngredientList függvények
 */
bool isIngredientInArray( IngredientList* list, String name );
void freeIngredientList( IngredientList* list );
IngredientList* findIngredientByName( IngredientList* ingredients, String name );
IngredientList* findIngredientById( IngredientList* ingredients, int id );
IngredientList* deleteIngredient( IngredientList* list, IngredientList* item );
IngredientList* lastIngredient( IngredientList* start );
IngredientList* insertIngredient( IngredientList* list, String name );


/**
 * IngredientQuantityList függvények
 */
bool isIngredientQInArray( IngredientQList* list, String name );
void freeIngredientQList( IngredientQList* list );
IngredientQList* findQIngredientByName( IngredientQList* list, String _name );
IngredientQList* lastQIngredient( IngredientQList* list );
IngredientQList* insertQIngreient( IngredientQList* list, String name, String unit, int quantity );
IngredientQList* deleteQIngredient( IngredientQList* list, IngredientQList* item );
IngredientQList* findQIngredientById( IngredientQList* list, int id );

/**
 * InstructionList függvények
 */
void freeInstructionList( InstructionList* list );
InstructionList* lastInstruction( InstructionList* list );
InstructionList* insertInstruction( InstructionList* list, String text );


/**
 * RecipeList függvények
 */
void freeRecipeList( RecipeList* list );
RecipeList* isRecipeInArray( RecipeList* list, RecipeList* item );
RecipeList* lastRecipe( RecipeList* list );
RecipeList* insertRecipe( RecipeList* list, String name, InstructionList* instructionList, IngredientQList* ingredientQList );
RecipeList* findRecipeById( RecipeList* list, int id );
RecipeList* deleteRecipe( RecipeList* list, RecipeList* item );
RecipeList* insertRecipeList( RecipeList* list, RecipeList* new );
RecipeList* findRecipeByName( RecipeList* list, String name );

RecipeListFound* findRecipesByIngredient( RecipeList* list, String ingredient );
RecipeListFound* lastRecipeFound( RecipeListFound* list );
RecipeListFound* insertRecipeFound( RecipeListFound* list, RecipeList** ptr );
RecipeListFound* findRecipesByName( RecipeList* list, String needle );
RecipeList* randomRecipe( RecipeList* list );


/**
 * StrList függvények
 */
void freeStrList( StrList* list );
StrList* lastStr( StrList* list );
int strlistLength( StrList* list );
StrList* findStrListById( StrList* list, int id );
StrList* insertStr( StrList* list, String item, int length );
StrList* fromIngredients( IngredientList* list);
StrList* fromQIngredints( IngredientQList* list );
StrList* fromInstructions( InstructionList* list );
StrList* fromRecipeFound( RecipeListFound* list );
StrList* fromRecipeToDisplay( RecipeList* selected );

#endif //RECEPTKONYV_COMPONENTS_H
