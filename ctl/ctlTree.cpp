//////////////////////////////////////////////////////////////////////////
//
//
// Copyright (C) 2002 - 2016, The pgAdmin Development Team
// Copyright (C) 2027, asctime
// This software is released under the PostgreSQL Licence
//
// ctlTree.cpp - wxTreeCtrl containing pgObjects
//
//////////////////////////////////////////////////////////////////////////

// wxWindows headers
#include <wx/wx.h>
#include <wx/popupwin.h>

// App headers
#include "pgAdmin3.h"
#include "ctl/ctlTree.h"
#include "schema/pgObject.h"
#include "schema/pgCollection.h"
#include "schema/pgServer.h"

BEGIN_EVENT_TABLE(ctlTree, wxTreeCtrl)
	EVT_CHAR(ctlTree::OnChar)
	EVT_MOUSE_EVENTS(ctlTree::OnMouse)
	EVT_LEAVE_WINDOW(ctlTree::OnLeave)
END_EVENT_TABLE()

// Ancestor icons for the hovered row. Drawn in a popup to the right of the
// label. Left to right is the root toward that row. A click selects that
// ancestor. The icon under the pointer shows that row's text under the strip.
class ctlAncestorTip : public wxPopupWindow
{
public:
	ctlAncestorTip(wxWindow *parent)
		: wxPopupWindow(parent, wxBORDER_SIMPLE), m_images(NULL), m_dismissed(false), m_hot(-1), m_textH(0)
	{
		SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INFOBK));
		SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INFOTEXT));
		SetFont(wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT));
		SetCursor(wxCursor(wxCURSOR_HAND));
		Bind(wxEVT_PAINT, &ctlAncestorTip::OnPaint, this);
		Bind(wxEVT_MOTION, &ctlAncestorTip::OnMotion, this);
		Bind(wxEVT_ENTER_WINDOW, &ctlAncestorTip::OnMotion, this);
		Bind(wxEVT_LEAVE_WINDOW, &ctlAncestorTip::OnLeaveTip, this);
	}

	void SetIcons(wxImageList *images, const wxArrayInt& ids, const std::vector<wxTreeItemId>& items, const wxArrayString& labels)
	{
		m_images = images;
		m_ids = ids;
		m_items = items;
		m_labels = labels;
		if (m_hot >= (int)m_labels.GetCount())
			m_hot = -1;
		Relayout();
		Refresh();
	}

	wxTreeItemId HitItem(const wxPoint& pt) const
	{
		const int index = HitIndex(pt);
		if (index < 0)
			return wxTreeItemId();
		return m_items[(size_t)index];
	}

	// Hiding this window from its own click sends a mouse move back to the
	// tree, and that move would open the strip again. Hold it until the
	// pointer leaves the row that was clicked.
	void Dismiss(const wxTreeItemId& item)
	{
		m_dismissed = true;
		m_dismissItem = item;
	}
	bool Dismissed() const { return m_dismissed; }
	const wxTreeItemId& DismissItem() const { return m_dismissItem; }
	void Release()
	{
		m_dismissed = false;
		m_dismissItem.Unset();
	}

