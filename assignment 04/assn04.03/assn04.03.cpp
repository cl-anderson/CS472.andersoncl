// assn04.03.cpp : This file contains the 'main' function. Program execution begins and ends there.
// sources: https://www.geeksforgeeks.org/tiling-problem-using-divide-and-conquer-algorithm/
//          https://www.geeksforgeeks.org/domino-and-tromino-tiling-problem/
//          https://www.calstatela.edu/sites/default/files/triomino_tilings.pdf
// I needed some background info on tiling, so here's the sources I read for that. After reading these
// I'm glad the tiling required was periodic!
//          https://www.mathsisfun.com/geometry/tessellation.html
//          https://mathstat.slu.edu/escher/index.php/Tessellations_by_Polygons
//          https://www.quora.com/What-is-the-difference-between-aperiodic-and-periodic-tilings
// 
// as far as i can tell, this seeeeems to fit the brief as follows:
//      Every unit square other than the forbidden square is covered by a tromnio.
//      No tromino covers the forbidden square.
//      No two trominos overlap. No tromino extends beyond the board.
// Each tromino piece is identified by a number. The forbidden square is -1.
#include <iostream>
// C++ program to place tiles
using namespace std;

int size_of_grid, b, a, cnt = 0;
int arr[128][128];

// Placing tile at the given coordinates
void place(int x1, int y1, int x2,
    int y2, int x3, int y3)
{
    cnt++;
    arr[x1][y1] = cnt;
    arr[x2][y2] = cnt;
    arr[x3][y3] = cnt;
}
// Quadrant names
// 1   2
// 3   4

// Function based on divide and conquer
int tile(int n, int x, int y)
{
    int r, c;
    if (n == 2) {
        cnt++;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (arr[x + i][y + j] == 0) {
                    arr[x + i][y + j] = cnt;
                }
            }
        }
        return 0;
    }
    // finding hole location
    for (int i = x; i < x + n; i++) {
        for (int j = y; j < y + n; j++) {
            if (arr[i][j] != 0)
                r = i, c = j;
        }
    }

    // If missing tile is 1st quadrant
    if (r < x + n / 2 && c < y + n / 2)
        place(x + n / 2, y + (n / 2) - 1, x + n / 2,
            y + n / 2, x + n / 2 - 1, y + n / 2);

    // If missing Tile is in 3rd quadrant
    else if (r >= x + n / 2 && c < y + n / 2)
        place(x + (n / 2) - 1, y + (n / 2), x + (n / 2),
            y + n / 2, x + (n / 2) - 1, y + (n / 2) - 1);

    // If missing Tile is in 2nd quadrant
    else if (r < x + n / 2 && c >= y + n / 2)
        place(x + n / 2, y + (n / 2) - 1, x + n / 2,
            y + n / 2, x + n / 2 - 1, y + n / 2 - 1);

    // If missing Tile is in 4th quadrant
    else if (r >= x + n / 2 && c >= y + n / 2)
        place(x + (n / 2) - 1, y + (n / 2), x + (n / 2),
            y + (n / 2) - 1, x + (n / 2) - 1,
            y + (n / 2) - 1);

    // dividing it again in 4 quadrants. 
    // a note from cl-anderson: similar to the chocolate breaking, we break the grid into smaller
    // grids to then be tiled!
    tile(n / 2, x, y + n / 2);
    tile(n / 2, x, y);
    tile(n / 2, x + n / 2, y);
    tile(n / 2, x + n / 2, y + n / 2);

    return 0;
}
// Driver program to test above function
int main()
{
    // size of box
    size_of_grid = 8;
    memset(arr, 0, sizeof(arr));
    // Coordinates which will be marked
    a = 2, b = 2;
    // Here tile can not be placed
    arr[a][b] = -1;
    tile(size_of_grid, 0, 0);
    // The grid is
    for (int i = 0; i < size_of_grid; i++) {
        for (int j = 0; j < size_of_grid; j++)
            cout << arr[i][j] << " \t";
        cout << "\n";
    }
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
