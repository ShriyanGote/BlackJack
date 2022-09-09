// blackjack

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

int scorePlayer(int rounds, int totalPlyers, char players[]);
int ace(int totalSum, int checkAce, char playersTurn[]);
int dealerAce(int totalSum, int checkAce);
int scoreDealer(char dealerName[]);
int currentScoreCheck(int totalSum, int newCard, char playersTurn[]);

typedef struct dealer
{
    char name[50];
    int scores[10];
    int finalScores;
} dealer;

typedef struct player
{
    char name[50];
    int scores[10];
    int finalScores;
    int bet;
    int dollars;
} player;

struct player players[10];
struct dealer dealer1;

int sizeOfDeck = 52;
int deck[] = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4,
    5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8,
    9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10};


int main(int argc, const char * argv[])
{
    srand(time(NULL));
    int totalPlayers;
    int rounds;
    
    printf("Instructions: This is a multiplayer game - Each player will be given 100 dollars to bet, before every round the player will be asked how much they want to bet.\n");

    printf("How many players are playing blackjack: ");
    scanf("%d", &totalPlayers);
    

    printf("Enter dealer's name: ");
    scanf("%s", dealer1.name);
    
    for (int i = 0; i<totalPlayers; ++i)
    {
        printf("Enter player %d's name: ", i+1);
        scanf("%s", players[i].name);
    }

    printf("How many rounds are being played: ");
    scanf("%d", &rounds);
    
    int random = rand() % sizeOfDeck;
    dealer1.scores[0] = deck[random];
    for (int i = random-1; i< sizeOfDeck; i++ )
        deck[i] = deck[i+1];
    sizeOfDeck--;
        
    for (int c = 0; c<totalPlayers; c++)
        players[c].dollars = 100;
    
    for (int i = 0; i<rounds; i++)
    {
        puts("\n");
        for (int j = 0; j<totalPlayers; j++)
        {
            printf("Enter bet for player %s: ", players[j].name);
            scanf("%d", &players[j].bet);
            players[j].dollars -= players[j].bet;
        }
        puts("\n");
        printf("\nDealer %s starts off by drawing a card valued at %d.\n\n", dealer1.name, dealer1.scores[0]);
        scorePlayer(rounds, totalPlayers, dealer1.name);
        scoreDealer(dealer1.name);
        
        for (int i = 0; i < totalPlayers; i++)
            printf("%s's total score: %d\n", players[i].name, players[i].finalScores);
        puts("\n");
        
        for (int f = 0; f<totalPlayers; f++)
        {
            if (players[f].finalScores == 21)
            {
                printf("%s won against the dealer, and recieves %d dollars!\n", players[f].name, players[f].bet);
                players[f].dollars += 2*(players[f].bet) + 10;
                printf("%s's Bank Account: %d$\n\n", players[f].name, players[f].dollars);
            }
            else if (players[f].finalScores == dealer1.finalScores)
            {
                printf("Dealer and %s tied, player gets back bet!\n", players[f].name);
                players[f].dollars += players[f].bet;
                printf("%s's Bank Account: %d$\n\n", players[f].name, players[f].dollars);
            }
            else if (players[f].finalScores < dealer1.finalScores)
            {
                printf("%s loses their bet!\n", players[f].name);
                printf("%s's Bank Account: %d$\n\n", players[f].name, players[f].dollars);
            }
            else if (players[f].finalScores > 21)
            {
                printf("%s loses their bet!\n", players[f].name);
                printf("%s's Bank Account: %d$\n\n", players[f].name, players[f].dollars);
            }
            if (players[f].finalScores > dealer1.finalScores && players[f].finalScores <= 21)
            {
                printf("%s won against the dealer, and recieves %d dollars!\n", players[f].name, players[f].bet);
                players[f].dollars += 2*(players[f].bet);
                printf("%s's Bank Account: %d$\n\n", players[f].name, players[f].dollars);
            }
        }
    }
}