private:
	enum { kSlot = 18, kPad = 4 };

	int HitIndex(const wxPoint& pt) const
	{
		if (m_items.empty())
			return -1;
		// The caption under the icons belongs to the icon that opened it,
		// including the part that is wider than that icon.
		const int iconBottom = kSlot + kPad;
		if (m_hot >= 0 && pt.y >= iconBottom)
			return m_hot;
		if (pt.x < kPad)
			return -1;
		const int index = (pt.x - kPad) / kSlot;
		if (index < 0 || (size_t)index >= m_items.size())
			return -1;
		return index;
	}

	static wxString FitText(wxDC& dc, const wxString& text, int maxW)
	{
		if (text.empty() || maxW < 8)
			return wxEmptyString;
		if (dc.GetTextExtent(text).GetWidth() <= maxW)
			return text;
		wxString out = text;
		const wxString ellipsis = wxT("...");
		while (out.length() > 1 && dc.GetTextExtent(out + ellipsis).GetWidth() > maxW)
			out = out.Left(out.length() - 1);
		return out + ellipsis;
	}

	void Relayout()
	{
		const int iconW = wxMax(kPad + (int)m_ids.GetCount() * kSlot + kPad, 8);
		const int iconH = kSlot + kPad;
		int w = iconW;
		int h = iconH;
		m_text.clear();
		m_textH = 0;
		if (m_hot >= 0 && (size_t)m_hot < m_labels.GetCount() && !m_labels[m_hot].empty())
		{
			wxClientDC dc(this);
			dc.SetFont(GetFont());
			int maxText = 320;
			if (GetHandle())
			{
				const int room = wxGetClientDisplayRect().GetRight() - GetScreenPosition().x - kPad;
				if (room > iconW && room - kPad < maxText)
					maxText = room - kPad;
			}
			m_text = FitText(dc, m_labels[m_hot], maxText);
			if (!m_text.empty())
			{
				const wxSize extent = dc.GetTextExtent(m_text);
				m_textH = extent.GetHeight();
				const int textW = extent.GetWidth() + kPad * 2;
				if (textW > w)
					w = textW;
				h = iconH + m_textH + 2;
			}
		}
		if (GetClientSize() != wxSize(w, h))
			SetClientSize(w, h);
	}

	void OnMotion(wxMouseEvent& e)
	{
		const int idx = HitIndex(e.GetPosition());
		if (idx != m_hot)
		{
			m_hot = idx;
			Relayout();
			Refresh();
		}
		e.Skip();
	}

	void OnLeaveTip(wxMouseEvent& e)
	{
		// A resize while the pointer is still over an icon can report a leave.
		if (GetScreenRect().Contains(wxGetMousePosition()))
		{
			e.Skip();
			return;
		}
		if (m_hot != -1)
		{
			m_hot = -1;
			Relayout();
			Refresh();
		}
		e.Skip();
	}

	void OnPaint(wxPaintEvent&)
	{
		wxPaintDC dc(this);
		dc.SetBackground(wxBrush(GetBackgroundColour()));
		dc.Clear();
		if (!m_images)
			return;
		int x = kPad;
		for (size_t i = 0; i < m_ids.GetCount(); i++)
		{
			if ((int)i == m_hot)
			{
				dc.SetPen(wxPen(GetForegroundColour()));
				dc.SetBrush(*wxTRANSPARENT_BRUSH);
				dc.DrawRectangle(x - 1, 1, kSlot, kSlot);
			}
			m_images->Draw(m_ids[i], dc, x, 2, wxIMAGELIST_DRAW_TRANSPARENT);
			x += kSlot;
		}
		if (m_text.empty())
			return;
		dc.SetFont(GetFont());
		dc.SetTextForeground(GetForegroundColour());
		dc.DrawText(m_text, kPad, kSlot + kPad);
	}

	wxImageList *m_images;
	wxArrayInt m_ids;
	wxArrayString m_labels;
	std::vector<wxTreeItemId> m_items;
	bool m_dismissed;
	wxTreeItemId m_dismissItem;
	int m_hot;
	wxString m_text;
	int m_textH;
};

void ctlTree::OnLeave(wxMouseEvent& event)
{
	if (m_ancestorTip && m_ancestorTip->Dismissed())
	{
		wxPoint pt = ScreenToClient(wxGetMousePosition());
		wxRect row;
		const wxTreeItemId held = m_ancestorTip->DismissItem();
		const bool onRow = held.IsOk() && GetBoundingRect(held, row, false) && row.Contains(pt);
		if (!onRow)
			m_ancestorTip->Release();
	}
	// Leaving for the icon strip reports a point that is not on this window
	// yet and not inside the popup yet. Hide only after that crossing fails.
	if (PointerInTipHot())
		m_tipHideTimer.Stop();
	else
		ArmTipHide();
	event.Skip();
}


