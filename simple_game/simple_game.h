#pragma once

#define PLAYER_HEALTH 100
#define ENEMY_HEALTH 1000
#define MAX_AMMO 12
#define AMMO_DAMAGE 20

class Entity {
private:
    bool is_player;
    int health;
    int ammo = MAX_AMMO;
    bool alive = true;

public:
    bool is_dodging = false;

    explicit Entity(const bool _is_player = false) {
        is_player = _is_player;
        if (is_player) {
            health = PLAYER_HEALTH;
        } else {
            health = ENEMY_HEALTH;
        }
    }

    void shoot_at_Entity(Entity *e) {
        if (ammo > 0) {
            ammo--;
            e->take_damage(AMMO_DAMAGE);
        }
    }

    void reload() { ammo = 12; }

    void take_damage(const int damage) {
        if (is_dodging) {
            return;
        }
        if (damage >= health) {
            health = 0;
        } else {
            health -= damage;
        }
        if (!health) {
            alive = false;
        }
    }

    [[nodiscard]] int get_ammo() const { return ammo; }

    [[nodiscard]] bool is_alive() const { return alive; }

    void print_status() const {
        printf(is_player ? "Player: " : "Boss: ");
        printf("health=%d ammo=%d\n", health, ammo);
    }

    void print_memory() {
        printf(is_player ? "Player:\n" : "Boss:\n");
        printf("health: %p\n", &health);
        printf("ammo: %p\n", &ammo);
        printf("\n");
    }
};
