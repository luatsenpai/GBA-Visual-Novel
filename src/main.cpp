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

    bn::regular_bg_ptr title_bg = bn::regular_bg_items::title.create_bg(0, 0);
    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
    text_generator.set_center_alignment();

    bn::vector<bn::sprite_ptr, 32> text_sprites;
    text_generator.generate(80, 50, "Press START", text_sprites);

    while(true) {
        
        if(bn::keypad::start_pressed()) {
            break;
        }
bn::core::update();
    }
    title_bg.set_visible(false);
    for(auto& s : text_sprites) s.set_visible(false);

    run_opening();

    return 0;
    


}