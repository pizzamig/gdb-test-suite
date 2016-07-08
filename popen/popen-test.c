#include <stdio.h>

int main()
{
	FILE * output;
	output=popen("cat","w");
	fprintf( output, "Hello pipe! How are you doing, pipe mate?\n");
	return 0;
}

