#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "../../../debugmalloc.h"

typedef char* String;

String strcopy( String _inpt )
{
    String new = malloc( (strlen(_inpt)+1) * sizeof(char) );
    if ( new == NULL ) return NULL; // Nem sikerült a foglalás

    strcpy( new, _inpt );

    return new;
}
int strlength( String _inpt )
{
    if ( _inpt == NULL ) return -1;
    return strlen( _inpt );
}
bool strcompare( String _first, String _second )
{
    if ( !(_first == NULL || _second == NULL) && strcmp( _first, _second ) == 0 ) return true;
    return false;
}
String trim( String _inpt )
{
    while ( (char)*_inpt == ' ' )
    {
        _inpt++;
    }

    if ( *_inpt == 0  ) return _inpt;

    String end = _inpt + strlength(_inpt) -1;
    while ( end > _inpt && (char)*end == ' ' )
    {
        end--;
    }

    end[1] = '\0';

    _inpt = realloc( _inpt, (strlength(_inpt)+1) );
    return _inpt;
}
bool substr( String haystack, String needle )
{
    if ( strstr( haystack, needle ) == NULL ) return false;
    return true;
}
String strToLower( String input )
{
    String new = strcopy(input);

    for(int i = 0; new[i]; i++){
        new[i] = tolower(new[i]);
    }

    return new;
}