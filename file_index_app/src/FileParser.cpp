#include<boost/algorithm/string.hpp>
#include "FileParser.hpp"
#include<fstream>
#include<boost/thread/thread.hpp>
#include<boost/thread/mutex.hpp>
#include<boost/bind.hpp>
#include<algorithm>
#include<map>

using namespace std;

template<typename A, typename B>
using MapIterator =  typename std::map<A,B>::const_iterator;

template<typename A, typename B>
std::multimap<B,A> flip_map(std::map<A,B>& src) {

	std::multimap<B,A> dst;
	for(MapIterator<A,B> it = src.begin(); it!= src.end(); ++it)
		dst.insert(std::pair<B,A>(it->second, it->first));

	return dst;

}


FileParser::FileParser() : mThreadsNum(1), mThreadsRef(0) {
}

FileParser::~FileParser() {
}

int FileParser::incThreadsRefCount() {
	boost::mutex::scoped_lock lock(mThreadsRefMutex);
	if (mThreadsRef < mThreadsNum) {
		mThreadsRef++;
		return mThreadsRef;
	} else
		return 0;
}

int FileParser::decThreadsRefCount() {
	boost::mutex::scoped_lock lock(mThreadsRefMutex);
	if (mThreadsRef) {
		mThreadsRef--;
		return mThreadsRef;
	} else
		return 0;
}

void FileParser::countWords(const std::list<fs::path>& paths) {
	//cout<<"Paths in given directory: "<<endl;
	for (auto& path : paths) {
		addPathFiles(path);
	}
	//cout<<"count : X"<<endl;
}

void FileParser::getWordsCounts(std::map<std::string, int>& output) {
	if (output.empty() != 0)
		output.clear();

	WaitForCompletion(); //mFileParserThreads.join_all();
	boost::mutex::scoped_lock lock(mFileParserMutex);
	for (auto& item : mParserResults)
		output[item.first] += item.second;
}

void FileParser::WaitForCompletion() {
	mFileParserThreads.join_all();
}

void FileParser::parse(const boost::filesystem::path& path, bool enableThreads) {
	std::ifstream word_file;
        std::locale locality("C");

	//cout<<"parse :E "<<'\t';
	//cout<<path.string().c_str()<<endl;
	word_file.open(path.string().c_str());
	if (word_file)
	{
		std::map<std::string, int> file_wc;
		std::string line;
                //cout<<word_file<<endl;
		while (std::getline(word_file, line))
		{
			boost::algorithm::to_lower(line);
			auto end=line.end();
			auto itr=line.begin();
			auto word_start=line.end();
			while (itr != end)
			{
				if (*itr < 0 || (!std::isalnum(*itr, locality) && *itr != '_'))
				{
					if (word_start != end) {
						++file_wc[std::string(word_start, itr)];
					}
					word_start = end;
				} else if (word_start == end) {
					word_start = itr;
				}
				++itr;
			}
			if (word_start != end)
			{
				++file_wc[std::string(word_start, itr)];
			}
		}
		word_file.close();
		boost::mutex::scoped_lock lock(mFileParserMutex);
                for (auto& itr_wc : file_wc)
                     mParserResults[itr_wc.first] += itr_wc.second;
	}
	else
	{
		std::cerr << "Failed to read: " << path.string()  << std::endl;
	}
        if (enableThreads)
            decThreadsRefCount();
	//cout<<"parse :X"<<endl;
}

void FileParser::addPathFiles(const boost::filesystem::path& path) {
        if (incThreadsRefCount()) {
		mFileParserThreads.create_thread(boost::bind(&FileParser::parse, this, path, true));
	} else {
           parse(path, false);
        }
}

void FileParser::startFileParsing(std::list<fs::path> paths, int thread_num) {
	mThreadsNum = thread_num;
	if(paths.empty()) {
		cout<<"paths list is empty"<<endl;
		return;
	}

	countWords(paths);
	getWordsCounts(mOutput);

	std::multimap<int, std::string> mapbyvalue = flip_map(mOutput);
	int words_num = 10;
	std::multimap<int, std::string>::const_reverse_iterator item = mapbyvalue.rbegin();
	cout<<"File Indexer results: " <<endl;
	while((item != mapbyvalue.rend()) && words_num--)
	{
		cout<<item->second<<"\t";
                cout<<std::dec<<item->first<<endl;
		++item;
	}
}
