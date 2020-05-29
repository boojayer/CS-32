#include <stack>
#include <iostream>
#include <string>
using namespace std;

const char discovered = '#';


class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};



bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
{
    stack<Coord> mazeStack;

    // 1. Push the starting coordinate(sr, sc) onto the coordinate stackand
    Coord start(sr, sc);

    // update maze[sr][sc] to indicate that the algorithm has encountered
    //it(i.e., set maze[sr][sc] to have a value other than '.').
    mazeStack.push(start);
    maze[start.r()][start.c()] = discovered;


    //2. While the stack is not empty,
    while (!mazeStack.empty())
    {
        //Pop the top coordinate off the stack.This gives you the current
        //(r,c) location that your algorithm is exploring.
        Coord pos = mazeStack.top();
        mazeStack.pop();


        //3. If the current(r,c) coordinate is equal to the ending coordinate,
        if (pos.r() == er && pos.c() == ec)
        {
            //then we've solved the maze so return true!
            return true;
        }


        //4. Check each place you can move from the current cell as follows :

        //If you can move EAST and haven't encountered that cell yet,
        if (maze[pos.r()][pos.c() + 1] == '.')
        {
            //then push the coordinate(r,c + 1) onto the stack and update
            //maze[r][c + 1] to indicate the algorithm has encountered it.
            Coord east(pos.r(), pos.c() + 1);
            mazeStack.push(east);
            maze[pos.r()][pos.c() + 1] = discovered;
        }

        //If you can move SOUTH and haven't encountered that cell yet,
        if (maze[pos.r() + 1][pos.c()] == '.')
        {
            //then push the coordinate(r + 1,c) onto the stack and update
            //maze[r + 1][c] to indicate the algorithm has encountered it.
            Coord north(pos.r() + 1, pos.c());
            mazeStack.push(north);
            maze[pos.r() + 1][pos.c()] = discovered;
        }


        //If you can move WEST and haven't encountered that cell yet,
        if (maze[pos.r()][pos.c() - 1] == '.')
        {
            //then push the coordinate(r,c - 1) onto the stack and update
            //maze[r][c - 1] to indicate the algorithm has encountered it.
            Coord west(pos.r(), pos.c() - 1);
            mazeStack.push(west);
            maze[pos.r()][pos.c() - 1] = discovered;
        }


        //If you can move NORTH and haven't encountered that cell yet,
        if (maze[pos.r() - 1][pos.c()] == '.')
        {
            //then push the coordinate(r - 1,c) onto the stack and update
            //maze[r - 1][c] to indicate the algorithm has encountered it.
            Coord north(pos.r() - 1, pos.c());
            mazeStack.push(north);
            maze[pos.r() - 1][pos.c()] = discovered;
        }
    }
    //There was no solution, so return false
    return false;
}


