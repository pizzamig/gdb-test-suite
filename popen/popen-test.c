#include <stdio.h>

int main()
{
	FILE * output;
	output=popen("cat","w");
	fprintf( output, "mannaiacane\n");
	return 0;
}

