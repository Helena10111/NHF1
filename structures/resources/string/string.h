#ifndef RECEPTKONYV_STRING_H
#define RECEPTKONYV_STRING_H

#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "../../../debugmalloc.h"

typedef char* String;

String strcopy( String _inpt );
int strlength( String _inpt );
bool strcompare( String _first, String _second );
String trim( String _inpt );
bool substr( String haystack, String needle );
String strToLower( String input );

#endif //RECEPTKONYV_STRING_H
