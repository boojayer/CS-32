#include <queue>
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
    queue<Coord> mazeQueue;

    Coord start(sr, sc);
    mazeQueue.push(start);
    maze[start.r()][start.c()] = discovered;

    while (!mazeQueue.empty())
    {
        Coord pos = mazeQueue.front();
        mazeQueue.pop();

        //solve the maze
        if (pos.r() == er && pos.c() == ec)
        {
            return true;
        }

        //If you can move EAST and haven't encountered that cell yet,
        if (maze[pos.r()][pos.c() + 1] == '.')
        {
            Coord temp(pos.r(), pos.c() + 1);
            mazeQueue.push(temp);
            maze[pos.r()][pos.c() + 1] = discovered;
        }

        //If you can move SOUTH and haven't encountered that cell yet,
        if (maze[pos.r() + 1][pos.c()] == '.')
        {
            Coord temp(pos.r() + 1, pos.c());
            mazeQueue.push(temp);
            maze[pos.r() + 1][pos.c()] = discovered;
        }


        //If you can move WEST and haven't encountered that cell yet,
        if (maze[pos.r()][pos.c() - 1] == '.')
        {
            Coord temp(pos.r(), pos.c() - 1);
            mazeQueue.push(temp);
            maze[pos.r()][pos.c() - 1] = discovered;
        }


        //If you can move NORTH and haven't encountered that cell yet,
        if (maze[pos.r() - 1][pos.c()] == '.')
        {
            Coord temp(pos.r() - 1, pos.c());
            mazeQueue.push(temp);
            maze[pos.r() - 1][pos.c()] = discovered;
        }
    }
    //There was no solution, so return false
    return false;
}
   

