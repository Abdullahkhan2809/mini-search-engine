#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <cmath>
#include <filesystem>
#include <functional> 
#include <memory>

namespace fs = std::filesystem;
using namespace std;

// Simple dynamic array: MyVector
template<typename T>
class MyVector {
public:
    T* data;
    int cap;
    int len;

    void grow() {
        int newcap;
        if(cap==0){
            newcap=4;
        }
        else{
            newcap=cap*2;
        }
        T* newdata = new T[newcap];
        for (size_t i = 0; i < len; ++i){ 
            newdata[i] = data[i];
        }
        delete[] data;
        data = newdata;
        cap = newcap;
    }

    MyVector(): data(nullptr), cap(0), len(0) {}
    ~MyVector() { delete[] data; }

    void push_back(const T& v) {
        if (len >= cap) {
            grow();
        }
        data[len++] = v;
    }

    T& operator[](int i) { return data[i]; }
    const T& operator[](int i) const { return data[i]; }
    int size() const { return len; }
    bool empty() const { return len == 0; }

    // find index by predicate (returns -1 when not found)
    template<typename Pred>
    int find_index(Pred p) const {
        for (int i = 0; i < len; ++i) {
            if (p(data[i])) {
                return (int)i;
        
            }
        }
        return -1;
    }
};


// Posting (docID, freq)

struct Posting {
    int docID;
    int freq;
    Posting(): docID(0), freq(0) {}
    Posting(int d, int f): docID(d), freq(f) {}
};

// PostingList (wraps MyVector<Posting>)

class PostingList {
private:
    MyVector<Posting> postings;   // stores all postings

public:
    PostingList() {}

    void addOrIncrement(int docID) {

        // find if docID already exists
        int idx = -1;

        for (int i = 0; i < postings.len; i++) {
            if (postings.data[i].docID == docID) {
                idx = i;
                break;
            }
        }

        // if not found, add new posting
        if (idx == -1) {
            Posting p(docID, 1);
            postings.push_back(p);
        }

        // if found, increment frequency
        else {
            postings.data[idx].freq = postings.data[idx].freq + 1;
        }
    }

    int size() const {
        return postings.len;
    }

    const MyVector<Posting>& getAll() const {
        return postings;
    }
};



// Simple chained hash map string->pointer (value stored as void* templated T*)
template<typename T>
class HashMapStringToPtr {
private:

    // Simple linked list entry
    struct Entry {
        string key;
        T* value;
        Entry* next;

        Entry(const std::string& k, T* v) {
            key = k;
            value = v;
            next = nullptr;
        }
    };

    Entry** buckets;      // array of pointers
    int bucketCount;      // number of buckets
    std::hash<std::string> hasher;

    // create bucket array
    void makeBuckets(int n) {
        bucketCount = n;
        buckets = new Entry*[bucketCount];
        for (int i = 0; i < bucketCount; i++) {
            buckets[i] = nullptr;
        }
    }

    // delete all entries
    void deleteAll() {
        for (int i = 0; i < bucketCount; i++) {
            Entry* e = buckets[i];
            while (e != nullptr) {
                Entry* nextEntry = e->next;

                delete e->value;  // delete stored value
                delete e;         // delete entry

                e = nextEntry;
            }
        }
        delete[] buckets;
    }

public:

    // constructor
    HashMapStringToPtr(int size = 4099) {
        makeBuckets(size);
    }

    // destructor
    ~HashMapStringToPtr() {
        deleteAll();
    }

    // get existing key or return nullptr
    T* get(const string& key) const {
        int index = hasher(key) % bucketCount;

        Entry* e = buckets[index];

        while (e != nullptr) {
            if (e->key == key) {
                return e->value;
            }
            e = e->next;
        }

        return nullptr; // not found
    }

    // get key OR create new one
    T* getOrCreate(const std::string& key) {
        int index = hasher(key) % bucketCount;

        Entry* e = buckets[index];

        // check if exists
        while (e != nullptr) {
            if (e->key == key) {
                return e->value;
            }
            e = e->next;
        }

        // not found → create
        T* val = new T();          // new value
        Entry* newEntry = new Entry(key, val);

        newEntry->next = buckets[index]; // insert at start
        buckets[index] = newEntry;

        return val;
    }

    // count all keys (slow)
    int keyCount() const {
        int count = 0;

        for (int i = 0; i < bucketCount; i++) {
            Entry* e = buckets[i];
            while (e != nullptr) {
                count++;
                e = e->next;
            }
        }

        return count;
    }

    // simple key iteration (no fancy lambdas)
    void printAllKeys() const {
        for (int i = 0; i < bucketCount; i++) {
            Entry* e = buckets[i];

            while (e != nullptr) {
                cout << e->key << "\n";
                e = e->next;
            }
        }
    }
};


// Tokenizer

class Tokenizer {
public:
    Tokenizer() {}

    MyVector<string> tokenize(const std::string& text) {
        MyVector<string> tokens;

        stringstream ss(text);
        string word;

        // read each raw word
        while (ss >> word) {

            string cleanWord;

            // clean word: keep only letters
            for (int i = 0; i < word.size(); i++) {
                char ch = word[i];

                // convert to lowercase (simple way)
                if (ch >= 'A' && ch <= 'Z') {
                    ch = ch + 32;   // make lowercase
                }

                // keep alphabet only
                if ((ch >= 'a' && ch <= 'z')) {
                    cleanWord.push_back(ch);
                }
            }

            // if we got something valid, add it
            if (cleanWord.size() > 0) {
                tokens.push_back(cleanWord);
            }
        }

        return tokens;
    }
};



