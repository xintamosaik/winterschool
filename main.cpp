#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include "winterschool.h"

int main( int argc, char* args[] )
{
  SDL_Init( SDL_INIT_VIDEO );
  SDL_Window* window = SDL_CreateWindow( "Winter School",
			     SDL_WINDOWPOS_UNDEFINED,
			     SDL_WINDOWPOS_UNDEFINED,	       
			     PIXELWIDTH * SCREEN_RATIO,
			     PIXELHEIGHT * SCREEN_RATIO,
			     SDL_WINDOW_SHOWN );
  SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
  SDL_Surface* Scene_Surf = SDL_CreateRGBSurface ( 0, PIXELWIDTH, PIXELHEIGHT, 32,0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF );

  SDL_Surface* surfacegrid[40][25];
  SDL_Rect grid[40][25];
  
  for (int i = 0; i < 40; i++){
    for (int j = 0; j < 25; j++){
      surfacegrid[i][j] = SDL_CreateRGBSurface ( 0, 8, 8, 32,0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF );
      grid[i][j].x = i*8;
      grid[i][j].y = j*8;
      grid[i][j].w = 8;
      grid[i][j].h = 8;
    }
  } 
  
SDL_Rect grid_five[8][5];
SDL_Surface* surfacegrid_five[8][5];
  for (int i = 0; i < 8; i++){
    for (int j = 0; j < 5; j++){
      surfacegrid_five[i][j] = SDL_CreateRGBSurface ( 0, 5*8, 5*8, 32,0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF );
      grid_five[i][j].x = i*8*5;
      grid_five[i][j].y = j*8*5;
      grid_five[i][j].w = 8*5;
      grid_five[i][j].h = 8*5;
    }
  } 

int color0 = DARKGREY;
int color1 = LIGHTGREY;
int color2 = ORANGE;
int alter0 = MEDIUMGREY;
int highlight = CYAN;
int shadow = BLACK;

int frnt_c1 = color0;
int frnt_c2 = alter0;
int frnt_t1 = color1;
int back_c1 = color0;
int back_t1 = color2;
int wall_c1 = color2;
int wall_t1 = color0;
int room_c1 = color1;
int room_t1 = color0;
int room_t2 = color2;

enum hex {A = 10, B = 11, C = 12, D = 13, E = 14, F=15 };  
int pattern_full[16] = {0,0, 0,0,  0,0, 0,0,  0,0, 0,0, 0,0, 0,0};
int pattern_tup1[16] = {0,0, 0,0,  0,0, 0,0,  0,3, 0,D,  3,5, D,5};
int pattern_tup2[16] = {0,3, 0,D,  3,5, D,5,  5,5, 5,5,  5,5, 5,5};
int pattern_tdn2[16] = {0,0, 0,0,  0,0, 0,0,  C,0, 7,0,  5,C, 5,7};
int pattern_tdn1[16] = {C,0, 7,0,  5,C, 5,7,  5,5, 5,5,  5,5, 5,5};

SDL_Surface* surface8[16] = {};
surface8[frnt] = mkTile( pattern_full, frnt_c1, frnt_c2, frnt_t1, alter0  ); 
surface8[back] = mkTile( pattern_full, back_c1, back_c1, back_c1, alter0  ); 
surface8[room] = mkTile( pattern_full, room_c1, room_t1, room_t1, room_t2  ); 
surface8[wall] = mkTile( pattern_full, wall_c1, wall_t1, alter0, alter0  ); 

surface8[bwu1] = mkTile( pattern_tup1, back_c1, wall_c1, highlight, alter0  ); 
surface8[bwu2] = mkTile( pattern_tup2, back_c1, wall_c1, highlight, alter0  ); 
surface8[bwd1] = mkTile( pattern_tdn1, back_c1, wall_c1, highlight, alter0  ); 
surface8[bwd2] = mkTile( pattern_tdn2, back_c1, wall_c1, highlight, alter0  ); 

surface8[wru1] = mkTile( pattern_tup1, wall_c1, room_c1, highlight, alter0  ); 
surface8[wru2] = mkTile( pattern_tup2, wall_c1, room_c1, highlight, alter0  ); 
surface8[wrd1] = mkTile( pattern_tdn1, wall_c1, room_c1, highlight, alter0  ); 
surface8[wrd2] = mkTile( pattern_tdn2, wall_c1, room_c1, highlight, alter0  ); 

surface8[rfu1] = mkTile( pattern_tup1, room_c1, frnt_c1, highlight, alter0  ); 
surface8[rfu2] = mkTile( pattern_tup2, room_c1, frnt_c1, highlight, alter0  ); 
surface8[rfd1] = mkTile( pattern_tdn1, room_c1, frnt_c1, highlight, alter0  ); 
surface8[rfd2] = mkTile( pattern_tdn2, room_c1, frnt_c1, highlight, alter0  ); 

SDL_Rect tile_rect = {0,0,8,8};
SDL_Surface* tile_surf25[16];

for (int t = 0; t < 16; t++){
  tile_surf25[t] = SDL_CreateRGBSurface ( 0, 40, 40, 32,0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF );
  for (int i = 0; i < 5; i++){
    for (int j = 0; j < 5; j++){     
      tile_rect.x=i*8;
      tile_rect.y=j*8;
      SDL_BlitSurface(surface8[room_patterns[t][j][i]], NULL, tile_surf25[t], &tile_rect); 
    }
  }
}

for (int i = 0; i < 5; i++){
  for (int j = 0; j < 8; j++){
    surfacegrid_five[i][j] = tile_surf25[pattern_Grid[i][j]];
    SDL_BlitSurface(surfacegrid_five[i][j], NULL, Scene_Surf, &grid_five[j][i]);
  }
}
SDL_Texture* Statics = SDL_CreateTextureFromSurface(renderer, Scene_Surf);

  SDL_Event e;
  bool quit = false;
  
  while( !quit )
  {
    while( SDL_PollEvent( &e ) != 0 ) {
      if( e.type == SDL_QUIT ) { quit = true; }
      else if (e.type == SDL_KEYDOWN ){ EventSwitch ( e ); }
    }    
    SDL_RenderClear 	( renderer);
    SDL_RenderCopy 	( renderer, Statics, NULL, NULL );
 
    SDL_RenderPresent 	( renderer);
  }
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);

  SDL_Quit();
  return 0;
}

