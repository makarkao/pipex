/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:01:48 by makarkao          #+#    #+#             */
/*   Updated: 2025/02/27 13:41:08 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "./libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct pipex_s
{
	int		cmd_c;
	int		infilefd;
	int		outfilefd;
	char	**cmd_path;
	char	***cmd;
	pid_t	*pid;
	int		**pipefd;
	int		herdoc;
	int		piphdc[2];
	char	*ll;
}			t_pipex;

void		ft_freestrs(char **strs);
void		ft_freepcmds(char **pcmds, int cmd_c);
void		ft_freecmds(char ***cmds, int cmd_c);
void		cmds_handler(char **av, char **ev, t_pipex *p);
void		cleanpip(t_pipex *p);
int			errnov(void);
void		free_pip(int **pid, int n);
char		*ft_slashjoin(char *s1, char *s3);
void		fill_herefoc(char **av, t_pipex *p);
char		*cmds_paths(char **ev);
void		init_pip(t_pipex *p, int ac, char **av);
void		manage_flow(t_pipex *p, char **av, int i);
void		close_pipes(t_pipex *p);
void		global_init(int ac, char **av, char **ev, t_pipex *p);
char		*get_next_line(int fd, t_pipex *p);

#endif