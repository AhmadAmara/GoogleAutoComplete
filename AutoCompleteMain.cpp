#include <iostream>
#include <string>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <unordered_map> 
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <memory>
#include <chrono> 

#include "AutoCompleteData.h"
using namespace std;
using namespace std::chrono; 

typedef std::unordered_map<string, std::vector<std::shared_ptr<struct LineDetails>>> LinesDetailsMap;
typedef unordered_map<string, vector<std::shared_ptr<string>>> IndexedFiles;


std::ostream& operator<<(std::ostream& os,const AutoCompleteData& d)
{
	os << "=======================" << endl; 
	os<< "score : " << d.getScore() << endl;
	os << "completed : " << d.getCompleted() << endl;
	os << " source : " << d.getSource() << endl;
	os << "offset : " << d.getOffset() << endl;
	os << "=======================";
	return os;
}


bool pointerCmp(const AutoCompleteData* l, const AutoCompleteData* r)
{
	return *l > *r;
}

struct LineDetails{
	string source_name;
	int line_idx;
};


int calculate_score(string prefix, string substr)
{
	
	int orig_score = 2 * (prefix.length());
	int remove_scores[] = {10, 8, 6, 4};
	int substute_scores[] = {5, 4, 3, 2};


	if(prefix == substr)
	{
		return orig_score;
	}

	if (prefix.length() < substr.length()) //a char added
	{
		for(int i = 0; i < prefix.length(); i++)
		{	

			if(prefix[i] != substr[i])
			{
				return i < 4 ? orig_score - remove_scores[i] : orig_score - 2; 
			}
		}
		return orig_score - 2;
	}

	else if(prefix.length() > substr.length()) //a char removed
	{

		for(int i = 0; i < substr.length(); i++)
		{
			if(prefix[i] != substr[i])
			{
				int score = i < 4 ? orig_score - remove_scores[i] : orig_score - 2;

				return  score;
			}
			return orig_score - 2;
		}
	}
	else // a char substiuted
	{
		for(int i = 0; i < substr.length(); i++)
		{
			
			if(prefix[i] != substr[i])
			{
				return i < 4 ? orig_score - substute_scores[i] : orig_score - 1; 
			}
		}
	}

	return orig_score;
}


vector<string> get_all_options(string prefix)
{
	

	std::vector<string> options;
	string prefix_copy = prefix;
	options.push_back(prefix);
	for(int i = 0; i < prefix.length(); i++)
	{
		string temp = prefix_copy.erase(i,1);
		options.push_back(temp);
		prefix_copy = prefix;
	}

	std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

  	for(char& c: alphabet)
  	{
  		for(int i = 0; i < prefix.length(); i++)
		{
			prefix_copy[i] = c;
			options.push_back(prefix_copy);
			prefix_copy = prefix;
		}
  	}
  	return options;
}

vector<AutoCompleteData> get_all_auto_completions(string prefix, LinesDetailsMap& subs_map, unordered_map<string, vector<std::shared_ptr<string>>>& indexd_files)
{
	

	vector<AutoCompleteData*> matched;
	vector<AutoCompleteData> best_five;

	int max_score = 2 * prefix.length();


	LinesDetailsMap::const_iterator it = subs_map.find(prefix); // the prefix allredy in the offline data
	if (it != subs_map.end())
	{
		for(shared_ptr<struct LineDetails> ld :it->second)
		{
			string file_name = ld->source_name;
			file_name = file_name.substr(file_name.find("/") + 1);
			string line = *(indexd_files[file_name.substr(file_name.find("/") + 1)][ld->line_idx]);
			AutoCompleteData* autucomplete = new AutoCompleteData(line, file_name, ld->line_idx, max_score);
			matched.push_back(autucomplete);

		}

	}

	if (matched.size() >= 5)
	{
		for(int i =0; i < 5; i++)
		{
			best_five.push_back(*matched[i]);
		}	

		return best_five;
	}

	else
	{
		int matched_count = matched.size();

		// best_score_less_than_max = (2 * prefix.length()) - 1;
		// good_scores = matched_count;
		vector<string> options = get_all_options(prefix);

		for(string& substr: options)
		{
 			LinesDetailsMap::const_iterator it = subs_map.find(substr);

			if ( it != subs_map.end())
			{
				
				for(shared_ptr<struct LineDetails> ld :it->second)
				{
					string file_name = ld->source_name;
					file_name = file_name.substr(file_name.find("/") + 1);
					string line = *(indexd_files[file_name.substr(file_name.find("/") + 1)][ld->line_idx]);
					int score = calculate_score(prefix, substr);
					/*if (score == best_score_less_than_max)
					{
						good_scores++;
						if(good_scores == 5)
						{

						}
					}*/
					if (score < 0)
						continue;

					AutoCompleteData* autucomplete = new AutoCompleteData(line, file_name, ld->line_idx, score);
					matched.push_back(autucomplete);


				}

			}

		}
	}


	std::sort(matched.begin(), matched.end(),pointerCmp);


	if(matched.size() < 5)
	{
		for(int i = 0; i < matched.size(); i++)
		{
			best_five.push_back(*matched[i]);

		}
			return best_five;

	}
	
	for(int i = 0; i < 5; i++)
	{
		best_five.push_back(*matched[i]);
	}	

	return best_five;


}


