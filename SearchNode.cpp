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
		SearchState tmp = SearchState(SearchStateResult::FOUND, searchText, text.find(searchText));
		ret.push_back(tmp);
		return ret;
	}

	if (searchText.find(text) != std::string::npos)	// if substring of the keyword found in the all text process
		ret.push_back(SearchState(SearchStateResult::SUB_MIDDLE, text));

	for (int textCounterForward = 0, textCounterBackward = text.size() - 1;
		textCounterForward < text.size();
		++textCounterForward, --textCounterBackward)	// forward search
	{
		SearchState tmpResult; 

		// parallelize these both
		int searchTextCounterForward = 0;
		tmpResult = SearchState::SearchForward(searchTextCounterForward, textCounterForward, text, searchText);
		if (tmpResult != SearchState::null())
			ret.push_back(tmpResult);

		int searchTextCounterBackward = searchText.size() - 1;
		tmpResult = SearchState::SearchBackward(searchTextCounterBackward, textCounterBackward, text, searchText);
		if (tmpResult != SearchState::null())
			ret.push_back(tmpResult);
	}

	return  ret;
}

int SearchNode::CombineSearchNodes(SearchState state)
{
	return 0;
}
