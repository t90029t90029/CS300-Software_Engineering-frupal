#include "Map.h"

Map::Map() {

}


void Map::displayMap()
{
    start_color();

    init_pair(1, COLOR_BLACK, COLOR_GREEN); 
    init_pair(2, COLOR_BLACK, COLOR_BLUE); 
    init_pair(3, COLOR_BLACK, COLOR_MAGENTA); 
    init_pair(4, COLOR_BLACK, COLOR_WHITE); 
    init_pair(5, COLOR_BLACK, COLOR_CYAN); 

    char empty = ' ';

    TileType currentType = tiles[0][0].type;

    for(int h = 0; h <= HEIGHT; ++h)
    {
        for(int w = 0; w<= WIDTH; ++w)
        {
            currentType = tiles[h][w].type;
            switch(currentType)
            {
                case MEADOW:
                    //make square GREEN at tiles[h][w];
                    attron(COLOR_PAIR(1));
                    mvprintw(h, w, "%c", empty);
                    attroff(COLOR_PAIR(1));
                    break;
                case WATER:
                    //make square BLUE at tiles[h][w];
                    attron(COLOR_PAIR(2));
                    mvprintw(h, w, "%c", empty);
                    attroff(COLOR_PAIR(2));
                    break;
                case SWAMP:
                    //make square MAGENTA at tiles[h][w];
                    attron(COLOR_PAIR(3));
                    mvprintw(h, w, "%c", empty);
                    attroff(COLOR_PAIR(3));
                    break;
                case WALL:
                    //make square WHITE at tiles[h][w];
                    attron(COLOR_PAIR(4));
                    mvprintw(h, w, "%c", empty);
                    attroff(COLOR_PAIR(4));
                    break;
                case DIAMOND:
                    //make square CYAN at tiles[h][w];
                    attron(COLOR_PAIR(5));
                    mvprintw(h, w, "%c", empty);
                    attroff(COLOR_PAIR(5));
                default:
                    break;
            }
        }
    }
    refresh(); 
}
void Map::loader() {
	string line;
	int nline = 0;
	ifstream mapfile ("map1.txt");
	if(mapfile.is_open()){
		while (getline(mapfile, line)) {
			for(unsigned i = 0; i < line.length(); i++) {
				switch(line.at(i)) {
					case 'M':
						tiles[nline][i].type = MEADOW;
						tiles[nline][i].item = 'M';
						break;
					case 'W':
						tiles[nline][i].type = WATER;
						tiles[nline][i].item = 'W';
						break;
					case 'S':
						tiles[nline][i].type = SWAMP;
						tiles[nline][i].item = 'S';
						break;
					case 'L':
						tiles[nline][i].type = WALL;
						tiles[nline][i].item = 'L';
						break;
					case 'D':
						tiles[nline][i].type = DIAMOND;
						tiles[nline][i].item = 'D';
						break;
					case 'H':
						tiles[nline][i].type = MEADOW;
						tiles[nline][i].item = 'S';
						break;
					case 'B':
						tiles[nline][i].type = MEADOW;
						tiles[nline][i].item = 'B';
						break;
					case 'T':
						tiles[nline][i].type = MEADOW;
						tiles[nline][i].item = 'T';
						break;
					case 'F':
						tiles[nline][i].type = MEADOW;
						tiles[nline][i].item = 'F';
						break;
					case '!':
						tiles[nline][i].type = MEADOW;
						tiles[nline][i].item = '!';
						break;
					case '?':
						tiles[nline][i].type = MEADOW;
						tiles[nline][i].item = '?';
						break;
					case '$':
						tiles[nline][i].type = MEADOW;
						tiles[nline][i].item = '$';
						break;
					default:
						break;
				}
			}
			nline++;
		}
		mapfile.close();

	}
	else 
		cout<<"Failed to open file\n";
}