wxTreeItemId ctlTree::FindItem(const wxTreeItemId &idParent, const wxString &prefixOrig, const bool full )
{
	// match is case insensitive as this is more convenient to the user: having
	// to press Shift-letter to go to the item starting with a capital letter
	// would be too bothersome
	wxString prefix = prefixOrig.Lower();

	// determine the starting point: we shouldn't take the current item (this
	// allows to switch between two items starting with the same letter just by
	// pressing it) but we shouldn't jump to the next one if the user is
	// continuing to type as otherwise he might easily skip the item he wanted
	wxTreeItemId id = idParent;
	int le=prefix.length();
	if ( prefix.length() == 1 )
	{
		wxCookieType cookie;
		if (HasChildren(id))
			id = GetFirstChild(id, cookie);
		else
		{
			// Try a sibling of this or ancestor instead
			wxTreeItemId p = id;
			wxTreeItemId toFind;
			do
			{
				toFind = GetNextSibling(p);
				p = GetItemParent(p);
			}
			while (p.IsOk() && !toFind.IsOk());
			id = toFind;
		}
	}

	// look for the item starting with the given prefix after it
	while ( id.IsOk() &&
	        ( ( GetItemText(id) == wxT("Dummy") && !GetItemData(id) ) ||
			!( (!full&&GetItemText(id).Lower().StartsWith(prefix)) || 
			(full && //GetItemText(id).Lower().StartsWith(prefix) && GetItemText(id).length()==le)
			           GetObject(id)!=NULL&&GetObject(id)->GetName()==prefix )
			)
			))
	{
		wxCookieType cookie;
		if ( HasChildren(id) )
			id = GetFirstChild(id, cookie);
		else
		{
			// Try a sibling of this or ancestor instead
			wxTreeItemId p = id;
			wxTreeItemId toFind;
			do
			{
				toFind = GetNextSibling(p);
				p = GetItemParent(p);
			}
			while (p.IsOk() && !toFind.IsOk());
			id = toFind;
		}
	}

	// if we haven't found anything...
	if ( !id.IsOk() )
	{
		// ... wrap to the beginning
		id = GetRootItem();
		if ( HasFlag(wxTR_HIDE_ROOT) )
		{
			wxCookieType cookie;
			// can't select virtual root
			if ( HasChildren(id) )
				id = GetFirstChild(id, cookie);
			else
			{
				// Try a sibling of this or ancestor instead
				wxTreeItemId p = id;
				wxTreeItemId toFind;
				do
				{
					toFind = GetNextSibling(p);
					p = GetItemParent(p);
				}
				while (p.IsOk() && !toFind.IsOk());
				id = toFind;
			}
		}

		// and try all the items (stop when we get to the one we started from)
		while ( id.IsOk() && id != idParent &&
		        (( GetItemText(id) == wxT("Dummy") && !GetItemData(id) ) ||
		         !((!full&&GetItemText(id).Lower().StartsWith(prefix)) || 
				   (full && //GetItemText(id).Lower().StartsWith(prefix) && GetItemText(id).length()==le)
							GetObject(id)!=NULL&&GetObject(id)->GetName()==prefix )
				  )
				))
		{
			wxCookieType cookie;
			if ( HasChildren(id) )
				id = GetFirstChild(id, cookie);
			else
			{
				// Try a sibling of this or ancestor instead
				wxTreeItemId p = id;
				wxTreeItemId toFind;
				do
				{
					toFind = GetNextSibling(p);
					p = GetItemParent(p);
				}
				while (p.IsOk() && !toFind.IsOk());
				id = toFind;
			}
		}
		// If we haven't found the item, id.IsOk() will be false, as per
		// documentation
	}

	return id;
}
wxTreeItemId ctlTree::GetVerticalItem(wxPoint& pt) {
	int flags = 0;
	wxTreeItemId item = DoTreeHitTest(pt, flags);
	if (flags & wxTREE_HITTEST_ONITEMBUTTON)
		return wxTreeItemId();
	if ((flags & wxTREE_HITTEST_ONITEMINDENT) == wxTREE_HITTEST_ONITEMINDENT) {
		if (item) {
			wxRect r;
			wxTreeItemId itemParent = item;
			GetBoundingRect(itemParent, r, true);
			const int step = wxMax((int)GetIndent(), 1);
			r.x = r.x - step;
			wxTreeItemId prev;
			bool ex = false;
			while (!ex) {
				ex = true;
				prev = itemParent;
				itemParent = GetItemParent(itemParent);
				r.x = r.x - step;
				if (r.x >= pt.x) ex = false;
			}
			if (prev) return (prev);
		}
	}
	return wxTreeItemId();
}

void ctlTree::HideAncestorTip()
{
	if (m_tipHideTimer.IsRunning())
		m_tipHideTimer.Stop();
	m_tipItem.Unset();
	if (m_ancestorTip && m_ancestorTip->IsShown())
		m_ancestorTip->Hide();
}

