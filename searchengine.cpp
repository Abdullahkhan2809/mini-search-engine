#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<set>
#include<unordered_map>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<cmath>
#include<cctype>
#include<filesystem>
using namespace std;
namespace fs = filesystem;

map<string, map<int,int>> invertedIndex;

map<int, int> docLength;

int totaldoc=0;

// spliting the string into words 

vector <string> tokenize(string text){
    stringstream ss(text);
    string word,clean;

    vector<string> token;

    // lowercasing and removing punctuation of the text 

    while(ss>>word){
        clean="";
        for (auto & c : word){
            c=tolower(c);
           if(isalpha(c)){
            clean+=tolower(c);
           }

           
        }
        if(!clean.empty()) token.push_back(clean);
    }
    return token;
}


//indexing 

void buildIndexes(string folderpath){
    int docID=0;

    for(auto &entry: fs::directory_iterator(folderpath)){
        if(entry.is_regular_file()){
            docID++;
            totaldoc++;
            ifstream file(entry.path());
            if(!file.is_open()){
                cerr<<"Error cannot open! "<<entry.path()<<endl;
                continue;
            }
            stringstream buffer;
            buffer<<file.rdbuf();
            string content=buffer.str();
            vector<string> token= tokenize(content);

            docLength[docID]=token.size();

            for(string term : token){
                invertedIndex[term][docID]++;
            }
            file.close();
        }
        
    }
     cout<<"Index has been build: "<<totaldoc<<" document processed!\n";   
}

//TF-IDF query channel






int main(){

return 0;
}