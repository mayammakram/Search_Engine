#include "web_graph.h"
#include <iomanip>

double web_graph::maxPR = -1;
//double web_graph::minPR = -1;

void web_graph::readFile()
{
    ifstream keywordsInFile;
    ifstream webgraphInFile;
    ifstream impressionsInFile;
    ifstream clicksInFile;
    impressionsInFile.open("C:/Users/maya3/Desktop/CSCE 2203/Lab/Analysis and Design Lab Proj. - Search Engine/Data Sheets/impressions.csv");
    keywordsInFile.open("C:/Users/maya3/Desktop/CSCE 2203/Lab/Analysis and Design Lab Proj. - Search Engine/Data Sheets/keywords.csv");
    webgraphInFile.open("C:/Users/maya3/Desktop/CSCE 2203/Lab/Analysis and Design Lab Proj. - Search Engine/Data Sheets/web_graph.csv");
    clicksInFile.open("C:/Users/maya3/Desktop/CSCE 2203/Lab/Analysis and Design Lab Proj. - Search Engine/Data Sheets/NumberOfClicks.csv");

    if (keywordsInFile.fail() || webgraphInFile.fail() || impressionsInFile.fail()) //File Failure
    {
        cout << "Error: File not opening.";
    }
    else
    {
        int i = 0;
        string comma, dummy, dummy2;

        while (!keywordsInFile.eof())
        {
            impressionsInFile >> dummy >> comma >> web_pages[i].impressions;
            clicksInFile >> dummy2 >> comma >> web_pages[i].num_of_clicks;

            keywordsInFile >> web_pages[i].name;
            keywordsInFile >> comma;

            int j = 0;
            
            while( comma == ",")
            {
                keywordsInFile >> web_pages[i].keywords[j];
                keywordsInFile >> comma;

                j++;
            }
            web_pages[i].keywords.resize(j);
            i++;
        }
        web_pages.resize(i);
        keywordsInFile.close();
        impressionsInFile.close();
        
    }
}

vector<web_page> web_graph::search_query(string keyword)
{
    if (keyword.find("AND")<keyword.length())
    {
        string keyword_pt1 = keyword.substr(0, keyword.find("AND") - 1);
        string keyword_pt2 = keyword.substr(keyword.find_last_of("AND") + 2, keyword.length() - 1);
        
        cout << keyword_pt1 << endl;
        cout << keyword_pt2 << endl;
        int m = 0;
        for (int j = 0; j < web_pages.size(); j++)
            for (int i = 0; i < web_pages[j].keywords.size(); i++)
            {
                
                if (web_pages[j].keywords[i] == keyword_pt1)
                    for (int k = 0; k < web_pages[j].keywords.size(); k++)
                        if (web_pages[j].keywords[k] == keyword_pt2)
                        {
                            searched_websites.push_back(web_pages[j]);
                            m++;
                        }
            }
                
        searched_websites.resize(m);
    }

    else if (keyword.find("OR"))
    {
        string keyword_pt1 = keyword.substr(0, keyword.find("OR") - 2);
        string keyword_pt2 = keyword.substr(keyword.find_last_of("OR") + 1, keyword.length() - 1);

     int m = 0;
     for (int j = 0; j < web_pages.size(); j++)
         for (int i = 0; i < web_pages[j].keywords.size(); i++)
         {
             if (web_pages[j].keywords[i] == keyword_pt1 || web_pages[j].keywords[i] == keyword_pt2)
             {
                 searched_websites.push_back(web_pages[j]);
                 m++;
             }
         }

    searched_websites.resize(m);
    }

    else if (keyword.find("\"") == 0)
    {
        keyword.erase(0,1);
        keyword.erase(keyword.size() - 1,keyword.size());

        int m = 0;
        for (int j = 0; j < web_pages.size(); j++)
            for (int i = 0; i < web_pages[j].keywords.size(); i++)

                if (web_pages[j].keywords[i] == keyword)
                {
                    searched_websites.push_back(web_pages[j]);
                    m++;
                }
        searched_websites.resize(m);
        

    }

    else
    {
        cout << "No Results found. Error 404" << endl;
        exit;
    }

    return searched_websites;
}


