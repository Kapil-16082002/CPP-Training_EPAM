
✅ Header File (.h / .hpp) 
Contains declarations (function prototypes, macros, data types, etc.)
What They Do:
They tell the compiler what functions, variables, and classes exist — but not how they work.

Example: math.h /* Declaration only — no definition here */
double sqrt(double x);

When you write:
#include <math.h>
You are telling the compiler:
“Hey, there’s a function called sqrt that takes a double and returns a double.”

But where’s the actual code of sqrt()?
👉 It’s inside the math library, not the header.



✅Library (.lib / .a / .so / .dll)
Contains definitions (actual compiled machine code of functions, classes, etc.)
Libraries contain the compiled definitions — the actual machine code.
| Type                         | Description                                                     | Example                                   |
| ---------------------------- | --------------------------------------------------------------- | ----------------------------------------- |
| **Static Library**           | Linked *at compile/link time*; becomes part of the final `.exe` | `libm.a` (Linux), `math.lib` (Windows)    |
| **Dynamic / Shared Library** | Linked *at runtime*; loaded by the OS when the program runs     | `libm.so` (Linux), `msvcrt.dll` (Windows) |




| Concept             | Header File (.h / .hpp)                                                 | Library (.lib / .a / .so / .dll)                                                  |
| ------------------- | ----------------------------------------------------------------------- | --------------------------------------------------------------------------------- |
| **Purpose**         | Contains *declarations* (function prototypes, macros, data types, etc.) | Contains *definitions* (actual compiled machine code of functions, classes, etc.) |
| **Used by**         | Compiler (during *compilation*)                                         | Linker (during *linking*)                                                         |
| **Phase of use**    | Compilation time                                                        | Linking time                                                                      |
| **Example**         | `#include <stdio.h>`                                                    | Links to `libc` (contains `printf`, `scanf`, etc.)                                |
| **Contains**        | No executable code                                                      | Precompiled object code                                                           |
| **Extension (C)**   | `.h`                                                                    | `.a`, `.so`, `.dll`, `.lib`                                                       |
| **Extension (C++)** | `.hpp` or `.h`                                                          | `.a`, `.so`, `.dll`, `.lib`                                                       |


