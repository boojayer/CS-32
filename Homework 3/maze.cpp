#include <iostream>
#include <string>
#include <cassert>

using namespace std;


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
{
    maze[sr][sc] = '@';
    if (sr == er && sc == ec)
        return true;

    //east
    Coord east = Coord(sr, sc + 1);
    if (sc != nCols && maze[east.r()][east.c()] == '.')
    {
        if (pathExists(maze, nRows, nCols, sr, sc + 1, er, ec))
            return true;
    }

    //south
    Coord south = Coord(sr + 1, sc);
    if (sr != nRows && maze[south.r()][south.c()] == '.')
    {
        if (pathExists(maze, nRows, nCols, sr + 1, sc, er, ec))
            return true;
    }

    //west
    Coord west = Coord(sr, sc - 1);
    if (sc != 0 && maze[west.r()][west.c()] == '.')
    {
        if (pathExists(maze, nRows, nCols, sr, sc - 1, er, ec))
            return true;
    }

    //north
    Coord north = Coord(sr - 1, sc);
    if (sr != 0 && maze[north.r()][north.c()] == '.')
    {
        if (pathExists(maze, nRows, nCols, sr -1, sc, er, ec))
            return true;
    }

    return false;
}

