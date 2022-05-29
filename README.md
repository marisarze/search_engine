# Simple search engine

## The purpose

Hello! Here is a simple search engine project. The source code of the project is intended to create a console application designed to search for a word/sentence among the indexed files.

## Installing

To create a working executable, you must have [CMake](https://cmake.org/) installed on your computer along with the compiler. Download the repository: Click on the green Code button on this page and Download Zip or in the command window enter the command

git clone https://github.com/marisarze/search_engine.git\
cd search_engine\
cmake -B build\
cd build\
cmake --build .

In the build directory where we are located, the executable file "search_engine"  is created.

## Running

The application is launched using the command \
search_engine [-c,--config /path/to/config.json] [-r,--request /path/to/requests.json] [-o,--output /path/to/answers.json]

### -c, --config
Option sets the path to the configuration file config.json.\
Default value is ./config.json. \
The content of the configuration file should looks like \
{ \
&emsp;"config": { \
&emsp;&emsp;"name": "Search Engine", \
&emsp;&emsp;"version": "0.0.9.1", \
&emsp;&emsp;"max_responses": 5 \
&emsp;}, \
&emsp;"files": [ \
&emsp;&emsp;"../resources/file001.txt", \
&emsp;&emsp;"../resources/file002.txt", \
&emsp;&emsp;"../resources/file003.txt", \
&emsp;&emsp;… \
&emsp;] \
} \

where fields describe \
● **config** - general information, without which the application does not start. \
● **name** - field with the name of the search engine. It can be anything. You can come up with a name for the search engine yourself. \
● **max_responses** - a field that determines the maximum number of responses to one request.\
● **version** - field with the version number of the search engine. **Must match the version of the application (current 0.0.9.2) otherwise an error will be raised.** \
● **files** - contains the paths to the files to be searched.. Each resource text file contains no more than 1000 words with a maximum length of 100 characters each. Words consist of lowercase English letters and are separated by one or more spaces.

### -r, --request
Option sets path to the request file requests.json. \
Default value is ./requests.json. \
An example of a requests.json file description:\
{\
"requests": [\
&emsp;"some words..",\
&emsp;"some words..",\
&emsp;"some words..",\
&emsp;"some words..",\
&emsp;…\
]\
}

● **requests** - consists of a list of requests that need to be processed by the search engine. The field contains no more than 1000 queries, each of which includes from one to ten words. \
● **some words..** — search query, a set of words separated by one or more spaces. They need to be searched. All words are composed of lowercase Latin letters.

### -o, --output
Option sets the path to the output file answers.json.\
Default value is ./answers.json. \

answers.json records the results of the search engine. An example of a description of the file:

{ \
&emsp;"answers": {\
&emsp;&emsp;"request001": { \
&emsp;&emsp;&emsp;"result": "true", \
&emsp;&emsp;&emsp;"relevance": [ \
&emsp;&emsp;&emsp;&emsp;"docid": 0, “rank” : 0.989, \
&emsp;&emsp;&emsp;&emsp;"docid": 1, “rank” : 0.897, \
&emsp;&emsp;&emsp;&emsp;"docid": 2, “rank” : 0.750, \
&emsp;&emsp;&emsp;&emsp;"docid": 3, “rank” : 0.670, \
&emsp;&emsp;&emsp;&emsp;"docid": 4, “rank” : 0.561 \
&emsp;&emsp;&emsp;] \
&emsp;&emsp;}, \
&emsp;&emsp;"request002": { \
&emsp;&emsp;&emsp;"result": "true",\
&emsp;&emsp;&emsp;"docid": 0, \
&emsp;&emsp;&emsp;“rank” : 0.769 \
&emsp;&emsp;}, \
&emsp;&emsp;"request003": {\
&emsp;&emsp;&emsp;"result": "false" \
&emsp;&emsp;} \
&emsp;} \
}

Consider each field: \
● **answers** is the base field in this file that contains the answers to queries. \
● **request001 … 003** — identifier of the request that generated the response.
The request ID is generated automatically in the order in which the requests appear in the requests field of the requests.json file. For example: \
"requests": [ \
&emsp;"some words..", for this string the request id will be "request001" \
&emsp;"some words..", for this string the request id will be "request002" \
&emsp;"some words..", for this string the request id will be "request003" \
&emsp;"some words..", for this string the request id will be "request004" \
&emsp;… \
] \
● **result** – query search result. If it evaluates to true, then at least one document was found for this query. If the result is false, then no documents were found. Then there are no other fields in the response to this request. \
● **relevance** is included in the response if more than one document was found for the query.

Next, there are correspondences between the response rating and the name of the id of the document in which the search was carried out:

● **docid** is the ID of the document in which the response to the request was found. It is generated automatically when indexing all documents based on the order in which the documents are located in the files field in the config.json file. For example, if in the config.json the "files" field contains: \
"files": [ \
&emsp;"../resources/file001.txt", for this file docid will be 0 \
&emsp;"../resources/file002.txt", for this file docid will be equal to 1 \
&emsp;"../resources/file003.txt", for this file docid will be equal to 2 \
&emsp;… \
] \
● **rank** — rank or search rating. This number indicates how good the document is for a given query. In the response, document id's are arranged in order of decreasing search ranking.