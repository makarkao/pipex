/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:59:49 by makarkao          #+#    #+#             */
/*   Updated: 2025/02/27 13:37:05 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# elif BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

typedef struct s_gnlsv
{
	ssize_t	k;
	char	*s;
}			t_gnlsv;

typedef struct s_gnlnsv
{
	ssize_t	j;
	ssize_t	i;
	char	*l;
}			t_gnlnsv;

typedef struct sp_var
{
	size_t	i;
	size_t	j;
	size_t	k;
}			t_spvar;

char		*ft_itoa(int x);
char		*ft_strcpy(char *str, char *s);
size_t		ft_strlen(char *str);
size_t		ft_strchr(char *str, ssize_t *j, char c);
char		*ft_sub(char *str, char *s, ssize_t *k, size_t size2);
int			ft_putchar(int fd, char c);
int			ft_putstr(int fd, char *s);
int			ft_putnbr(int fd, int n);
char		**ft_split(char *s, char c);
void		free_string(char **str, size_t k);
int			ft_tstrslen(char **strs, int size);
size_t		ft_strslen(char **strs);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strncmp(char *s1, char *s2, size_t n);
char		*ft_strdup(char *s);
int			ft_strcmp(char *s1, char *s2);
int			ft_chrinstr(char *str, char c);
char		**ft_sqsplit(char *s, char c);
#endif
