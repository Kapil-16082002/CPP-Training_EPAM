#Padding_in_Structures -
Padding is extra unused bytes added to the structure members to align them to memory boundaries (usually 2, 4, or 8 bytes).
The goal is to make memory access faster on some architectures.
The size of a structure may be larger than the sum of its members due to padding.

#Example: Structure with #Padding
#include <stdio.h>
struct PaddedStruct {
    char a;    // 1 byte -> will become 4bytes
    int b;     // 4 bytes
    char c;    // 1 byte -> will become 4bytes
};
int main() {
    printf("Size of structure with padding: %lu bytes\n", sizeof(struct PaddedStruct));
    return 0;
}
✅ Output (with padding): Size of structure with padding: 12 bytes(4+4+4)
Memory Layout:
-------------------
| 'a' (1B) | PADDING (3B) | 'b' (4B) | 'c' (1B) | PADDING (3B) |
-------------------
Total: 12 bytes

Why padding?
   char a takes 1 byte.
   Compiler adds 3 bytes padding to align int b to a 4-byte boundary.
   int b takes 4 bytes.
   char c takes 1 byte.
   Compiler adds 3 bytes padding at the end for alignment.

🔹 Removing Padding using #pragma pack(1)
   We can force no padding using #pragma pack(1), but this may cause performance issues.
   #include <stdio.h>
   #pragma pack(1)  // Disable padding-> it means all datatypes will be multiple of 1.
   struct NoPaddingStruct {
       char a;   // 1 byte
       int b;    // 4 bytes
       char c;   // 1 byte
   };
   int main() {
       printf("Size of structure without padding: %lu bytes\n", sizeof(struct NoPaddingStruct));
       return 0;
   }
   ✅ Output (without padding):
   Size of structure without padding: 6 bytes
   -------------------
| 'a' (1B) | 'b' (4B) | 'c' (1B) |
-------------------
Total: 6 bytes
   Pros: Saves memory.
   Cons: Slower memory access on some architectures.
   /////////////////////////////////////////////////////////////////////////////////////////////////////////
🔹 Structure Padding Based on Member Order
  Changing the order of members can reduce padding.

1.Bad Order (More Padding)
struct BadOrder {
    char a;   // 1 byte
    int b;    // 4 bytes
    char c;   // 1 byte
};
✅ Size = 12 bytes

2.Good Order (Less Padding)
struct GoodOrder {
    char a;   // 1 byte
    char c;   // 1 byte
    int b;    // 4 bytes
};
✅ Size = 8 bytes
📌 Memory Layout:
-------------------
| 'a' (1B) | 'c' (1B) | PADDING (2B) | 'b' (4B) |
-------------------
Total: 8 bytes

🔹Padding vs Alignment
    Padding	Extra bytes added to align memory
    Alignment Ensuring data fits word boundaries (2B, 4B, 8B)




    