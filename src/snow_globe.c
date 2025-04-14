#include "snow_globe.h"

char PARTICLES[] = {'.', '`', '\'', '*', '+', '\"', ',', ';', ':'};



void init_globe() {
  initscr();       // initialize ncurses
  cbreak();        // disable line buffering
  noecho();        // don't echo input characters
  curs_set(0);     // make cursor invisible

  refresh();       // just to update curscr same as stdscr

  // seed the random no generator
  srand(time(NULL));

  if (curs_set(0) != OK) 
    throw_error_nd_exit("Terminal don't support cursor hidding");
}



void destroy_globe() {
  curs_set(1);     // make cursor visible

  clear();
  refresh();

  endwin();
}



void throw_error_nd_exit(char *err) {
  destroy_globe();
  puts(err);
  exit(EXIT_FAILURE);  
}



void render_globe(WINDOW *win, char *file_data) {
  for (int i = 0; i < strlen(file_data); i++)
    waddch(win, file_data[i]);
  
  refresh();
}



WINDOW* generate_snow_window() {
  WINDOW *s_win = newwin(MAX_HEIGHT, MAX_WIDTH, 0, 0);

  // draw a border around the window
  box(s_win, 0, 0);

  return s_win;
}



snow_particle** generate_snow() {
  // array of snow struct references (array of pointers)
  snow_particle **snows = malloc(SNOW_DENSITY * sizeof(snow_particle *));
  if (snows == NULL)
    throw_error_nd_exit("Memory allocation failed for snow particle array");
  
  // initialize snow particles & setup preliminary parameters
  for (int snow = 0; snow < SNOW_DENSITY; snow++) {
    // allocated memory for each snow
    snows[snow] = malloc(sizeof(snow_particle));
    if (snows[snow] == NULL)
      throw_error_nd_exit("Memory allocation failed for a Snow struct");
    
    
    // calculate no of character used as snow particles
    int particles_cnt = sizeof(PARTICLES) / sizeof(PARTICLES[0]);

    snows[snow]->particle = PARTICLES[rand() % particles_cnt];   // index = 0 -> particles_cnt
    snows[snow]->x = (rand() % (MAX_WIDTH - 2)) + 1;             // x = 1 -> (MAX_WIDTH - 2)
    snows[snow]->y = (rand() % (MAX_HEIGHT- 1)) + 1;             // y = 1 -> (MAX_HEIGHT - 1)
    snows[snow]->speed = rand() % MAX_SPEED + 1;                 // speed = 1 -> MAX_SPEED
  }

  return snows;
}



void render_snow(WINDOW *win, snow_particle **snows) {
  for (int snow = 0; snow < SNOW_DENSITY; snow++) {
    mvwaddch(
      win,
      snows[snow]->y,
      snows[snow]->x,
      snows[snow]->particle
    );
  }
}



void update_snow(snow_particle **snows) {
  for (int snow = 0; snow < SNOW_DENSITY; snow++) {
    // update the positon of y by incrementing the speed
    snows[snow]->y += snows[snow]->speed;

    if (snows[snow]->y > MAX_HEIGHT - 1) {
      snows[snow]->y = 1;

      // randomize x position, while resetting the y 
      snows[snow]->x = rand() % (MAX_WIDTH - 2) + 1;
    }
  }
}



size_t calculate_file_size(FILE *fptr, size_t bytes_per_element) {
  // move to the end of the file
  fseek(fptr, 0, SEEK_END);

  // get the current position (ie. size of the file)
  long file_size = ftell(fptr);

  // move back to the beginning of the file
  fseek(fptr, 0, SEEK_SET);

  return (file_size / bytes_per_element);  
}



char* read_file() {
  FILE *fptr;
  if ( !(fptr = fopen(GLOBE_FILE, "r")) ) 
    throw_error_nd_exit("Reading Globe file failed");
  

  // as we are consider the contents of the file to be characters
  // bytes_per_element will be size of single character  
  size_t file_size = calculate_file_size(fptr, sizeof(char));

  char *file_content = malloc(file_size * sizeof(char));
  if (file_content == NULL)
    throw_error_nd_exit("Memory allocation of character array failed");
  
  // read the file data into the array
  fread(file_content, sizeof(char), file_size, fptr);

  // finally close the file
  fclose(fptr);

  return file_content;
}
