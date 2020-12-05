# Frupal
#### Introduction ####
Frupal is an adventure / survival game for Linux.  
Our adventurer must scour the Kingdom of Frupal in search of a Royal Diamond (shown as a cyan $), worth one zillion zillion whiffles, the currency of the Kingdom of Frupal.

#### Exploring ####
Each square of the map is referred to as a grovnick in the Kingdom of Frupal.
Only grovnicks that have been discovered by the adventurer can be seen.  
The adventurer can see one grovnick ahead with the naked eye, or two grovnicks ahead with binoculars (B).  
Water (blue) can only be traversed if a ship (S) has been found.  
The adventurer can pre-emptively inspect grovnicks it has discovered before it moves forward.

#### Energy ####
The adventurer only has a limited amount of energy for traveling. If the adventurer runs out of energy, the game is over.  
Traveling across meadows (green) expends 1 energy, swamps (magenta) expend 2 energy. If using a ship on water, no energy is expended.  
Food (F) can be bought to restore energy.  
Obstacles (!) might be encountered such as monsters, large boulders, rough terrain, which expend much more energy.
Tools (T) can be bought to make overcoming these obstacles easier. Each tool only works on certain types of obstacles.  
Tools can only be used once before they break.  

#### Helpful Items ####
Treasure chests ($) are located throughout the Kingdom, which contain a varying amount of whiffles.  
There are clues (?) on the map to the locations of useful items, and maybe even the Royal Diamond. Be careful though, the clues can be deceptive.  

## Contributers

**CS300 Group 10**
* Jared Collums (@jcollums)
* Melissa Barnes (@MelissaPSU)
* Jordan Lopez-Santizo (@9L-S)
* Huy Doan (@huy26)
* Shang Chun Lin (@t90029t90029)

## Controls
The adventurer can move north (W), west (A), south (S), and east (D).  
The adventurer can move the cursor to inspect grovnicks with the arrow keys.  
The 'i' key toggles the adventurer's inventory view, which will show tools and quest items.  
The Enter key will buy an item, if the adventurer has enough whiffles.

## Building
Frupal requires the ncurses library.  
Frupal can be built with the following commands:

* This command builds and runs the game
```
make run
```

* These commands build and run the game with cheats enabled
```
make nofog    # All grovnicks discovered from the beginning
make noclip   # The adventurer can walk through walls and on water
make godmode  # The adventurer cannot die
make ghost    # All the the above cheats enabled
```

* These commands are used for debugging
```
make test     # Load with test map, lots of useful items around spawn point
make debug    # Build, run in GDB
make leak     # Build, run in valgrind
```
