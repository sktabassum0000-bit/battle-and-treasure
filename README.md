# battle-and-treasure
A console adventure game where you move on a grid, fight enemies, and collect healing items to survive. Combat uses weapons with different damage and hit chances. After defeating all enemies, a treasure appears at the bottom-right corner, and reaching it wins the game.
✔ C Concepts Used

Arrays: The game grid is stored as a 2D array (field[H][W]).

Functions: Separate functions for drawing, fighting, and treasure rewards.

Control structures: Loops, switch-case, if/else for gameplay logic.

Pointers: Player HP is passed by pointer to modify it inside fight().

Randomization: rand() and srand() for enemy stats and item effects.

Character & string handling: Movement input, symbols for the map.

✔ Why Make This Code

To practice core C programming concepts through a fun project.

To build a simple interactive grid-based game.

To learn handling user input, random events, and combat mechanics.

To explore basic game loops and terminal graphics using ASCII/emoji.

✔ Goal of the Code

The objective is to move the player across the grid, survive enemy battles, collect healing items, and reach the treasure.

The player wins by defeating all enemies and reaching the treasure at the bottom-right.

✔ How to Compile

Open a terminal and run:

gcc battle and treasure.c -o battel and treasure


Then run it:

./battel and treasure


(On Windows MinGW)

gcc battel and treasure.c -o battel and treasure.exe
battel and treasure.exe

✔ Important Notes

Emoji output may look different depending on your terminal.

Movement accepts multiple characters at once (e.g., "wwasd").

HP is capped at 100 after healing.

Random elements mean each run is different (enemy positions, items, damage).

Player dies if HP reaches 0 during combat.
