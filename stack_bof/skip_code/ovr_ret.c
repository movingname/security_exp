#include<stdio.h>

void function(int a, int b, int c){
    char buffer1[5] = "aaaaa";
    char buffer2[10] = "bbbbbbbbbb";
    int *ret;
   
    // Here is the stack layout:
    // 0xFFFFFFFF
    // c
    // b
    // a
    // eip
    // ebp
    // ??? (Find while using gdb, the size could be 8 or 12. Alignment or canary?)
    // buffer1 - 5 bytes (The compiler will not align it to 4)
    // buffer2 - 10 bytes

    // Find the eip
    // Q: Can we use &buffer1?
    // It seems that &buffer1 also gives you buffer,
    // However, the type is (char (*)[5]), so the arithmetic will be different.
    ret = buffer1 + 5 + 12 + 4;
    
    // Modify eip to skip the x=1 line in main
    // How should we set eip?
    // Use gdb.
    // 1. Find the saved eip in function's frame. It should be the 
    //    addr of the next instruction (x=1) after call function in main.
    // 2. Do disas main to get the disassembly. Then find the ins addr
    //    after x=1. The addr diff is what we want.
    (*ret) += 8;
}

void main(){
    int x;
    x = 0;
    function(1, 2, 3);

    // We want to skip this line using stack overflow.
    x = 1;
    printf("%d\n", x);
}
