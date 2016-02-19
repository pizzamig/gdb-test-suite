#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
	int rc;
	rc = system("echo Hello system");
	cout << "system: value return" << rc << endl;
	return 0;
}
