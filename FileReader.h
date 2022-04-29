#ifndef FILEREADER_H
#define FILEREADER_H
#include <string>
#include <vector>
#include "Variables.h"

using namespace std;
 
class FileReader {
	
	private:
		std::vector<Variables> dataFile;
	
	public:
		FileReader(){};
		vector<Variables> read_file();
};
#endif

