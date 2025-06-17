✅The register storage class is used to suggest that a variable should be stored in the processor's register instead of RAM.
Because Accessing register variable is much faster than accessing variables stored in RAM

✅Why register Variables Cannot Be Global:
A register variable cannot have external linkage, because CPU registers only exist at runtime for specific active functions, so their scope is tied to the function in which they are declared.


✅ Characteristics of the register Storage Class
The register storage class has unique properties:
Scope:

Same as a normal automatic (auto) variable, i.e.,function or block scope.

Lifetime:
Exists only as long as the block/function in which it is defined is active (automatic storage duration).

Storage:
Suggests that the variable be stored in a CPU register rather than in RAM for faster access.

Restrictions:
You can’t take the address of register variables because they are stored in CPU registers that have no memory address.
It is used primarily for loop counters or other frequently accessed variables.

#include <stdio.h>
int main() {
    // Register variable declaration
    register int i;

    // Loops commonly use register variables for faster execution
    for (i = 0; i < 10; i++) {
        printf("%d ", i);
    }

    return 0;
}

Example 2: Attempting to Take Address of a register Variable
#include <stdio.h>
int main() {
    register int x = 5;
    // int *ptr = &x; // Error: Cannot take address of a register variable
    printf("Value of x: %d\n", x);
}

✅Advantages of register Storage Class
Improved Speed:
Accessing variables stored in CPU registers is much faster than accessing variables in RAM.
Useful for variables that are frequently accessed like loop counters or temporary variables in computations.



✅Limitations of register Storage Class
1.No Address:
You can’t take the address of register variables because they are stored in CPU registers that have no memory address.

2.Limited Registers:
The number of registers available on a CPU is limited, so the compiler may not always place a register variable in an actual register.

3.Compiler choice:
The register keyword is merely a request; it is up to the compiler whether to accept request or not.