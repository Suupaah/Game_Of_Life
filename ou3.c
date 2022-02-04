/*
Generates a 20x20 field of elements which follow the rules of Game of life
Generation can be done randomly or by chosing existing presets.


Date: 2021-10-20
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Constants, representation of states */
#define ALIVE 'X'
#define DEAD '.'
#define ROWS 20
#define COLS 20

/* Declaration of data structure */
typedef struct
{
    char current;
    char next;
} cell;

/* Declaration of functions */
void initField(const int rows, const int cols, cell field[rows][cols]);
void clearField(const int rows, const int cols, cell field[rows][cols]);
void loadGlider(const int rows, const int cols, cell field[rows][cols]);
void loadSemaphore(const int rows, const int cols, cell field[rows][cols]);
void loadRandom(const int rows, const int cols, cell field[rows][cols]);
void loadCustom(const int rows, const int cols, cell field[rows][cols]);
char getStartStateChoice(void);
void runGame(const int rows, const int cols, cell field[rows][cols]);
int countAliveNeighbours(const int rows, const int cols, cell field[ROWS][COLS]);
void NewGeneration(const int rows, const int cols, cell field[rows][cols]);
void updateWorld(int const rows, int const cols, cell field[rows][cols]);


/* Function:    main
 * Description: Start and run simulations, interact with the user.
 *              Lets the user choose initial structure and whether to step
 *              or exit. Writes information to the user, and the game field
 *              in each step.
 */

int main(void)
{

    cell game[ROWS][COLS];



    initField(ROWS, COLS, game);

    runGame(ROWS, COLS, game);

    return 0;
}

/* Function:    initField
 * Description: Loads a structure that the user selects
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 * Output:      The field array is updated.
 */

void initField(const int rows, const int cols, cell field[rows][cols])
{
    char choice;

    clearField(rows, cols, field);

    choice = getStartStateChoice();

    switch (choice)
    {
    case 'g':
    case 'G':
        loadGlider(rows, cols, field);
        break;
    case 's':
    case 'S':
        loadSemaphore(rows, cols, field);
        break;
    case 'r':
    case 'R':
        loadRandom(rows, cols, field);
        break;
    case 'c':
    case 'C':
    default:
        loadCustom(rows, cols, field);
        break;
    }
}

/* Function:    getStartStateChoice
 * Description: Lets the user choose starting state
 * Input:
 * Output:      The users choice. Should be one of the letters G,S,R or C.
 */
char getStartStateChoice(void)
{
    int ch;

    printf("Select field spec to load ([G]lider, [S]emaphore, [R]andom ");
    printf("or [C]ustom): ");

    ch = getchar();

    /* Ignore following newline */
    if (ch != '\n')
    {
        getchar();
    }
    return ch;
}

/* Function:    clearField
 * Description: Initialize all the cells in the field to dead
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 * Output:      The field array is updated.
 */
void clearField(const int rows, const int cols, cell field[rows][cols])
{

    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            field[r][c].current = DEAD;
        }
    }
}

/* Function:    loadGlider
 * Description: Inserts a glider into the field.
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 * Output:      The field array is updated.
 */

void loadGlider(const int rows, const int cols, cell field[rows][cols])
{

    field[0][1].current = ALIVE;
    field[1][2].current = ALIVE;
    field[2][0].current = ALIVE;
    field[2][1].current = ALIVE;
    field[2][2].current = ALIVE;
}

/* Function:    loadSemaphore
 * Description: Inserts a semaphore into the field.
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 * Output:      The field array is updated.
 */

void loadSemaphore(const int rows, const int cols, cell field[rows][cols])
{

    field[8][1].current = ALIVE;
    field[8][2].current = ALIVE;
    field[8][3].current = ALIVE;
}

/* Function:    loadRandom
 * Description: Inserts a random structure into the field. To assure true rand-
                omness a function which uses the computers internal clock is us
                ed. Then a random number is generated and that rumber dictates
                wether an element is either alive of dead.
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 * Output:      The field array is updated. There is a 50 % chance that a cell
 *              is alive.
 */

