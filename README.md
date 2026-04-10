# cub3D

## 🎮 About the Project

**cub3D** is one of the most visually striking and technically demanding projects of the 42 curriculum.  
Its goal: build a fully functional **2.5D first-person raycasting engine**, rendering a 3D-looking maze from a 2D map grid — just like the legendary *Wolfenstein 3D*.

This project pushed my understanding of **graphics programming, math, and systems** to a completely new level.  
I developed it in partnership with **[mrapp-he](https://github.com/mrapp-he)** 👥

---

## 🧠 What I Learned

- Implementing a **raycasting engine** from scratch:
  - DDA (Digital Differential Analysis) algorithm
  - Wall distance and height projection per pixel column
  - Texture mapping with correct perspective correction
- Working with **MiniLibX**, a minimal X11 windowing library:
  - Pixel-level image rendering
  - Event and hook management
- Writing a **robust `.cub` file parser**:
  - Texture and color configuration
  - Map grid validation
  - Flood-fill closed-map enforcement
- Building a **thread pool** for parallel raycasting:
  - POSIX threads (`pthreads`)
  - Synchronisation with mutexes and barriers
- Implementing **gameplay systems**:
  - Door interaction and level transitions
  - Enemy AI with line-of-sight detection
  - Flashlight effect with HUD (battery, stamina)
  - Procedural level generation
- Ensuring **memory safety** across a multi-threaded, graphics-heavy codebase.

---

## ⚙️ Features Implemented

### ✅ Core Features

- 2.5D raycasting renderer with wall textures and floor/ceiling shading
- Thread pool–based ray computation for performance
- `.cub` map parsing with full validation pipeline
- Flood-fill enclosed-map checker
- Flashlight toggle with HUD indicators
- Minimap overlay during gameplay
- Door interaction and exit tiles
- Enemy AI with independent movement and line-of-sight logic
- Procedurally generated levels (maps 1–5)
- Full menu system with controls and instructions screens

---

## 🖥️ How to Use

### Requirements

- Linux (X11 environment)
- `cc` and `make`
- X11 dev libraries:

```bash
sudo apt-get install libx11-dev libxext-dev
```

### Compile & Run

```bash
git clone git@github.com:PedroLouzada/42-Cub3d.git
cd cub3D
make
./cub3D maps/tutorial.cub
```

### Makefile Shortcuts

```bash
make r   # rebuild and run with tutorial map
make v   # rebuild and run under Valgrind (memcheck)
```

---

## 🕹️ Controls

| Input | Action |
|---|---|
| `W A S D` | Move |
| `Shift` | Sprint |
| `Ctrl` | Slow walk |
| `← →` | Rotate camera |
| `Tab` | Toggle mouse-look |
| `Mouse` | Rotate (mouse-look mode) |
| `F` | Toggle flashlight |
| `E` | Interact with door / exit tile |
| `Esc` | Quit |

---

## 🗺️ Map File Format (`.cub`)

The `.cub` file defines textures, colors, and the maze layout. The parser enforces:

- Valid map characters only
- Exactly one player spawn marker
- A fully enclosed map (flood-fill validated)
- Door (`D`) and tile definitions

---

## 🚀 Future Improvements

- Add sound effects using a cross-platform audio library.
- Implement a level editor with real-time `.cub` preview.

---

## 💡 Final Thoughts

cub3D was one of the most **mind-expanding** projects I've worked on at 42.  
There's something genuinely magical about watching a 2D array of characters transform into a navigable 3D world — column by column, ray by ray.

It taught me how early game developers built immersive worlds with almost no hardware to rely on, using nothing but clever math and sheer ingenuity.

---

## 📬 Contact

Feel free to reach out:  
[GitHub](https://github.com/mrapp-he)
