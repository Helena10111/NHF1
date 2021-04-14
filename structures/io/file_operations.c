#include "../resources/components/components.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../debugmalloc.h"

void writeRecipeFile( RecipeList* recipes )
{
    FILE* file;
    file = fopen("recipes.txt", "wt");

    if ( recipes != NULL && file != NULL )
    {
        RecipeList* current = recipes;
        while ( current != NULL )
        {
            fprintf(file, "%s   ", current->name);

            InstructionList* currentInstruction = current->instructions;
            while ( currentInstruction != NULL )
            {
                fprintf(file, "%s;", currentInstruction->text);
                currentInstruction = currentInstruction->next;
            }

            fprintf(file, "%s", "   ");

            IngredientQList* currentIngredients = current->ingredients;
            while ( currentIngredients != NULL )
            {
                fprintf(file, "%s %d %s;", currentIngredients->name, currentIngredients->quantity, currentIngredients->unit);
                currentIngredients = currentIngredients->next;
            }

            fprintf(file, "%s", "\n");

            current = current->next;
        }
    }

    fclose(file);
}
void writeIngredientlistFile( IngredientList* ingredients )
{
    FILE* file;
    file = fopen( "ingredients.txt", "wt");

    if ( ingredients != NULL && file != NULL )
    {
        IngredientList* current = ingredients;
        while ( current != NULL )
        {
            fprintf(file, "%s\n", current->name);
            current = current->next;
        }
    }

    fclose(file);
}
void writePantrylistFile( IngredientQList* pantry)
{
    FILE* file;
    file = fopen( "pantry.txt", "wt");

    if ( pantry != NULL && file != NULL )
    {
        IngredientQList* current = pantry;
        while ( current != NULL )
        {
            fprintf(file, "%s   %d    %s\n", current->name, current->quantity, current->unit);
            current = current->next;
        }
    }

    fclose(file);
}

RecipeList* readRecipeFile()
{
    RecipeList* newList = NULL;

    FILE* file;
    char * line = malloc(2*sizeof(char));
    int linecounter = 0;
    int chr;
    size_t len = 0;

    file = fopen( "recipes.txt", "r");
    if ( file == NULL ) return NULL;

    while ( (chr = fgetc(file)) != EOF )
    {
        if ( chr == '\n' )
        {
            if ( linecounter > 0 )
            {
                line[linecounter] = '\0';

                String name = malloc(101*sizeof(char));
                String instructions = malloc(3001*sizeof(char));
                String ingredients = malloc(1001*sizeof(char));

                sscanf( line, "%s   %s  %s", name, instructions, ingredients );
                name = realloc(name, (strlength(name)+1) * sizeof(char));
                instructions = realloc(instructions, (strlength(instructions)+1) * sizeof(char));
                ingredients = realloc(ingredients, (strlength(ingredients)+1) * sizeof(char));

                int buffercounter = 0;
                String buffer = malloc(2*sizeof(char));
                InstructionList* instructionList = NULL;
                for(int i = 0; instructions[i] != '\0'; ++i)
                {
                    if ( instructions[i] == ';' )
                    {
                        buffer[buffercounter] = '\0';

                        instructionList = insertInstruction(instructionList, strcopy(buffer));

                        free(buffer);
                        buffercounter = 0;
                        buffer = malloc(2*sizeof(char));
                    }
                    else
                    {
                        buffer[buffercounter++] = instructions[i];
                        buffer = realloc(buffer, (strlen(buffer)+1) * sizeof(char));
                    }
                }
                free(instructions);

                buffercounter = 0;
                buffer = malloc(2*sizeof(char));
                IngredientQList* ingredientQList = NULL;
                for(int i = 0; ingredients[i] != '\0'; ++i)
                {
                    if ( ingredients[i] == ';' )
                    {
                        buffer[buffercounter] = '\0';

                        String nm = malloc(101*sizeof(char));
                        String unit = malloc(51*sizeof(char));
                        int quant;

                        sscanf(buffer, "%s %d %s", nm, &quant, unit);
                        nm = realloc(nm, (strlen(nm)+1)*sizeof(char));
                        unit = realloc(unit, (strlen(unit)+1)*sizeof(char));

                        ingredientQList = insertQIngreient(ingredientQList, nm, unit, quant);

                        free(buffer);
                        buffercounter = 0;
                        buffer = malloc(2*sizeof(char));
                    }
                    else
                    {
                        buffer[buffercounter++] = ingredients[i];
                        buffer = realloc(buffer, (strlen(buffer)+1) * sizeof(char));
                    }
                }
                free(ingredients);

                newList = insertRecipe(newList, name, instructionList, ingredientQList );

                linecounter = 0;
                free(line);
                line = malloc(2*sizeof(char));
            }
        }
        else
        {
            line[linecounter++] = chr;
            line = realloc(line, (strlen(line)+1)*sizeof(char));
        }
    }
    fclose(file);
    return newList;
}
IngredientList* readIngredientlistFile()
{
    IngredientList* newList = NULL;

    FILE* file;
    char * line = malloc(2*sizeof(char));
    int linecounter = 0;
    int chr;
    size_t len = 0;

    file = fopen( "ingredients.txt", "r");
    if ( file == NULL ) return NULL;

    while ( (chr = fgetc(file)) != EOF )
    {
        if ( chr == '\n' )
        {
            if ( linecounter > 0 )
            {
                line[linecounter] = '\0';

                newList = insertIngredient(newList, strcopy(line));

                linecounter = 0;
                free(line);
                line = malloc(2*sizeof(char));
            }
        }
        else
        {
            line[linecounter++] = chr;
            line = realloc(line, (strlen(line)+1)*sizeof(char));
        }
    }
    fclose(file);
    return newList;
}
IngredientQList* readPantrylistFile()
{
    IngredientQList* newList = NULL;

    FILE* file;
    char * line = malloc(2*sizeof(char));
    int linecounter = 0;
    int chr;
    size_t len = 0;

    file = fopen( "pantry.txt", "r");
    if ( file == NULL ) return NULL;

    while ( (chr = fgetc(file)) != EOF )
    {
        if ( chr == '\n' )
        {
            if ( linecounter > 0 )
            {
                line[linecounter] = '\0';

                String name = malloc(201*sizeof(char));
                int quantity;
                String unit = malloc(51*sizeof(char));
                printf("%s\n", line);
                sscanf(line, "%s    %d  %s", name, &quantity, unit);

                name = realloc(name, (strlength(name)+1) * sizeof(char));
                unit = realloc(unit, (strlength(unit)+1) * sizeof(char));

                newList = insertQIngreient(newList,name, unit, quantity);

                linecounter = 0;
                free(line);
                line = malloc(2*sizeof(char));
            }
        }
        else
        {
            line[linecounter++] = chr;
            line = realloc(line, (strlen(line)+1)*sizeof(char));
        }
    }
    fclose(file);
    return newList;
}