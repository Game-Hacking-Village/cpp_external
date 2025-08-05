#include <cstdio>
#include <string>
#include <windows.h>

#include "simple_game.h"

void win() {
    printf("You won!\n");
    system("pause");
    exit(0);
}

char print_menu_get_selection() {
    const auto actions = "sdrq_";
    char input = 1;
    do {
        printf("s: Shoot Enemy\n");
        printf("d: Dodge\n");
        printf("r: Reload\n");
        printf("_: Print Memory\n");
        printf("q: Quit \n");
        scanf("%c", &input);

        // clear stdin
        char clear_buf[256];
        fgets(clear_buf, sizeof(clear_buf), stdin);
    } while (!strchr(actions, input));


    return input;
}

int main(int argc, char *argv[]) {
    printf("Defeat the Boss to win!\n");

    Entity player(true);
    Entity enemy{};

    enemy.print_status();
    player.print_status();

    while (player.is_alive()) {
        // reset dodge
        player.is_dodging = false;

        // get player selection
        switch (print_menu_get_selection()) {
            case 's': // shoot
                player.shoot_at_Entity(&enemy);
                break;
            case '_':
                enemy.print_memory();
                player.print_memory();
            case 'd': // dodge
                player.is_dodging = true;
                break;
            case 'r': // reload
                player.reload();
			case 'q':
        		return 0;
        default:
                break;
        }

        // enemy will always shoot player or reload
        if (!enemy.get_ammo()) {
            enemy.reload();
        } else {
            enemy.shoot_at_Entity(&player);
        }

        // print result
        printf("---Game Status---\n");
        enemy.print_status();
        player.print_status();

        // check win
        if (!enemy.is_alive()) {
            win();
        }
    }

    printf("You died :(\n");

    system("pause");
    return 1;
}
