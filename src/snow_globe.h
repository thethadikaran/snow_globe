#ifndef __SNOW_GLOBE_HEADER__
#define __SNOW_GLOBE_HEADER__

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>    // for using usleep()
#include <time.h>      // for using time()


#define GLOBE_FILE   "../resource/globe.txt"

#define WAIT_TIME       190      // time in milli seconds
#define MAX_HEIGHT      25
#define MAX_WIDTH       73
#define SNOW_DENSITY    75      // no of snow particles to render
#define MAX_SPEED       3       // 1 - low, 3 - high

extern char PARTICLES[];

// struct representation of Snow Particle
// speed should be a value b/w 1 to 3
typedef struct {
  char particle;
  int y, x, speed;
} snow_particle;


void init_globe();

void destroy_globe();

void throw_error_nd_exit(char*);


void render_globe(WINDOW*, char*);

char* read_file();

size_t calculate_file_size(FILE*, size_t);


WINDOW* generate_snow_window();

snow_particle** generate_snow();

void render_snow(WINDOW*, snow_particle**);

void update_snow(snow_particle**);


#endif   
