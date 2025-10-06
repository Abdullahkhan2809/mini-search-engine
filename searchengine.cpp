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
using namespace std;


// spliting the string into words 

vector <string> tokenize(const string & text){
    stringstream ss(text);
    string word;

    vector<string> token;

    // lowercasing and removing punctuation of the text 

    while(ss>>word){
        for (auto & c : word){
            c=tolower(c);
            if(ispunct(word.back())){
                word.pop_back();

            }
            token.push_back(word);
            
        }
    }
    return token;
}

int main(){

return 0;
}