#ifndef WEB_PAGES_H
#define WEB_PAGES_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>  
using namespace std;

class web_page
{
public:
	string name;
	vector<string> links;
	vector<string> keywords;
	
	int impressions;
	double page_rank;
	double normalized_PR;
	double page_score;
	double CTR;
	int num_of_clicks;


	web_page()
	{
		keywords.resize(15);
		links.resize(30);
		normalized_PR = 0;
		num_of_clicks = 0;
		impressions = 0;
	}
};

#endif // !WEB_PAGES