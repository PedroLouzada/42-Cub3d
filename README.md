# cub3D (42-Cub3d)

A first-person raycasting game built in C with MiniLibX.

This project mixes:
- a **parsed tutorial map** (`map[0]`, loaded from `.cub` file), and
- **procedurally generated levels** (`map[1..5]`) with doors, exits, and enemy AI.

---

## Features

- 2.5D raycasting renderer (wall textures, floor/ceiling shading)
- Threaded player raycasting (`thread pool` based)
- Menu + controls screen + gameplay screens
- Flashlight effect and HUD battery/stamina indicators
- Minimap overlay in gameplay levels
- Door interaction (`E`) and level progression via exit tiles
- Enemy object present in generated levels (`map[1..5]`)
- Tutorial/parsed level (`map[0]`) without enemy

---

## Project Layout

```text
src/
  engine/      # game loop, drawing, raycasting, input hooks, map creation
  objects/     # player, enemy, door logic
  parsing/     # .cub parsing and validation for tutorial map
  utils/       # drawing/math/string/time helpers + cleanup
lib/
  minilibx-linux/
maps/
  tutorial.cub # tutorial/parsing input map
  level_*.cub  # generated levels output
```

---

## Requirements

- Linux (X11)
- `cc` (C compiler)
- `make`
- X11 dev packages required by MiniLibX (`X11`, `Xext`, `z`, `m`)

> The Makefile links with:
> `-lmlx -lXext -lX11 -lm -lz`

---

## Build

```bash
make
```

Useful targets:

```bash
make clean
make fclean
make re
```

Run helper targets (from Makefile):

```bash
make r   # rebuild + run maps/tuturial.cub
make v   # rebuild + valgrind
make t   # rebuild + helgrind
```

Manual run:

```bash
./cub3D maps/tuturial.cub
```

---

## Controls

### Menus
- `Mouse Left Click`:
  - Start game
  - Open controls screen
  - Open tutorial/instructions screen

### Gameplay
- `W A S D`: move
- `Shift`: sprint
- `Ctrl`: slow walk
- `Left/Right Arrow`: rotate
- `Tab`: toggle mouse-look mode
- `Mouse`: rotate camera (when mouse-look is active)
- `F`: toggle flashlight
- `E`: interact with door / exit
- `Q`: leave tutorial/instructions screen
- `Esc`: quit

---

## Game Flow

1. Program starts with parsed map from the provided `.cub` file (`map[0]`).
2. Additional maps (`map[1..5]`) are generated at startup.
3. Entering gameplay from the title sets current map to level 1.
4. In generated levels:
   - enemy updates and rendering are enabled,
   - doors can be toggled,
   - exit tile (`S`) advances to next level.
5. Reaching past level 5 ends the game.

---

## Parsing Notes

The parser validates:
- map dimensions/content
- allowed characters
- exactly one player spawn marker (`P` after direction normalization)
- closed map via flood-fill validation

During parsing, object creation for `map[0]` is performed directly from parsed content:
- player object is created from parsed spawn
- door objects are created from `D` tiles
- enemy is intentionally not created for tutorial map

---

## Development Notes

- Rendering path uses object-owned ray buffers (`player->ray`, `enemy->ray`).
- `cast_rays`/`reduced_ray` are currently player-render oriented.
- Enemy logic remains independent (`enemy_los`, movement/AI files).
- This repository appears to be under active merge/refactor work; if you see build issues, check recent branch integration changes first.

---

## Troubleshooting

### MiniLibX / X11 link errors
Install Linux X11 development libraries, then rebuild:

```bash
make fclean
make
```

### Runtime issues after merges
- Re-run from clean state:

```bash
make re
```

- Verify key API signatures across files (`functions.h` vs `.c` definitions).
- Check for duplicate global symbol definitions when linker errors appear.

---

## Authors

Project by `mrapp-he` and `pbongiov`.
