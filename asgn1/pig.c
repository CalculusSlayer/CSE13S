#include "names.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Ask user how many players are playing.
    printf("How many players? ");
    char some_buffer[500];
    scanf("%s", some_buffer);
    int players = 0;
    if (atoi(some_buffer) >= 2 && atoi(some_buffer) <= 10) {
        players = atoi(some_buffer);
    } else {
        fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
        players = 2;
    }
    // Prompt user for a seed number.
    printf("Random seed: ");
    long long int seed = -1;
    scanf("%lli", &seed);
    if (!(seed >= 0 && seed <= UINT_MAX)) {
        seed = 2021;
        fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
    } else {
    }

    // Define the Position type and assign a numerical value to each of the positions.
    typedef enum { SIDE = 0, RAZORBACK = 10, TROTTER = 10, SNOUTER = 15, JOWLER = 5 } Position;

    // Make an array that connects the pig's positions and the random number generator.
    const Position pig[7] = {
        SIDE,
        SIDE,
        RAZORBACK,
        TROTTER,
        SNOUTER,
        JOWLER,
        JOWLER,
    };

    // Make an array to keep track of scores and initialize them all to zero.
    int scores[players];
    for (int count = 0; count < players; count++) {
        scores[count] = 0;
    }

    // Assign the seed number to the srand function to prepare for a replicable series of "random" numbers.
    srandom(seed);
    int player_turn = 0;
    int pig_roll = 0;
    bool exit = false;

    // Main part of the program where the code for actual game is.
    while (true) {
        printf("%s rolls the pig...", names[player_turn]);
        while (true) {
            // Limit the numbers generated to range from 0 to 6 inclusive.
            pig_roll = random() % 7;
            scores[player_turn] += pig[pig_roll];

            // Go to the next player's turn if pig rolls on its side.
            // Otherwise the current player's turn continues.
            if (pig_roll == 0 || pig_roll == 1) {
                printf(" pig lands on side\n");
                if (player_turn == players - 1) {
                    player_turn = 0;
                } else {
                    player_turn += 1;
                }
                break;
            } else if (pig_roll == 2) {
                printf(" pig lands on back");
            } else if (pig_roll == 3) {
                printf(" pig lands upright");
            } else if (pig_roll == 4) {
                printf(" pig lands on snout");
            } else if (pig_roll == 5 || pig_roll == 6) {
                printf(" pig lands on ear");
            }

            // Exit both while loops if player's score is 100 or higher.
            if (scores[player_turn] >= 100) {
                exit = true;
                break;
            }
        }

        // Will only break out of loop if a player has 100 or more points.
        // Otherwise the loop will go to its next iteration.
        if (exit == true) {
            break;
        }
    }

    // Game is over so player who won gets congratulated.
    printf("\n%s wins with %d points!\n", names[player_turn], scores[player_turn]);
    return 0;
}