bool ctlTree::PointerInTipHot() const
{
	if (!m_ancestorTip || !m_ancestorTip->IsShown() || !m_tipItem.IsOk())
		return false;

	wxRect hot = m_ancestorTip->GetScreenRect();
	wxRect text;
	if (GetBoundingRect(m_tipItem, text, true) && text.height > 0)
	{
		wxRect row = text;
		wxRect full;
		if (GetBoundingRect(m_tipItem, full, false) && full.height > 0)
			row = full;
		int bridge = text.GetWidth() / 100;
		if (bridge < 1)
			bridge = 1;
		const wxPoint origin = ClientToScreen(row.GetTopLeft());
		const wxPoint textOrigin = ClientToScreen(text.GetTopLeft());
		const int left = wxMin(textOrigin.x, hot.GetLeft());
		const int right = wxMax(textOrigin.x + text.GetWidth() + bridge, hot.GetRight());
		const int top = wxMin(origin.y, hot.GetTop());
		const int bottom = wxMax(origin.y + row.GetHeight(), hot.GetBottom());
		hot = wxRect(left, top, right - left, bottom - top);
	}
	// The window change at the popup edge is a pixel or two wide.
	hot.Inflate(2, 3);
	return hot.Contains(wxGetMousePosition());
}

void ctlTree::ArmTipHide()
{
	if (!m_ancestorTip || !m_ancestorTip->IsShown())
		return;
	if (!m_tipHideTimer.IsRunning())
		m_tipHideTimer.StartOnce(250);
}

