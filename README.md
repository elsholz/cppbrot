# `cppbrot`

cppbrot is a terminal based Mandelbrot explorer.
You can use the keyboard to navigate the rendering. Terminal with color support required. Uses ncurses.

## What it looks like rn 🔥
![img of fractal shall appear here](https://github.com/elsholz/pybrot/blob/master/examples/2019-06-27-220018_1600x900_scrot.png "Mandelbrot.jpg😉")

## Usage
Execute `cmake-build-debug/cppbrot` or compile yourself. <br> 
To navigate aroung use VIM key bindings:
- `h` Move Left
- `j` Move Down
- `k` Move Up
- `l` Move Right
- `J` Zoom Out
- `K` Zoom In
- `+` Increase Iteration Count
- `-` Decrease Iteration Count
### If run with option `--julia`
- `w` Decrease Julia y constant
- `s` Increase Julia y constant
- `a` Decrease Julia x constant
- `d` Increase Julia x constant

### Command Line Options
- `--julia` Explore Julia Set instead of Mandelbrot Set
- `--auto-rotate` Anmate julia set. Automatically activates the `--julia` option as well. No User Interaction is possible, if this option is used.
- `--random-colors` Sets random values for the color variables. Good if you need a refreshing look.

## Further Development
For the future, I can imagine to take the output of the program `cli-visualizer` and use it to generate a music visualizer based on the Mandelbrot set. E.g. The levels of the different frequencies as visualized by cls-visualizer could be taken to set the colors for different iteration levels. Also the frequencies could affect the movement of a julia set.\
Another Option would be to add an option named `--split` and have a split view that shows the mandelbrot set and its corresponding julia set at the current position.

