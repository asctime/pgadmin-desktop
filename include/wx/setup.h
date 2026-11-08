/* Local override. The installed wx 3.2 setup enables std::string conversions,
   which removes wxString's implicit conversion to const wxChar*. This tree
   passes wxString to const wxChar* APIs. The conversion operators are inline,
   so this does not change the wx DLL layout. */
#ifndef PGADMIN_WX_SETUP_WRAPPER
#define PGADMIN_WX_SETUP_WRAPPER
#include_next "wx/setup.h"
#undef wxUSE_STD_STRING_CONV_IN_WXSTRING
#define wxUSE_STD_STRING_CONV_IN_WXSTRING 0
#endif
