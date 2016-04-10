
CC=gcc

all: call_shellcode exploit

call_shellcode:
	$(CC) -z execstack -fno-stack-protector call_shellcode.c -o call_shellcode

exploit:
	$(CC) exploit.c -o exploit
