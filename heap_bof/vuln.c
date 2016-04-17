#include<stdlib.h>

int main (int argc, char *argv[])
{
    char *buf, *buf1;
	buf = malloc(16);
    buf1 = malloc (16);
    if (argc > 1)
        memcpy (buf, argv[1], strlen (argv[1]));
		sprintf(buf1, "%s", "BBBBBBBBBBBBBBB\0");
        printf ("%#p [ buf ] (%.2d) : %s\n", buf, strlen(buf), buf);
        printf ("%#p [ buf1 ] (%.2d) : %s \n", buf1, strlen(buf1), buf1);
        printf ("From buf to buf1 :%d\n\n", buf1 -buf);
        printf ("Before free buf\n");
        free (buf); 
        printf ("Before free buf1\n");
        free (buf1); 
        return 0;
}

// GDB Investigation
// bt: At crash, the current function is __kernel_vsyscall()
// frame 5: Jump to the main stack frame
// print buf: Want to figure out the addr of buf.
//            It is 0x80485d0, but the area is in text section.
//            Actually, buf is corrupted when doing free.
// print buf1: The location is 0x804b020, and it is indeed on the heap.
// x/40 $buf1-20: It shows that the overflow passes buf and reaches buf1.
// Now, we want to examine the no crash cases.
// b 10:
// p buf
// x/40x $buf-20: Strangely, the surrounding data are zero. I cannot 
// identify the heap data structure. So I guess the minimal allocation 
// size is a page?
// To examine the size of the heap, run "cat /proc/<pid>/maps",
// then find the [heap] section: 0804b000-0806c000, but this is a very
// large area. We need deeper inspection.
// Can we examine the heap data structure? One idea is to step through
// a normal allocation. Suppose buf is filled with A, and buf1 is filled 
// with B. Then how are they allocated and how are they freed?
// Allocation:
// 0x804aff4:	0x00000000	0x00000000	0x00000000	0x00000000
// 0x804b004:	0x00000019	0x41414141	0x41414141	0x41414141
// 0x804b014:	0x41414141	0x00000000	0x00000019	0x42424242
// 0x804b024:	0x42424242	0x42424242	0x00424242	0x00000000
// 0x804b034:	0x00020fd1	0x00000000	0x00000000	0x00000000
// After buf is freed:
// 0x804aff4:	0x00000000	0x00000000	0x00000000	0x00000000
// 0x804b004:	0x00000019	0x00000000	0x41414141	0x41414141
// 0x804b014:	0x41414141	0x00000000	0x00000019	0x42424242
// 0x804b024:	0x42424242	0x42424242	0x00424242	0x00000000
// 0x804b034:	0x00020fd1	0x00000000	0x00000000	0x00000000
// Several questions:
// 1. What are the purpose of 19 and 20fd1?
// 2. Why the free only clears the first word of buf?
