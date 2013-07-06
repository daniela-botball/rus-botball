// Main function for running when using OpenCV.
// It calls the "main2" function to run the C code.

#include <iostream>

using namespace std;

extern int main2();

int main(int argc, char *argv[]) {
	int status;

	cout << "Starting the program from C++!" << endl;

	status = main2();
	
	return status;
}
