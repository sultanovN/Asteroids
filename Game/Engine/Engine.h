#pragma once

#include <stdint.h>
#include "Surface.h"
#include "../Entity/Entity.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

#ifndef VK_ESCAPE
#  define VK_ESCAPE 0x1B
#  define VK_SPACE  0x20
#  define VK_LEFT   0x25
#  define VK_UP     0x26
#  define VK_RIGHT  0x27
#  define VK_DOWN   0x28
#  define VK_RETURN 0x0D
#define VK_A 0x41 //65
#define VK_D 0x44 //68

#endif

// backbuffer
extern uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

void PixelDraw(int x, int y, uint32_t Color);
void DrawRectangle(float LocationX, float LocationY, float SizeX, float SizeY, uint32_t Color);

void DrawSprite(int x, int y, const Surface& s, Color Chroma);

void DrawSprite(int x, int y, const Entity& ent, const Surface& s, Color Chroma);

void DrawSprite(int x, int y, Entity ent, const Entity& clip, const Surface& s, Color Chroma);

void DrawSpriteNonChroma(int x, int y, const Surface& s);

void DrawSpriteNonChroma(int x, int y, const Entity& ent, const Surface& s);

bool is_window_active();

// VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, 'A', 'B' ...
bool is_key_pressed(int button_vk_code);

// 0 - left button, 1 - right button
bool is_mouse_button_pressed(int button);

int get_cursor_x();
int get_cursor_y();

void clear_buffer();

void initialize();
void finalize();

void act(float dt);
void draw();

void schedule_quit_game();

