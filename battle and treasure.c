#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define H 15
#define W 20

#define PLAYER '@'
#define ENEMY 'X'
#define TREASURE 'T'
#define EMPTY '.'
#define BANDAGE 'B'   // 🩹
#define HEALTH 'H'    // H

// Fight function: returns 1 if player survives
int fight(int *playerHP) {
    int enemyHP = rand() % 30 + 40;  // Enemy HP 40-70
    int enemyWeapon = rand() % 20 + 10; // Enemy damage 10-29

    printf("\n⚔️ ENEMY ENCOUNTER! Enemy HP: %d\n", enemyHP);

    while(enemyHP > 0 && *playerHP > 0) {
        int choice;
        printf("\nChoose weapon:\n1) Sword (35 dmg)\n2) Axe (45 dmg, 50%% hit)\n3) Dagger (25 dmg)\n> ");
        scanf("%d",&choice);

        int playerDmg = 0;
        if(choice==1) playerDmg = 35;
        else if(choice==2) {
            int hit = rand() % 100;
            if(hit < 50) playerDmg = 45;
            else playerDmg = 0;
        }
        else playerDmg = 25;

        enemyHP -= playerDmg;
        printf("You hit the enemy for %d damage! Enemy HP: %d\n", playerDmg, (enemyHP>0?enemyHP:0));

        if(enemyHP <= 0) break;

        int enemyDmg = rand() % enemyWeapon + 1;
        *playerHP -= enemyDmg;
        printf("Enemy hits you for %d damage! Your HP: %d\n", enemyDmg, (*playerHP>0?*playerHP:0));
    }

    return (*playerHP > 0);
}

void giveTreasureReward() {
    printf("\n============== TREASURE CHEST ==============\n");

    int r = rand() % 7; // 7 random treasures

    switch(r) {
        case 0: // Sword
            printf("🎁 Sword\n");
            printf("  🗡️\n");
            break;
        case 1: // Magic Wand
            printf("🎁 Magic Wand\n");
            printf("  ✨\n");
            break;
        case 2: // Gem
            printf("🎁 Shiny Gem\n");
            printf("  💎\n");
            break;
        case 3: // Shield
            printf("🎁 Shield\n");
            printf("  🛡️\n");
            break;
        case 4: // Cute Pet
            printf("🎁 Cute Pet Companion\n");
            printf("  (\\_/)\n");
            printf("  (•_•)\n");
            printf("  / >🎁\n");
            break;
        case 5: // Treasure Pile
        {
            printf("🎁 Treasure Pile\n");
            char *items[] = {"💰","💎","🪙","🗡️","🛡️","⛑️","🪖"}; // emoji options
            printf("  [");
            for(int i=0;i<3;i++) {
                printf("%s", items[rand()%7]);
                if(i<2) printf("][");
            }
            printf("]\n");
            printf("  [");
            for(int i=0;i<3;i++) {
                printf("%s", items[rand()%7]);
                if(i<2) printf("][");
            }
            printf("]\n");
            break;
        }
        case 6: // Wizard Level-Up
            printf("🧙 The Wizard is thinking...\n");
            printf("✨ He grants you a LEVEL UP!! ✨\n");
            break;
    }

    // Wizard message for all treasures except direct level-up
    if(r != 6) {
        printf("🧙 The Wizard says: 'May this gift aid you in your quest!'\n");
    }

    printf("============================================\n");
}

void draw(char field[H][W], int hp, int enemies) {
    printf("\nHP: %d | Enemies: %d\n\n", hp, enemies);
    printf("+");
    for(int i = 0; i < W * 2; i++) printf("-");
    printf("+\n");
    for(int i = 0; i < H; i++) {
        printf("|");
        for(int j = 0; j < W; j++) {
            if(field[i][j] == PLAYER) printf("🗡️");
            else if(field[i][j] == ENEMY) printf("🔴");
            else if(field[i][j] == TREASURE) printf("🪎");
            else if(field[i][j] == BANDAGE) printf("🩹");
            else if(field[i][j] == HEALTH) printf("H");
            else printf(" .");
        }
        printf(" |\n");
    }
    printf("+");
    for(int i = 0; i < W * 2; i++) printf("-");
    printf("+\n");
}

