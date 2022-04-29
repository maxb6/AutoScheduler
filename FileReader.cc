#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>   
#include <utility> 
#include <stdexcept> 
#include <sstream> 
#include "FileReader.h"
#include <iostream>

using namespace std;

vector<Variables> FileReader::read_file() {
	//Dataset being read is put into a vector with the column name and columns value <string, vector<int>> and <column name, column values>
    try
    {
        //Vector created to store the data in the file
        vector<Variables> data;
        //Input filestream for dataset
        ifstream myFile("/public/coen320/dataset.csv", ifstream::in);
        //Making sure the file opens
        if (!myFile.is_open()){
        	 throw runtime_error("File could not be opened");
        }

        string line;

        //If the file opens
        if (myFile.good()){
            //Doesnt count the first line since its the column names
            getline(myFile, line);
            //File loading while being read
            cout <<"\nLoading File ... " <<endl;
        	
            // Read data, line by line
            while (getline(myFile, line)){     	
                Variables vars = Variables();

                // Create a stringstream of the current line
                stringstream ss(line);

                // Keep track of the current column index
                int row = 0;
                string handle;

                // Extract each integer
                while (getline(ss, handle, ',')) {

					const char* token = handle.c_str();
                    switch (row)
                    {
					//Case numbers are the column numbers in the dataset +1
                    case 0:
                        vars.setFuelConsumption(atof(token));
                        break;

                    case 12:
                        vars.setEngineSpeed(atof(token));
                        break;

                    case 17:
                        vars.setEngineCoolantTemp(atof(token));
                        break;

                    case 33:
                        vars.setCurrentGear(atof(token));
                        break;

                    case 43:
                        vars.setVehicleSpeed(atof(token));
                        break;

                    default:
                        break;
                    }

                    //Increment column number
                    row++;
                }
                data.push_back(vars);
            }
            cout <<"Loading Complete. \n" <<endl;
        }
        //File is closed once it was read
        myFile.close();

        return data;
    }
	catch (runtime_error e){
        throw runtime_error("File could not be opened.");
	}
}

