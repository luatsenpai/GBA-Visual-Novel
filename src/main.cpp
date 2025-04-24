#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_font.h"
#include "bn_sprite_ptr.h"
#include "common_variable_8x16_sprite_font.h"
#include "bn_regular_bg_items_title.h"
#include "bn_string.h"
#include "opening.h"

int main()
{

    bn::core::init();

    // Initialize text generator with the included font
    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);

    // Load title background
    bn::regular_bg_ptr title_bg = bn::regular_bg_items::title.create_bg(0, 0);

    // Display "Press Start" text
    bn::vector<bn::sprite_ptr, 32> text_sprites;
    text_generator.set_center_alignment();
    text_generator.generate(80, 50, "Press Start", text_sprites);

    while(true)
    {
        if(bn::keypad::start_pressed())
        {
            text_sprites.clear();
            title_bg.set_visible(false);
            break;
        }
        bn::core::update();
    }

    // Transition to opening scene
    vn::OpeningScene opening_scene;
    opening_scene.run();

    // Main loop (keeps the game running after scene ends)
    while(true)
    {
        bn::core::update();
    }

}