#ifndef RECEPTKONYV_FILE_OPERATIONS_H
#define RECEPTKONYV_FILE_OPERATIONS_H

#include "../resources/components/components.h"
#include <stdio.h>
#include <stdlib.h>

void writeRecipeFile( RecipeList* recipes );
void writeIngredientlistFile( IngredientList* ingredients );
void writePantrylistFile( IngredientQList* pantry);

RecipeList* readRecipeFile();
IngredientList* readIngredientlistFile();
IngredientQList* readPantrylistFile();

#endif //RECEPTKONYV_FILE_OPERATIONS_H
