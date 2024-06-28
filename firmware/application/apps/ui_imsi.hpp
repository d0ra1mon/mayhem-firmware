#ifndef UI_IMSI_HPP
#define UI_IMSI_HPP

#include "ui.hpp"
#include "ui_widget.hpp"
#include "ui_navigation.hpp"
#include "string_format.hpp"

namespace ui
{
    class IMSIAppView : public View
    {
    public:
        IMSIAppView(NavigationView& nav);
        std::string title() const override { return "IMSI APP"; };

    private:
        void update();
        NavigationView& nav_;
    };

    // Dichiarazione di button_widget
    extern Button button_widget;
} 

#endif // UI_IMSI_HPP
