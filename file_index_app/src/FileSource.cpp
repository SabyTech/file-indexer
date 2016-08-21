#include<iostream>
#include "FileSource.hpp"
#include<boost/thread.hpp>

using namespace std;

FileSource::FileSource() {
}

FileSource::~FileSource() {
}

bool FileSource::setFileSource(fs::path dir) {
    bool ret = false;
    cout<<"Search Directory: "<<dir<<endl;
    if (fs::exists(dir) && fs::is_directory(dir))
	ret = true;
    else
	ret = false;
    return ret;
}

void FileSource::findFiles(fs::path dir, std::list<fs::path>& paths, std::string extn) {
    std::list<std::list<fs::path>> branch_paths;
    if (fs::exists(dir) && fs::is_directory(dir)) {
        boost::thread_group threads;
	fs::directory_iterator end_itr;
	for(fs::directory_iterator itr(dir); itr != end_itr; ++itr) {
	    if (fs::is_regular_file(itr->status())) {
		if (itr->path().extension() == extn) {
                    //cout<<itr->path()<<endl;
		    paths.push_back(itr->path());
                }
	    } else if (fs::is_directory(itr->status())) {
		std::list<fs::path> leaf;
		branch_paths.push_back(leaf);
		threads.create_thread(boost::bind(&FileSource::findFiles, this, itr->path(), boost::ref(branch_paths.back()), extn));
	    }
	}
        threads.join_all();

        if (branch_paths.size())
         {
           for(auto& path : branch_paths)
               paths.merge(path);
         }
    }
}

void FileSource::search(fs::path dir, std::list<fs::path>& paths, std::string extn) {
	findFiles(dir, paths, extn);
    /*cout<<"****test the path*****"<<endl;
    std::list<fs::path>::iterator itr;
    for(itr = paths.begin(); itr!=paths.end(); ++itr)
        cout<<*itr<<endl;
    cout<<"**********************"<<endl; */
}
