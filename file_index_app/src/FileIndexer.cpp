#include<iostream>
#include "FileIndexer.hpp"
#include "FileSource.hpp"
#include "FileParser.hpp"

using namespace std;

FileIndexer::FileIndexer()
    :mPath("."),
    mExtn(".txt") { 

}

FileIndexer::~FileIndexer() {

}

bool FileIndexer::setFilePath(const std::string& path) {
    bool ret = false;
    if(path.empty()) {
	cout<< "empty path\n";
	return false;
    }
    mPath = path;
    ret = mFileSource->setFileSource(mPath);

    return ret;
}

void FileIndexer::getFileList(std::list<fs::path>& paths) {
    /* by default search extension is .txt, initialized by ctor. setter getter can be implemented for application input and output */
    mFileSource->search(mPath, paths, mExtn);
}