uint32_t convertSDLColor (SDL_Color color){ return color.r*256*256 + color.g * 256 +color.b; }

bool EventSwitch(SDL_Event event)
{
  switch (event.key.keysym.sym)
  {
    case SDLK_UP:
      std::cout << "Up \n";
      break;
    case SDLK_DOWN:
      std::cout << "Down \n";
      
      break;
    case SDLK_RIGHT:
      std::cout << "Right \n";
      
      break;
    case SDLK_LEFT:
      std::cout << "Left \n ";
      break;

    default:
      break;
  }
}


SDL_Surface* mkTile(int* pattern, uint32_t x_col, uint32_t o_col, uint32_t i_col, uint32_t y_col){
  
SDL_Surface* surface1 = SDL_CreateRGBSurface(0, 8, 8, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF  );
  
  std::vector<uint32_t> pixels(surface1->h * surface1->pitch, 0);
  for (int i = 0;i < 16 ;i++){
    //if (i == 0 || !(i%2) ) std::cout << "Reihe " << i/2 << " : " <<std::endl;
    //std::cout << "Pixel " << i*4 << "-" << ((i+1)*4)-1 << " was declared " << patternz[i];
    
    switch (pattern[i]){
      case 0x0: case 0x4: case 0x8: case 0xC:
	pixels[4*i+2] = x_col;
	pixels[4*i+3] = x_col;
	//  std::cout << " .. so pixel " << 4*i << "-" << 4*i+1 << " are colored Black ";
	break;
      case 0x1: case 0x5: case 0x9: case 0xD: 
	pixels[4*i+2] = o_col;
	pixels[4*i+3] = o_col;
	// std::cout << " .. so pixel " << 4*i << "-" << 4*i+1 << " are colored White ";
	break;
      case 0x2: case 0x6: case 0xA: case 0xE:
	pixels[4*i+2] = i_col;
	pixels[4*i+3] = i_col;
	//std::cout << " .. so pixel " << 4*i << "-" << 4*i+1 << " are colored Green ";
	break;
      case 0x3: case 0x7: case 0xB: case 0xF:
	pixels[4*i+2] = y_col;
	pixels[4*i+3] = y_col;
	// std::cout << " .. so pixel " << 4*i << "-" << 4*i+1 << " are colored Violet";
	break;
    }
    switch (pattern[i]){  
      case 0x0: case 0x1: case 0x2: case 0x3: 
	pixels[4*i] = x_col; 
	pixels[4*i+1] = x_col; 
	// std::cout << " and " << 4*i+2 << "-" << 4*i+3 << " are colored Black " << std::endl;
	break;
	
      case 0x4: case 0x5: case 0x6: case 0x7: 
	pixels[4*i] = o_col; 
	pixels[4*i+1] = o_col;
	// std::cout << " and " << 4*i+2 << "-" << 4*i+3 << " are colored White " << std::endl;
	break;
	
      case 0x8:case 0x9:case 0xA:case 0xB:
	pixels[4*i] = i_col; 
	pixels[4*i+1] = i_col;  
	// std::cout << " and " << 4*i+2 << "-" << 4*i+3 << " are colored Green " << std::endl;
	break;
	
      case 0xC:case 0xD:case 0xE:case 0xF:
	pixels[4*i] = y_col;
	pixels[4*i+1] = y_col;
	// std::cout << " and " << 4*i+2 << "-" << 4*i+3 << " are colored Violet " << std::endl;
	break;
	
    }
  }
  SDL_LockSurface(surface1);
  memcpy(surface1->pixels, pixels.data(), surface1->pitch * surface1->h);
  SDL_UnlockSurface(surface1);  
  return surface1;
}


