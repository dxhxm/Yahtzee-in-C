#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//defining constants
#define MAX_ROLLS 3
#define DICE_AMOUNT 5
#define NUM_CATEGORIES 13

const char *categories[] = {
    "Ones", "Twos", "Threes", "Fours", "Fives", "Sixes", 
    "Three of a Kind", "Four of a Kind", "Full House", 
    "Small Straight", "Large Straight", "Yahtzee", "Chance"
};

void rollDice(int dice[]); //function for roll the dice
void displayDice(int dice[]); //function for display the dice values
void displayCategories(bool used[]); //function for display the categories
int chooseCategory(bool used[]); //function for choose the categories
int scoreForCategory(int dice[], int category); //function for category scoring method

int main()
{
    //defining variables
    int player_score = 0;
    int computer_score = 0;
    int playerUpperSum = 0;
    int computerUpperSum = 0;

    //defining arrays
    int playerdice[DICE_AMOUNT];
    int computerdice[DICE_AMOUNT];
    bool playerUsedCategories[NUM_CATEGORIES] = {false};
    bool computerUsedCategories[NUM_CATEGORIES] = {false}; 

    srand(time(NULL)); //seed random number generator

    //starting the game flow
    printf("\n ----- WELCOME TO YAHTZEE! -----\n");

    for (int i=0 ; i < 13 ; i++) //loop for the all rounds of the game
    {
        printf("\nROUND %d\n\n",i+1);

        //starting player turn
        printf("Your Turn\n");

        rollDice(playerdice);
        displayDice(playerdice);

        for (int i = 1; i < MAX_ROLLS; i++) 
        {
            printf("Do you want to reroll? (y/n): ");
            char response;
            scanf(" %c", &response);

            if (response == 'y' || response == 'Y') //player rerolling method
            {
                printf("Enter the positions of the dice you want to reroll (1-5).Enter 0 to stop: ");
                int position;
                while (scanf("%d", &position) && position != 0) 
                {
                    if (position >= 1 && position <= DICE_AMOUNT) 
                    {
                        playerdice[position - 1] = rand() % 6 + 1;
                    } 
                    else 
                    {
                        printf("Invalid position.Try again");
                    }
                }
                displayDice(playerdice);
            } 
            else 
            {
                break;
            }
        }

        //displaying categoies and calculating player score

        printf("\nChoose the category you want\n\n");
        displayCategories(playerUsedCategories);

        int selectedCategory = chooseCategory(playerUsedCategories);
        playerUsedCategories[selectedCategory] = true; 

        int categoryScore = scoreForCategory(playerdice, selectedCategory);
        player_score += categoryScore;

        if (selectedCategory >= 0 && selectedCategory <= 5) {
            playerUpperSum += categoryScore;
        }

        printf("\nYou chose %s with score %d\n", categories[selectedCategory], categoryScore);
        printf("Your Total Score: %d\n\n", player_score);

        //starting computer turn
        printf("Computer's Turn\n");

        rollDice(computerdice);
        displayDice(computerdice);

        bool rerollNeeded = true;
        int best_category = -1;

        for (int reroll = 0; reroll < 2 && rerollNeeded; reroll++)
        {
            int tempMaxScore = -1;
            int tempBestCategory = -1;

            for (int category = NUM_CATEGORIES - 1; category >= 0; category--)
            {
                if (!computerUsedCategories[category]) // Only consider unused categories
                {
                    int score = scoreForCategory(computerdice, category);
                    if (score > tempMaxScore)
                    {
                        tempMaxScore = score;
                        tempBestCategory = category;
                    }
                }
            }
            if (tempBestCategory != -1)
            {
                int max_score = tempMaxScore;
                best_category = tempBestCategory;

                if (best_category == 12 || best_category == 11 || best_category == 10 || best_category == 9 ||
                    best_category == 8 || best_category == 7)
                {
                    rerollNeeded = false;
                }
                else
                {
                    int counts[6] = {0};
                    for (int i = 0; i < DICE_AMOUNT; i++)
                    {
                        counts[computerdice[i] - 1]++;
                    }
                    printf("Computer rerolls dice:\n"); //computer rerolling method
                    for (int i = 0; i < DICE_AMOUNT; i++)
                    {
                        if (best_category < 6 && computerdice[i] != best_category + 1)
                        {
                            computerdice[i] = (rand() % 6) + 1;
                        } else if (best_category == 6 && counts[computerdice[i] - 1] < 3) {
                            computerdice[i] = (rand() % 6) + 1;
                        } else if (best_category == 7 && counts[computerdice[i] - 1] < 4) {
                            computerdice[i] = (rand() % 6) + 1;
                        } else if (best_category == 11 && counts[computerdice[i] - 1] < 5) {
                            computerdice[i] = (rand() % 6) + 1;
                        }
                    }
                    displayDice(computerdice);
                }
            }
            else
            {
                break;
            }
        }
        if (best_category != -1) //calculating computer score
        {
            computerUsedCategories[best_category] = true;
            int computerCategoryScore = scoreForCategory(computerdice, best_category);
            computer_score += computerCategoryScore;

            if (best_category >= 0 && best_category <= 5) {
                computerUpperSum += computerCategoryScore;
            }

            printf("\nComputer chose %s with score %d\n", categories[best_category], computerCategoryScore);
            printf("Computer's Total Score: %d\n\n", computer_score);
        }
    } //end of the rounds

    if (playerUpperSum >= 63) {
        printf("You earned a 35-point bonus for scoring %d in Ones to Sixes!\n", playerUpperSum);
        player_score += 35;
    }
    if (computerUpperSum >= 63) {
        printf("Computer earned a 35-point bonus for scoring %d in Ones to Sixes!\n", computerUpperSum);
        computer_score += 35;
    }

    //final scores calculating 
    printf("\nGame Over!\n");
    printf("Your Final Score: %d\n", player_score);
    printf("Computer's Final Score: %d\n", computer_score);

    if (player_score > computer_score) {
        printf("Congratulations! You win!\n");
    } else if (player_score < computer_score) {
        printf("The computer wins! Better luck next time.\n");
    } else {
        printf("Match tied!\n");
    }
    return 0;
}

