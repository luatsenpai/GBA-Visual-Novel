#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_string.h"
#include "bn_memory.h"
#include "bn_utility.h"
#include "bn_vector.h"
#include "bn_sprite_ptr.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_items_bg1.h"
#include "common_variable_8x16_sprite_font.h"
#include "bn_sprite_font.h"
#include "bn_fixed_point.h"
#include "bn_sprite_actions.h"
#ifndef OPENING_H
#define OPENING_H

namespace vn
{
    class OpeningScene
    {
    public:
        OpeningScene();
        void run();

    private:
        bn::regular_bg_ptr bg;
        bn::sprite_text_generator text_generator;
        bn::vector<bn::sprite_ptr, 32> text_sprites;
        int selected_choice;

        void display_text(const bn::string_view& text);
        void clear_text();
        void show_choices();
        void update_choices();
    };
}

#endif