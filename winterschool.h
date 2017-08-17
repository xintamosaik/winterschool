const int PIXELWIDTH 	= 320;
const int PIXELHEIGHT 	= 200;
const int SCREEN_RATIO = 4;
const int TILESIZE 	= 8;     
const int TILE_WIDTH 	= 40;
const int TILE_HEIGHT 	= 25;
const int COLOR_DEPTH 	= 32;
const int RGB_MASK_RED 	= 0xFF000000;
const int RGB_MASK_GREEN 	= 0x00FF0000;
const int RGB_MASK_BLUE 	= 0x0000FF00;
const int RGB_MASK_ALPHA 	= 0x000000FF;
const uint32_t WHITE 	= 0xFFFFFFFF;
const uint32_t BLACK 	= 0x000000FF;
const uint32_t RED 	= 0x880000FF;
const uint32_t CYAN 	= 0xAAFFEEFF;
const uint32_t PURPLE 	= 0xCC44CCFF;
const uint32_t GREEN 	= 0x00CC55FF;
const uint32_t BLUE 	= 0x0000AAFF;
const uint32_t YELLO 	= 0xEEEE77FF;
const uint32_t ORANGE 	= 0xDD8855FF;
const uint32_t BROWN 	= 0x664400FF;
const uint32_t LIGHTRED = 0xFF7777FF;
const uint32_t DARKGREY = 0x333333FF;
const uint32_t MEDIUMGREY=0x777777FF;
const uint32_t LIGHTGREEN=0xAAFF66FF;
const uint32_t LIGHTGREY= 0xBBBBBBFF;

enum {
  frnt, back, room, wall, 
  bwu1, bwu2, bwd1, bwd2,
  wru1, wru2, wrd1, wrd2,
  rfu1, rfu2, rfd1, rfd2
};

int pattern_Grid [5][8] = {
  bwu1, bwu2, wall, wall, wall, wall, bwd1, bwd2,
  wall, wall, wru1, wru2, wrd1, wrd2, wall, wall,
  wru1, wru2, room, room, room, room, wrd1, wrd2,
  rfd1, rfd2, room, room, room, room, rfu1, rfu2,
  frnt, frnt, rfd1, rfd2, rfu1, rfu2, frnt, frnt
};

int room_patterns[16][5][5] =
{ 
  frnt, frnt, frnt, frnt, frnt, 
  frnt, frnt, frnt, frnt, frnt,
  frnt, frnt, frnt, frnt, frnt,
  frnt, frnt, frnt, frnt, frnt,
  frnt, frnt, frnt, frnt, frnt,
  
  back, back, back, back, back,
  back, back, back, back, back, 
  back, back, back, back, back,
  back, back, back, back, back,
  back, back, back, back, back,
  
  room, room, room, room, room, 
  room, room, room, room, room, 
  room, room, room, room, room, 
  room, room, room, room, room, 
  room, room, room, room, room, 
  
  wall, wall, wall, wall, wall, 
  wall, wall, wall, wall, wall, 
  wall, wall, wall, wall, wall, 
  wall, wall, wall, wall, wall, 
  wall, wall, wall, wall, wall, 

  back, back, back, back, back,
  back, back, back, back, back, 
  back, back, back, back, bwu1,
  back, back, bwu1, bwu2, wall, 
  bwu1, bwu2, wall, wall, wall, 

  back, back, back, bwu1, bwu2, 
  back, bwu1, bwu2, wall, wall, 
  bwu2, wall, wall, wall, wall, 
  wall, wall, wall, wall, wall, 
  wall, wall, wall, wall, wall, 

  bwd1, bwd2, back, back, back,
  wall, wall, bwd1, bwd2, back,
  wall, wall, wall, wall, bwd1,
  wall, wall, wall, wall, wall,
  wall, wall, wall, wall, wall,
  
  back, back, back, back, back,  
  back, back, back, back, back, 
  bwd2, back, back, back, back,
  wall, bwd1, bwd2, back, back,  
  wall, wall, wall, bwd1, bwd2,
  
  wall, wall, wall, wall, wall,
  wall, wall, wall, wall, wall, 
  wall, wall, wall, wall, wru1,
  wall, wall, wru1, wru2, room, 
  wru1, wru2, room, room, room, 

  wall, wall, wall, wru1, wru2, 
  wall, wru1, wru2, room, room, 
  wru2, room, room, room, room, 
  room, room, room, room, room, 
  room, room, room, room, room, 

  wrd1, wrd2, wall, wall, wall,
  room, room, wrd1, wrd2, wall,
  room, room, room, room, wrd1,
  room, room, room, room, room,
  room, room, room, room, room,
 
  wall, wall, wall, wall, wall,  
  wall, wall, wall, wall, wall, 
  wrd2, wall, wall, wall, wall,
  room, wrd1, wrd2, wall, wall,  
  room, room, room, wrd1, wrd2,
  
  room, room, room, room, room,
  room, room, room, room, room, 
  room, room, room, room, rfu1,
  room, room, rfu1, rfu2, frnt, 
  rfu1, rfu2, frnt, frnt, frnt, 
   
  room, room, room, rfu1, rfu2, 
  room, rfu1, rfu2, frnt, frnt, 
  rfu2, frnt, frnt, frnt, frnt, 
  frnt, frnt, frnt, frnt, frnt, 
  frnt, frnt, frnt, frnt, frnt, 
 
  rfd1, rfd2, room, room, room,
  frnt, frnt, rfd1, rfd2, room,
  frnt, frnt, frnt, frnt, rfd1,
  frnt, frnt, frnt, frnt, frnt,
  frnt, frnt, frnt, frnt, frnt,

  room, room, room, room, room,  
  room, room, room, room, room, 
  rfd2, room, room, room, room,
  frnt, rfd1, rfd2, room, room,  
  frnt, frnt, frnt, rfd1, rfd2,
};


bool EventSwitch(SDL_Event event);
SDL_Surface* mkTile(int *pattern, uint32_t x_col, uint32_t o_col, uint32_t i_col, uint32_t y_col);

// - deactivated - SDL_Surface* mkSide(bool invert, int size, SDL_Surface* all_x_surf, SDL_Surface* all_o_surf, SDL_Surface* all_y_surf); 
// - deactivated - uint32_t convertSDLColor (SDL_Color color);
// - deactivated - SDL_Surface* mkBack(SDL_Surface* background);
// - deactivated - SDL_Surface* mkRoom(SDL_Surface* wallpaper, SDL_Surface* edge2, SDL_Surface* edge1);