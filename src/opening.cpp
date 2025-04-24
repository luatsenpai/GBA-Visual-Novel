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
    bool showing_second_dialogue = false;
    bool showing_second_choices = false;
    int selected_choice = 0;

    // First dialogue sequence
    constexpr bn::string_view dialogue[] = {
        "Hello",
        "How are you?"
    };

    // First choices
    constexpr bn::string_view choices[] = {
        "I'm good",
        "I can't complain too much"
    };

    // Responses based on first choice
    constexpr bn::string_view responses[] = {
        "Really? Goodddd.",
        "Well? Not good."
    };

    // Second dialogue sequence
    constexpr bn::string_view second_dialogue[] = {
        "Where shall we go now?",
        "Would you like to go to the cinema",
        "or to the coffee shop?"
    };

    // Second choices
    constexpr bn::string_view second_choices[] = {
        "Cinema",
        "Coffee"
    };

    // Responses based on second choice
    constexpr bn::string_view second_responses[] = {
        "That's a good idea, so let's go",
        "watch Star Wars",
        "That's a good idea! So, let's go",
        "for a cappuccino"
    };

    // Display "Hello" immediately
    text_generator.generate(-100, 50, dialogue[0], text_sprites);
    text_index = 1;

    while(true)
    {
        if(!showing_choices && !showing_second_dialogue && !showing_second_choices)
        {
            if(text_index == 1 && bn::keypad::a_pressed())
            {
                // Clear previous text
                text_sprites.clear();

                // Display "How are you?"
                text_generator.generate(-100, 50, dialogue[1], text_sprites);
                text_index = 2;
            }
            else if(text_index == 2 && bn::keypad::a_pressed())
            {
                // Clear previous text
                text_sprites.clear();

                // Prepare to show first choices
                showing_choices = true;
                selected_choice = 0;
            }
        }
        else if(showing_choices && !showing_second_dialogue && !showing_second_choices)
        {
            // Handle first choice selection
            if(bn::keypad::up_pressed() && selected_choice > 0)
            {
                selected_choice--;
            }
            if(bn::keypad::down_pressed() && selected_choice < 1)
            {
                selected_choice++;
            }

            // Display first choices with cursor
            text_sprites.clear();
            for(int i = 0; i < 2; ++i)
            {
                bn::string<32> choice_text(i == selected_choice ? "> " : "  ");
                choice_text.append(choices[i]);
                text_generator.generate(-100, 50 + i * 16, choice_text, text_sprites);
            }

            // Confirm first choice
            if(bn::keypad::a_pressed())
            {
                // Clear choices
                text_sprites.clear();

                // Display response based on first choice
                text_generator.generate(-100, 50, responses[selected_choice], text_sprites);
                bn::core::update();

                // Move to second dialogue
                showing_choices = false;
                showing_second_dialogue = true;
                text_index = 0; // Reset for second dialogue
            }
        }
        else if(showing_second_dialogue && !showing_second_choices)
        {
            if(text_index == 0 && bn::keypad::a_pressed())
            {
                // Clear previous text
                text_sprites.clear();

                // Display "Where shall we go now?"
                text_generator.generate(-100, 50, second_dialogue[0], text_sprites);
                text_index = 1;
            }
            else if(text_index == 1 && bn::keypad::a_pressed())
            {
                // Clear previous text
                text_sprites.clear();

                // Display "Would you like to go to the cinema" and "or to the coffee shop?"
                text_generator.generate(-100, 50, second_dialogue[1], text_sprites);
                text_generator.generate(-100, 66, second_dialogue[2], text_sprites);
                text_index = 2;
            }
            else if(text_index == 2 && bn::keypad::a_pressed())
            {
                // Clear previous text
                text_sprites.clear();

                // Prepare to show second choices
                showing_second_dialogue = false;
                showing_second_choices = true;
                selected_choice = 0;
            }
        }
        else if(showing_second_choices)
        {
            // Handle second choice selection
            if(bn::keypad::up_pressed() && selected_choice > 0)
            {
                selected_choice--;
            }
            if(bn::keypad::down_pressed() && selected_choice < 1)
            {
                selected_choice++;
            }

            // Display second choices with cursor
            text_sprites.clear();
            for(int i = 0; i < 2; ++i)
            {
                bn::string<32> choice_text(i == selected_choice ? "> " : "  ");
                choice_text.append(second_choices[i]);
                text_generator.generate(-100, 50 + i * 16, choice_text, text_sprites);
            }

            // Confirm second choice
            if(bn::keypad::a_pressed())
            {
                // Clear choices
                text_sprites.clear();

                // Display response based on second choice (two lines)
                text_generator.generate(-100, 50, second_responses[selected_choice * 2], text_sprites);
                text_generator.generate(-100, 66, second_responses[selected_choice * 2 + 1], text_sprites);
                bn::core::update();

                // Wait for A press to exit
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