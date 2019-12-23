## GoogleAutoComplete

I implemented the funtion :

vector<AutoCompleteData> GetBestKCompletions(const string& prefix);
which returns the best 5 matches for the given prefix.

## output example:



## Run:
to run it,firstly you need to parse text files to a json file using the python parser in parse lines directory, after that you should put the json file in jsons directory and compile the program using this line :

g++ -o runme AutoCompleteMain.cpp AutoCompleteData.h -ljsoncpp
