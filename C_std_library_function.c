
strcpy is a standard C library function used to copy a string from one location to another. 
It is declared in the <string.h> header file.

Function Prototype->
char *strcpy(char *destination, const char *source);
Parameters->
        destination: Pointer to the destination array where the copied string will be stored.
        source: Pointer to the null-terminated source string that will be copied.
Return Value: Returns a pointer to the destination string (destination).

#include <stdio.h>
#include <string.h>
int main() {
    char src[] = "Hello, World!";
    char dest1[20]="kapil";  // Ensure enough space
    char dest2[20];   //   Ensure enough space
    strcpy(dest1, src);  // Copy source to destination
    strcpy(dest2, src);
    printf("Copied String: %s\n", dest1); // Hello, World!  -> Overwrites Existing Data
    printf("Copied String: %s\n", dest2); // Hello, World!
    return 0;
}
Properties and Behavior
1.Copies characters from source to destination including the null-terminator (\0).
2.strcpy does not check the size of destination, which can lead to buffer overflows if destination is smaller than source.
3.The function directly copies the contents of source to destination, overwriting existing data.
4.The source string must be null-terminated, or the function will continue reading beyond the intended string, causing undefined behavior.
5.Returns the pointer to the destination, allowing function chaining like:
        printf("%s", strcpy(dest, src));

Safe Alternative-> 
Use strncpy to limit copying size:
 strncpy(dest, src, sizeof(dest) - 1);
 dest[sizeof(dest) - 1] = '\0';  // Ensure null-termination

strcpy_s (part of C11) provides a safer way to copy strings by enforcing size restrictions.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
strncpy in C ->
Function Prototype:
char *strncpy(char *destination, const char *source, size_t n);

Parameters
destination: Pointer to the destination array where the copied string will be stored.
source: Pointer to the null-terminated source string to be copied.
n: Maximum number of characters to copy from source.

Return Value: Returns a pointer to the destination string.

Properties and Behavior:
Copies at Most n Characters->
   If source is shorter than n, strncpy will stop at the null character.
   If source is longer than n, it copies only n characters without adding a null terminator.
No Automatic Null-Termination->
   Unlike strcpy, strncpy does not always append \0 if n is less than or equal to strlen(source).
   The programmer must manually add \0 to ensure null-termination.
Fills Remaining Space with Null Characters (\0)->
   If source is shorter than n, the remaining part of destination is padded with \0 until n bytes are filled.
Handles Buffer Overflows Better Than strcpy->
    Prevents reading beyond source but does not guarantee null-termination.
Does Not Handle Overlapping Memory->
  Like strcpy, overlapping source and destination leads to undefined behavior.

#include <stdio.h>
#include <string.h>

int main() {
    char src[] = "Hello, World!";
    char dest[10];  // Smaller buffer to demonstrate strncpy behavior

    strncpy(dest, src, sizeof(dest) - 1);  // Copy at most 9 characters
    dest[sizeof(dest) - 1] = '\0';  // Ensure null-termination

    printf("Copied String: %s\n", dest);
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
