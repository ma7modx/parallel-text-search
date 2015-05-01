#include "SearchState.h"

SearchState::SearchState()
{
	*this = SearchState::null();
}
SearchState::SearchState(int found, int state)
{
	SearchState::found = found;
	SearchState::state = state;
}
SearchState::SearchState(int found, int state, string foundText)
{
	SearchState(found, state);
	SearchState::foundText = foundText;
}
SearchState::SearchState(int found, int state, string foundText, int processID)
{
	SearchState(found, state, foundText);
	SearchState::processID = processID;
}
SearchState::SearchState(SearchState state, int processID)
{
	*this = state;
	SearchState::processID = processID;
}

// static region

SearchState SearchState::null() { return SearchState(-1, -1, ""); }

SearchState SearchState::SearchForward(int searchTextCounter, int textCounter, string text, string searchText)
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

SearchState SearchState::SearchBackward(int searchTextCounter, int textCounter, string text, string searchText)
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

SearchState SearchState::Search(string text, string searchText)
{
	SearchState ret;
	if (text.find(searchText) != string::npos)
		return ret = SearchState(1, text.find(searchText));

	for (int textCounterForward = 0, textCounterBackward = text.size() - 1;
		textCounterForward < text.size();
		++textCounterForward, --textCounterBackward)	// forward search
	{
		// parallelize these both
		int searchTextCounterForward = 0;
		ret = SearchForward(searchTextCounterForward, textCounterForward, text, searchText);

		int searchTextCounterBackward = searchText.size() - 1;
		ret = SearchBackward(searchTextCounterBackward, textCounterBackward, text, searchText);
	}

	/*
	if (ret == SearchState(-1, -1))
	for (int textCounterBackward = text.size() - 1; textCounterBackward >= 0; --textCounterBackward)
	{
	int searchTextCounterBackward = searchText.size()-1;
	ret = SearchBackward(searchTextCounterBackward, textCounterBackward, text, searchText);;
	}
	*/

	return ret;
}

int SearchState::HandleState(SearchState state)
{
	return 0;
}
