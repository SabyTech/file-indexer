#ifndef _FILE_SOURCE_H
#define _FILE_SOURCE_H

#include<iostream>
#include<boost/filesystem.hpp>
#include<string>

namespace fs = boost::filesystem;
using namespace std;

class FileSource {
    public:
	FileSource();
	bool setFileSource(fs::path dir);
        void search(fs::path dir, std::list<fs::path>& path, std::string extn);
        void findFiles(fs::path dir, std::list<fs::path>& path, std::string extn);
	virtual ~FileSource();

    private:
	FileSource(const FileSource&){}
	FileSource &operator=(const FileSource &);
};
#endif //FILE_SOURCE_H_