/*
SDL_Surface* mkBack(SDL_Surface* background) {
  SDL_Rect surf_rect = { 0, 0, 8, 8 };
  SDL_Surface* BG_Surf = SDL_CreateRGBSurface(0, 320, 200, 32,0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF );
  for (int j = 0; j < 25; j++) {  
    for (int i = 0; i < 40; i++) { 
      surf_rect.x = i * 8;
      surf_rect.y = j * 8;
      SDL_BlitSurface(background, NULL, BG_Surf, &surf_rect);
    }    
  }
  return BG_Surf;
}*/


// SDL_Surface* mkRoom(SDL_Surface* wallpaper, SDL_Surface* edge2, SDL_Surface* edge1){
// 
//   int size = 8;
//   SDL_Surface* surf = SDL_CreateRGBSurface(0, size*TILESIZE*2, size*TILESIZE, 32,0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF );
//   SDL_Rect surf_rect = { 0, 0, TILESIZE, TILESIZE };
//   for (int i = 0; i < size; i++){ 
//     surf_rect.x = TILESIZE*i*2;
//     surf_rect.y = TILESIZE*i;
//     SDL_BlitSurface(edge2, NULL , surf, &surf_rect);
//     surf_rect.x += TILESIZE;
//     SDL_BlitSurface(edge1, NULL , surf, &surf_rect);
//     for (int j = 0; j < i; j++){ 
//       surf_rect.x = TILESIZE * j * 2; 
//       surf_rect.y = TILESIZE * i;
//       SDL_BlitSurface( wallpaper, NULL , surf, &surf_rect);
//       surf_rect.x += TILESIZE; 
//       SDL_BlitSurface( wallpaper, NULL , surf, &surf_rect); 
//     }
//   }
//   return surf;
// }

/*  
SDL_Surface* mkWall_l(SDL_Surface* wallpaper, SDL_Surface* edge2, SDL_Surface* edge1){

  int size = 8;
  SDL_Surface* surf = SDL_CreateRGBSurface(0, size*TILESIZE*2, size*TILESIZE, 32,0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF );
  SDL_Rect surf_rect = { 0, 0, TILESIZE, TILESIZE };
  for (int i = 0; i < size; i++){ 
    surf_rect.x = TILESIZE*i*2;
    surf_rect.y = TILESIZE*i;
    SDL_BlitSurface(edge2, NULL , surf, &surf_rect);
    surf_rect.x += TILESIZE;
    SDL_BlitSurface(edge1, NULL , surf, &surf_rect);
    for (int j = 0; j < i; j++){ 
      surf_rect.x = TILESIZE * j * 2; 
      surf_rect.y = TILESIZE * i;
      SDL_BlitSurface( wallpaper, NULL , surf, &surf_rect);
      surf_rect.x += TILESIZE; 
      SDL_BlitSurface( wallpaper, NULL , surf, &surf_rect); 
    }
  }
  return surf;
}*/

// SDL_Surface* mkSide(bool invert, int size, SDL_Surface* all_x_surf, SDL_Surface* all_o_surf, SDL_Surface* all_y_surf) {
//  int width=4;
//  int height=8;
//  SDL_Rect test_rect {0,0,width,height};
// 
//  SDL_Surface* testpattern = SDL_CreateRGBSurface ( 0, size*width*2, size*height, 32,0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF );
// for (test_rect.y = 0; test_rect.y < size * height; test_rect.y += height) {
//   if (invert){ 
//  for (test_rect.x = 0; test_rect.x < size * width *2; test_rect.x += width*2){
//    if (test_rect.y <  test_rect.x) SDL_BlitSurface(all_x_surf, NULL, testpattern, &test_rect);
//    if (test_rect.y >  test_rect.x) SDL_BlitSurface(all_o_surf, NULL, testpattern, &test_rect);
//    if (test_rect.y == test_rect.x) SDL_BlitSurface(all_y_surf, NULL, testpattern, &test_rect);
// } 
//     
//   }
// else {
//    for (test_rect.x = 0; test_rect.x < size * width *2; test_rect.x += width*2){
//    if (test_rect.y < size*height - test_rect.x) SDL_BlitSurface(all_x_surf, NULL, testpattern, &test_rect);
//    if (test_rect.y > size*height- test_rect.x) SDL_BlitSurface(all_o_surf, NULL, testpattern, &test_rect);
//    if (test_rect.y == size*height -test_rect.x) SDL_BlitSurface(all_y_surf, NULL, testpattern, &test_rect);
// }
// 
// }
//   
// }
// return testpattern;
// }
// 
// 
// 

