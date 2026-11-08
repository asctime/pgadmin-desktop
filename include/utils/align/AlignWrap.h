#pragma once
#include "Item.h"

class AlignWrap {
public:
	enum cfg
	{
		// Line-list alignment. Can be combined with FIND_UP_LONG_LINE
		// for example INSERT statements with the same value list
		ALL_LINES = 1,
		// wrap to the width of the first line
		// newlines from the second line on are ignored
		// used to wrap an IN list to the width set by the first line
		FIRST_LINE= 2,
		// helper flag for the odd short line
		// look back for a longer line already processed
		FIND_UP_LONG_LINE=4,
		/// Collapse runs of spaces to one space. Does not align.
		ONLY_SINGLE_SPACE=8,
		/// A tighter layout. Meaningful for ALL_LINES
		COMPACT_VIEW=16

	};
	AlignWrap() {}
#define CHKCFGPARAM(val,par) ((val & par)==par)
	
	wxString build(wxString & strsrc, int config,wxString linesep);
	void Resize(int idx, int newSize);
	wxString range_print(int s, int e);
private:
	
	int range_size(int s, int e);
	int range_size(int s);
	Item parseItem(int &pos, bool &breakline);
	int chkspace(int &pos, bool& br);
	int find(int s, int e, Item& k);
	//
	int parserows = 0;

	std::vector <Item> list;

	wxString str, lnsep;
	int cfg = 0;
};
