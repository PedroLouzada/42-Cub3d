*This project has been created as part of the 42 curriculum by mrapp-he, pbongiov.*

---

# cub3D

A 2.5D first-person raycasting game built in C with MiniLibX, inspired by the pioneering techniques behind *Wolfenstein 3D*.

---

## Description

**cub3D** is a graphical application that simulates a first-person perspective inside a maze using the **raycasting** technique — a method that renders a 3D-looking environment from a 2D map grid, computing wall distances and heights per column of pixels.

The project is split into two distinct experiences:

- **Tutorial level (`map[0]`)** — loaded and validated from a `.cub` configuration file. This level demonstrates the parsing pipeline and serves as an introduction to the game world. No enemy is present.
- **Procedurally generated levels (`map[1..5]`)** — created at startup, featuring doors, exit tiles, and an enemy with line-of-sight AI. Completing all five levels ends the game.

### Key Features

- 2.5D raycasting renderer with wall textures and floor/ceiling shading
- Thread pool–based raycasting for parallel ray computation
- Flashlight effect with HUD indicators (battery, stamina)
- Minimap overlay during gameplay
- Door interaction and level progression
- Enemy AI with independent movement and line-of-sight logic
- Full menu system with controls and instructions screens
- `.cub` map parsing with flood-fill closed-map validation

---

## Instructions

### Requirements

- Linux (X11 environment)
- `cc` (C compiler)
- `make`
- X11 development libraries: `libX11-dev`, `libXext-dev`

Install dependencies on Debian/Ubuntu:

```bash
sudo apt-get install libx11-dev libxext-dev
```

### Compilation

```bash
make
```

Other useful targets:

```bash
make clean    # remove object files
make fclean   # remove object files and binary
make re       # full rebuild
```

### Running

```bash
./cub3D maps/tutorial.cub
```

Makefile shortcuts:

```bash
make r   # rebuild and run with tutorial map
make v   # rebuild and run under Valgrind (memcheck)
make t   # rebuild and run under Helgrind (thread check)
```

### Controls

**Menus**

| Input | Action |
|---|---|
| `Left Click` | Navigate menus (start, controls, tutorial screens) |

**Gameplay**

| Input | Action |
|---|---|
| `W A S D` | Move |
| `Shift` | Sprint |
| `Ctrl` | Slow walk |
| `Left / Right Arrow` | Rotate camera |
| `Tab` | Toggle mouse-look mode |
| `Mouse` | Rotate camera (when mouse-look is active) |
| `F` | Toggle flashlight |
| `E` | Interact with door / use exit tile |
| `Q` | Leave tutorial/instructions screen |
| `Esc` | Quit |

### Map File Format (`.cub`)

The `.cub` file defines textures, colors, and the map grid. The parser enforces:

- Valid map characters only
- Exactly one player spawn marker
- A fully enclosed map (validated via flood-fill)
- Door (`D`) and wall/floor/empty tile definitions

---

## Resources

### Raycasting & Graphics

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — the primary reference for the raycasting algorithm, wall rendering, and texture mapping used in this project.
- [MiniLibX Documentation (42 Linux)](https://harm-smits.github.io/42docs/libs/minilibx) — reference for the MiniLibX windowing and drawing API.
- [Wolfenstein 3D Game Mechanics](https://en.wikipedia.org/wiki/Wolfenstein_3D) — historical background on the raycasting technique this project is inspired by.
- [X11 Programming Basics](https://tronche.com/gui/x/xlib/) — low-level X11 documentation relevant to MiniLibX internals.

### Threading & Performance

- [POSIX Threads (pthreads) — man pages](https://man7.org/linux/man-pages/man7/pthreads.7.html) — reference for the thread pool implementation used in the raycasting pipeline.

---

### AI Usage

AI tools (specifically **Claude by Anthropic**) were used during the development of this project for the following tasks:

- **Debugging** — identifying logic errors in raycasting geometry, texture coordinate calculation, and thread synchronisation issues.
- **Code review** — reviewing C code for memory safety, pointer correctness, and undefined behaviour.
- **Documentation** — drafting and structuring documentation, including this README.
- **Algorithm explanations** — clarifying mathematical concepts such as DDA (Digital Differential Analysis), FOV projection, and flood-fill validation.

AI was used as a reference and review assistant. All architectural decisions, implementation choices, and final code were written and validated by the project authors.