
#ifndef FUNCTIONPGHELPER_H
#define FUNCTIONPGHELPER_H
#include <utils/sysSettings.h>
#include <wx/regex.h>
#include <map>
#include <vector>
class pgConn;
struct anchor_src { int start ;int end; wxString id;};
class FunctionPGHelper
{
public:
    FunctionPGHelper() {dblast=NULL;};
    /// <summary>
    /// Build only the HTML passed to the constructor, under the name "content"
    /// </summary>
    /// <param name="content"></param>
    FunctionPGHelper(const wxString& content) {
        body.clear();
        Add("content", content);
        isload = true;
        dblast=NULL;
    };
    int Size() {
        return body.size();
    }
    void SetTimerClose(int ms) { m_interval = ms; }
    int GetTimerClose() { return m_interval; }
    void Add(const wxString& key, const wxString& v) { body.emplace(key, v); }
    wxString getHelpString(wxString fnd, bool isPart = true) ;
    // Load the file and build the anchors
    wxString getHelpFile(wxString filename);
    
    bool isValid();
    void setDbConn(pgConn *db);
    // Look up the keyword in database objects
    wxString getDBinfoKeyword(wxString objname,bool islower);
    // Look up help files for SQL commands
    wxString getSqlCommandHelp(wxString fnd);
    // text for an anchor
    wxString getTextForAnchor(wxString filename);
private:
    bool isload = false;
    int m_interval = -1;
    wxString path;
    std::map<wxString, wxString> body;
    // db connect
    pgConn *dblast;
    //
    std::vector<anchor_src> an;
    wxString filecontext;

    void loadfile();
};

#endif