void web_graph::setGraph()
{
    ifstream webGraphFile;

    string website1, website2, comma;
    webGraphFile.open("C:/Users/maya3/Desktop/CSCE 2203/Lab/Analysis and Design Lab Proj. - Search Engine/Data Sheets/web_graph.csv");
    
    int j = 0;
    while (!webGraphFile.eof()) {
        
        webGraphFile >> website1 >> comma >> website2;
        if (website1 == web_pages[j].name)
        {
            for (int i = 0; i < web_pages.size(); i++)
                if (website2 == web_pages[i].name)
                {
                    graph[i][j] = 1;
                    edge_counter[i]++;
                    break;
                }
        }
        else
            j++;
    }
      
    webGraphFile.close();
    
}


void web_graph::matrix_display(double** m1, double size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            cout << m1[i][j] << " ";

        cout << endl;
    }
}


double** web_graph::matrix_multiply(double** mat1, double** mat2, int sizeRow, int sizeCol, int sizeCommon)
{
    double** result = new double* [web_pages.size()];
    for(int i=0;i< web_pages.size();i++)
        result[i] = new double[web_pages.size()];

    for (int m = 0; m < sizeRow; m++)
        for (int j = 0; j < sizeCol; j++)
        {
            result[m][j] = 0;
            for (int k = 0; k < sizeCommon; k++)
                result[m][j] += mat1[m][k] * mat2[k][j];
        }

    return result;
}

double** web_graph::power_matrix(double** m1, int n)
{

    /*int** matrix = new int* [2];
    matrix[0] = new int[2]{ 1, 1 };
    matrix[1] = new int[2]{ 1, 0 };*/

    double** result = new double* [size];
    for (int i = 0; i < size; i++)
    {
        result[i] = new double[size];
    }

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (i == j)
                result[i][j] = 1;
            else
                result[i][j] = 0;

    while (n > 0)
    {
        if (n % 2 == 1)
        {
            result = matrix_multiply(result, m1, size, size, size);
            n--;
        }
        n /= 2;
        m1 = matrix_multiply(m1, m1, size, size, size);
    }

    return result;
}

double** web_graph::pageRank() 
{
    double** initial= new double*[16];
    
    for (int i = 0; i < web_pages.size(); i++)
    {
        initial[i] = new double[1];
        initial[i][1] = 1 / web_pages.size();

        if (web_pages[i].num_of_clicks == 0)
            web_pages[i].page_rank = initial[i][1];
    }

    vector<double> counter(web_pages.size());

    double** matrixH= new double*[web_pages.size()];
    for (int i = 0; i < web_pages.size(); i++)
    {
        matrixH[i] = new double[web_pages.size()];
    }

    for (int j = 0; j < web_pages.size(); j++)
        for (int i = 0; i < web_pages.size(); i++)
        {
            if (graph[i][j] == 1)
                counter[j]++;
            matrixH[i][j] = 0;
        }
    for (int j = 0; j < web_pages.size(); j++)
        for (int i = 0; i < web_pages.size(); i++)
            if (graph[i][j] == 1)
                matrixH[i][j] = 1.0 / counter[j];

   double** PowerMatrix = power_matrix(matrixH, 3);
   
   for (int j = 0; j < web_pages.size(); j++)
   {
       for (int i = 0; i < web_pages.size(); i++)
           cout << PowerMatrix[j][i] << " ";
       cout << endl;
   }

   cout << endl << endl;
   matrix_multiply(PowerMatrix, initial, web_pages.size(), 1, web_pages.size());
    
   for (int i = 0; i < web_pages.size(); i++)
   {
       for (int j = 0; j < web_pages.size(); j++)
       {
           web_pages[i].page_rank = PowerMatrix[i][1];
       }

   }
   return PowerMatrix;

  
}


void web_graph::CTR()
{
    for (int i = 0; i < web_pages.size(); i++)
    {
        web_pages[i].CTR = (web_pages[i].num_of_clicks / web_pages[i].impressions) * 100;
    }
}

