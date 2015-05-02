#pragma once 
#include <Windows.h>
#include <omp.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>

#include "SearchNode.h"
#include "SearchState.h"
using namespace std; 

string GetText(string file)
{
	fstream fileStream;
	fileStream.open(file, fstream::in | fstream::out | fstream::app);

	string text = "", tmp;
	while (getline(fileStream, tmp))
		text = text + tmp;
	return text;
}
void ShowInfo(string text , int segment)
{
	cout << "text size = " << text.size() << endl; 
	cout << text << endl;

	cout << "number of threads: " << omp_get_max_threads() << endl;
	cout << "segment size :" << segment << endl << endl;
}
void ShowMessage(int id, SearchNode foundState)
{
	printf("from thread number (%d) text found %d \n", id, foundState.nodeStates.size());
	for (int i = 0; i < foundState.nodeStates.size(); ++i)
	{
		//printf("%s ,", foundState.nodeStates[i].foundText);
		// why the hell it's not working!!! ~_~
	}
	printf("\n");
}

int main()
{
	omp_set_num_threads(omp_get_max_threads());

	string text = GetText("text.txt");
	const int segment = text.size() / omp_get_max_threads();
	const int segmentRemain = text.size() % omp_get_max_threads();

	ShowInfo(text , segment);

	string searchText;
	cout << "type the search word: "; 
	getline(cin, searchText);

	vector< SearchNode > saveNodesStates;
	
	int id;
#pragma omp parallel private(id)
	{
		id = omp_get_thread_num();

		SearchNode foundState = SearchNode(id);
		if (id != omp_get_max_threads() - 1)
		{
			string subtext = text.substr(id*segment, segment);
			printf("from thread %d .. %d \n %s \n", id, subtext.size(), subtext);
			foundState = SearchNode(SearchNode::Search(subtext, searchText), id);
		}
		else
		{
			string subtext = text.substr(id*segment, segment + segmentRemain);
			printf("from thread %d .. %d \n %s \n", id, subtext.size(), subtext);
			foundState = SearchNode(SearchNode::Search(subtext, searchText), id);
		}

		saveNodesStates.push_back(foundState);
	
		ShowMessage(id , foundState);
	}

}