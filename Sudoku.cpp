#include<iostream>
#include<vector>

using namespace std;

bool check(int grid[9][9], int i, int j, int n)
{
    for(int k=0; k<9; k++)
    {
        if ((grid[i][k]==n)&&(k!=j))
            return false;
        else if ((grid[k][j]==n)&&(k!=i))
            return false;
    }
    
    int x = i/3;
    int y = j/3;
    
    for(int m=3*x; m<3*x+3; m++)
        for (int b=3*y; b<3*y+3; b++)
            if ((b!=i)&&(b!=j)&&(grid[m][b]==n))
                return false;
    
    return true;
}

void next_cell(int next[2])
{
    if (next[1]==8)
    {
        next[0]++;
        next[1]=0;
    }
    else
        next[1]++;
}

bool solve(int grid[9][9], int x, int y)
{
    int next[2] = {x,y};
    next_cell(next);
    
    if (x==9)
        return true;
    
    if (grid[x][y]!=0)
    {
        return solve(grid, next[0], next[1]);
    }
    else 
    {
        bool valid_state = false;
        for (int n=1; n<10; n++)
        {
            if (check(grid, x,y,n))
            {
                /*if (grid[0][0]==3)
                    if (grid[0][1]==4)
                        if (grid[0][2]==5)
                            if (grid[0][3]==6)
                    cout<<x<<" "<<y<<" "<<n<<endl;*/
                    
               /* if (grid[x][y]==8)
                    cout<<x<<" "<<y<<" "<<n<<endl;*/
                grid[x][y]=n;
                if (solve(grid, next[0], next[1]))
                    {
                        
                        valid_state = true;
                        break;
                    }
                else {
                    grid[x][y]=0;
                }
            }
        }
        if (valid_state)
            return true;
        else  {
        grid[x][y]=0;
        return false;
        }
    }
}

void sudoku_solve(int grid[9][9]) {
    //your logic here
    solve(grid,0,0);
    
    for(int i=0; i<9;i++)
    {
        for(int j=0;j<9;j++)
            cout<<grid[i][j]<<" ";
        cout<<endl;
    }
    
}

int main(void) {
    int n, board[9][9];
    cin >> n;
    for(int i=0;i<n;i++) {
        for(int j=0;j<9;j++) {
            for(int k=0;k<9;k++) {
                board[j][k] = 0;
                cin >> board[j][k];
            }
        }
        sudoku_solve(board);
    }
    return 0;
}
