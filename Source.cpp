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
void ShowMessage(int id, SearchNode foundState)
{
	printf("from thread number (%d) text found %d \n", id, foundState.nodeStates.size());
	for (int i = 0; i < foundState.nodeStates.size(); ++i)
	{
		printf("%s ,", foundState.nodeStates[i].foundText);
	}
}
int main()
{
	int id, threads ;
	omp_set_num_threads(omp_get_max_threads());

	string text = GetText("text.txt");
	
	int segment = text.size() / omp_get_max_threads();
	int segmentRemain = text.size() % omp_get_max_threads();

	string searchText;
	getline(cin, searchText);

	vector< SearchNode > saveNodesStates;
	cout << omp_get_max_threads() << endl;

#pragma omp parallel private(id)
	{
		id = omp_get_thread_num();

		SearchNode foundState = (id); 
		if (id != omp_get_max_threads()-1)
			foundState = SearchNode(	SearchNode::Search(text.substr(id*segment, id*segment + segment), searchText),	id);
		else
			foundState = SearchNode(	SearchNode::Search(text.substr(id*segment, id*segment + segment + segmentRemain), searchText),	id);

		saveNodesStates.push_back(foundState);

		ShowMessage(id , foundState);
	}

}