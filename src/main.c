#include "snow_globe.h"



int main() {
  // initialize NCurses and snow globe parameters
  init_globe();

  // create a new window to render the snow particle
  WINDOW *snow_win = generate_snow_window();

  // generate snow particles (array of 'struct pointer')
  snow_particle **snows = generate_snow();

  // read globe file in to an array
  char *file_data = read_file();

  while (TRUE) {
    // clear the newly created window (snow_win)
    werase(snow_win);
    
    render_globe(snow_win, file_data);

    render_snow(snow_win, snows);

    update_snow(snows);

    // redraw the border for every iteration
    box(snow_win, 0, 0);

    wrefresh(snow_win);

    napms(190);
  }

  delwin(snow_win);
  destroy_globe();

  return 0;
}