#include <Windows.h>
#include <omp.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>

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

int main()
{
	int id, threads ;
	omp_set_num_threads(omp_get_max_threads());

	string text = GetText("text.txt");
	
	int segment = text.size() / omp_get_max_threads();
	int segmentRemain = text.size() % omp_get_max_threads();

	string searchText;
	getline(cin, searchText);

	vector<SearchState> saveStates;
	cout << omp_get_max_threads() << endl;

#pragma omp parallel private(id)
	{
		id = omp_get_thread_num();

		SearchState foundState; 
		if (id != omp_get_max_threads()-1)
			foundState = SearchState(SearchState::Search(text.substr(id*segment, id*segment + segment), searchText), id);
		else
			foundState = SearchState(SearchState::Search(text.substr(id*segment, id*segment + segment + segmentRemain), searchText), id);

		saveStates.push_back(foundState);

		printf("from thread number (%d) text found %s \n", id , foundState.foundText);
	}

}