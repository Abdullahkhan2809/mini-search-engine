```markdown
# Mini Search Engine (C++ Object-Oriented Project)

## Author

**Abdullah Adil**

## Description

This project implements a mini search engine in C++ using object-oriented programming principles. It indexes text documents in a folder and allows term-based search queries with TF-IDF ranking. Core data structures such as dynamic arrays, posting lists, and hash maps are implemented manually, avoiding STL containers for the main logic.

---

## Features

- Index multiple documents from a folder
- Tokenize text and filenames
- Compute TF-IDF scores for queries
- Sort results by relevance
- Command-line interface (CLI) for user queries
- No STL containers used for data structures (custom `MyVector` and `HashMapStringToPtr`)

---

## Directory Structure

```

/src       -> C++ source files (.cpp, .h)
/tests     -> Sample input documents and expected outputs
/docs      -> Project report, figures, diagrams
README.md  -> This file
Makefile or CMakeLists.txt -> Build automation

````

---

## Build Instructions

### Using g++

```bash
g++ -std=c++17 -o searchengine main.cpp
````

### Using Makefile

```bash
make
```

---

## Run Instructions

1. Open a terminal and navigate to the folder containing `searchengine.exe` (Windows) or `./searchengine` (Linux/Mac).
2. Run the executable:

```bash
./searchengine
```

3. Enter the folder path containing your documents when prompted.
4. Enter search queries or type `exit` to quit.

---

## Workflow

### 1. Indexing Workflow

**Description:** Reads all documents from the folder, tokenizes text, builds the inverted index, and calculates document statistics.

**Flowchart Placeholder:**
![Indexing Workflow](path_to_indexing_flowchart.png)

**Steps:**

1. User enters folder path.
2. Read all supported files (`.cpp`, `.h`, `.docx`, `.txt`).
3. Tokenize document content and filenames.
4. Build inverted index: map tokens → posting lists.
5. Calculate document lengths and TF-IDF stats.
6. Index ready for search queries.

---

### 2. Search Workflow

**Description:** Processes user queries, calculates relevance scores using TF-IDF, and displays sorted results.

**Flowchart Placeholder:**
![Search Workflow](path_to_search_flowchart.png)

**Steps:**

1. User enters search query.
2. Tokenize the query.
3. Lookup tokens in the inverted index.
4. Compute TF-IDF scores for matching documents.
5. Sort documents by descending relevance score.
6. Display search results in CLI.

---

## Sample Output

**Example Run:**

```
Enter folder path: C:\Users\Ryuk\OneDrive\Desktop\dsa
Index built: 27 documents processed.

Enter search query (type 'exit' to quit): lab
Search results:
1) DocID: 13 Name: Lab-1 done.docx Score: 0.219921

Enter search query (type 'exit' to quit): linked
Search results:
1) DocID: 1 Name: doublylinkedlist.cpp Score: 0.0058471
2) DocID: 25 Name: tempCodeRunnerFile.cpp Score: 0.0058471

Enter search query (type 'exit' to quit): information
No files found for query: information

Enter search query (type 'exit' to quit): I
Search results:
1) DocID: 22 Name: lab6task.cpp Score: 0.0470785
2) DocID: 1 Name: doublylinkedlist.cpp Score: 0.030564
3) DocID: 25 Name: tempCodeRunnerFile.cpp Score: 0.030564
```

**Screenshot of sample run:**

![Search Engine Output](path_to_your_screenshot.png)

---

## Assumptions

* Only `.cpp`, `.h`, `.docx`, or text files are processed.
* Tokens are lowercase alphabetic strings; punctuation and numbers are ignored.
* TF-IDF formula uses log-based IDF with smoothing to avoid division by zero.
* Search is case-insensitive.

---

## Future Improvements

* Support for phrase queries and Boolean search
* Multi-threaded indexing for faster processing
* Persistent index storage to disk
* More efficient posting list search for very large document sets


