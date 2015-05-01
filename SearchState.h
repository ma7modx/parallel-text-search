#include <string>
using namespace std; 

class SearchState
{
public :
	int processID, found, state;
	string foundText = "";

	SearchState();
	SearchState(int found, int state);
	SearchState(int found, int state, string foundText);
	SearchState(int found, int state, string foundText, int processID);
	SearchState(SearchState state, int processID);

	// static region

	static SearchState null();

	static SearchState SearchForward(int searchTextCounter, int textCounter, string text, string searchText);

	static SearchState SearchBackward(int searchTextCounter, int textCounter, string text, string searchText);

	static SearchState Search(string text, string searchText);

	static int HandleState(SearchState state);

};
