#include "Map.h"
#include "Menu.h"

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

void Map::display(int playerY, int playerX, bool hasBinoculars)
{
    //ncurses colors
    start_color();

    init_pair(MEADOW, COLOR_BLACK, COLOR_GREEN);
    init_pair(WATER, COLOR_BLACK, COLOR_BLUE);
    init_pair(SWAMP, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(WALL, COLOR_BLACK, COLOR_WHITE);
    init_pair(DIAMOND, COLOR_WHITE, COLOR_CYAN);
    init_pair(PLAYER, COLOR_BLACK, COLOR_RED);
    init_pair('0', COLOR_BLACK, COLOR_BLACK);
    init_pair('H', COLOR_BLACK, COLOR_YELLOW);

    char empty = ' ';
    char playerSymbol = '@';

    // Fog of war -- reveal tiles around the player
    TileType currentType;
    int sight = 1;
    if(hasBinoculars == true)
        sight = 2;

    for(int h = -sight; h <= sight; ++h)
    {
        for(int w = -sight; w <= sight; ++w)
        {
            if(playerY+h < HEIGHT && playerY+h >= 0 && playerX+w >= 0 && playerX+w < WIDTH)
            {
                    tiles[playerY+h][playerX+w].isVisible = true;
            }
        }
    }

    //modifying display to get a shifting viewport
    viewportSize(); // Get current size of the viewport

    // Put player in the center
    shiftX = playerX - (wView / 2);
    shiftY = playerY - (hView / 2);

    // Check viewport bounds
    if (shiftX < 0)
       shiftX = 0;
    else if(shiftX + wView > WIDTH)
       shiftX = WIDTH - wView;

    if (shiftY < 0)
       shiftY = 0;
    else if (shiftY + hView > HEIGHT)
       shiftY = HEIGHT - hView;

     // Display a portion of the map
    for(int h = shiftY; h < shiftY + hView; ++h)
    {
      for(int w = shiftX; w < shiftX + wView; ++w)
      {
        //Check if visible = true, if true print tile, else print black
#ifdef NOFOG
        if (true)
#else
        if (tiles[h][w].isVisible == true)
#endif // NOFOG
        {
          char item = empty = ' ';
          if(tiles[h][w].item != empty)
              item = tiles[h][w].item;

          currentType = tiles[h][w].type;

          // h,w coordinates on the map need to be shifted when printing on screen
          attron(COLOR_PAIR(currentType));
          mvprintw(h - shiftY, w - shiftX, "%c", item);
          attroff(COLOR_PAIR(currentType));
       }
       // Hide undiscovered tiles
       else
       {
            attron(COLOR_PAIR(0));
            mvprintw(h - shiftY, w - shiftX, "%c", empty);
            attroff(COLOR_PAIR(0));
       }

      }
    }

    // Draw player
    attron(COLOR_PAIR(PLAYER));
    mvprintw(playerY - shiftY, playerX - shiftX, "%c", playerSymbol);
    attroff(COLOR_PAIR(PLAYER));
    refresh();
}

void Map::viewportSize() {
  hView = LINES;
  wView = COLS - MENU_WIDTH;

	if(hView > HEIGHT)
	  hView = HEIGHT;
	else if(hView <= 0)
	  hView = MIN_HEIGHT;

	if(wView > WIDTH)
	    wView = WIDTH;
	else if (wView <= 0)
	  wView = MIN_WIDTH;
}

bool Map::isPurchasable(int y, int x) {
  Tile *tile = getTile(y, x);

  if (tile != NULL) {
    char type = tile->item;
    return (type == 'S' || type == 'B' || type == 'T' || type == 'F');
  }
  return false;
}

void Map::highlightItem(int y, int x) {
  Tile * tile = getTile(y, x);

  // Change background color
  attron(COLOR_PAIR('H'));
  mvaddch(y - shiftY, x - shiftX, tile->item);
  attroff(COLOR_PAIR('H'));
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
						tiles[nline][i].item = '$';
            break;
					case 'H':
						tiles[nline][i].type = MEADOW;
						tiles[nline][i].item = 'S';
						tiles[nline][i].itemType = new Ship;
						break;
					case 'B':
						tiles[nline][i].type = MEADOW;
						tiles[nline][i].item = 'B';
						tiles[nline][i].itemType = new Binoculars;
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
