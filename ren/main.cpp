// filename main.cpp
// description: Change all the files with extention ".stp" in specific directory "geo_dir" by adding the number increasely after the original file name.
// eg: before: abc.stp, abd.stp, abe.txt; after: abc-01.stp, abd-02.stp, abe.txt
// c++17


#include <limits.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;
using namespace std;

const string EXT_STP(".stp");
const int EXT_LEN = EXT_STP.length();


class Findupdate{
private:
    string pName;   // path name
    string fullPName; // ful path name
    int cnt; // the counter used for changing the 

    bool checkLen(int fnameLen, int pathLen);
    bool checkFile(string fname);

public:
    Findupdate() = delete;
    Findupdate(const string t);
    int getCnt (){return cnt;}
    int doChange();

};

Findupdate::Findupdate(const string t){
    pName = t;
    cnt = 0;
    fullPName = "";

    try {
        // Get the absolute path
        fs::path full_path = fs::absolute(pName);
        fullPName = full_path.generic_string();
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        
    } 
    // finally

}

bool Findupdate::checkLen(int fnameLen, int pathLen){

    // if filename changes, the constrains as  below must be mached.
    // len(fname) <= NAME_MAX AND
    // len(path) + len(fname) <= PATH_MAX
    if ((fnameLen <= NAME_MAX)
        && ((fnameLen + pathLen) <= PATH_MAX))
        return true;
    return false;
}

bool Findupdate::checkFile(string fname) {

    // if has specific extion
    if (EXT_STP.compare(fname.substr(fname.length() - EXT_LEN)))
        return false;

    // if new filename length exceeds system limit
    if (!checkLen(fname.length() + to_string(cnt).length(), pName.length())) {
        cout << "Full filename len limit exceeded error!" << endl;
        return false;
    }

    return true;
}

int Findupdate::doChange(){

    // iterate the files and check if need changes then do the change
    for (auto const& dir_entry : std::filesystem::directory_iterator{pName}) {
        string fName = dir_entry.path().generic_string();
        if (checkFile(fName)) {
            // do the change
            string result = to_string(cnt);
            int digtalSWidth = 2;
            while (result.length() < digtalSWidth) {
                result.insert(0, digtalSWidth - result.length(), '0');
            }

            string newFName = fName.substr(0, fName.length() - EXT_LEN) + "-" + result + EXT_STP;
            // print result
            fs:rename(fName.c_str(), newFName.c_str());
            std::cout << newFName << " - " << ++ cnt  << endl;
        }
    }
    return 0;
}


int main(int argc, char* argv []){

    int cnt = 0;
    int abs_path_len = 0;
    string pName;
    
    // read the parameters
    if (2 != argc) {
        cout << "Please input correct CLI with proper parameters." << endl;
        exit(0);
    }

    pName = argv[1];

    //cout << "pName: " << pName <<endl;
    // remove last slack if there is.    

    if(pName.back() == '/'){
        pName.pop_back();
    }
    //cout << "pName: " << pName <<endl;

    Findupdate fu(pName);
    fu.doChange();

    // summary
    cout << "There was(were) " << fu.getCnt() << " file(s) changed." <<endl;
    return 0;
}
