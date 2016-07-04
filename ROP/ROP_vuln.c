// From: http://resources.infosecinstitute.com/an-introduction-to-returned-oriented-programming-linux/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
//#include

void fill(int,int,int*);

int main(int argc,char** argv)
{
	FILE* fd;
	int in1,in2;
	int arr[2048];
	char var[20];
	
	if (argc !=2){
		printf("usage : %s ",*argv);
		exit(-1);
	}

	fd = fopen(argv[1],"r");
	if(fd == NULL)
	{
		fprintf(stderr, "%s\n",strerror(errno));
		exit(-2);
	}

	memset(var,0,sizeof(var));
	memset(arr,0,2048*sizeof(int));

	while(fgets(var,20,fd))
	{
		in1 = atoll(var);
		fgets(var,20,fd);
		in2 = atoll(var);
		/* fill array */
		fill(in1,in2,arr);
	}
}

void fill(int of,int val,int *tab)
{
	tab[of]=val;
}
