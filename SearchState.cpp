#pragma once
#include "SearchState.h"

SearchState::SearchState()
{
	*this = SearchState::null();
}
SearchState::SearchState(int found, int state)
{
	this->found = found;
	this->state = state;
}
SearchState::SearchState(int found, int state, std::string foundText)
{
	//SearchState(found, state);

	this->found = found;
	this->state = state;
	this->foundText = foundText;
}

// static region

SearchState SearchState::null() { return SearchState(-1, -1, ""); }

SearchState SearchState::SearchForward(int searchTextCounter, int textCounter, std::string text, std::string searchText)
{
	while (searchTextCounter < searchText.size())
	{
		if (text[textCounter++] != searchText[searchTextCounter++])	// increment both indices 
			break;
		else
		{
			if (textCounter >= text.size())
			{
				return SearchState(0, 1, searchText.substr(0, searchTextCounter));	// sub last in the next process
			}
		}
	}

	return SearchState(-1, -1, "");
}

SearchState SearchState::SearchBackward(int searchTextCounter, int textCounter, std::string text, std::string searchText)
{
	while (searchTextCounter >= 0)
	{
		if (text[textCounter--] != searchText[searchTextCounter--])	// increment both indices 
			break;
		else
		{
			if (textCounter < 0)
			{
				return SearchState(0, -1, searchText.substr(searchTextCounter, searchText.size() - 1));	// sub last in the next process
			}
		}
	}

	return SearchState(-1, -1, "");
}
