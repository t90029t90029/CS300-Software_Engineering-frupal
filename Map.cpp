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

    char empty = ' ';
    char playerSymbol = '@';

    TileType currentType;

    for(int h = 0; h < HEIGHT; ++h)
    {
      for(int w = 0; w < WIDTH; ++w)
      {
        char item = empty = ' ';
        if (tiles[h][w].item != empty)
          item = tiles[h][w].item;

        currentType = tiles[h][w].type;

        attron(COLOR_PAIR(currentType));
        mvprintw(h, w, "%c", item);
        attroff(COLOR_PAIR(currentType));
      }
    }
    attron(COLOR_PAIR(PLAYER));
    mvprintw(playerY, playerX, "%c", playerSymbol);
    attroff(COLOR_PAIR(PLAYER));
    refresh();
}

void Map::load() {
	string line;
	int nline = 0;
	int foodtype;
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
						break;
					case 'F':
						tiles[nline][i].type = MEADOW;
						tiles[nline][i].item = 'F';
						foodtype = rand() % 3 + 1;
						if(foodtype == 1)
						  tiles[nline][i].food = CRACKER;
						else if(foodtype == 2)
						  tiles[nline][i].food = STEAK;
						else if(foodtype == 3)
						  tiles[nline][i].food = SPRITE;
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

Tile* Map::getTile(int y, int x) {
  if (HEIGHT - 1 < y || y < 0)
    return NULL;

  if (WIDTH - 1 < x || x < 0)
    return NULL;

  return &tiles[y][x];
}
