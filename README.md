<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Mini Search Engine</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            line-height: 1.6;
            margin: 0;
            padding: 0 20px;
            background-color: #f9f9f9;
            color: #333;
        }
        h1, h2, h3 {
            color: #2c3e50;
        }
        h1 {
            text-align: center;
            margin-top: 30px;
        }
        .badge {
            display: inline-block;
            margin: 0 5px 10px 0;
            padding: 2px 8px;
            font-size: 12px;
            color: white;
            border-radius: 5px;
        }
        .badge-cpp { background-color: #00599C; }
        .badge-license { background-color: #28a745; }
        .badge-status { background-color: #2ecc71; }
        pre {
            background: #eee;
            padding: 10px;
            border-radius: 5px;
            overflow-x: auto;
        }
        code {
            font-family: monospace;
            background: #eee;
            padding: 2px 4px;
            border-radius: 4px;
        }
        a {
            color: #2980b9;
            text-decoration: none;
        }
        a:hover {
            text-decoration: underline;
        }
        .section {
            margin-bottom: 30px;
        }
        ul {
            padding-left: 20px;
        }
        .screenshot img {
            max-width: 100%;
            border: 1px solid #ccc;
            border-radius: 5px;
            margin-top: 10px;
        }
    </style>
</head>
<body>

    <h1>Mini Search Engine</h1>
    <div class="badges" style="text-align:center;">
        <span class="badge badge-cpp">C++</span>
        <span class="badge badge-license">MIT License</span>
        <span class="badge badge-status">Completed</span>
    </div>

    <p>A <strong>C++ project</strong> that searches and ranks text files using data structures and algorithms. 
    It builds an <strong>inverted index</strong> to store words and their document locations and uses the 
    <strong>TF-IDF</strong> method to rank and display the most relevant results for a user’s query.</p>

    <div class="section">
        <h2>📑 Table of Contents</h2>
        <ul>
            <li><a href="#features">Features</a></li>
            <li><a href="#installation">Installation</a></li>
            <li><a href="#usage">Usage</a></li>
            <li><a href="#how-it-works">How It Works</a></li>
            <li><a href="#technologies-used">Technologies Used</a></li>
            <li><a href="#screenshots">Screenshots</a></li>
            <li><a href="#author">Author</a></li>
            <li><a href="#license">License</a></li>
        </ul>
    </div>

    <div class="section" id="features">
        <h2>📝 Features</h2>
        <ul>
            <li>Builds an <strong>inverted index</strong> from a collection of text files.</li>
            <li>Implements <strong>TF-IDF ranking</strong> to display relevant results.</li>
            <li>Efficient search for large sets of documents.</li>
            <li>Handles multiple queries interactively.</li>
            <li>Written entirely in <strong>C++</strong>.</li>
        </ul>
    </div>

    <div class="section" id="installation">
        <h2>💻 Installation</h2>
        <ol>
            <li>Clone the repository:
                <pre><code>git clone https://github.com/YourUsername/mini-search-engine.git
cd mini-search-engine</code></pre>
            </li>
            <li>Compile the project using g++:
                <pre><code>g++ main.cpp -o mini_search_engine</code></pre>
            </li>
            <li>Run the executable:
                <pre><code>./mini_search_engine</code></pre>
            </li>
        </ol>
    </div>

    <div class="section" id="usage">
        <h2>📂 Usage</h2>
        <ol>
            <li>Place all your <strong>text files</strong> in a folder.</li>
            <li>Run the program and provide the folder path when prompted.</li>
            <li>Enter your search query.</li>
            <li>The program will return a <strong>ranked list of relevant documents</strong>.</li>
        </ol>
    </div>

    <div class="section" id="how-it-works">
        <h2>📈 How It Works</h2>
        <ul>
            <li><strong>Indexing:</strong> Each document is tokenized, and an inverted index maps words to document locations.</li>
            <li><strong>Querying:</strong> The user enters a search query.</li>
            <li><strong>Ranking:</strong> TF-IDF algorithm calculates relevance scores and displays results in descending order.</li>
        </ul>
    </div>

    <div class="section" id="technologies-used">
        <h2>🛠️ Technologies Used</h2>
        <ul>
            <li><strong>C++</strong> — core programming language</li>
            <li>Data Structures — maps, vectors, strings</li>
            <li>Algorithms — TF-IDF for document ranking</li>
            <li>File I/O — reading and processing text files</li>
        </ul>
    </div>

    <div class="section" id="screenshots">
        <h2>📸 Screenshots</h2>
        <p>You can add screenshots here to showcase your project. For example:</p>
        <div class="screenshot">
            <img src="path/to/screenshot.png" alt="Example search results">
        </div>
    </div>

    <div class="section" id="author">
        <h2>👤 Author</h2>
        <p><strong>Abdullah Adil</strong><br>
        GitHub: <a href="https://github.com/AbdullahAdil">@AbdullahAdil</a></p>
    </div>

    <div class="section" id="license">
        <h2>📄 License</h2>
        <p>This project is licensed under the <strong>MIT License</strong>.</p>
    </div>

</body>
</html>
