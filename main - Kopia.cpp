#include <stdio.h>
#include <allegro5\allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5\keyboard.h>
#include <allegro5\keycodes.h>

int main()
{
	al_init();
	al_init_ttf_addon();
	al_init_font_addon();
	al_init_primitives_addon();
	//al_init_keyboard_addon();
	//al_init_keycodes_addon();

	ALLEGRO_DISPLAY* display = al_create_display(640, 480);
	ALLEGRO_COLOR DarkBlue = al_map_rgb(0, 0, 100);
	ALLEGRO_COLOR White = al_map_rgb(255, 255, 255);

	//ALLEGRO_FONT* font = al_create_builtin_font();
	ALLEGRO_FONT* font = al_load_ttf_font("C:\\Windows\\Fonts\\bauhs93.ttf", 22, 0);


	enum MYKEYS {
		KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE
	};

	

	float x1 = 300, x2 = 340, y1 = 220, y2 = 260;
	float velx = 0.02, vely = 0.02;

	bool loop = true;

	while (loop)
	{
		al_clear_to_color(DarkBlue);
		al_draw_text(font, al_map_rgb(0, 255, 0), 400, 100, ALLEGRO_ALIGN_CENTER, "Nacisnij spacje, zeby zakonczyc.");
		al_draw_filled_rectangle(x1, y1, x2, y2, White);
		al_flip_display();
		if ((x2 > 640 || x1 < 0))
		{
			velx = -velx;
		}
		if (y2 > 480 || y1 < 0)
		{
			vely = -vely;
		}
		x1 += velx;
		x2 += velx;
		y1 += vely;
		y2 += vely;

		//if (al_key_down())

	}

	al_rest(3.0);

	return 0;
}