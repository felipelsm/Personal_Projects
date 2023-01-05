#pragma once

#include "utils.h"
#include "platform_common.h"


// Macros
#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)



void simulate_game(Input* input, float dt);