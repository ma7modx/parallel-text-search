#include <string>

class SearchState
{
public :
	int found, state;
	std::string foundText;
	
	SearchState();
	SearchState(int found, int state);
	SearchState(int found, int state, std::string foundText);
	
	// static region

	static SearchState null();

	static SearchState SearchForward(int searchTextCounter, int textCounter, std::string text, std::string searchText);

	static SearchState SearchBackward(int searchTextCounter, int textCounter, std::string text, std::string searchText);
};
