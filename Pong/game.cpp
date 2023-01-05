
#include "utils.h"
#include "renderer.h"
#include "game.h"



/*** Variables ***/
internal float ddp = 1500.0f, friction = 10.f, start_dpx = 130;

internal int player1_score, player2_score;

// Half sizes
internal const float arena_hsx = 85, arena_hsy = 45;
internal const float player_hsx = 2.5f, player_hsy = 12;


enum Gamemode {
	GM_MENU,
	GM_GAMEPLAY,
};
internal Gamemode current_gamemode;
internal int hot_button;
internal bool enemy_is_ai;


/*** Structs ***/
typedef struct {
	float px, py, dp, ddp;
	float hsx, hsy;
} Player;
struct Ball {
	float px, py, dpx, dpy;
	float hs;
};


/*** Objects ***/
internal Player player1 = { -80, 0, 0, 0, player_hsx, player_hsy };
internal Player player2 = { 80, 0, 0, 0, player_hsx, player_hsy };
internal Ball ball = { 0, 0, start_dpx, 0, 1 };



/*** Functions ***/
internal void simulate_player(Player* player, float dt) {
	player->ddp -= player->dp * friction;
	player->dp += player->ddp * dt;
	player->py += player->dp * dt + player->ddp * dt * dt / 2.f;

	if (player->py + player->hsy > arena_hsy - 1) {
		player->py = arena_hsy - player->hsy - 1;
		player->dp = 0;
	}
	else if (player->py - player->hsy < -arena_hsy + 1) {
		player->py = -arena_hsy + player->hsy + 1;
		player->dp = 0;
	}
}

internal bool aabb_vs_aabb(Ball ball, Player player) {
	// AABB - Axis Aligned Bounding Box
	return (ball.px + ball.hs > player.px - player.hsx &&
		ball.px - ball.hs < player.px + player.hsx &&
		ball.py + ball.hs > player.py - player.hsy &&
		ball.py + ball.hs < player.py + player.hsy);
}




void simulate_game(Input* input, float dt) {
	clear_screen(0xffaa33);
	draw_arena_borders(arena_hsx, arena_hsy, 0xff5500);

	// Gameplay
	if (current_gamemode == GM_GAMEPLAY) {
		draw_arena_borders(arena_hsx, arena_hsy);
		draw_rect(0, 0, arena_hsx, arena_hsy, 0xffaa33);

		// Simulate Players
		{
			player1.ddp = 0.f; // units per second
			if (is_down(BUTTON_W)) player1.ddp += ddp;
			if (is_down(BUTTON_S)) player1.ddp -= ddp;

			player2.ddp = 0.f; // units per second
			if (!enemy_is_ai) {
				if (is_down(BUTTON_UP)) player2.ddp += ddp;
				if (is_down(BUTTON_DOWN)) player2.ddp -= ddp;
			}
			else {
				if (ball.py > player2.py + 2.f) player2.ddp += ddp;
				if (ball.py < player2.py - 2.f) player2.ddp -= ddp;
			}


			simulate_player(&player1, dt);
			simulate_player(&player2, dt);
		}

		// Simulate Ball
		{
			ball.px += ball.dpx * dt;
			ball.py += ball.dpy * dt;

			// Player colisions
			{
				if (aabb_vs_aabb(ball, player1)) {
					ball.px = player1.px + player_hsx + ball.hs;
					ball.dpx *= -1.02f;
					ball.dpy += player1.dp / 3.f;
				}
				else if (aabb_vs_aabb(ball, player2)) {
					ball.px = player2.px - player_hsx - ball.hs;
					ball.dpx *= -1.02f;
					ball.dpy += player2.dp / 3.f;
				}
			}

			// Top and bottom colisions
			{
				if (ball.py + ball.hs > arena_hsy) {
					ball.py = arena_hsy - ball.hs;
					ball.dpy *= -1;
				}
				else if (ball.py - ball.hs < -arena_hsy) {
					ball.py = -arena_hsy + ball.hs;
					ball.dpy *= -1;
				}
			}

			// Left and right colisions
			{
				if (ball.px + ball.hs > arena_hsx) {
					ball.dpx *= -130 / ball.dpx;
					ball.dpy = 0;
					ball.px = 0;
					ball.py = 0;
					player1_score++;
				}
				else if (ball.px - ball.hs < -arena_hsx) {
					ball.dpx *= -130 / ball.dpx;
					ball.dpx *= -1;
					ball.dpy = 0;
					ball.px = 0;
					ball.py = 0;
					player2_score++;
				}
			}
		}

		// Rendering
		{
			draw_number(player1_score, -10, 40, 1.f, 0xbbffbb);
			draw_number(player2_score, 10, 40, 1.f, 0xbbffbb);

			draw_rect(ball.px, ball.py, ball.hs, ball.hs, 0xffffff);

			draw_rect(player1.px, player1.py, player_hsx, player_hsy, 0xff0000);
			draw_rect(player2.px, player2.py, player_hsx, player_hsy, 0xff0000);
		}
	}
	// Menu
	else {
		// Button Handling
		{
			if (pressed(BUTTON_LEFT) || pressed(BUTTON_RIGHT)) {
				hot_button = !hot_button;
			}

			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_GAMEPLAY;
				enemy_is_ai = hot_button ? 0 : 1;
			}
		}

		// Text Rendering
		{
			// Single Player
			if (hot_button == 0) {
				draw_text("SINGLE PLAYER", -80, -10, 1.1f, 0xff0000);
				draw_text("MULTIPLAYER", 20, -10, 1, 0xaaaaaa);
			}
			//Multiplayer
			else {
				draw_text("SINGLE PLAYER", -80, -10, 1, 0xaaaaaa);
				draw_text("MULTIPLAYER", 14, -10, 1.1f, 0xff0000);
			}

			draw_text("PONG", -25, 35, 2.5, 0xffffff);
		}
	}
}
