CRAWL THE DUNGEON GAME
Written for Linux
AUTHOR: Braeden Lisowski
You can compile this game on linux with the command: 
g++ *.cpp -w -lSDL2 -SDL2_image
This would of course require SDL2 and SDL2_image installed to do so along with a C++ compiler. All other libraries are included in the C++ compiler.


How to play:
	Your current health and movement are shown in the bottom corners. For each movement you may move a tile. Click on a tile within range of the character to move. 
	You are only allowed to move to certain tiles (basic, loot, stairs, enemies). Basic tiles are the tiles all over, loot are the chests, stairs look like stairs, and enemies are 
	slime monsters. When stepping on loot chests you will recieve a buff (or rarely a debuff), stepping on stairs takes you to the next floor, and on an enemy removes them from
	the game. Try to get to as many floors as possible.
	
Happy Crawling!
