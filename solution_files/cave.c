#include <stdio.h>
#include <string.h>

#define BUFSIZE 16

unsigned long read_stdin(char *buf, int size) {
    fgets(buf, BUFSIZE, stdin);

    unsigned long length = strlen(buf);
    while (length > 0) {
        char value = buf[length - 1];
        if (value == '\n' || value == '\r') {
            length -= 1;
        } else {
            break;
        }
    }

    buf[length] = 0;

    return length;
}

void password() {
    char *target = "Zfxnddzxb";
    char input[BUFSIZE];

    puts("As you approach the cave, a statue bars your path. Slowly and methodically, it turns to face you, and after it has settled to a stop, it begins to speak.\n\n\"Hello there, strange person from beyond. Before you may enter the great cave, I must ask one question from you. What is my name?\"");

    while (1) {
        read_stdin(input, BUFSIZE);

        if (strncmp(input, target, BUFSIZE) == 0) {
            printf("\"That is correct. I do not get many visitors, so I am pleased to hear that outsiders still remember the name of %s.\"\n\nYou refrain from mentioning that you have never heard of %s before. The statue bows, and you hear rumbling stone as a stairway opens in the wall. You step into the opening, beginning your descent into the darkness below.\n\n", target, target);
            break;
        }

        puts("\"That is not my name.\"");
    }
}

int char_to_direction(char dir_in) {
    switch (dir_in) {
        case 'N':
        case 'n':
            return 1;
        case 'S':
        case 's':
            return 2;
        case 'W':
        case 'w':
            return 3;
        case 'E':
        case 'e':
            return 4;
        default:
            return 0;
    }
}

void maze() {
    int target[10] = {1, 4, 2, 4, 1, 1, 3, 1, 4, 1};

    char input[BUFSIZE];

    int pos = 0;
    int goal = 10;

    puts("As you arrive at a large underground chamber, you catch a glimpse of a rickety-looking maze built from wooden bridges. However, before you can get a good look, the door closes behind you and shrouds the room in darkness. Bathed in near-total quiet, you hear a faint sound of dripping water.");

    while (pos < goal) {
        puts("Enter a direction (N, S, W, E):");
        unsigned long length = read_stdin(input, BUFSIZE);
        if (length == 0) {
            puts("Invalid input.");
            continue;
        }

        char direction_char = input[0];
        int direction = char_to_direction(direction_char);

        if (direction == 0) {
            puts("Invalid input.");
        } else {
            if (direction == target[pos]) {
                ++pos;
            } else {
                puts("Your stomach lurches as you take a step off the bridge, and for a second, you feel yourself falling. Just as suddenly, you feel the floor below you, and once again hear the sound of dripping water.");
                pos = 0;
            }
        }
    }

    puts("As you reach the end of the maze, a wave of relief washes over you. Your footsteps echo as you begin the climb up another flight of stairs.\n");
}

void door() {
    const int enable_boulder = 1;

    puts("But now, you reach one final chamber, a square room with an exit doorway right in front of you.\n");

    if (enable_boulder) {
        puts("Unfortunately, a large boulder sits blocking the exit. You try to move it out of the way, but it is far too heavy. It seems your adventure has ended here... but doubt still lingers within you. Could there be another way?\n\nGAME OVER.");
    } else {
        puts("When you arrive, you find that the door is already open. Light shines at you from within, and you push forward to see what lies beyond.\n\nYOU WIN?\n\nCongratulations on solving the puzzles of the cave. This game was inspired by The Beginner's Guide, so if you enjoyed it, why not give the original a look?");
    }
}


int main(int argc, char **argv) {
    password();
    maze();
    door();
}