void ctlTree::ShowAncestorTip(const wxTreeItemId& item)
{
	if (m_ancestorTip && m_ancestorTip->Dismissed())
		return;

	if (!item.IsOk() || !isJumpRoot)
	{
		HideAncestorTip();
		return;
	}

	wxArrayInt ids;
	std::vector<wxTreeItemId> items;
	wxArrayString labels;
	wxTreeItemId parent = GetItemParent(item);
	while (parent.IsOk())
	{
		int image = GetItemImage(parent);
		if (image >= 0)
		{
			ids.Insert(image, 0);
			items.insert(items.begin(), parent);
			labels.Insert(GetItemText(parent), 0);
		}
		wxTreeItemId next = GetItemParent(parent);
		if (!next.IsOk() || next == parent)
			break;
		parent = next;
	}
	if (ids.IsEmpty())
	{
		HideAncestorTip();
		return;
	}

	wxRect label;
	if (!GetBoundingRect(item, label, true))
	{
		HideAncestorTip();
		return;
	}

	if (!m_ancestorTip)
	{
		m_ancestorTip = new ctlAncestorTip(this);
		m_ancestorTip->Bind(wxEVT_ENTER_WINDOW, [this](wxMouseEvent& e)
		{
			m_tipHideTimer.Stop();
			e.Skip();
		});
		m_ancestorTip->Bind(wxEVT_LEAVE_WINDOW, [this](wxMouseEvent& e)
		{
			if (PointerInTipHot())
				m_tipHideTimer.Stop();
			else
				ArmTipHide();
			e.Skip();
		});
		m_ancestorTip->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& e)
		{
			wxTreeItemId target = m_ancestorTip->HitItem(e.GetPosition());
			if (!target.IsOk())
				return;
			wxTreeItemId hover = m_tipItem;
			m_ancestorTip->Dismiss(hover);
			HideAncestorTip();
			CallAfter([this, target]()
			{
				if (!target.IsOk())
					return;
				// The popup took the click. Put focus back so the new row paints selected.
				SetFocus();
				EnsureVisible(target);
				SelectItem(target);
			});
		});
	}
	m_ancestorTip->SetIcons(GetImageList(), ids, items, labels);
	m_tipItem = item;
	m_tipHideTimer.Stop();

	// Overlap the label by 1% of its width so the pointer enters the icons
	// before it leaves the text.
	int bridge = label.GetWidth() / 100;
	if (bridge < 1)
		bridge = 1;
	wxPoint scr = ClientToScreen(wxPoint(label.GetRight() - bridge, label.GetTop()));
	const wxRect screen = wxGetClientDisplayRect();
	const wxSize sz = m_ancestorTip->GetSize();
	if (scr.x + sz.x > screen.GetRight())
		scr.x = screen.GetRight() - sz.x;
	if (scr.x < screen.GetLeft())
		scr.x = screen.GetLeft();
	if (scr.y + sz.y > screen.GetBottom())
		scr.y = screen.GetBottom() - sz.y;
	if (m_ancestorTip->IsShown() && m_ancestorTip->GetScreenPosition() == scr)
		return;
	m_ancestorTip->Move(scr);
	if (!m_ancestorTip->IsShown())
		m_ancestorTip->Show();
}
void ctlTree::DrawDbName(const wxTreeItemId& item) {
	if (!item.IsOk() || !settings->GetVisibleDbNameTree())
		return;

	pgObject* o = GetObject(item);
	if (!o)
		return;

	pgConn* conn = o->GetConnection();
	if (!conn)
		return;

	// Database name shown on the opposite side of the selected row.
	wxString name = conn->GetName().BeforeFirst(' ');
	if (name.IsEmpty())
		return;

	// The row already is that database. A second copy is what spills past the pane.
	if (GetItemText(item) == name)
		return;

	wxRect label;
	if (!GetBoundingRect(item, label, true) || label.height <= 0)
		return;

	const int margin = 4;
	const int gap = 8;
	const int padX = 3;
	int clientW = GetClientSize().GetWidth();
	int clientH = GetClientSize().GetHeight();
	if (clientW <= margin * 2 || clientH <= 0)
		return;

	int right = clientW - margin;
	int leftLimit = label.GetRight() + gap;
	if (leftLimit < margin)
		leftLimit = margin;
	int avail = right - leftLimit;
	// Need room for a short badge. Otherwise the object name already fills the row.
	if (avail < 28)
		return;

	wxClientDC dc(this);
	dc.SetFont(GetFont());

	wxString shown = wxControl::Ellipsize(name, dc, wxELLIPSIZE_END, avail - padX * 2);
	wxSize sz = dc.GetTextExtent(shown);
	int badgeW = sz.GetWidth() + padX * 2;
	if (badgeW > avail)
		badgeW = avail;
	if (badgeW < 8)
		return;

	wxRect badge(right - badgeW, label.y, badgeW, label.height);
	if (badge.x < leftLimit)
		badge.x = leftLimit;
	if (badge.GetBottom() > clientH)
		badge.height = clientH - badge.y;
	if (badge.height <= 0)
		return;

	extern wxBrush selectFindBrush;
	wxColour bg = selectFindBrush.GetColour();
	pgServer* s = o->GetServer();
	if (s && !s->GetColour().IsEmpty())
		bg = wxColour(s->GetColour());
	if (!bg.IsOk())
		bg = selectFindBrush.GetColour();

	dc.SetClippingRegion(wxRect(0, 0, clientW, clientH));
	dc.SetPen(*wxTRANSPARENT_PEN);
	dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(bg));
	dc.DrawRoundedRectangle(badge, 2);

	int luma = (bg.Red() * 299 + bg.Green() * 587 + bg.Blue() * 114) / 1000;
	dc.SetTextForeground(luma < 140 ? *wxWHITE : *wxBLACK);
	dc.SetBackgroundMode(wxTRANSPARENT);
	int textY = badge.y + (badge.height - sz.GetHeight()) / 2;
	dc.DrawText(shown, wxPoint(badge.x + padX, textY));
	dc.DestroyClippingRegion();
}
// The node control is the +/- drawn in the image-width column just left of
// the icon. Clicks further left are the tree line, not the button.
static bool InExpander(wxTreeCtrl* tree, const wxTreeItemId& item, const wxPoint& pt, int flags)
{
	if (flags & wxTREE_HITTEST_ONITEMBUTTON)
		return item.IsOk();
	if (!item.IsOk() || !tree->ItemHasChildren(item))
		return false;

	wxRect label;
	if (!tree->GetBoundingRect(item, label, true) || label.height <= 0)
		return false;
	if (pt.y < label.y || pt.y >= label.GetBottom())
		return false;

	int imgW = 16;
	wxImageList* images = tree->GetImageList();
	if (images && images->GetSize().GetWidth() > 0)
		imgW = images->GetSize().GetWidth();
	const int bandRight = label.x - imgW;
	const int bandLeft = bandRight - imgW - 2;
	return pt.x >= bandLeft && pt.x < bandRight;
}

