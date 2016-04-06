# Run this script in root

gcc -z execstack -fno-stack-protector stack.c -o stack

# setuid
chmod 4755 stack