// Document container

class Document {
public:
    int id;
    string name;
    int length;

    // default constructor
    Document() {
        id = 0;
        name = "";
        length = 0;
    }

    // parameter constructor
    Document(int i, const string& n, int l) {
        id = i;
        name = n;
        length = l;
    }
};


// InvertedIndex
class InvertedIndex {
private:
    HashMapStringToPtr<PostingList> index;

public:
    InvertedIndex() : index(8192) {}

    // add term → docID mapping
    void addTermOccurrence(const string& term, int docID) {
        PostingList* list = index.getOrCreate(term);
        list->addOrIncrement(docID);
    }

    // get the posting list for a term
    PostingList* getPostingList(const string& term) const {
        return index.get(term);
    }

    // how many different terms we have
    int vocabularySize() const {
        return (int) index.keyCount();
    }

    // simple beginner-friendly iterator
   template<typename Func>
void forEachKey(Func f) const {
    for (int i = 0; i < bucketCount; i++) {
        Entry* e = buckets[i];
        while (e != nullptr) {
            f(e->key, e->value);
            e = e->next;
        }
    }
}

};


// SearchEngine

class SearchEngine {
private:
    InvertedIndex index;
    MyVector<Document> docs;
    Tokenizer tokenizer;
    int totalDocs;

public:
    SearchEngine() {
        totalDocs = 0;
    }

    void buildIndex(const string& folderPath) {
        int docID = 0;

        for (auto &entry : fs::directory_iterator(folderPath)) {
            if (!entry.is_regular_file()) continue;

            docID++;
            totalDocs++;

            string filename = entry.path().filename().string();

            // open file
            ifstream file(entry.path());
            if (!file.is_open()) {
                cout << "Error opening file: " << filename << "\n";
                continue;
            }

            // read content
            stringstream buffer;
            buffer << file.rdbuf();
            string content = buffer.str();

            // include filename as term
            content += " " + filename;

            MyVector<string> tokens = tokenizer.tokenize(content);
            int length = tokens.size();

            docs.push_back(Document(docID, filename, length));

            // add tokens to index
            for (int i = 0; i < tokens.size(); i++) {
                index.addTermOccurrence(tokens[i], docID);
            }

            file.close();
        }

        cout << "Index built: " << totalDocs << " documents processed.\n";
    }

    MyVector<pair<int,double>> search(const string& query) {
        MyVector<pair<int,double>> results;
        MyVector<string> qtokens = tokenizer.tokenize(query);
        if (qtokens.size() == 0) return results;

        double* scores = new double[totalDocs + 1];
        int* seen = new int[totalDocs + 1];
        for (int i = 0; i <= totalDocs; i++) {
            scores[i] = 0.0;
            seen[i] = 0;
        }

        for (int i = 0; i < qtokens.size(); i++) {
            PostingList* pl = index.getPostingList(qtokens[i]);
            if (pl == nullptr) continue;

            int df = pl->size();
            double idf = log((double)(totalDocs + 1) / (df + 1));

            MyVector<Posting> all = pl->getAll();
            for (int p = 0; p < all.size(); p++) {
                int did = all[p].docID;
                int freq = all[p].freq;
                int doclen = getDocLength(did);
                if (doclen == 0) continue;
                double tf = (double)freq / doclen;
                scores[did] += tf * idf;
                seen[did] = 1;
            }
        }

        for (int d = 1; d <= totalDocs; d++) {
            if (seen[d]) {
                results.push_back(make_pair(d, scores[d]));
            }
        }

        delete[] scores;
        delete[] seen;

        // simple insertion sort
        for (int i = 1; i < results.size(); i++) {
            pair<int,double> key = results[i];
            int j = i - 1;
            while (j >= 0 && results[j].second < key.second) {
                results[j+1] = results[j];
                j--;
            }
            results[j+1] = key;
        }

        return results;
    }

    int getDocLength(int docID) {
        for (int i = 0; i < docs.size(); i++) {
            if (docs[i].id == docID) return docs[i].length;
        }
        return 0;
    }

    string getDocName(int docID) {
        for (int i = 0; i < docs.size(); i++) {
            if (docs[i].id == docID) return docs[i].name;
        }
        return "";
    }

    int getTotalDocs() {
        return totalDocs;
    }
};


// CLI

class CLI {
private:
    SearchEngine engine;

public:
    CLI() {}

    void run() {
        string folderPath;
        cout << "Enter folder path: ";
        getline(cin, folderPath);

        engine.buildIndex(folderPath);

        while (true) {
            cout << "\nEnter search query (type 'exit' to quit): ";
            string query;
            getline(cin, query);

            if (query == "exit") break;

            MyVector<pair<int,double>> results = engine.search(query);

            if (results.size() == 0) {
                cout << "No files found for query: " << query << "\n";
            } else {
                cout << "Search results:\n";
                for (int i = 0; i < results.size(); i++) {
                    int docID = results[i].first;
                    double score = results[i].second;
                    cout << (i+1) << ") DocID: " << docID
                         << " Name: " << engine.getDocName(docID)
                         << " Score: " << score << "\n";
                }
            }
        }
    }
};



// main

int main() {
    CLI cli;
    cli.run();
    return 0;
}
