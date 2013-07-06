// Main function for running when using OpenCV.
// It calls the "main2" function to run the C code.

#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
	cout << "Starting the program from C++!" << endl;
	main2();
	
	return 0;
}
