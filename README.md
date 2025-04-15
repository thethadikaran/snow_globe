<div align="center">
<h2>:mountain_snow: <b>Snow Globe</b> :snowman: </h2>

<!-- badge section -->
<img alt="c badge" src="https://img.shields.io/badge/C-11-blue">
<img alt="ncurses badge" src="https://img.shields.io/badge/ncurses-6.5-yellow">
<img alt="cmake badge" src="https://img.shields.io/badge/cmake-3.30-gree">
</div>

<br>
<br>

<h6>SCREEN CAST</h6>

![screencast](resource/screen_cast.gif)


<h6>BUILD & RUN</h6>

```bash
# PRE-REQUISITE - install NCurses library
# for MSYS2 terminal in Windows
pacman -S mingw-w64-x86_64-ncurses     

# for debian based systems
sudo apt-get install libncurses5-dev libncursesw5-dev     

# for fedora based systems
sudo dnf install ncurses-devel     

# BUILD - using cmake, build the files
cd snow_globe; mkdir build; cd build
cmake ..

# RUN
./snow_globe
```
