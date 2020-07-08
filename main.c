#include <stdio.h>

#define M_SIZE 30000

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr,"File not specified.\n");
		return 1;
	}

	FILE *fp=fopen(argv[1],"r");

	if (!fp)
	{
		fprintf(stderr,"Could not open file '%s'.\n",argv[1]);
		return 1;
	}
	char c;

	char mem[M_SIZE]; // 30k memory cells
	int ptr = 0;
	for(int i=0;i<M_SIZE;i++)mem[i]=0;

	// parse file
	do {
		c = fgetc(fp);
		if(feof(fp)) break;

		switch(c)
		{
			case '>':
				ptr++;
			break;

			case '<':
				ptr--;
			break;

			case '+':
				mem[ptr]++;
			break;

			case '-':
				mem[ptr]--;
			break;

			case '.':
				printf("%c",mem[ptr]);
			break;

			case ',':
			break;

			case '[':
			break;

			case ']':
			break;

		}
	} while(1);

	printf("\n");
	fclose(fp);
	
	return 0;
}
