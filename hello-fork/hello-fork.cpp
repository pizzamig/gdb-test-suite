#include <iostream>
#include <unistd.h>
//#include <stdlib.h>

using namespace std;

int main()
{
	pid_t pid;
	pid = fork();
	if ( pid == 0 ) {
		cout << "Hello world, I'm the child" << endl;
//		exit(0);
	} else {
		cout << "Hello world!" << endl;
	}
	return 0;
}