// Label text, plus 1% of its width past the right edge. The icon popup is
// placed in that strip, so the pointer can move onto it.
static bool InLabelTipZone(wxTreeCtrl* tree, ctlAncestorTip* tip, const wxTreeItemId& item, const wxPoint& pt)
{
	if (!item.IsOk())
		return false;
	wxRect label;
	if (!tree->GetBoundingRect(item, label, true) || label.height <= 0)
		return false;
	wxRect row = label;
	wxRect full;
	if (tree->GetBoundingRect(item, full, false) && full.height > 0)
		row = full;
	if (pt.y < row.y || pt.y >= row.GetBottom())
		return false;
	int reach = label.GetWidth() / 100;
	if (reach < 1)
		reach = 1;
	if (tip && tip->IsShown())
		reach += tip->GetSize().GetWidth();
	return pt.x >= label.x && pt.x < label.GetRight() + reach;
}

void ctlTree::OnMouse(wxMouseEvent& event)
{
	wxPoint pt = event.GetPosition();
	int flags = 0;
	wxTreeItemId item = DoTreeHitTest(pt, flags);

	if (m_ancestorTip && m_ancestorTip->Dismissed())
	{
		if (!item.IsOk() || item != m_ancestorTip->DismissItem())
			m_ancestorTip->Release();
	}

	if (InExpander(this, item, pt, flags))
	{
		// Open or close the branch and nothing else. The native click also
		// selects the row, and Expand() from inside this mouse message does
		// not stick, so toggle once the click has been eaten.
		HideAncestorTip();
		if (event.LeftDown())
		{
			wxTreeItemId target = item;
			CallAfter([this, target]()
			{
				if (!target.IsOk())
					return;
				if (IsExpanded(target))
					Collapse(target);
				else
					Expand(target);
			});
			return;
		}
		// A double-click is a second toggle. The first click already did it.
		if (event.LeftDClick())
			return;
		event.Skip();
		return;
	}

	if (isJumpRoot && event.LeftDown() && item.IsOk() && (flags & wxTREE_HITTEST_ONITEMINDENT))
	{
		wxTreeItemId prev = GetVerticalItem(pt);
		if (prev.IsOk())
			SelectItem(prev);
		HideAncestorTip();
		return;
	}

	if (isJumpRoot && InLabelTipZone(this, m_ancestorTip, item, pt))
		ShowAncestorTip(item);
	else if (PointerInTipHot())
		m_tipHideTimer.Stop();
	else
		ArmTipHide();

	event.Skip();
}
void ctlTree::OnChar(wxKeyEvent &event)
{
	int keyCode = event.GetKeyCode();
	if ( !event.HasModifiers() &&
	        ((keyCode >= '0' && keyCode <= '9') ||
	         (keyCode >= 'a' && keyCode <= 'z') ||
	         (keyCode >= 'A' && keyCode <= 'Z')))
	{
		wxTreeItemId currItem = GetSelection();

		if (!currItem.IsOk())
			return;

		wxTreeItemId matchItem;
		wxTreeItemData* data = GetItemData(currItem);
		// Set the item colour
		if (data)
		{
			if (((pgObject*)data)->GetMetaType() == PGM_SERVER)
			{
				wxString prefix = m_findPrefix + (wxChar)keyCode;
				wxTreeItemId id= GetNextSibling(currItem);
				while (id.IsOk() &&
					((GetItemText(id) == wxT("Dummy") && !GetItemData(id)) ||
						!((GetItemText(id).Lower().StartsWith(prefix))
							)
					))
				{
					id = GetNextSibling(id);
				}
				if (id.IsOk()) matchItem = id;
			} else
				matchItem = FindItem(currItem, m_findPrefix + (wxChar)keyCode);
		}

		

		if ( matchItem.IsOk() )
		{
			EnsureVisible(matchItem);
			SelectItem(matchItem);

			m_findPrefix += (wxChar)keyCode;

			// also start the timer to reset the current prefix if the user
			// doesn't press any more alnum keys soon -- we wouldn't want
			// to use this prefix for a new item search
			if ( !m_findTimer )
			{
				m_findTimer = new ctlTreeFindTimer(this);
			}

			m_findTimer->Start(ctlTreeFindTimer::CTLTREE_DELAY, wxTIMER_ONE_SHOT);
			return;
		}
	}
	else
	{
		bool directionup;
		if (event.ControlDown()) 
			{
				wxTreeItemId serverId;
				if (keyCode==WXK_UP) {
					directionup=true;
					serverId=GetSelection();
				} else if (keyCode==WXK_DOWN) {
					directionup=false;
					serverId=GetSelection();
				}
				if (serverId.IsOk()) {
					wxTreeItemId currid=serverId;
					wxTreeItemData* data = GetItemData(currid);
					while (data && (((pgObject*)data)->GetMetaType() != PGM_SERVER)) {
						currid=GetItemParent(currid);
						if (currid.IsOk()) {
							data = GetItemData(currid);
						} else return;
					}
					int closeIconId=serverFactory.GetClosedIconId();
					wxTreeItemIdValue groupcookie;
					wxTreeItemId groupitem;
					std::vector<wxTreeItemId> openservers;
					// Count number of servers and groups
					groupitem = GetFirstChild(GetRootItem(), groupcookie);
					int idx=-1,delta=0;
					while (groupitem)
					{
						wxTreeItemId nId;
						wxTreeItemIdValue groupcookie2;
						nId = GetFirstChild(groupitem, groupcookie2);
						while (nId) {
							if (GetItemImage(nId)!=closeIconId) {
								openservers.push_back(nId);
								if (nId==currid) delta=-1;
							}
							if (nId==currid && directionup) idx=delta+openservers.size()-1;
							if (nId==currid && !directionup) idx=openservers.size();
							nId=GetNextChild(groupitem, groupcookie2);
						}
						groupitem =GetNextChild(GetRootItem(), groupcookie);
					}
					if (openservers.size()>0) {
						if (idx>=0 && idx<openservers.size()) {
							currid=openservers[idx];
							SelectItem(currid);
							EnsureVisible(currid);
						}
					}
					return;
				}
			}
			event.Skip(true);
	}
}

