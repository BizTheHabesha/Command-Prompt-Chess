#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <thread>
#include <fstream>

using namespace std;
vector <string> stringToWords(string input){
    std::vector <std::string> vecWords;
    std::stringstream ss(input);
    std::string sIndivStr;
    char cSpace = ' ';
    while(getline(ss, sIndivStr, cSpace)){
        vecWords.push_back(sIndivStr);
    }
    return vecWords;

}
int trySTOI(string sInput){
    int iInput = -1;
    try{
        iInput = stoi(sInput);
        return iInput;
    }catch(const invalid_argument& ia){
        cerr << "Error: -Invalid Argument: -" << ia.what() << endl;
        return -1;
    }catch(const out_of_range& oor){
        cerr << "Error: -Out of Range: -" << oor.what() << endl;
        return -1;
    }catch(exception& ex){ 
        cerr << "Error: -Undefined-Throw: -" << ex.what() << endl;
        cout << "Sorry, something unexpected happend! Please submit a screenshot to github.\n";
        return -1;
    }catch(...){
        cerr << "Error: -Unexpected-Throw: -catch_all\n";
        cout << "Sorry, something unexpected happend! Please submit a screenshot to github.\n";
        abort();
    }
    return -1;
}
bool ableSTOI(string sInput){
    bool tf = false;
    try{
        stoi(sInput);
        return true;
    }catch(const invalid_argument& ia){
        cerr << "Error: --Invalid Argument: --" << ia.what() << endl;
        return false;
    }catch(const out_of_range& oor){
        cerr << "Error: --Out of Range: --" << oor.what() << endl;
        return false;
    }catch(exception& ex){ 
        cerr << "Error: --Undefined-Throw: --" << ex.what() << endl;
        cout << "Sorry, something unexpected happend! Please submit a screenshot to github.\n";
        return false;
    }catch(...){
        cerr << "Error: --Unexpected-Throw --catch_all abort()\n";
        cout << "Sorry, something unexpected happend! Please submit a screenshot to github.\n";
        abort();
    }
    return tf;
}
bool ableFSTREAM(string location){
    fstream file;
    file.open(location);
    try{
        if(file.is_open()){
            file.close();
            return true;
        }else if(!file.is_open()){
            throw runtime_error(string("fstream: failed to open \"")+=location+=string("\""));
        }else{
            cerr << "something unexcepected happened" << endl;
        }
        file.close();
    }catch(runtime_error& fto){
        cerr << "Error: --" << fto.what() << endl;
        return false;
    }catch(exception& ex){
        cerr << "Error: Undefined Throw: --" << ex.what() << endl;
        return false;
    }catch(...){
        cerr << "Error: Unexpected Throw catch_all abort()\n";
        abort();
    }
    file.close();
    return false;
};