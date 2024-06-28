#ifndef UI_IMSI_HPP
#define UI_IMSI_HPP

#include "ui.hpp"
#include "ui_widget.hpp"
#include "ui_navigation.hpp"
#include "string_format.hpp"

namespace ui
{
    class IMSIView : public View
    {
    public:
        IMSIView(NavigationView& nav);
        std::string title() const override { return "IMSI APP"; };

        void focus() override;

    private:
        void update();                                            // Function declaration
        MessageHandlerRegistration message_handler_update{        // Example, not required: MessageHandlerRegistration class
            Message::ID::DisplayFrameSync,                        // relays messages to your app code from baseband. Every time you 
            [this](const Message *const) {                        // get a  DisplayFrameSync message the update() function will
                this->update();                                   // be triggered.  
            }};

        NavigationView& nav_;

    // Dichiarazione di button_widget
    Button button_widget{
        {10, 10, 100, 24}, // Coordinates are: int:x (px), int:y (px), int:width (px), int:height (px)
        "Search"};
    };
} 

#endif // UI_IMSI_HPP