IndexedFiles indexd_files;
LinesDetailsMap lines_map;

void index_files()
{
	// unordered_map<string, vector<std::shared_ptr<string>>> indexd_files;
	string text_files[] = {"google/The picture of Dorian Gray.txt",
	 						"google/Moses_and_the_Sages__Bible.txt"};

	std::cout << "indexing files..." << endl;
	for(string& file_name: text_files)
	{
		// string file_name = "google/The picture of Dorian Gray.txt";
		std::ifstream infile(file_name);
		std::vector<std::shared_ptr<string>> lines;

		for (std::string line; std::getline(infile, line); ) {
			std::shared_ptr<string> l(new string(line));
		   	lines.push_back(l);
		}

		indexd_files.insert({file_name.substr(file_name.find("/") + 1), lines});
	}

	// return indexd_files;
}


void map_lines()
{
	std::cout << "converting json files to map ..." << endl;
	string jsons_files[] = {"jsons/The picture of Dorian Gray.json", "jsons/Moses_and_the_Sages__Bible.json"};

	string file_name = "jsons/output.json";
    ifstream ifs(file_name);
    Json::Reader reader;
    Json::Value root;
    reader.parse(ifs, root);

	for( Json::Value::iterator itr = root.begin() ; itr != root.end() ; itr++ )
	{

		Json::Value sub_lines = root[itr.key().asString()];

		std::vector<std::shared_ptr<struct LineDetails>> line_details;

		for ( int index = 0; index < sub_lines.size(); ++index )
	    {

		        std::shared_ptr<struct LineDetails> l(new LineDetails{sub_lines[index][0].asString(), sub_lines[index][1].asInt()});

		        line_details.push_back(l);


		}


		lines_map.insert({itr.key().asString(), line_details});

	}
	// return umap;
}



// the function which Google asked to implement
vector<AutoCompleteData> GetBestKCompletions(const string& prefix)
{
	

	auto start = high_resolution_clock::now(); 

	vector<AutoCompleteData> best_completions = get_all_auto_completions(prefix , lines_map, indexd_files);

	auto stop = high_resolution_clock::now(); 
	auto duration = duration_cast<microseconds>(stop - start); 
	cout<<endl;
	cout << "*********** runtime : " << duration.count() << " microseconds ***********" << endl;
	cout<<endl;

	return best_completions;
}





int main() 
{
	// this is an offline stage, it initialized here to keep it in the cache.

	string text_files[] = {"google/The picture of Dorian Gray.txt", "google/Moses_and_the_Sages__Bible.txt"};
	std::cout << "indexing files..." << endl;
	for(string& file_name: text_files)
	{
		std::ifstream infile(file_name);
		std::vector<std::shared_ptr<string>> lines;

		for (std::string line; std::getline(infile, line); ) {
			std::shared_ptr<string> l(new string(line));
		   	lines.push_back(l);
		}

		indexd_files.insert({file_name.substr(file_name.find("/") + 1), lines});
	}


	std::cout << "converting json files to map ..." << endl;
	string output_file = "jsons/output.json";
    ifstream ifs(output_file);
    Json::Reader reader;
    Json::Value root;
    reader.parse(ifs, root);

	for( Json::Value::iterator itr = root.begin() ; itr != root.end() ; itr++ )
	{

		Json::Value sub_lines = root[itr.key().asString()];

		std::vector<std::shared_ptr<struct LineDetails>> line_details;

		for ( int index = 0; index < sub_lines.size(); ++index )
	    {
	        
		        std::shared_ptr<struct LineDetails> l(new LineDetails{sub_lines[index][0].asString(), sub_lines[index][1].asInt()});

		        line_details.push_back(l);

		}
		lines_map.insert({itr.key().asString(), line_details});

	}

	//////////////////////////////////////////////////////////////////
	// online
	string prefix;
	cout << "please insert your prefix :" << endl;
	std::getline(std::cin, prefix);
	while(prefix != "exit")
	{

		vector<AutoCompleteData> best_completions = GetBestKCompletions(prefix);

		for(AutoCompleteData d:best_completions)
		{
			cout << d << endl;
		}
		cout<<endl;
		cout<<endl;
		cout << "please insert your prefix :" << endl;
		std::getline(std::cin, prefix);

	}

    return 0;
}