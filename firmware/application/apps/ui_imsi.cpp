#include "ui_imsi.hpp"
#include "optional.hpp"
#include "portapack.hpp"
#include <cstring>

using namespace portapack;

namespace ui
{
    IMSIView::IMSIView(NavigationView& nav): nav_{nav} // Application Main
    {
        add_child(&button_widget);
    }

    void IMSIView::update()                   // Every time you get a DisplayFrameSync message this function will be ran
    {
         // Message code
    }

    void IMSIView::focus()                   // Every time you get a DisplayFrameSync message this function will be ran
    {
         button_widget.focus();
    }

} 