/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prompt.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/24 09:52:17 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/24 13:26:25 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	join_git_colors(char *line, int fd, int *len, char **git_path)
{
	ft_strdel(git_path);
	if (!check_empty(fd, line))
	{
		ft_strdel(&line);
		*git_path = ft_strdup("\x1b[0;93m∆\x1b[0;m ");
		*len += 2;
		return (1);
	}
	*git_path = ft_strfjoin(ft_strdup("\x1b[92;1mgit:(\x1b[35;1m"), line);
	*git_path = ft_strfjoin(*git_path,
			ft_strdup("\x1b[92;1m)\x1b[0;93;1m ∆\x1b[0;m "));
	*len += 6;
	return (1);
}

static int	build_git_head(int fd, char **git_path, DIR *rep, int *len)
{
	char	*line;

	ft_strdel(git_path);
	line = NULL;
	get_next_line(fd, &line);
	if (!ft_strncmp(line, "ref: refs/heads/", 16))
	{
		ft_strfsub(&line, 16, ft_strlen(line) - 16);
		*len += ft_strlen(line);
		closedir(rep);
		return (join_git_colors(line, fd, len, git_path));
	}
	else if (!ft_strncmp(line, "ref: refs/", 10))
	{
		ft_strfsub(&line, 5, ft_strlen(line) - 5);
		*len += ft_strlen(line);
		closedir(rep);
		return (join_git_colors(line, fd, len, git_path));
	}
	return (0);
}

static char	*find_git_info(char *path, int *len)
{
	DIR				*rep;
	struct dirent	*file;
	int				fd;
	char			*git_path;

	if ((rep = opendir(path)))
	{
		while ((file = readdir(rep)))
			if (!ft_strcmp(file->d_name, ".git"))
			{
				git_path = ft_strjoin(path, "/");
				git_path = ft_strfjoin(git_path, ft_strdup(file->d_name));
				git_path = ft_strfjoin(git_path, ft_strdup("/HEAD"));
				if ((fd = open(git_path, O_RDONLY)) > 0)
					if (build_git_head(fd, &git_path, rep, len))
						return (git_path);
				ft_strdel(&git_path);
			}
		closedir(rep);
	}
	return (NULL);
}

static int	print_git_info(void)
{
	char	*git_info;
	char	*path;
	int		len;

	if (!(path = getcwd(NULL, 0)))
		return (0);
	git_info = NULL;
	len = 0;
	while (ft_strchr(path, '/'))
	{
		if ((git_info = find_git_info(path, &len)))
		{
			ft_putstr(git_info);
			ft_strdel(&git_info);
			ft_strdel(&path);
			return (len);
		}
		ft_strfsub(&path, 0, (ft_strrchr(path, '/') - path));
	}
	ft_putstr("\x1b[0;93m∆\x1b[0;m ");
	ft_strdel(&path);
	return (-1);
}

int			print_prompt(char **env, int cmd_ret)
{
	int		i;
	char	*pwd;
	int		del;

	if (!(pwd = getcwd(NULL, 0)) && env)
	{
		ft_printf(cmd_ret == 0 ? "{FGG}➜{E}   " : "{FRG}➜{E}   ");
		return (print_git_info() + 7);
	}
	del = ft_strrchr(pwd, '/') - pwd + 1;
	ft_strfsub(&pwd, del, ft_strlen(pwd) - del);
	if (is_empty(pwd))
		pwd = ft_strfjoin(pwd, ft_strdup("/"));
	ft_printf(cmd_ret == 0 ? "{FGG}➜{E}  \x1B[96;1m%s{E} "
			: "{FRG}➜{E}  \x1B[96;1m%s{E} ", pwd);
	i = print_git_info() + 7 + ft_strlen(pwd);
	ft_strdel(&pwd);
	return (i);
}
