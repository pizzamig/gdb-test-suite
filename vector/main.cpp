#include <vector>
#include <iostream>

struct S {};

int main() {
	std::vector<S*> vv;
	vv.push_back(0);
	std::cout << "program is ending and vector size is : " << vv.size() << std::endl;
}

