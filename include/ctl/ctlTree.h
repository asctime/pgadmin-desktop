//////////////////////////////////////////////////////////////////////////
//
//
// Copyright (C) 2002 - 2016, The pgAdmin Development Team
// Copyright (C) 2027, asctime
// This software is released under the PostgreSQL Licence
//
// ctlTree.h - wxTreeCtrl containing pgObjects
//
//////////////////////////////////////////////////////////////////////////

#ifndef CTLTREE_H
#define CTLTREE_H

// wxWindows headers
#include <wx/wx.h>
#include <wx/treectrl.h>
#include <wx/timer.h>

class pgObject;
class ctlAncestorTip;
class pgCollection;
class pgaFactory;
class ctlTreeFindTimer;

class ctlTree : public wxTreeCtrl
{
public:
	ctlTree(wxWindow *parent, wxWindowID id, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = wxTR_HAS_BUTTONS);
	void SetItemImage(const wxTreeItemId &item, int image, wxTreeItemIcon which = wxTreeItemIcon_Normal);
	wxTreeItemId AppendItem(const wxTreeItemId &parent, const wxString &text, int image = -1, int selImage = -1, wxTreeItemData *data = NULL);
	wxTreeItemId AppendObject(pgObject *parent, pgObject *object);
	void RemoveDummyChild(pgObject *obj);
	pgCollection *AppendCollection(pgObject *parent, pgaFactory &factory);
	pgObject *GetObject(wxTreeItemId id);
	pgObject *GetParentObject(wxTreeItemId id)
	{
		return GetObject(GetItemParent(id));
	}
	pgCollection *GetParentCollection(wxTreeItemId id);
	pgObject *FindObject(pgaFactory &factory, wxTreeItemId parent);
	pgCollection *FindCollection(pgaFactory &factory, wxTreeItemId parent);
	wxTreeItemId FindItem(const wxTreeItemId &item, const wxString &str, bool full = false);
	void NavigateTree(int keyCode);
	virtual ~ctlTree();
	void OnMouse(wxMouseEvent& ev);
	void OnLeave(wxMouseEvent& ev);
	void DrawDbName(const wxTreeItemId& item);
	wxTreeItemId GetVerticalItem(wxPoint& pt);
	DECLARE_EVENT_TABLE()

private:

	void OnChar(wxKeyEvent &event);
	void ShowAncestorTip(const wxTreeItemId& item);
	void HideAncestorTip();
	// Label row through the icon strip, in screen coordinates. The pointer
	// crosses this on the way from the text to the icons.
	bool PointerInTipHot() const;
	void ArmTipHide();
	wxString m_findPrefix;
	ctlTreeFindTimer *m_findTimer;
	ctlAncestorTip *m_ancestorTip;
	wxTimer m_tipHideTimer;
	wxTreeItemId m_tipItem;
	friend class ctlTreeFindTimer;
	bool isJumpRoot;
};


// timer used to clear ctlTreeCtrl::m_findPrefix if no key was pressed
// for a sufficiently long time
class ctlTreeFindTimer : public wxTimer
{
public:
	// reset the current prefix after half a second of inactivity
	enum { CTLTREE_DELAY = 500 };

	ctlTreeFindTimer( ctlTree *owner )
	{
		m_owner = owner;
	}

	virtual void Notify()
	{
		m_owner->m_findPrefix.clear();
	}

private:
	ctlTree *m_owner;

	DECLARE_NO_COPY_CLASS(ctlTreeFindTimer)
};


class treeObjectIterator
{
public:
	treeObjectIterator(ctlTree *browser, pgObject *obj);
	pgObject *GetNextObject();

private:
	wxTreeItemId lastItem;
	ctlTree *browser;
	pgObject *object;
	wxCookieType cookie;
};



#endif
