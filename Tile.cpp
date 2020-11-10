#include "Tile.h"

Tile::Tile(): type(MEADOW), item(' ') { 

}


void Tile::displayMap()
{
    start_color();

    init_pair(1, COLOR_BLACK, COLOR_GREEN); 
    init_pair(2, COLOR_BLACK, COLOR_BLUE); 
    init_pair(3, COLOR_BLACK, COLOR_MAGENTA); 
    init_pair(4, COLOR_BLACK, COLOR_WHITE); 
    init_pair(5, COLOR_BLACK, COLOR_CYAN); 

    char empty = ' ';

    TileType currentType = tiles[0][0].type;

    for(int h = HEIGHT; h <= HEIGHT; ++h)
    {
        for(int w = WIDTH; w<= WIDTH; ++w)
        {
            currentType = tiles[h][w].type;
            switch(currentType)
            {
                case MEADOW:
                    //make square GREEN at tiles[h][w];
                    attron(COLOR_PAIR(1));
                    mvprint(h, w, "%c", empty);
                    attroff(COLOR_PAIR(1));
                    break;
                case WATER:
                    //make square BLUE at tiles[h][w];
                    attron(COLOR_PAIR(2));
                    mvprint(h, w, "%c", empty);
                    attroff(COLOR_PAIR(2));
                    break;
                case SWAMP:
                    //make square MAGENTA at tiles[h][w];
                    attron(COLOR_PAIR(3));
                    mvprint(h, w, "%c", empty);
                    attroff(COLOR_PAIR(3));
                    break;
                case WALL:
                    //make square WHITE at tiles[h][w];
                    attron(COLOR_PAIR(4));
                    mvprint(h, w, "%c", empty);
                    attroff(COLOR_PAIR(4));
                    break;
                case DIAMOND:
                    //make square CYAN at tiles[h][w];
                    attron(COLOR_PAIR(5));
                    mvprint(h, w, "%c", empty);
                    attroff(COLOR_PAIR(5));
                    break;
                case default:
                    break;
            }
        }
    }

}
