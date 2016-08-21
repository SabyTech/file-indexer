#include<iostream>
#include<stdlib.h>
#include<string>
#include "FileIndexer.hpp"
#include "FileParser.hpp"
#include<boost/filesystem.hpp>

namespace fs = boost::filesystem;
using namespace std;

int main (int argc, char* argv[]) {
    int numThreads = 0;
    std::string path = ".";
    char *paramKey = NULL;
    int paramValue = 1;
    FileIndexer fi;
    FileParser fp;

    if(argc == 2) {
	path = argv[1];
    } else if(argc == 4) {
	paramKey = argv[1];
	paramValue = atoi(argv[2]);
	if (strcmp(paramKey, "-t")) {
            paramValue = 1;
	    cout<<"please use -t as argument for setting number of threads, default is 1"<<endl;
	} else if (paramValue > 10) {
            paramValue = 10;
	    cout<<"The number of threads can be upto 10 in this app, default is 1"<<endl;
	 } else if(paramValue <= 0) {
            paramValue = 1;
         }
	path = argv[3];
    } else {
	cout<<"suggested command: ./ssfi -t <number_of_threads_upto_10> <Input_File_Path>"<<endl;
    }

    numThreads = paramValue;
    if(!fi.setFilePath(path))
    { 
      cout<< "setting the path failed"<<endl;
      return 0;
    }
    std::list<fs::path> paths;
    fi.getFileList(paths);
    fp.startFileParsing(paths, numThreads);

    return 0;
}
