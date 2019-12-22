#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <map>
#include <vector>
#include <chrono>
#include <algorithm>

#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>


using namespace std;

size_t fun1(const string & data) {
    size_t out = 0;
    char *input = strdup(data.data());
    char *token = std::strtok(input, " ");

    while(token != nullptr) {
        ++out;
        token = std::strtok(nullptr, " ");
    }

    free(input);
    return out;
}

//------------WIN-------------------
size_t fun2(const string & data) {
    size_t out = 0;

    auto lastPos = data.find_first_not_of(' ', 0);
    auto pos = data.find_first_of(' ', lastPos);

    while(lastPos != string::npos || pos != string::npos) {
        ++out;
        //lastPos, pos - lastPos
        lastPos = data.find_first_not_of(' ', pos);
        pos = data.find_first_of(' ', lastPos);
    }

    return out;
}


size_t fun3(const string & data) {
    boost::tokenizer<> tok(data);
    return distance(tok.begin(), tok.end());
}


size_t fun4(const string & data) {
    istringstream iss(data);
    size_t out = 0;
    string buff;

    while(iss >> buff) {//getline?
        ++out;
    }

    return out;
}


size_t fun5(const string & data) {
    istringstream iss(data);
    size_t out = 0;
    string buff;

    while(std::getline(iss, buff, ' ')) {
        if(! buff.empty()) {//test2 fail without
            ++out;
        }
    }

    return out;
}


size_t fun6(const string & data) {
    size_t out = 0;
    vector<string> outStrs;

    split(outStrs, data, boost::is_space(), boost::token_compress_off);

    for(const auto & el: outStrs) {
        if(! el.empty()) {//token_compress_on - failed with double space
            ++out;
        }
    }

    return out;
}


size_t fun7(const string & data) {
    string delims(" ");

    typedef boost::tokenizer<boost::char_separator<char>> splitup;
    boost::char_separator<char> sep(delims.c_str());

    splitup tokens(data, sep);
    return distance(tokens.begin(), tokens.end());
}


size_t funTest(const string & data) {
    typedef vector< boost::iterator_range<string::const_iterator> > find_vector_type;

    size_t out = 0;

    find_vector_type FindVec; // #1: Search for separators
    boost::ifind_all( FindVec, data, " " ); // FindVec == { [abc],[ABC],[aBc] }

    //    boost::split(FindVec, data, " ");

    cout << "DUpa size:" << FindVec.size() << endl;

    for(size_t i = 0; i < FindVec.size(); ++i) {
        //    for(FindVec::const_iterator it = FindVec.cbegin(); it != FindVec.cend(); ++it) {

        if(FindVec[i].begin() != FindVec[i].end()) {
            cout << "Licz dist:" << distance(FindVec[i].begin(), FindVec[i].end()) << endl;
        }
        cout << "front:" << *(FindVec[i].begin()) << endl;//iter_range
    }

    return out;
}


template<typename T, typename Callable>
bool verify(const T & mapIterator, Callable callable) {
    return mapIterator.first == callable(mapIterator.second);
}

//-----------CORECTNES-----------------------------
void verifyTests() {
    std::multimap<size_t, string> testMap;
    string test1("testowy pierwszy string");
    string test2(" testowy pierwszy string ");
    string test3("  testowy  pierwszy  string  ");


    testMap.insert(make_pair(3, test1));
    testMap.insert(make_pair(3, test2));
    testMap.insert(make_pair(3, test3));


    for(auto it = testMap.cbegin(); it != testMap.cend(); ++it) {
        cout << "verify f1:" << verify(*it, fun1) << " for[" << it->second << "]" << endl;
        cout << "verify f2:" << verify(*it, fun2) << " for[" << it->second << "]" << endl;
        cout << "verify f3:" << verify(*it, fun3) << " for[" << it->second << "]" << endl;
        cout << "verify f4:" << verify(*it, fun4) << " for[" << it->second << "]" << endl;
        cout << "verify f5:" << verify(*it, fun5) << " for[" << it->second << "]" << endl;
        cout << "verify f6:" << verify(*it, fun6) << " for[" << it->second << "]" << endl;
        cout << "verify f7:" << verify(*it, fun7) << " for[" << it->second << "]" << endl;
    }
}


vector<string> generateString() {
    size_t number = 1000000;

    string test1("testowy pierwszy string");
    string test2(" testowy pierwszy string ");
    string test3("  testowy  pierwszy  string  ");

    vector<string> out(number);

    for(size_t i = 0; i < number; ++i) {
        out[i] = test1;
    }

    return out;
}

typedef pair<string, double> ReportPair_T;


template<typename T, typename Callable>
ReportPair_T speedFun(T strings, Callable callable, string functionName) {
    //startTimer
    const auto start = chrono::high_resolution_clock::now();
    for(const auto & el: strings) {
        callable(el);
    }
    //endTimer
    const auto end = chrono::high_resolution_clock::now();
    auto diff = end - start;

    return make_pair(functionName, chrono::duration<double, nano>(diff).count());
}

//---------------SPEED--------------------------------------
void speedTests() {
    const vector<string> & testStrings = generateString();
    vector<ReportPair_T> outVector;

    outVector.push_back( speedFun(testStrings, fun1, "funkcja 1") );
    outVector.push_back( speedFun(testStrings, fun2, "funkcja 2") );
    outVector.push_back( speedFun(testStrings, fun3, "funkcja 3") );
    outVector.push_back( speedFun(testStrings, fun4, "funkcja 4") );
    outVector.push_back( speedFun(testStrings, fun5, "funkcja 5") );
    outVector.push_back( speedFun(testStrings, fun6, "funkcja 6") );
    outVector.push_back( speedFun(testStrings, fun7, "funkcja 7") );

    std::sort(outVector.begin(), outVector.end(),
              [](const ReportPair_T & l, const ReportPair_T & r)->bool {

                  return l.second < r.second;
              });

    cout << fixed << "RAPORT---begin\n";
    for(const auto & el: outVector) {
        cout << el.first << " time[ns]:" << el.second << endl;
    }
    cout << "RAPORT---end\n";
}


int main() {
    verifyTests();
    speedTests();

    return 0;
}