int scorePlayer(int rounds, int totalPlayers, char dealerName[])
{
    int a;
    int i;
    int playerCount;

    for (playerCount = 0; playerCount<totalPlayers; playerCount++)
    {
        printf("total players: %d\nplayerCount: %d\n", totalPlayers, playerCount);

        int totalSum = 0;
        // assigning card values to each card
        int random = rand() % (sizeOfDeck);
        players[playerCount].scores[0] = deck[random];
        for (int i = random-1; i< sizeOfDeck; i++ )
            deck[i] = deck[i+1];
        sizeOfDeck--;
        
        random = rand() % (sizeOfDeck);
        players[playerCount].scores[1] = deck[random];
        for (i = random-1; i< sizeOfDeck; i++ )
            deck[i] = deck[i+1];
        sizeOfDeck--;
        
        // TOTALSUM
        totalSum = players[playerCount].scores[0] + players[playerCount].scores[1];

        // if ACE is received
        if (players[playerCount].scores[0] == 1)
            players[playerCount].scores[0] = ace(totalSum, players[playerCount].scores[0], players[playerCount].name);
    
        if (players[playerCount].scores[1] == 1)
            players[playerCount].scores[1] = ace(totalSum,players[playerCount].scores[1], players[playerCount].name);
        
        // drawing more cards or checking
        totalSum = players[playerCount].scores[0] + players[playerCount].scores[1];
        int current = currentScoreCheck(totalSum, players[playerCount].scores[0], players[playerCount].name);
        if (current == 0)
        {
            players[playerCount].finalScores = totalSum;
            printf("%s's final score: %d\n\n", players[playerCount].name, players[playerCount].finalScores);
        }
        if ((totalSum == 21) && (players[playerCount].scores[1] + players[playerCount].scores[0] == 21))
        {
            printf("%s has received blackjack they will receive their bet + 10 dollars!\n\n", players[playerCount].name);
            players[playerCount].finalScores = totalSum;
            players[playerCount].bet += 10;
        }
        if (current == 1)
        {
            for (a = 2; a<10; a++)
            {
                ace(totalSum, players[playerCount].scores[a], players[playerCount].name);
                random = rand() % (sizeOfDeck);
                // checking random card for ace
                ace(totalSum+1, deck[random], players[playerCount].name);
                // random card is taken out of deck and assign to next value
                players[playerCount].scores[a] = deck[random];
                sizeOfDeck--;
                for (int i = random-1; i< sizeOfDeck; i++ )
                    deck[i] = deck[i+1];
                // added to sum
                totalSum += players[playerCount].scores[a];
                int new = currentScoreCheck(totalSum, players[playerCount].scores[a], players[playerCount].name);
                if (new == 0 || new == -1)
                {
                    players[playerCount].finalScores = totalSum;
                    if (totalSum > 21)
                        printf("%s's final score: %d (Bust)\n\n", players[playerCount].name, players[playerCount].finalScores);
                    else
                        printf("%s's final score: %d\n\n", players[playerCount].name, players[playerCount].finalScores);
                    puts("\n");
                    break;
                }
                else if (new > 21)
                    break;
            } // end for
        } // end if want new card
    } // end last for
    return 0;
}

int ace (int totalSum, int checkAce, char playersTurn[])
{
    int oneEL = 0;
    if (checkAce == 1)
    {
        printf("%s's Turn:\nDealer %s has given you an ace, your total sum with ACE = 1 would be %d, your total sum with ACE = 11 would be %d.\nDo you want to have the value as 1 or 11: ",playersTurn, dealer1.name, totalSum, totalSum + 10);
    
        scanf("%d", &oneEL);
    }
    return oneEL;
}

int currentScoreCheck(int totalSum, int newCard, char playersTurn[])
{
    int check;
    if (totalSum > 21)
    {
        printf("%s's turn:\nDealer %s gave you a card valued at %d and your total is above 21, you have busted!\n\n", playersTurn, dealer1.name,newCard);
        totalSum = -1;
        return totalSum;
    }
    else
    {
    printf("%s's turn:\nDealer %s gave you a card valued at %d, your total is %d, do you want to draw another card (1 for yes, 0 for no)? ", playersTurn, dealer1.name,newCard, totalSum);
    scanf("%d", &check);

    }
    if (check == 0)
        return check;
    else
        return 1;
}

int scoreDealer(char dealerName[])
{
    int i;
    int a = 0;
    
    int random = rand() % sizeOfDeck;
    dealer1.scores[1] = deck[random];
    for (i = random-1; i< sizeOfDeck; i++ )
        deck[i] = deck[i+1];
    sizeOfDeck--;
    int totalSum = dealer1.scores[1] + dealer1.scores[0];
    
    if (dealer1.scores[0] == 1)
        dealer1.scores[0]=dealerAce(totalSum, dealer1.scores[0]);
    if (dealer1.scores[1] == 1)
        dealer1.scores[1]=dealerAce(totalSum, dealer1.scores[1]);

    totalSum = dealer1.scores[1] + dealer1.scores[0];
    
    while (totalSum < 17)
    {
        for (a = 2; a< 10; a++)
        {
            int random = rand() % sizeOfDeck;
            dealer1.scores[a] = deck[random];
            for (i = random-1; i< sizeOfDeck; i++ )
                deck[i] = deck[i+1];
            sizeOfDeck--;
            totalSum += dealer1.scores[a];
            
            printf("Dealer has a total score of %d.\n", totalSum);
            if (totalSum >= 17 && totalSum <= 21)
                break;
            if (totalSum > 21)
                break;
        }
    }
    if (totalSum >= 17 && totalSum <= 21)
    {
        dealer1.finalScores = totalSum;
        printf("Dealer recieved a card valued %d and a final score of %d!\n\n",dealer1.scores[1], dealer1.finalScores);
    }
    else
    {
        dealer1.finalScores = 0;
        printf("Dealer received a card valued at %d and their total is above 21, the dealer has busted!\n\n", dealer1.scores[a]);
    }
    return dealer1.finalScores;
}

int dealerAce(int totalSum, int checkAce)
{
    int ace;
        printf("The dealer has received an ace.\nWith a value of 1 the total will be: %d\nWith a value of 11 the total will be %d\nDoes the dealer want the ace to be 1 or 11: ", totalSum, totalSum + 10);
        scanf("%d", &ace);
        return ace;
}

