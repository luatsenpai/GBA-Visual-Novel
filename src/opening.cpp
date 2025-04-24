

#include "opening.h"

namespace vn
{
    OpeningScene::OpeningScene() :
        bg(bn::regular_bg_items::bg1.create_bg(0, 0)),
        text_generator(common::variable_8x16_sprite_font),
        selected_choice(0)
    {
        text_generator.set_left_alignment();
    }

    void OpeningScene::display_text(const bn::string_view& text)
    {
        clear_text();
        text_generator.generate(-100, 50, text, text_sprites);
    }

    void OpeningScene::clear_text()
    {
        text_sprites.clear();
    }

    void OpeningScene::show_choices()
    {
        clear_text();
        text_generator.set_left_alignment();
        bn::string_view choices[] = {"I'm good", "I can't complain too much"};
        for(int i = 0; i < 2; ++i)
        {
            bn::string<32> choice_text;
            choice_text = i == selected_choice ? "> " : "  ";
            choice_text += choices[i];
            text_generator.generate(20, 100 + i * 20, choice_text, text_sprites);
        }
    }

    void OpeningScene::update_choices()
    {
        if(bn::keypad::up_pressed() && selected_choice > 0)
        {
            --selected_choice;
            show_choices();
        }
        else if(bn::keypad::down_pressed() && selected_choice < 1)
        {
            ++selected_choice;
            show_choices();
        }
    }

    void OpeningScene::run()
    {
        // Display "Hello"
        display_text("Hello");
        while(!bn::keypad::a_pressed())
        {
            bn::core::update();
        }
        bn::core::update(); // Debounce A press

        // Display "How are you?"
        display_text("How are you?");
        while(!bn::keypad::a_pressed())
        {
            bn::core::update();
        }
        bn::core::update(); // Debounce A press

        // Show choices
        show_choices();
        while(true)
        {
            update_choices();
            if(bn::keypad::a_pressed())
            {
                break;
            }
            bn::core::update();
        }
        bn::core::update(); // Debounce A press

        // Display response based on choice
        if(selected_choice == 0)
        {
            display_text("Really? Goodddd.");
        }
        else
        {
            display_text("Well? Not good.");
        }

        // Wait for final A press to end scene
        while(!bn::keypad::a_pressed())
        {
            bn::core::update();
        }
    }
}