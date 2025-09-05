#include<stdio.h>
// #include<stdlib.h>
// #include<string.h>
// #include<time.h>


void execute(unsigned char instruction) {
    // Speed
    // switch (instruction & (3 << 6)) {
    //     case 0: printf("Slow | ");break;
    //     case 1: printf("Normal | ");break;
    //     case 2: printf("Above Normal | ");break;
    //     case 3: printf("Fast | ");break;
    // }

    // Time
    // switch (instruction & (3 << 4)) {
    //     case 0: printf("15 mins later | ");break;
    //     case 1: printf("30 mins later | ");break;
    //     case 2: printf("45 mins later | ");break;
    //     case 3: printf("60 mins later | ");break;
    // }

    // Room
    // switch (instruction & (3 << 2)) {
    //     case 0: printf("First Room | ");break;
    //     case 1: printf("Second Room | ");break;
    //     case 2: printf("Third Room | ");break;
    //     case 3: printf("Fourth Room | ");break;
    // }


    // Direction
    // switch (instruction & (3 << 0)) {
    //     case 0: printf("Left ");break;
    //     case 1: printf("Right ");break;
    //     case 2: printf("Forward ");break;
    //     case 3: printf("Backward ");break;
    // }



    // printf("%s %s %s %s\n", 
    //         speed[instruction & (0b11 << 6)], 
    //         time_r[instruction & (0b11 << 4)], 
    //         room[instruction & (0b11 << 2)], 
    //         speed[instruction & (3 << 0)]
    //         );

}

int
main(int argc, char ** args)
{
    /*
     * Robot Instructions
     *  Speed    Time          Room       Direction
     *   00       00            00           00 
     *
     *
     *
     * Direction:
     * 0 = Left
     * 1 = Right
     * 2 = Forward
     * 3 = Backward
     *
     *
     *  Room: 
     *  0 = First room 
     *  1 = Second room
     *  2 = Third room
     *  3 = Fourth room
     *
     *  Time: 
     *  0 = 15 mins
     *  1 = 30 mins
     *  2 = 45 mins
     *  3 = 60 mins
     * 
     *
     * Speed: 
     * 0 = slow
     * 1 = normal
     * 2 = above normal
     * 3 = fast
     */

    char* direction[4] = {
        "Left",
        "Right",
        "Forward",
        "Backward"
    };

    char* room[4] = {
        "First Room",
        "Second Room",
        "Third Room",
        "Fourth Room"
    };

    char* time_r[4] = {
        "15 mins",
        "30 mins",
        "45 mins",
        "60 mins"
    };

    char* speed[4] = {
        "Slow",
        "Normal",
        "Above Normal",
        "Fast"
    };

    for(int instruction =0; instruction<=0xF; instruction++) {
        printf("%s %s %s %s\n", 
            speed[(instruction & (3 << 6)) >> 6], 
            time_r[(instruction & (3 << 4)) >> 4], 
            room[(instruction & (3 << 2)) >> 2], 
            speed[(instruction & (3 << 0)) >> 0]
            );
        // execute(instruction);
        // printf("\n");
    }
    // unsigned char robot_instrction = 0;
    // execute(robot_instrction);

    // 0,1,2,3
    //(x & 3 << i) >> i

    // 0b00000000;
    // 0b00000000;

   return 0;
}
