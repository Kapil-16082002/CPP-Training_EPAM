
strcpy is a standard C library function used to copy a string from one location to another. 
It is declared in the <string.h> header file.
/* 
1️⃣ char src[] — Character Array
char src[] means you are defining an array of characters —
the compiler allocates memory for the characters inside the array itself.

🔹 Example:
char src[] = "Kapil";
✅ Here:
Compiler creates an array of 6 chars ('K' 'a' 'p' 'i' 'l' '\0')
The string literal "Kapil" is copied into the array.
src acts like the base address of the array.

💡 You can modify characters inside the array:
src[0] = 'k';   // ✅ allowed
char *src

🧩 2️⃣ char *src — Pointer to Character/String Literal
🔹 Definition:
char *src is a pointer that stores the address of a string literal (or some memory location).
🔹 Example:
char *src = "Kapil";
✅ Here:
"Kapil" is stored in read-only memory (text segment).
src just points to that location.
You cannot modify the string literal!

💥 If you try to modify:
src[0] = 'k';  // ❌ Runtime error (segmentation fault)
📌 The pointer itself is on stack, but it points to read-only memory.


*/

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


//================================================================================================================
🧩 Function: strcpy(dest, src)

Header: <string.h>

4️⃣ “If dest was larger than needed, bytes after the null terminator remain unchanged but are not part of the string.”

✔ This means:
Even if dest has extra space, the string ends at '\0' —
anything after that is ignored by string functions.

Example:
char dest[10] = "ABCDEFGH";
char src[] = "Hi";
strcpy(dest, src);

✅ After copy:
dest = "Hi\0EFGH"

Explanation:
'H', 'i', and '\0' overwrite the first three bytes of dest.
The remaining bytes (EFGH) are unchanged,
but they are not part of the new string (because string ends at '\0').
Memory layout:

|H|i|\0|E|F|G|H|\0|?|?|
 ↑
 End of new string here (strlen = 2)

✅ Extra characters (E F G H) still exist physically in memory,
but logically, the string is "Hi".
Before:
dest: [A][B][C][D][E][F][\0]
src : [H][i][\0]

After strcpy(dest, src):
dest: [H][i][\0][D][E][F][\0]
           ^
           End of new string


2️⃣If src is longer than dest
strcpy() does not check buffer size!, it will cause a buffer overflow, leading to undefined behavior.

⚠️ Situation:
char dest[5];     // can hold up to 4 chars + '\0'
char src[] = "KapilSolanki";  // 12 characters + '\0'
strcpy(dest, src);  // ⚠️ dangerous!

Step-by-step:
strcpy() starts copying from src → dest.
It keeps copying until it finds the first '\0' in src.
But dest only has space for 5 bytes, while src needs 13 bytes (12 + '\0').
So copying goes beyond the allocated memory for dest.



✅ Safer alternative:
Use strncpy to limit copying size:
strncpy(dest, src, sizeof(dest) - 1); // reserve 1 byte for '/0'
dest[sizeof(dest) - 1] = '\0';  // Ensure placing null-termination

✔ This copies at most (n - 1) characters, and ensures the string is properly terminated.
strcpy_s (part of C11) provides a safer way to copy strings by enforcing size restrictions.




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

✅strncpy in C ->
Function Prototype:
char *strncpy(char *destination, const char *source, size_t n);

Parameters
destination: Pointer to the destination array where the copied string will be stored.
source: Pointer to the null-terminated source string to be copied.
n: Maximum number of characters to copy from source.

Return Value: Returns a pointer to the destination string.

Properties and Behavior:
1.Copies at Most n Characters->
   If source is shorter than n, strncpy will stop at the null character.
   If source is longer than n, it copies only n characters without adding a null terminator.
2.No Automatic Null-Termination->
   Unlike strcpy, strncpy does not always append \0 if n is less than or equal to strlen(source).
   The programmer must manually add \0 to ensure null-termination.
3.Fills Remaining Space with Null Characters (\0)->
   If source is shorter than n, the remaining part of destination is padded with \0 until n bytes are filled.
4.Handles Buffer Overflows Better Than strcpy->
    Prevents reading beyond source but does not guarantee null-termination.
5.Does Not Handle Overlapping Memory->
  Like strcpy, overlapping source and destination leads to undefined behavior.


#include <stdio.h>
#include <string.h>

int main() {
    char src[] = "Kapil";  // sizeof(src)= 6 i.e (5+'/0' == 6)
    char dest[5];  // Smaller than src, only 5 bytes (no room for full string + '\0')

    // Copy at most sizeof(dest) - 1 characters
    strncpy(dest, src, sizeof(dest) - 1);

    // Manually add null terminator to ensure proper string termination
    dest[sizeof(dest) - 1] = '\0';

    printf("Source String : %s\n", src);  // Source String : "Kapil"
    printf("Copied String : %s\n", dest);  // Output will be "Kapi"

    return 0;
}
🚫 If you forget to add '\0'

Without this line:
dest[sizeof(dest) - 1] = '\0';

then dest might not contain a null terminator —
so printf("%s", dest); could read beyond its boundary, leading to undefined behavior.



//////////////////////////////////////////////////////////////////////////////////////////////////////////////






