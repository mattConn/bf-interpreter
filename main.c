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
	int pos;

	char mem[M_SIZE]; // 30k memory cells
	unsigned int ptr = 0;
	for(int i=0;i<M_SIZE;i++)mem[i]=0;

	// parse file
	do {
		c = fgetc(fp);
		if(feof(fp)) break;

		switch(c)
		{
			case '>':
				ptr = ++ptr == M_SIZE ? 0 : ptr; // wraparound
				printf("PTR:%d\n",ptr);
			break;

			case '<':
				ptr = --ptr == -1 ? M_SIZE-1 : ptr; // wraparound
				printf("PTR: %d\n",ptr);
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
				pos = ftell(fp);
				if(!mem[ptr])
				{
					do {
						c = fgetc(fp);
						if(feof(fp)) break;
					}
					while (c != ']');
				}
			break;

			case ']':
			break;

		}
	} while(1);

	printf("\n");
	fclose(fp);
	
	return 0;
}