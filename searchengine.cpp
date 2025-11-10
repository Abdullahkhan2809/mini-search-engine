#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <vector>
#include <cmath>
#include <filesystem>
using namespace std;
namespace fs = filesystem;

map<string, map<int, int>> invertedIndex;
map<int, int> docLength;
map<int, string> docNames;
int totaldoc = 0;

// Tokenize text
vector<string> tokenize(string text) {
    stringstream ss(text);
    string word, clean;
    vector<string> tokens;

    while (ss >> word) {
        clean = "";
        for (auto &c : word) {
            c = tolower(c);
            if (isalpha(c))
                clean += c;
        }
        if (!clean.empty())
            tokens.push_back(clean);
    }
    return tokens;
}

// Build index from folder
void buildIndexes(string folderpath) {
    int docID = 0;

    for (auto &entry : fs::directory_iterator(folderpath)) {
        if (entry.is_regular_file()) {
            docID++;
            totaldoc++;

            string filename = entry.path().filename().string();
            docNames[docID] = filename;

            ifstream file(entry.path());
            if (!file.is_open()) {
                cerr << "Error: cannot open " << entry.path() << endl;
                continue;
            }

            stringstream buffer;
            buffer << file.rdbuf();
            string content = buffer.str();

            content += " " + filename;

            vector<string> tokens = tokenize(content);
            docLength[docID] = tokens.size();
            

            for (string term : tokens)
                invertedIndex[term][docID]++;

            file.close();
        }
    }

    cout << "\nIndex built successfully! " << totaldoc << " documents processed.\n";
}

// TF-IDF scoring
map<int, double> queryEngine(string query) {
    vector<string> qTokens = tokenize(query);
    map<int, double> scores;

    for (string term : qTokens) {
        if (invertedIndex.find(term) == invertedIndex.end())
            continue;

        int df = invertedIndex[term].size();
        double idf = log((double)totaldoc / (df + 1));

        for (auto [docID, freq] : invertedIndex[term]) {
            double tf = (double)freq / docLength[docID];
            double tfidf = tf * idf;
            scores[docID] += tfidf;
        }
    }

    return scores;
}

// Display results
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
                cout<<"No file found. "<<endl; return;
             } 
            cout<<"Search Result: "; 
            for(auto & p: result){ 
                cout<<"Doc "<<p.first<<" Score: "<<p.second<<endl;
             }
         }

int main() {
    string folderPath;
    cout << "Enter folder path : ";
    getline(cin, folderPath);

    buildIndexes(folderPath);

    while (true) {
        string query;
        cout << "\nEnter search query : ";
        getline(cin, query);

        if (query == "exit")
            break;

        map<int, double> scores = queryEngine(query);
        displayResult(scores);
    }

return 0;
}
