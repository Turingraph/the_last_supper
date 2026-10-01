#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

// atoi.c

int		f_atoi(const char *src,
			bool *is_int, const char *base, size_t digits);
size_t	ft_putnbr_fd(int n, int fd, const char *base, size_t digits);

// math.c

int		f_abs(int x);
int		f_max(int a, int b);
float	f_floor(float num);
int		f_interval(int num, int min, int max);
float	f_round(float num);

// string.c

void	*malloc_talk(size_t elem_size, const char *comment);
size_t	f_strlen(const char *str);
size_t	knight_of_coin(const char *str, char stop);

#endif