int main() {
    char field[H][W];
    int px = 0, py = 0;
    int hp = 100;
    int enemies = 5;
    int bandages = 2;
    int healthPacks = 2;

    srand(time(NULL));

    // Legend / instructions
    printf("===== GAME LEGEND & TIPS =====\n");
    printf("🗡️ : Player (YOU)\n");
    printf("🔴 : Enemy\n");
    printf("🪎 : Treasure (Goal)\n");
    printf("🩹 : Bandaid (heal 4-5 HP)\n");
    printf("H  : Health pack (heal 6-9 HP)\n");
    printf(".  : Empty space\n");
    printf("\nTIP: If your HP is low, you can roam to collect bandaids or health packs before fighting enemies.\n");
    printf("You can move step by step or enter multiple moves at once.\n");
    printf("================================\n\n");

    // Initialize empty field
    for(int i=0;i<H;i++)
        for(int j=0;j<W;j++)
            field[i][j] = EMPTY;

    field[py][px] = PLAYER;

    // Random enemy placement
    for(int i=0;i<enemies;i++) {
        int ex, ey;
        do {
            ex = rand() % W;
            ey = rand() % H;
        } while(field[ey][ex] != EMPTY || (ex==0 && ey==0));
        field[ey][ex] = ENEMY;
    }

    // Random bandages
    for(int i=0;i<bandages;i++) {
        int bx, by;
        do {
            bx = rand() % W;
            by = rand() % H;
        } while(field[by][bx] != EMPTY);
        field[by][bx] = BANDAGE;
    }

    // Random health packs
    for(int i=0;i<healthPacks;i++) {
        int hx, hy;
        do {
            hx = rand() % W;
            hy = rand() % H;
        } while(field[hy][hx] != EMPTY);
        field[hy][hx] = HEALTH;
    }

    // Main loop
    while(hp > 0) {
        draw(field, hp, enemies);

        if(enemies == 0 && px == W-1 && py == H-1) {
            printf("\nYOU FOUND THE TREASURE!\n");
            giveTreasureReward();
            return 0;
        }

        printf("\nMove (W A S D, can enter multiple letters for multi-step): ");
        char moveInput[100];
        scanf("%s", moveInput);
        int len = strlen(moveInput);
        int multiStep = (len > 1);

        for(int step=0; step<len; step++) {
            char m = moveInput[step];
            int nx = px, ny = py;

            if(m=='w'||m=='W') ny--;
            else if(m=='s'||m=='S') ny++;
            else if(m=='a'||m=='A') nx--;
            else if(m=='d'||m=='D') nx++;
            else continue;

            if(nx<0 || nx>=W || ny<0 || ny>=H) continue;

            // Pick up health items
            if(field[ny][nx] == BANDAGE) {
                int heal = rand() % 2 + 4; // 4-5 HP
                hp += heal;
                if(hp > 100) hp = 100;
                printf("You picked up a bandaid! +%d HP. Your HP: %d\n", heal, hp);
                field[ny][nx] = EMPTY;
            }
            if(field[ny][nx] == HEALTH) {
                int heal = rand() % 4 + 6; // 6-9 HP
                hp += heal;
                if(hp > 100) hp = 100;
                printf("You picked up a health pack! +%d HP. Your HP: %d\n", heal, hp);
                field[ny][nx] = EMPTY;
            }

            if(field[ny][nx] == ENEMY) {
                int survived = fight(&hp);
                if(!survived) {
                    printf("\nYOU DIED. GAME OVER\n");
                    return 0;
                }
                field[ny][nx] = EMPTY;
                enemies--;
            }

            field[py][px] = EMPTY;
            px = nx;
            py = ny;
            field[py][px] = PLAYER;

            if(enemies == 0)
                field[H-1][W-1] = TREASURE;

            if(!multiStep) draw(field, hp, enemies);
        }

        if(multiStep) draw(field, hp, enemies);
        if(hp <= 20 && hp > 10) printf("⚠ LOW HEALTH!\n");
        if(hp <= 10) printf("❗ CRITICAL HEALTH!\n");
    }

    printf("\nYOU DIED. GAME OVER\n");
    return 0;
}
