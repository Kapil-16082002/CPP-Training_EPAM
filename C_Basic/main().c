 The main() function in C is the entry point of every C program.
 When you run a C program, execution always starts from main().

1️⃣ Syntax of main() in C
Standard Declaration
int main() {
    return 0;
}
OR
int main(int argc, char *argv[]) {
    return 0;
}

Key Components:
int → Return type (main() must return an integer).
main → Function name (predefined by the language).
() → Parameter list (can be empty or include command-line arguments).
{} → Function body (contains the program logic).
return 0; -> Returns an exit status to the operating system (0 means success).

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

2️⃣ What Does main() Return?
main() must return an integer.
The returned value is sent to the operating system to show the program execution result.
Return Value	   Meaning
0	               Successful execution
1 (or non-zero)	   Error occurred

✅ Check main() Return Value in Windows (CMD) -
1️⃣ Write the Same C Program
#include <stdio.h>
int main() {
    printf("Program executed.\n");
    return 5;
}
2️⃣ Compile and Run
gcc program.c -o program.exe
program.exe
echo %ERRORLEVEL%   //# Prints the exit status

3️⃣🔹 Expected Output
Program executed.
5
%ERRORLEVEL% stores the return value in Windows.

/* 
🚫 2. What if you don’t specify a return type?
Example:
main() {
    printf("Hello\n");
}

⚠️ Behavior:```````````````````````````````````````````````
Old C (pre-C89 / K&R C):
Implicit int return type was allowed, so this would compile (with warnings).

Modern C (C99 and later):
❌ Error: every function must have an explicitly declared return type.

//==============================================================================================================

🚫 3. What if you don’t return anything?
Example:
int main() {
    printf("Hello\n");
}

Behavior:
C89: Returning nothing was undefined behavior.

C99 and later:
It’s implicitly equivalent to return 0; in main only.
Meaning:
If main() reaches the end without a return, it’s as if you wrote: return 0;

🟢 So this is safe and standard-compliant in modern C.

//==============================================================================================================

⚙️ 4. What if you return a negative value?
Example:
int main() {
    return -1;
}
Behavior:
The value returned by main is passed to the operating system as the exit status.

By convention:
0 → success
non-zero → failure

*/


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
3️⃣ Variants of main()
1. Without Parameters (Most Common)
int main() {
    return 0;
}
✔ Standard in modern C (C99, C11).
✔ Works fine when no command-line arguments are needed.

2. With argc and argv (Command-line Arguments)
int main(int argc, char *argv[]) {
    return 0;
}
✔ Used when the program accepts command-line arguments.

argc (argument count) → Number of arguments passed (including program name).
argv (argument vector) → Array of arguments (strings).
Example
#include <stdio.h>
int main(int argc, char *argv[]) {
    printf("Number of arguments: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("Arg %d: %s\n", i, argv[i]);
    }
    return 0;
}
Output
Number of arguments: 3
Arg 0: ./program
Arg 1: hello
Arg 2: world
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

6️⃣ Where is main() Defined?
main() is not a keyword or built-in function in C or C++.
main() is not predefined in a C or c++ library, it’s automatically linked by the compiler and runtime.
It’s a user-defined function — but it has special significance because it’s the entry point of your program.

Where is main() defined? In your source file (.c or .cpp).

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
7️⃣ Who Calls main()?
When you run a C program, the Operating System calls main().
Internally, the C runtime (crt0.o) is responsible for setting up the environment before main() runs.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
8️⃣ How main() Works Internally

1.OS loads the program into memory.
2.Runtime environment (crt0.o) initializes:
    Stack
    Heap
    Global variables
3.Calls main().
4.Program executes.
5.Returns an exit code (return 0;).

.cpp file -->(preprocessing) ----> .i file----->> (compiler)------>.s file(assembly language file)-------->>>

------->(assembler)--------.... .obj file ------>( .linker )-------> .exe file ----->OS load into memory -----> above steps


Preprocessed file (.i)	
Compilation	Assembly file (.s)
Assembly	Object file (.o)	
Linking	Executable file (.exe)