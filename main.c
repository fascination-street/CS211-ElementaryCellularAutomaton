//Elementary Cellular Automaton

#include <stdio.h>
#include <stdbool.h>
#include <math.h> 

const int WORLD_SIZE = 65;

typedef struct cell_struct{
    bool state[3]; //active status for [left, me, right] cells 
    bool active; //current active status for this cell
} cell;

//convert an 8-bit integer rule (0-255) to array of bits 
//(stored in reverse order)
//   ex: rule = 6  = 00000110 -> [01100000] 
//   ex: rule = 30 = 00011110 -> [01111000] 
//   ex: rule = 65 = 01000001 -> [10000010]
//return true if input rule is valid (0-255)
//return false if input rule is invalid
bool setBitArray(bool bitArray[8], int rule) {

        //TODO: Task 1 - write the setBitArray() function
        if (rule >= 0 && rule < 256)
        {
            int i;
            for (i = 0; i < 8; i++)
            {
                if (rule % 2 > 0)
                {
                    bitArray[i] = true;
                }
                else
                {
                    bitArray[i] = false;
                }
                //printf("%d", bitArray[i]);

                rule /= 2;
            }
            return true;
        }

        return false;
}

//convert a 3-bit state array to its 
//associated index of the rule# bit array
//   ex: {0 0 0} -> 0
//   ex: {0 0 1} -> 1
//   ex: {1 0 1} -> 5
int stateToIndex(bool state[3]) {

    //TODO: Task 4 - write the stateToIndex() function
    int decVal = 0;
    for (int i = 0; i < 3; ++i)
    {
        decVal = decVal + (state[2 - i] * pow(2, i));  
    }

    return decVal;
}

//update the state array for each cell in the world array based on the
//current status of active for the nearby [left,me,right] cells
//note: world is assumed periodic/cyclic,
//with front-to-back and back-to-front wrapping 
void setStates(cell world[65]) {

    //TODO: Task 5 - write the setStates() function
    for (int i = 1; i <= WORLD_SIZE; i++)
    {
        //Determines "left" state
        if (world[(i-1)%65].active)
        {
            world[i%65].state[0] = 1;
        }
        else
        {
            world[i%65].state[0] = 0;
        }

        //Determines "me" state
        if (world[i%WORLD_SIZE].active)
        {
            world[i%WORLD_SIZE].state[1] = 1;
        }
        else
        {
            world[i%WORLD_SIZE].state[1] = 0;
        }

        //Determines "right" state
        if (world[(i+1)%WORLD_SIZE].active)
        {
            world[i%WORLD_SIZE].state[2] = 1;
        }
        else
        {
            world[i%WORLD_SIZE].state[2] = 0;
        }
    }

    return;
}

//evolve each cell's active status to the next generation 
//  using its state array
//ruleBitArray contains the 8-bits for the rule#, 
//  stored in reverse order
void evolveWorld(cell world[65], bool ruleBitArray[8]) {

    //TODO: Task 7 - write the evolveWorld() function
    int stateIndex;
    for (int i = 0; i < WORLD_SIZE; i++)
    {
        //The if statement checks to see if the specific state value held by stateIndex is true or false
        stateIndex = stateToIndex(world[i].state);
        if (ruleBitArray[stateIndex])
        {
            world[i].active = true;
        }
        else
        {
            world[i].active = false;
        }
    }
    setStates(world);

    return;
}



//Prints the evolution of all possible states
//For Task 3
void printEvoSteps(bool bitArray[])
{
    printf("The evolution of all possible states are as follows:\n"
           "|***|   |** |   |* *|   |*  |   | **|   | * |   |  *|   |   |\n");
    for (int i = 7; i >= 0; --i)
    {
        if (bitArray[i])
        {
            printf(" |*|");
        }
        else
        {
            printf(" | |");
        }
        printf("    ");
    }
}

int main() {
    cell world[65];

    printf("Welcome to the Elementary Cellular Automaton!\n");

    //TODO: Task 2 - read in a valid rule# and
    //      generate the rule's 8-bit rule bit array 
    //      print the bit array in correct binary number order
    int ruleNum = -1;
    int numSteps;
    bool bitArray[8];

    while (ruleNum < 0 || ruleNum > 255)
    {
        printf("Enter the rule # (0-255): ");
        scanf("%d", &ruleNum);
        if (setBitArray(bitArray, ruleNum))
        {
            break;
        }
    }
    
    printf("The bit array for rule #%d is ", ruleNum);
    for (int i = 0; i < 8; i++)
    {
        printf("%d", bitArray[7 - i]);
    }
    printf("\n");


    //TODO: Task 3 - use the rule bit array to report the evolution 
    //      step for all possible cell states.
    //      follow the format of the sample output exactly
    printEvoSteps(bitArray);


    //TODO: Task 6 - read in the total number of generation evolution 
    //      steps from the user and initialize the world with ONLY the 
    //      middle cell active, all other cells should be inactive; 
    //      make sure to set the state array for each cell.
    printf("\nEnter the number of generations: ");
    scanf("%d", &numSteps);

    //Sets all but middle cell active state to "false"
    for (int i = 0; i < WORLD_SIZE; i++)
    {
        if (i != WORLD_SIZE/2)
        {
            world[i].active = false;
        }
        else
        {
            world[i].active = true;
        }
    }

    setStates(world);
    printf("\nInitializing world & evolving...\n");

    for (int j = 0; j < WORLD_SIZE; j++)
    {
        if (world[j].active)
        {
            printf("*");
        }
        else
        {
            printf(" ");
        }
    }
    printf("\n");
    evolveWorld(world, bitArray);



    //TODO: Task 8 - evolve the world the user-specified number  
    //      of generations, printing each active cell as '*' and
    //      each non-active cell as ' ' (whitespace) after each
    //      evolution step to the next generation
    for (int i = 0; i < numSteps - 1; i++)
    {
        for (int j = 0; j < WORLD_SIZE; j++)
        {
            if (world[j].active)
            {
                printf("*");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
        evolveWorld(world, bitArray);
    }

    return 0;
}
