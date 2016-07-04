// We want to see if AddressSanitizer can detect the overflow.


#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


void printHost(char* str){

		// More information of this struct can be found at:
		// http://www.gnu.org/software/libc/manual/html_node/Host-Names.html
		struct hostent *lh = gethostbyname(str);
		struct in_addr **addr_list;
		int i;

    if (lh){
        // http://www.tutorialspoint.com/c_standard_library/c_function_puts.htm
        puts(lh->h_name);
        
        
        // The host could have multiple addresses
        addr_list = (struct in_addr **)lh->h_addr_list;

    		for(i = 0; addr_list[i] != NULL; i++) {
    		  // http://linux.die.net/man/3/inet_ntoa
        	printf("%s \n", inet_ntoa(*addr_list[i]));
       	}
    }else
        herror("gethostbyname");

}

int main(void) {

		int i = 0;

		for(i = 1001; i <= 1024; i++){

			printf("i=%d\n", i);

			size_t len = i - 16*sizeof(unsigned char) - 2*sizeof(char *) - 1;
			printf("len=%d\n", len);
  		char name[i];
  		memset(name, '0', len);
  		name[len] = '\0';
  		
  		printHost(name);
  		
		}
	
		
}