void loadRandom(const int rows, const int cols, cell field[rows][cols])
{

    srand(time(NULL));
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            int randomnumber = rand() % 2 + 1; // Gives Randomnumber a value between 1 and 2.
            if (randomnumber == 2)
            {
                field[r][c].current = ALIVE;
            }
            else
            {
                field[r][c].current = DEAD;
            }
        }
    }
}

/* Function:    loadCustom
 * Description: Lets the user specify a structure that then is inserted into
 *              the field.
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 * Output:      The field array is updated.
 */

void loadCustom(const int rows, const int cols, cell field[rows][cols])
{
    int r, c;

    printf("Give custom format string: ");
    do
    {
        scanf("%d,%d", &r, &c);
        field[r][c].current = ALIVE;
    } while (getchar() != '\n');
}

/* Function:    runGame
 * Description: Prints out the current cell and lets the user interact
                to either show a new generation or quit the program.
                The double for-loops are used to get to every single
                element in the 2d array.
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 * Output:      -.
 */
void runGame(const int rows, const int cols, cell field[rows][cols])
{
    char choice = '\n';
    do
    {
        for (int r = 0; r < ROWS; r++)
        {
            for (int c = 0; c < COLS; c++)
            {
                printf("%c ", field[r][c].current);
            }
            printf("\n");
        }

        printf("Select one of the following options: \n");
        printf("        (enter) Step\n");
        printf("        (any)   Exit\n");
        NewGeneration(rows, cols, field);
        scanf("%c", &choice);

    } while (choice == '\n');
}

/* Function:    CountAliveNeighbours
 * Description: Calculates the amount neighbours alive surrounding a cell.
                Neighbours are checked from top-left to bottom right. In order
                to prevent checking neighbours that some cells dont have for ex
                the leftmost column does not have any left neighbours so there
                are if-statements in place to prevent this.

 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 * Output:      An array consisting of alive neighbours for each element is made.
 */
int countAliveNeighbours(const int rows, const int cols, cell field[ROWS][COLS])
{
  // Resetting the Neighbours for when field.current changes to field.next
  int AliveNeighbours = 0;

  for (int r = rows - 1; r < rows + 2; r++)
  {
    if(r >= 0 && r < ROWS)
    {
      for (int c = cols - 1; c <cols + 2; c++)
      {
        if(c >= 0 && c < COLS)
        {
          if (!(r == rows && c == cols) && field[r][c].current == ALIVE)
          {
            AliveNeighbours++;
          }
        }
      }
    }
  }

  return AliveNeighbours;
}


/* Function:    NewGeneration
 * Description: The rules of Game of life are applied here with help of the
                array with alive neighbours we can determine which cell will
                live and which one will die in the next generation.

 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 *              AliveNeighbours - Two dimensional array with neighbours alive.
 *
 * Output:      The information is stored in field[r][c].next is sent to update
 *              world function.
 */
 void NewGeneration(const int rows, const int cols, cell field[rows][cols])
 {

     for (int r = 0; r < rows; r++)
     {
         for (int c = 0; c < cols; c++)
         {
             int Neighbours = countAliveNeighbours(r, c, field);

             if (field[r][c].current == ALIVE)
             {
                 if (Neighbours < 2)
                 {
                     field[r][c].next = DEAD;
                 }
                 if (Neighbours == 2 || Neighbours == 3)
                 {
                     field[r][c].next = ALIVE;
                 }
                 else
                 {
                     field[r][c].next = DEAD;
                 }
             }
             else if (Neighbours == 3)
             {
                 field[r][c].next = ALIVE;
             }
             else
             {
                 field[r][c].next = DEAD;
             }
         }
     }

     updateWorld(rows, cols, field);
 }

/* Function:    Updateworld
 * Description: The currect field becomes the next field which allows the
                program to change the field and print out the new generation
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 *              AliveNeighbours - Two dimensional array with neighbours alive.
 * Output:      Change the construct cell from field[r][c].current to next.
 */
void updateWorld(int rows, int cols, cell field[rows][cols])
{

    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            field[r][c].current = field[r][c].next;
        }
    }
}
