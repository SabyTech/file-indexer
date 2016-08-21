#ifndef _FILEPARSER_H
#define _FILEPARSER_H

#include<map>
#include<list>
#include<string>
#include<boost/thread/thread.hpp>
#include<boost/thread/mutex.hpp>
#include<boost/filesystem.hpp>
#include "FileIndexer.hpp"

namespace fs = boost::filesystem;
using namespace std;

class FileIndexer;
class FileParser
{
public:
FileParser();
void getWordsCounts(std::map<std::string, int>& output);
void countWords(const std::list<fs::path>& paths);
void startFileParsing(std::list<fs::path> paths, int thread_num);
int incThreadsRefCount();
int decThreadsRefCount();
virtual ~FileParser();

private:
FileParser(const FileParser&) { }
FileParser &operator=(const FileParser&);

void addPathFiles(const boost::filesystem::path& path);
void parse(const boost::filesystem::path& path, bool enableThreads);
void WaitForCompletion();


int mThreadsNum;
int mThreadsRef;
std::map<std::string, int> mOutput;
std::map<std::string, int> mParserResults;
boost::mutex mFileParserMutex;
boost::mutex mThreadsRefMutex;
boost::thread_group mFileParserThreads;
};
#endif
