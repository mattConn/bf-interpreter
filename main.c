/*
Matt's Brain**** Interpreter

Usage:
------
./bf bfCode.b optionalInput

Info:
-----
Mem: 30k 8bit char cells with wraparound.
Input files: EOF == -1 and is stored.

*/

#include <stdio.h>

#define M_SIZE 30000

FILE *fp, *ip; // bf file, input file
char c; // fgetc


int main(int argc, char *argv[])
{
	if (argc < 2) // missing bf file
	{
		fprintf(stderr,"Specify .b file and optional input file.\n");
		return 1;
	}
	fp=fopen(argv[1],"r");
	if (!fp)
	{
		fprintf(stderr,"Could not open file '%s'.\n",argv[1]);
		return 1;
	}

	if(argc == 3) // input file
	{
		ip=fopen(argv[2],"r");
		if (!ip)
		{
			fprintf(stderr,"Could not open input file '%s'.\n",argv[2]);
			return 1;
		}
	}
	else ip = NULL; // no input

	int counter; // brace counter for jumps

	char mem[M_SIZE]; // 30k memory cells
	for(int i=0;i<M_SIZE;i++)mem[i]=0; 

	unsigned int ptr = 0; // mem ptr

	// parse file
	do {
		c = fgetc(fp);
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

			case ',': // input, does not handle EOF
				if(!ip){fprintf(stderr,"Missing input file.\n"); return 1;}

				mem[ptr] = fgetc(ip);
			break;

			case '[': // jump when zero after closing ]
				if(mem[ptr] != 0) break; 

				counter = 1;
				while(counter != 0) // find closing bracket
				{
					c = fgetc(fp);
					if(feof(fp)) {fprintf(stderr, "Missing ']'.\n"); return 1;}

					if(c == '[') counter++;
					if(c == ']') counter--;
				}
			break;

			case ']': // jump when nonzero to opening [
				if(mem[ptr] == 0) break; 

				counter = 1;
				while(counter != 0)
				{
					if(fseek(fp, -2, SEEK_CUR) != 0) {fprintf(stderr, "Missing '['.\n"); return 1;}

					c = fgetc(fp);

					if(feof(fp)) return 1;

					if(c == '['){ counter--;}
					if(c == ']'){ counter++;}
				}
			break;

		}
	} while(1);

	printf("\n");
	fclose(fp);
	if(ip)fclose(ip);
	
	return 0;
}