void web_graph::pageScore()
{
    for (int i = 0; i < web_pages.size(); i++)
    {
        web_pages[i].page_score = 0.4 * web_pages[i].normalized_PR + ((1 - ((0.1 * web_pages[i].impressions) / (1 + 0.1 * web_pages[i].impressions))) * web_pages[i].normalized_PR + ((0.1 * web_pages[i].impressions) / (1 + 0.1 * web_pages[i].impressions)) * web_pages[i].CTR) * 0.6;
        cout << web_pages[i].page_score << endl;

    }
   
}



void web_graph::sortPageScores()
{
    sort(searched_websites.begin(), searched_websites.end(), [](web_page website1, web_page website2) {return website1.page_score > website2.page_score; });
}

int web_graph::updateImpressions(web_page website)
{
    return ++website.impressions;
}

int web_graph::updateNumOfClicks(web_page website)
{
    return ++website.num_of_clicks;
}

void web_graph::normalize() 
{

    double sum = 0;

    for (int i = 0; i < size; i++) {

        sum = sum + web_pages[i].page_rank; // sum up every elem squared in vector
    }

    //cout << "sum: " << sum << endl;
    double magnitude = sum; // take the sqaure root of the sum of the squares of each elem.

    maxPR = web_pages[0].normalized_PR;
    for (int i = 0; i < size; i++) 
    {

        web_pages[i].normalized_PR = web_pages[i].page_rank / magnitude; // normalize each elem of the vector
        if (i > 0 && web_pages[i].normalized_PR > web_pages[i - 1].normalized_PR)
            maxPR = web_pages[i].normalized_PR;
    }


}

void web_graph::displayWebsite()
{
    int* m = new int[searched_websites.size()];
    cout << "Search Results:" << endl;
    for (int i = 0; i < searched_websites.size(); i++)
    {
        cout << i + 1 << ". " << searched_websites[i].name << endl;
        m[i] = i + 1;
        searched_websites[i].impressions++;
        sendImpressions();

    }

    cout << endl << "Choose Website: ";
    int choice;
    cin >> choice;
    for (int i = 0; i < searched_websites.size(); i++)
    {
        if (choice == (i + 1))
            cout << searched_websites[i].name << " is now open. \n";
        searched_websites[i].num_of_clicks++;
        sendClicks();
    }
}



void web_graph::sendImpressions()
{
    ofstream impressionsUpdate;
    impressionsUpdate.open("C:/Users/maya3/Desktop/CSCE 2203/Lab/Analysis and Design Lab Proj. - Search Engine/Data Sheets/impressions.csv");
    int statement[16] = { false };
    for (int i = 0; i < web_pages.size(); i++)
    {
        for (int j = 0; j < searched_websites.size(); j++)
            if (web_pages[i].name == searched_websites[j].name)
            {
                impressionsUpdate << searched_websites[j].name << " , " << searched_websites[j].impressions << " \n";
                statement[i] = true;
            }
    }
    int i = 0;
    while (i < 16)
    {
        if (statement[i] == false)
        {
            impressionsUpdate << web_pages[i].name << " , " << web_pages[i].impressions << " \n";
            statement[i] = true;
        }
        i++;
    }

    
}

void web_graph::sendClicks()
{
    bool statement[16] = { false };
    ofstream clicksUpdate;
    clicksUpdate.open("C:/Users/maya3/Desktop/CSCE 2203/Lab/Analysis and Design Lab Proj. - Search Engine/Data Sheets/NumberOfClicks.csv");

    for (int i = 0; i < web_pages.size(); i++)
    {
        for (int j = 0; j < searched_websites.size(); j++)
            if (web_pages[i].name == searched_websites[j].name)
            {
                clicksUpdate << searched_websites[j].name << " , " << searched_websites[j].num_of_clicks << " \n";
                statement[i] = true;
            }
    }
    int i = 0;
    while (i < 16)
    {
        if (statement[i]==false)
        {
            clicksUpdate << web_pages[i].name << " , " << web_pages[i].num_of_clicks << " \n";
            statement[i] = true;
        }
        i++;
    }
}



