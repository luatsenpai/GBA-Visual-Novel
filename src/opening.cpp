

#include "opening.h"
void run_opening()
{
        // Initialize text generator
    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
    text_generator.set_left_alignment();

        // Set up store background
    bn::regular_bg_ptr store_bg = bn::regular_bg_items::bg1.create_bg(0, 0);

        // Text display variables
    bn::vector<bn::sprite_ptr, 128> text_sprites;
    int text_index = 0;
    bool showing_choices = false;
    int selected_choice = 0;

        // Text sequence
    constexpr bn::string_view dialogue[] = {
        "Hello",
        "How are you?"
    };

        // Choices
    constexpr bn::string_view choices[] = {
        "I'm good",
        "I can't complain too much"
    };

        // Responses based on choice
    constexpr bn::string_view responses[] = {
        "Really? Goodddd.",
        "Well? Not good."
    };

    while(true)
    {
        if(!showing_choices)
        {
            if(text_index < 2 && bn::keypad::a_pressed())
            {
                    // Clear previous text
                text_sprites.clear();

                    // Display current dialogue
                text_generator.generate(10, 100, dialogue[text_index], text_sprites);
                text_index++;

                if(text_index == 2)
                {
                        // Prepare to show choices
                    showing_choices = true;
                    text_sprites.clear();
                    selected_choice = 0;
                }
            }
        }
        else
        {
                // Handle choice selection
            if(bn::keypad::up_pressed() && selected_choice > 0)
            {
                selected_choice--;
            }
			if(bn::keypad::down_pressed() && selected_choice < 1)
            {
                selected_choice++;
            }

                // Display choices with cursor
            text_sprites.clear();
            for(int i = 0; i < 2; ++i)
            {
                    // Construct choice text with appropriate prefix
                bn::string<32> choice_text(i == selected_choice ? "> " : "  ");
                choice_text.append(choices[i]);
                text_generator.generate(10, 100 + i * 16, choice_text, text_sprites);
            }

                // Confirm choice
            if(bn::keypad::a_pressed())
            {
                    // Clear choices
                text_sprites.clear();

                    // Display response based on choice
                text_generator.generate(10, 100, responses[selected_choice], text_sprites);

                    // Exit after showing response (for simplicity)
                while(!bn::keypad::a_pressed())
                {
                    bn::core::update();
                }
                break;
            }
        }

        bn::core::update();
    }
}
