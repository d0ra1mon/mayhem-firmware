#include "ui_imsi.hpp"
#include "optional.hpp"
#include "portapack.hpp"
#include <cstring>

using namespace portapack;

namespace ui
{
    IMSIAppView::IMSIAppView(NavigationView& nav): nav_{nav} // Application Main
    {
        add_child(&button_widget);
    }

    void IMSIAppView::update()                   // Every time you get a DisplayFrameSync message this function will be ran
    {
         // Message code
    }

    void IMSIAppView::focus()                   // Every time you get a DisplayFrameSync message this function will be ran
    {
         button_widget.focus();
    }

}