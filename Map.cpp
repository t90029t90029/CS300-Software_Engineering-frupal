#include "Map.h"

using namespace std;

Map::Map() {
  tiles = new Tile*[HEIGHT];

  for(int i=0;i<HEIGHT;++i){
    tiles[i] = new Tile[WIDTH];
  }
}

Map::~Map() {
  if(!tiles){
    return;
  }

  for(int i=0;i<HEIGHT;++i){
    delete []tiles[i];
    tiles[i] = NULL;
  }

  delete []tiles;
  tiles = NULL;

  return;
}

void Map::display(int playerY, int playerX)
{
    start_color();

    init_pair(MEADOW, COLOR_BLACK, COLOR_GREEN);
    init_pair(WATER, COLOR_BLACK, COLOR_BLUE);
    init_pair(SWAMP, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(WALL, COLOR_BLACK, COLOR_WHITE);
    init_pair(DIAMOND, COLOR_BLACK, COLOR_CYAN);
    init_pair(PLAYER, COLOR_BLACK, COLOR_RED);
    init_pair('0', COLOR_BLACK, COLOR_BLACK);

    char empty = ' ';
    char playerSymbol = '@';

    TileType currentType;

    int sight = 1;
    if(sight == 1)
    {
        for(int h = -1; h <= 1; ++h)
        {
           for(int w = -1; w <= 1; ++w)
           {
                if(playerY+h < HEIGHT && playerY+h >= 0 && playerX+w >= 0 && playerX+w < WIDTH)
                {
                    tiles[playerY+h][playerX+w].isVisible = true;
                }
           }
        }
    }

    for(int h = 0; h < HEIGHT; ++h)
    {
      for(int w = 0; w < WIDTH; ++w)
      {
        //Check if visible = true, if true print tile, else print black
        if(tiles[h][w].isVisible == true)
        {
            char item = empty = ' ';
            if(tiles[h][w].item != empty)
                item = tiles[h][w].item;

            currentType = tiles[h][w].type;

            attron(COLOR_PAIR(currentType));
            mvprintw(h, w, "%c", item);
            attroff(COLOR_PAIR(currentType));
       }
       else
       {
            attron(COLOR_PAIR(0));
            mvprintw(h, w, "%c", empty);
            attroff(COLOR_PAIR(0));
       }

      }
    }
    attron(COLOR_PAIR(PLAYER));
    mvprintw(playerY, playerX, "%c", playerSymbol);
    attroff(COLOR_PAIR(PLAYER));
    refresh();
}

void Map::load(int & playerStartY, int & playerStartX) {
	string line;
	int nline = 0;
	ifstream mapfile ("map1.txt");
	if(mapfile.is_open()){
		while (getline(mapfile, line)) {
			for(unsigned i = 0; i < line.length(); i++) {
				switch(line.at(i)) {
					case 'M':
						tiles[nline][i].type = MEADOW;
						break;
					case 'W':
						tiles[nline][i].type = WATER;
						break;
					case 'S':
						tiles[nline][i].type = SWAMP;
						break;
					case 'L':
						tiles[nline][i].type = WALL;
						break;
					case 'D':
						tiles[nline][i].type = DIAMOND;
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
						tiles[nline][i].itemType = new Tool;
						break;
					case 'F':
						tiles[nline][i].type = MEADOW;
						tiles[nline][i].item = 'F';
						tiles[nline][i].itemType = new Food;
						break;
					case '!':
						tiles[nline][i].type = MEADOW;
						tiles[nline][i].item = '!';
						tiles[nline][i].itemType = new Obstacle;
						break;
					case '?':
						tiles[nline][i].type = MEADOW;
						tiles[nline][i].item = '?';
						tiles[nline][i].itemType = new Clue;
						break;
					case '$':
						tiles[nline][i].type = MEADOW;
						tiles[nline][i].item = '$';
						tiles[nline][i].itemType = new Treasure;
						break;
					case '@':
                                                tiles[nline][i].type = MEADOW;
                                                playerStartY = nline;
                                                playerStartX = i;
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

Tile* Map::getTile(int y, int x) {
  if (HEIGHT - 1 < y || y < 0)
    return NULL;

  if (WIDTH - 1 < x || x < 0)
    return NULL;

  return &tiles[y][x];
}
