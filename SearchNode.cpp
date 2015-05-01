#pragma once
#include "SearchNode.h"
#include "SearchState.h"

SearchNode::SearchNode(int processID)
{
	ID = processID;
}
SearchNode::SearchNode(std::vector<SearchState> state, int processID)
{
	nodeStates = state; 
	ID = processID; 
}
SearchNode::SearchNode(SearchState state, int processID)
{
	nodeStates.push_back( state );
	ID = processID;
}

std::vector<SearchState> SearchNode::Search(std::string text, std::string searchText)
{
	std::vector<SearchState> ret;
	if (text.find(searchText) != std::string::npos)
	{
		SearchState tmp = SearchState(1, text.find(searchText));
		ret.push_back(tmp);
		return ret;
	}

	if (searchText.find(text) != std::string::npos)	// if substring of the keyword found in the all text process
		ret.push_back(SearchState(-1, searchText.find(text), text));

	for (int textCounterForward = 0, textCounterBackward = text.size() - 1;
		textCounterForward < text.size();
		++textCounterForward, --textCounterBackward)	// forward search
	{
		// parallelize these both
		int searchTextCounterForward = 0;
		ret.push_back(SearchState::SearchForward(searchTextCounterForward, textCounterForward, text, searchText));

		int searchTextCounterBackward = searchText.size() - 1;
		ret.push_back(SearchState::SearchBackward(searchTextCounterBackward, textCounterBackward, text, searchText));
	}

	return  ret;
}

int SearchNode::CombineSearchNodes(SearchState state)
{
	return 0;
}
