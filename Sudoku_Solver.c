#include <stdio.h> 
#define N 9 

void print(int grid[N][N]) { // this function prints the Sudoku grid (separators & cells)
    for (int i = 0; i < N; i++) { 
        if (i % 3 == 0 && i != 0) 
            printf("----------------------\n"); 
        for (int j = 0; j < N; j++) { 
            if (j % 3 == 0 && j != 0) 
                printf("| "); 
            printf("%d ", grid[i][j]); 
        }
        printf("\n");
    }
}

int numberChecker(int grid[N][N], int row, int col, int num) { // function checks if it's safe to place a number in a cell
    for (int x = 0; x < N; x++) 
        if (grid[row][x] == num || grid[x][col] == num) 
            return 0; 
    
    //this part checks for repeat numbers within 3x3 subgrids
    int remainderRow = row % 3; 
    int subgridRow = row - remainderRow; 
    
    int remainderCol = col % 3;
    int subgridCol = col - remainderCol; 
    
    for (int i = 0; i < 3; i++) 
        for (int j = 0; j < 3; j++) 
            if (grid[i + subgridRow][j + subgridCol] == num) 
                return 0; 
    return 1; 
}

int solveSudoku(int grid[N][N], int *count) { // function solves the Sudoku puzzle; uses pointer to count iterations to avoid reset  
    int row, col;
    int emptyCell = 0; 
    (*count)++; 
   
    for (row = 0; row < N; row++) { 
        for (col = 0; col < N; col++) { 
            if (grid[row][col] == 0) { 
                emptyCell = 1; 
                break; 
            }
        }
        if (emptyCell) 
            break; 
    }

    if (!emptyCell) 
        return 1; 

    for (int num = 1; num <= 9; num++) { 
        if (numberChecker(grid, row, col, num)) { 
            grid[row][col] = num; 
            if (solveSudoku(grid, count)) 
                return 1; 
            grid[row][col] = 0; 
        }
    }
    return 0; 
}

int main() { // hard coding grid
    int grid[N][N] = { 
        {0, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 6, 0, 0, 0, 0, 3},
        {0, 7, 4, 0, 8, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 0, 0, 2},
        {0, 8, 0, 0, 4, 0, 0, 1, 0},
        {6, 0, 0, 5, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 7, 8, 0},
        {5, 0, 0, 0, 0, 9, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 4, 0}
    };

    int count = 0; 

    printf("The input Sudoku puzzle:\n"); 
    print(grid); 

    if (solveSudoku(grid, &count)) { 
        printf("Solution found after %d iterations:\n", count + 1); 
        print(grid); 
    } else { 
        printf("No solution exists.\n"); 
    }

    return 0; 
}