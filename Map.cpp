#include "Map.h"
#include "Menu.h"

using namespace std;

Map::Map() {
  tiles = new Tile*[HEIGHT];

  for(int i=0;i<HEIGHT;++i){
    tiles[i] = new Tile[WIDTH];
  }
}

void Map::getShift(int &y, int &x) {
  y = shiftY;
  x = shiftX;
}

void Map::init() {
  // Set tile colors
  init_pair(MEADOW, COLOR_BLACK, COLOR_GREEN);
  init_pair(WATER, COLOR_BLACK, COLOR_BLUE);
  init_pair(SWAMP, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(WALL, COLOR_BLACK, COLOR_WHITE);
  init_pair(DIAMOND, COLOR_WHITE, COLOR_CYAN);
  init_pair(PLAYER, COLOR_BLACK, COLOR_RED);
  init_pair('0', COLOR_BLACK, COLOR_BLACK);   // Blank tile
}

Map::~Map() {
  if(!tiles){
    return;
  }

  for(int i=0;i<HEIGHT;++i){
    delete [] tiles[i];
    tiles[i] = NULL;
  }

  delete []tiles;
  tiles = NULL;

  return;
}

void Map::display(int playerY, int playerX, bool hasBinoculars)
{
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
        if (tiles[h][w].isVisible == true)
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

  // Don't reveal the item on the tile if it's not discovered
  char c = tile->isVisible ? tile->item: ' ';

  // apply map shift
  y = y - shiftY;
  x = x - shiftX;

  // Check bounds
  if (y < 0) y = 0;
  if (y > LINES - 1) y = LINES - 1;

  if (x < 0) x = 0;
  if (x > COLS - MENU_WIDTH - 1) x = COLS - MENU_WIDTH - 1;

  // Change background color
  attron(COLOR_PAIR('H'));
  mvaddch(y, x, c);
  attroff(COLOR_PAIR('H'));
  refresh();
}

void Map::load(int & playerStartY, int & playerStartX) {
	string line;
	int nline = 0;
#ifdef TEST
	ifstream mapfile ("test.txt");
#else
	ifstream mapfile ("map1.txt");
#endif // TEST
	if(mapfile.is_open()){
		while (getline(mapfile, line)) {
			for(unsigned i = 0; i < line.length(); i++) {
				switch(line.at(i)) {
					case ' ':
						tiles[nline][i].type = MEADOW;
						break;
					case '~':
						tiles[nline][i].type = WATER;
						break;
					case '#':
						tiles[nline][i].type = SWAMP;
						break;
					case '|':
						tiles[nline][i].type = WALL;
						break;
					case 'D':
						tiles[nline][i].type = DIAMOND;
						tiles[nline][i].item = '$';
            					break;
					case 'S':
						tiles[nline][i].type = MEADOW;
						tiles[nline][i].item = 'S';
						tiles[nline][i].itemType = new Ship;
						tiles[nline][i].itemType->setType(0);
						break;
					case 'B':
						tiles[nline][i].type = MEADOW;
						tiles[nline][i].item = 'B';
						tiles[nline][i].itemType = new Binoculars;
						tiles[nline][i].itemType->setType(1);
						break;
					case 'T':
						tiles[nline][i].type = MEADOW;
						tiles[nline][i].item = 'T';
						tiles[nline][i].itemType = new Tool;
						tiles[nline][i].itemType->setType(2);
						break;
					case 'F':
						tiles[nline][i].type = MEADOW;
						tiles[nline][i].item = 'F';
						tiles[nline][i].itemType = new Food;
						tiles[nline][i].itemType->setType(3);
						break;
					case '!':
						tiles[nline][i].type = MEADOW;
						tiles[nline][i].item = '!';
						tiles[nline][i].itemType = new Obstacle;
						tiles[nline][i].itemType->setType(4);
						break;
					case '?':
						tiles[nline][i].type = MEADOW;
						tiles[nline][i].item = '?';
						tiles[nline][i].itemType = new Clue;
						tiles[nline][i].itemType->setType(5);
						break;
					case '$':
						tiles[nline][i].type = MEADOW;
						tiles[nline][i].item = '$';
						tiles[nline][i].itemType = new Treasure;
						tiles[nline][i].itemType->setType(6);
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
