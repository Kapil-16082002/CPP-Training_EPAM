#include <iostream>
#include <unordered_map>
#include <cstdlib>  // For malloc/free
using namespace std;

static unordered_map<void*, size_t> mp;
unordered_map<void*, size_t> &getMap() {

    return mp;

}
// Overloaded new operator with a line number parameter (placement new)
void* operator new(size_t size, const char* file, int line) {
    cout << "Overloaded new at " << file << ":" << line << endl;
    void* p = malloc(size);  // Use malloc to allocate memory
    if (!p) {
        throw std::bad_alloc();
    }
    getMap()[p] = size;  // Track the allocated memory
    return p;
}
// Overloaded delete operator
void operator delete(void* p) noexcept {
    if (p) {
        if(mp.find(p)!=mp.end()){
            getMap().erase(p);
        }
        cout << "Overloaded delete at " << p << endl;
          // Free the memory
    }
    else return;
    free(p);
}
// Overloaded new[] operator (for arrays)
void* operator new[](size_t size, const char* file, int line) {
    cout << "Overloaded new[] at " << file << ":" << line << endl;
    void* p = malloc(size);  // Use malloc to allocate memory
    getMap()[p] = size;  // Track the allocated memory
    return p;
}
void checkleak(unordered_map<void*, size_t> &mp){
    if(!mp.empty()){
        cout<<"leak detected"<<endl;
        for(auto& it: mp) cout<<it.first<<" "<<it.second<<endl;
    }
    else cout<<" no leak detected"<<endl;
}
 
// Overloaded delete[] operator (for arrays)
void operator delete[](void* p) noexcept {

    if (p) {
        mp.erase(p);
        cout << "Overloaded delete[] at " << p << endl;
        free(p);  // Free the memory
    }
}
 
// Macro to automatically insert the current line number and file
#define new new(__FILE__, __LINE__)

int main() {

    // Allocate memory for a single integer using the overloaded new
    int* x = new int;
    // Allocate memory for an array of integers
    // int* y = new int[1];
   // Deallocate memory

    //delete x;
    // delete[] y;
    
    checkleak(mp);

    return 0;

}

 