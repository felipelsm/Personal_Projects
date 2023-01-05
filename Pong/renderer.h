#pragma once

#include "utils.h"



void clear_screen(u32 color);

void draw_rect(float x, float y, float hsx, float hsy, u32 color);

void draw_arena_borders(float arena_x, float arena_y, u32 color);
void draw_arena_borders(float arena_x, float arena_y);

void draw_text(const char* text, float x, float y, float size, u32 color);
void draw_number(int num, float x, float y, float size, u32 color);