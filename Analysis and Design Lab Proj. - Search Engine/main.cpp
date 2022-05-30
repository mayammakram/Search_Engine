/*
* Search Engine Sample Project
* Fall '21
* Name: Maya Hussein
* CSCE-2203-04
* Instructor: Dr. Mohamed El Halaby
* Due: November 27th
*/

#include "web_graph.h"
#include <fstream>

void menu()
{
	web_graph allsites;
	allsites.readFile();
	cout << "Welcome to iSearch" << endl;
	cout << "What would you like to do?" << endl << "1. New Search" << endl << "2. Exit" << endl;
	int choice;
	string keyword;
	cin >> choice;
	if (choice == 1)
	{
		cout << "Type your search: ";
		cin >> keyword;
		allsites.search_query(keyword);
		allsites.sortPageScores();


		cout << "The following are the websites relevent to your search:\n";
		allsites.displayWebsite();

		cout << "1. Would you like to make a new search. /n 2. Back to search?"<<endl;
			int answer;
			cin >> answer;
			if (answer == 1 || answer == 2)
				menu();
			else
			{
				cout << "Thank You for your time.";
				exit;
			}
			

	}
	else
	{
		cout << "Thank You for your time.";
		exit;
	}
}


int main()
{
	////string keyword;
	////cout << "Enter your search: ";
	////getline(cin, keyword);
	//web_graph google;
	//google.readFile();
	///*cout << google.web_pages[12].keywords[2];
	//cout << google.web_pages[13].impressions;*/
	////google.search_query(keyword);
	//google.setGraph();
	////google.pageRank(3);
	/*for (int i = 0; i < google.searched_websites.size(); i++)
		cout << "Website Name : " << google.searched_websites[i].name << " Page Rank: " << google.searched_websites[i].page_rank << endl;
	*/
	//for (int i = 0; i < google.web_pages.size(); i++)
	//{
	//	for (int j = 0; j < google.web_pages.size(); j++)
	//		cout << google.graph[i][j] << " ";
	//	cout << endl;
	//}
	//cout << endl << endl;
	//google.pageRank();
	////google.displayWebsite();


	menu();



}


void sendData()
{

}
