#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <curses.h>
# include "classes.h"
# include <sys/time.h>
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"

//========================== PARSING =====================

void    parsing(int ac, char **av, t_game *game);
void	parse_exit(char *s, void *arg);

//=========================== UTILS ======================

int     ft_strlen(char *s);
char	*get_next_line(int fd);
char	*ft_strrchr(char *str, int c);
int		ft_isempty(char c);
size_t	ft_strlcpy(char *dest, char *src, size_t size);

#endif