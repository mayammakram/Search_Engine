#ifndef WEB_GRAPH_H
#define WEB_GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "web_pages.h"

using namespace std; 

class web_graph
{
public:
	vector<web_page> web_pages;
	vector<web_page> searched_websites;
	static double maxPR;
	//static int minPR;
	vector<int> edge_counter;
	int graph[30][30] = { 0 };
	int size = 16;
	void readFile();
	vector<web_page> search_query(string keyword); //could store couts in new vector called search vector
	void setGraph();

	double** pageRank();
	void CTR();
	void pageScore();

	void matrix_display(double** m1, double size);
	double** matrix_add(double** m1, double** m2, int size);
	double** matrix_subtract(double** m1, double** m2, int size);
	double** matrix_multiply(double** m1, double** m2, int sizeRow, int sizeCol, int sizeCommon);
	double** power_matrix(double** m1, int power);
	vector<double> matrixMult(vector<web_graph> matrix1, vector<web_graph> matrix2);
	void sortPageScores();
	int updateImpressions(web_page website); //send updated impressions to file again
	int updateNumOfClicks(web_page website);
	void normalize();
	void displayWebsite(); //display search vector

	web_graph()
	{
		//graph[30][30] = {0};
		edge_counter.resize(30);
		web_pages.resize(30);
		//searched_websites.resize(1);
	}
	void sendImpressions();
	void sendClicks();
};
#endif //!WEB_GRAPH_H

