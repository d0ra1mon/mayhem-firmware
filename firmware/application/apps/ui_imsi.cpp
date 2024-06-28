#include "ui_imsi.hpp"
#include "optional.hpp"
#include "portapack.hpp"
#include <cstring>

using namespace portapack;

namespace ui
{
    // Definizione di button_widget
    Button button_widget(
       {10, 10, 100, 24}, // Coordinates are: int:x (px), int:y (px), int:width (px), int:height (px)
       "Search"
    );

    IMSIAppView::IMSIAppView(NavigationView& nav): nav_{nav} // Application Main
    {
        add_child(&button_widget);
    }
}

