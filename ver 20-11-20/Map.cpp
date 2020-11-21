#include "Map.h"

using namespace std;

Map::Map() {
  tiles = new Tile*[HEIGHT];

  for(int i=0;i<HEIGHT;++i){
    tiles[i] = new Tile[WIDTH];
  }
  //testing
  hView = 32;
  wView = 44;//20 off for menu space
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
    clear();
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

    //Get sight from viewpoint
    //set sight to be either +-1 around the player, or +-2 around the player.
    //set tiles around player location to visible
    // int sight = getSight();
    int sight = 1;
    if(sight == 1)
    {
        for(int h = -1; h <= 1; ++h)
        {
           for(int w = -1; w <= 1; ++w)
            {
                tiles[playerY+h][playerX+w].isVisible = true;
            }
        }
    }
    //if(sight == 2)
    //for(int h = -2; i <= 2; ++h)
    //{
    //  for(int w = -2; w <= 2; ++w)
    //  {
    //      tiles[playerY+h][playerX+w].isVisible = TRUE;
    //  }
    //}

    //modifying display to get a shifting viewport
    shiftX = playerX - (wView/2);
    shiftY = playerY- (hView/2);
    //viewport bounds
    if(shiftX <0){
       shiftX = 0;
    }else if(shiftX+wView > WIDTH ){
       shiftX = WIDTH - wView;
    }
    if(shiftY <0){
       shiftY=0;
    }else if(shiftY+hView > HEIGHT){
       shiftY = HEIGHT-hView;
    }


    for(int h = shiftY; h < shiftY + hView; ++h)
    {
      for(int w = shiftX; w < shiftX + wView; ++w)
      {
        //Check if visible = true, if true print tile, else print black
        if(tiles[h][w].isVisible == true)
        {
            char item = empty = ' ';
            if(tiles[h][w].item != empty)
                item = tiles[h][w].item;

            currentType = tiles[h][w].type;

            attron(COLOR_PAIR(currentType));
            mvprintw(h-shiftY, w-shiftX, "%c", item);
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
    mvprintw(playerY-shiftY, playerX-shiftX, "%c", playerSymbol);
    attroff(COLOR_PAIR(PLAYER));
    refresh();
}

void Map::viewportSize(int &h, int &w){
	if(h >HEIGHT)
	  hView = HEIGHT;
	else if(h <=0)
	  hView = 1;
	else
	  hView = h;

	if(w>WIDTH+25)
	    wView = WIDTH;
	else if(w<=0)
	  wView = 1;
	else
	  wView = w-25;
	
}

void Map::load(int & playerStartY, int & playerStartX) {
	string line;
	int nline = 0;
	int whichItem;
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
						tiles[nline][i].itemType1 = new Tool;
						break;
					case 'F':
						tiles[nline][i].type = MEADOW;
						tiles[nline][i].item = 'F';
						whichItem = rand() % 3 + 1;
						if(whichItem == 1)
						  tiles[nline][i].itemtype = CRACKER;
						else if(whichItem == 2)
						  tiles[nline][i].itemtype = STEAK;
						else if(whichItem == 3)
						  tiles[nline][i].itemtype = SPRITE;
						break;
					case '!':
						tiles[nline][i].type = MEADOW;
						tiles[nline][i].item = '!';
						tiles[nline][i].itemType1 = new Obstacle;
						break;
					case '?':
						tiles[nline][i].type = MEADOW;
						tiles[nline][i].item = '?';
						break;
					case '$':
						tiles[nline][i].type = MEADOW;
						tiles[nline][i].item = '$';
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