ctlTree::ctlTree(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style)
	: wxTreeCtrl(parent, id, pos, size, style), m_findTimer(NULL), m_ancestorTip(NULL)
{
	isJumpRoot = settings->GetJumpRoot();
	m_tipHideTimer.SetOwner(this);
	Bind(wxEVT_TIMER, [this](wxTimerEvent&)
	{
		if (!PointerInTipHot())
			HideAncestorTip();
	}, m_tipHideTimer.GetId());
}

ctlTree::~ctlTree()
{
	if ( m_findTimer )
		delete m_findTimer;
	m_findTimer = NULL;
	if (m_tipHideTimer.IsRunning())
		m_tipHideTimer.Stop();
	if (m_ancestorTip)
	{
		m_ancestorTip->Destroy();
		m_ancestorTip = NULL;
	}
}


void ctlTree::RemoveDummyChild(pgObject *obj)
{
	wxCookieType cookie;
	wxTreeItemId childItem = GetFirstChild(obj->GetId(), cookie);
	if (childItem && !GetItemData(childItem))
	{
		// The child was a dummy item, which will be replaced by the following ShowTreeDetail by true items
		Delete(childItem);
	}
}


pgObject *ctlTree::GetObject(wxTreeItemId id)
{
	if (id)
		return (pgObject *)GetItemData(id);
	return 0;
}


pgCollection *ctlTree::GetParentCollection(wxTreeItemId id)
{
	pgCollection *coll = (pgCollection *)GetParentObject(id);
	if (coll && coll->IsCollection())
		return coll;
	return 0;
}


void ctlTree::SetItemImage(const wxTreeItemId &item, int image, wxTreeItemIcon which)
{
	wxTreeCtrl::SetItemImage(item, image, which);

	wxTreeItemData *data = GetItemData(item);

	// Set the item colour
	if (data)
	{
		if (((pgObject *)data)->GetMetaType() == PGM_SERVER)
		{
			if (!((pgServer *)data)->GetColour().IsEmpty())
				SetItemBackgroundColour(item, wxColour(((pgServer *)data)->GetColour()));
		}
		else if (((pgObject *)data)->GetServer())
		{
			if (!((pgObject *)data)->GetServer()->GetColour().IsEmpty())
				SetItemBackgroundColour(item, wxColour(((pgObject *)data)->GetServer()->GetColour()));
		}
	}
}