//defining functions 
void rollDice(int dice[]) //function for roll the dice
{
    for (int i = 0; i < DICE_AMOUNT; i++) {
        dice[i] = rand() % 6 + 1;
    }
}

void displayDice(int dice[]) //function for display the dice values
{
    printf("Dice: ");
    for (int i = 0; i < DICE_AMOUNT; i++) {
        printf("[%d] ", dice[i]);
    }
    printf("\n");
}

void displayCategories(bool used[]) //function for display the categories
{
    printf("Available Categories:\n");
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        if (!used[i]) 
        {
            printf("%d: %s\n", i+1, categories[i]);
        } else {
            printf("%d: %s (Used)\n", i+1, categories[i]);
        }
    }
}

int chooseCategory(bool used[]) //function for choose the categories
{
    int category;
    do 
    {
        printf("Select a category (1-%d): ", NUM_CATEGORIES);
        scanf("%d", &category);
        category--; 
        if (category < 0 || category >= NUM_CATEGORIES || used[category]) 
        {
            printf("Invalid choice. Try again.\n");
        }
    } 
    while (category < 0 || category >= NUM_CATEGORIES || used[category]);
    return category;
}

int scoreForCategory(int dice[], int category) //function for category scoring method
{
    int counts[6] = {0};
    int score = 0;

    for (int i = 0; i < DICE_AMOUNT; i++) 
    {
        counts[dice[i]-1]++;
    }

    switch (category) 
    {
        case 0: case 1: case 2: case 3: case 4: case 5: // Ones to Sixes 
            score = counts[category] * (category + 1);
            break;
        case 6: // Three of a Kind
            for (int i = 0; i < 6; i++) {
                if (counts[i] >= 3) {
                    score = dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
                    break;
                }
            }
            break;
        case 7: // Four of a Kind
            for (int i = 0; i < 6; i++) {
                if (counts[i] >= 4) {
                    score = dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
                    break;
                }
            }
            break;
        case 8: // Full House
            {
                bool hasThree = false, hasTwo = false;
                for (int i = 0; i < 6; i++) {
                    if (counts[i] == 3) hasThree = true;
                    if (counts[i] == 2) hasTwo = true;
                }
                if (hasThree && hasTwo) {
                    score = 25;
                }
            }
            break;
        case 9: // Small Straight
            if ((counts[0] && counts[1] && counts[2] && counts[3]) ||
                (counts[1] && counts[2] && counts[3] && counts[4]) ||
                (counts[2] && counts[3] && counts[4] && counts[5])) {
                score = 30;
            }
            break;
        case 10: // Large Straight
            if ((counts[0] && counts[1] && counts[2] && counts[3] && counts[4]) ||
                (counts[1] && counts[2] && counts[3] && counts[4] && counts[5])) {
                score = 40;
            }
            break;
        case 11: // Yahtzee
            for (int i = 0; i < 6; i++) {
                if (counts[i] == 5) {
                    score = 50;
                    break;
                }
            }
            break;
        case 12: // Chance
            score = dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
            break;
    }

    return score;
}