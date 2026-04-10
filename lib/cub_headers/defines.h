/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:06:04 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/10 17:26:43 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "cub3d.h"

# define E 0
# define P 1
# define STUCK 0
# define RESPAWN 1
# define MEMORY 2
# define FOV 0.6
# define K_ESC 65307
# define K_TAB 65289
# define CTRL 65507
# define K_F 102
# define K_W 119
# define K_A 97
# define K_S 115
# define K_D 100
# define K_E 101
# define K_Q 113
# define SHIFT 65505
# define K_RIGHT 65363
# define K_LEFT 65361
# define NORTH 1
# define EAST 2
# define WEST 3
# define SOUTH 4
# define RANGE 5
# define MAX_P 200
# define MIN_P 50
# define TILE_SZ 14
# define RIGHT 0
# define LEFT 1
# define BACK 2
# define VERTICAL 0
# define MAX_DIST 5
# define MIN_MOVES 2
# define HORIZONTAL 1
# define FOV_ANGLE 60
# define MAX_MOVES 10
# define MIN_DOORS 10
# define MAX_DOORS 15
# define MAP_WIDTH 60
# define MAP_HEIGHT 30
# define RADIUS 0.3
# define WALL 0xE4E6A8
# define FLOOR 0xC6C58B
# define BLUE 0x0000FF
# define BLACK 0x000000
# define GREEN 0x00FF00
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define PINK 0xFF69B4
# define PURPLE 0x800080
# define CLEAR 16711935
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define CENTER_Y 150
# define PERMISSIONS 0644
# define CEILING 0xE1E2BB
# define TITLE "||BACKROOMS | CUB3D||"
# define MLX_ERR "Error on mlx initialization"
# define ALLOC_ERR "Error: Memory Allocation"
# define GAME_WON "CONGRATULATIONS!"
# define GAME_OVER "GAME OVER!"
# define BUFFER 0
# define BACKGROUND 1
# define BUTTON1 2
# define BUTTON2 3
# define BUTTON3 4
# define BUTTONBORDER 5
# define WASDIMG 6
# define ARROWS 7
# define MOUSEIMG 8
# define BACKBUTTON 9 
# define BACKBORDER 10 
# define PLAYERIMG 11 
# define HEART 29
# define Q_KEYIMG 16
# define EXIT 17
# define N_ASSETS 30

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# ifndef M_PI_2
#  define M_PI_2 1.57079632679489661923
# endif
# ifndef M_PI_4
#  define M_PI_4 0.78539816339744830962
# endif

#endif