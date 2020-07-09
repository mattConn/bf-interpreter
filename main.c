#include <stdio.h>

#define M_SIZE 30000

FILE *fp;
char c;

int findCharFwd(char cur, char target)
{
	do {
		c = fgetc(fp);

		if(feof(fp)) return -1;

		if(c == cur) findCharFwd(cur,target);
	} while (c != target);
}

int findCharBwd(char cur, char target)
{
	do {
		ungetc(c, fp);

		if(feof(fp)) return -1;

		if(c == cur) findCharBwd(cur,target);
	} while (c != target);
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr,"File not specified.\n");
		return 1;
	}

	fp=fopen(argv[1],"r");

	if (!fp)
	{
		fprintf(stderr,"Could not open file '%s'.\n",argv[1]);
		return 1;
	}
	int pos;
	int counter;

	char mem[M_SIZE]; // 30k memory cells
	unsigned int ptr = 0;
	for(int i=0;i<M_SIZE;i++)mem[i]=0;

	// parse file
	do {
		c = fgetc(fp);
		//printf("%c:%d, ",c,ftell(fp));
		if(feof(fp)) break;

		switch(c)
		{
			case '>': // inc mem ptr 
				ptr = (++ptr)%M_SIZE; // wraparound
			break;

			case '<': // dec mem ptr
				ptr = --ptr == -1 ? M_SIZE-1 : ptr;
			break;

			case '+':
				mem[ptr]++;
			break;

			case '-':
				mem[ptr]--;
			break;

			case '.': // output
				printf("%c",mem[ptr]);
			break;

			case ',': // input
			break;

			case '[': // jz to closing ]
				if(mem[ptr] != 0) break; 

				counter = 1;
				while(counter != 0)
				{
					c = fgetc(fp);
					if(feof(fp)) {fprintf(stderr, "Missing ']'.\n"); return 1;}

					if(c == '[') counter++;
					if(c == ']') counter--;
				}
			break;

			case ']': // jnz to opening [
				if(mem[ptr] == 0) break; 

				counter = 1;
				while(counter != 0)
				{
					if(fseek(fp, -2, SEEK_CUR) != 0) {fprintf(stderr, "Missing '['.\n"); return 1;}

					c = getc(fp);

					if(feof(fp)) return 1;

					if(c == '['){ counter--;}
					if(c == ']'){ counter++;}
				}
			break;

		}
	} while(1);

	printf("\n");
	fclose(fp);
	
	return 0;
}
