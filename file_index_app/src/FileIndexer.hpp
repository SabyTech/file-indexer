#ifndef _FILEINDEXER_H
#define _FILEINDEXER_H

#include "FileSource.hpp"
#include "FileParser.hpp"
#include<map>
#include<string>
#include<list>
#include<boost/filesystem.hpp>

namespace fs = boost::filesystem;
using namespace std;

class FileSource;

class FileIndexer
{
    public:
	FileIndexer();
	bool setFilePath(const std::string& path);
        void getFileList(std::list<fs::path>& paths);
	virtual ~FileIndexer();

    private:
	fs::path mPath;
        std::string mExtn;
        FileSource *mFileSource;
};
#endif
