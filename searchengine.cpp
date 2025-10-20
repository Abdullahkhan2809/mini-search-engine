#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<algorithm>
#include<vector>
#include<cmath>
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

map<int , double> queryEngine(string query){
    vector<string> qToken= tokenize(query);
    map<int, double> scores;

    for(string term: qToken){
        if(invertedIndex.find(term)==invertedIndex.end()){
            continue;
        }
        int df= invertedIndex[term].size(); //number of docs containing searched terms
        double idf=log((double)totaldoc/(df+1));//inverse of doc frequency

        for(auto[docID,freq] : invertedIndex[term]){
            double tf= (double)freq/docLength[docID];
            double tfidf=tf*idf;
            scores[docID]+=tfidf;
        }
    }

    return scores;

}

//display of result

void displayResult(map<int, double> scores){
    vector<pair<int,double>> result(scores.begin(), scores.end());

    for(int i=0; i<result.size(); i++){
        auto key=result[i];
        int j=i-1;

        while(j>=0 && result[j].second<key.second){
            result[j+1]=result[j];
            j--;
        }
        result[j+1]=key;

    }
    if(result.empty()){
        cout<<"No file found. "<<endl;
        return;
    }
    cout<<"Search Result: ";
    for(auto & p: result){
        cout<<"Doc "<<p.first<<" Score: "<<p.second<<endl;
    }
}




int main(){
    string folderPath;
    buildIndexes(folderPath);

    while(true){
        string query;
        cout<<"Enter search query : ";
        getline(cin,folderPath);
        if(query=="exit")break;

        map<int,double> scores=queryEngine(query);
        displayResult(scores);
    }


return 0;
}