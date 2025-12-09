#include "cub3d.h"

void	*ft_calloc(size_t nm, size_t sz)
{
	size_t	size;
	t_str	data;
	void	*alloc;

	size = nm * sz;
	if (nm > SIZE_MAX / sz)
		return (NULL);
	if (!nm || !sz)
		size = 1;
	alloc = malloc(size);
	if (!alloc)
		return (NULL);
	data = (t_str)alloc; 
	while (size--)
		*data++ = '\0';
	return (alloc);
}
