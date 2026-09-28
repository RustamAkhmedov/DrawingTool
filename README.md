# DrawingTool

A small drawing program written in C++ with [raylib](https://www.raylib.com/).

**Try it in the browser:** https://rustamakhmedov.github.io/DrawingTool/

## Features

- Shapes: rectangle, circle, line, triangle
- 8 colours
- Select mode: click a shape to select it, drag to move it, delete it
- Undo and clear
- Save/load a drawing to `drawing.txt`

## Shortcuts

| Key | Action |
|---|---|
| `1`–`4` | Rectangle / Circle / Line / Triangle |
| `D` / `S` | Draw mode / Select mode |
| `Del` | Delete selected shape |
| `F` | Toggle fullscreen |

## Building (desktop)

Requires CMake ≥ 4.0 and a C++17 compiler. raylib 5.5 is downloaded automatically via `FetchContent`.

```bash
cmake -S . -B build
cmake --build build
./build/my_raylib_game
```

## Web version

`docs/` contains the WebAssembly build (compiled with Emscripten) that GitHub Pages serves. In the browser, *Save*/*Load* only write to the in-memory file system, so saved drawings are lost when you reload the page.