wxTreeItemId ctlTree::AppendItem(const wxTreeItemId &parent, const wxString &text, int image, int selImage, wxTreeItemData *data)
{
	wxTreeItemId itm = wxTreeCtrl::AppendItem(parent, text, image, selImage, data);

	// Set the item colour
	if (data)
	{
		if (((pgObject *)data)->GetMetaType() == PGM_SERVER)
		{
			if (!((pgServer *)data)->GetColour().IsEmpty())
				SetItemBackgroundColour(itm, wxColour(((pgServer *)data)->GetColour()));
		}
		else if (((pgObject *)data)->GetServer())
		{
			if (!((pgObject *)data)->GetServer()->GetColour().IsEmpty())
				SetItemBackgroundColour(itm, wxColour(((pgObject *)data)->GetServer()->GetColour()));
		}
	}

	return itm;
}

wxTreeItemId ctlTree::AppendObject(pgObject *parent, pgObject *object)
{
	wxString label;
	wxTreeItemId item;

	if (object->IsCollection())
		label = object->GetTypeName();
	else
		label = object->GetDisplayName();
	item = AppendItem(parent->GetId(), label, object->GetIconId(), -1, object);
	if (object->IsCollection())
		object->ShowTreeDetail(this);
	else if (object->WantDummyChild())
		AppendItem(object->GetId(), wxT("Dummy"));

	return item;
}


pgCollection *ctlTree::AppendCollection(pgObject *parent, pgaFactory &factory)
{
	pgCollection *collection = factory.CreateCollection(parent);
	AppendObject(parent, collection);
	return collection;
}


pgObject *ctlTree::FindObject(pgaFactory &factory, wxTreeItemId parent)
{
	wxCookieType cookie;
	wxTreeItemId item = GetFirstChild(parent, cookie);
	while (item)
	{
		pgObject *obj = (pgObject *)GetItemData(item);
		if (obj && obj->IsCreatedBy(factory))
			return obj;
		item = GetNextChild(parent, cookie);
	}
	return 0;
}


pgCollection *ctlTree::FindCollection(pgaFactory &factory, wxTreeItemId parent)
{
	pgaFactory *cf = factory.GetCollectionFactory();
	if (!cf)
		return 0;

	pgCollection *collection = (pgCollection *)FindObject(*cf, parent);

	if (!collection || !collection->IsCollection())
		return 0;
	return collection;
}


void ctlTree::NavigateTree(int keyCode)
{
	switch(keyCode)
	{
		case WXK_LEFT:
		{
			//If tree item has children and is expanded, collapse it, otherwise select it's parent if has one
			wxTreeItemId currItem = GetSelection();

			if (ItemHasChildren(currItem) && IsExpanded(currItem))
			{
				Collapse(currItem);
			}
			else
			{
				wxTreeItemId parent = GetItemParent(currItem);
				if (parent.IsOk())
				{
					SelectItem(currItem, false);
					SelectItem(parent, true);
				}
			}
		}
		break;
		case WXK_RIGHT:
		{
			//If tree item do not have any children ignore it,
			//otherwise  expand it if not expanded, and select first child if already expanded
			wxTreeItemId currItem = GetSelection();

			if(ItemHasChildren(currItem))
			{
				if (!IsExpanded(currItem))
				{
					Expand(currItem);
				}
				else
				{
					wxCookieType cookie;
					wxTreeItemId firstChild = GetFirstChild(currItem, cookie);
					SelectItem(currItem, false);
					SelectItem(firstChild, true);
				}
			}
		}
		break;
		default:
			wxASSERT_MSG(false, _("Currently handles only right and left arrow key, other keys are working"));
			break;
	}
}

//////////////////////

treeObjectIterator::treeObjectIterator(ctlTree *brow, pgObject *obj)
{
	browser = brow;
	object = obj;
}


pgObject *treeObjectIterator::GetNextObject()
{
	if (!object || !browser)
		return 0;

	if (!lastItem)
		lastItem = browser->GetFirstChild(object->GetId(), cookie);
	else
		lastItem = browser->GetNextChild(object->GetId(), cookie);

	if (lastItem)
		return browser->GetObject(lastItem);
	else
		object = 0;

	return 0;
}
