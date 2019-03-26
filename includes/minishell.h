/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   minishell.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/24 04:34:49 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 06:52:58 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <termios.h>
# include <fcntl.h>
# include <signal.h>

# define BI_ECHO			1
# define BI_CD				2
# define BI_SETENV			3
# define BI_UNSETENV		4
# define BI_ENV				5
# define BI_DIRS			6
# define BI_EXIT			7
# define CMD_BUFF_SIZE		32000

typedef struct		s_cmd
{
	char			*name;
	char			*bin_path;
	char			**argv;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_hist
{
	char			*command;
	struct s_hist	*next;
	struct s_hist	*prev;
}					t_hist;

typedef struct		s_shell
{
	char			**dir_stack;
	struct s_hist	*history;
	int				cmd_ret;
	int				prompt_len;
	int				interupt;
}					t_shell;

typedef struct		s_env
{
	int				i;
	int				maj_p;
	char			*alpath;
	int				maj_s;
	char			*string;
	int				u;
	char			**names;
	int				v;
	char			*bin_path;
	char			**param;
	char			**env;
}					t_env;

typedef struct		s_cmd_hdlr
{
	int				in_hist;
	char			buff;
	int				index;
	int				len;
	struct termios	raw;
	int				prompt_len;
	int				interupt;
}					t_cmd_hdlr;

char				**get_environ(void);

int					get_command(char **line, t_shell *shell, char **env);
void				manage_escape_seq(t_cmd_hdlr *data, char cmd[],
						char init_cmd[], t_shell *shell);
int					update_curr_cmd(char cmd[], t_cmd_hdlr *data);
void				delete_chr(char cmd[], t_cmd_hdlr *data);
void				manage_autocomp(char cmd[], t_cmd_hdlr *data,
						char **env, char **dir_stack);
void				manage_init_cmd(t_cmd_hdlr *data,
						char cmd[], char init_cmd[]);
int					move_left(t_cmd_hdlr *data);
int					move_right(t_cmd_hdlr *data, char cmd[], int prompt_len);
int					history_up(t_cmd_hdlr *data, t_hist **history, char cmd[]);
int					history_down(t_cmd_hdlr *data,
						t_hist **history, char cmd[]);
int					read_escape_seq(t_cmd_hdlr *data,
						char cmd[], t_hist **history, t_shell *shell);
void				add_char(char cmd[], int i, char c);
void				remove_char(char cmd[], int i);
char				*create_escape_seq(int i, char *code);
void				replace_cmd(char cmd[], int *i, int *len);
void				write_cmd(char cmd[], int i, int *len);
int					is_empty(char *line);
char				*get_argument(char *instr, int *i);
t_shell				*init_shell(char **env);
t_cmd				*parse_command(char **line, char **env, char **dir_stack);
char				**get_instr_arg(char *instr, int *i, char *name);
char				*get_argument(char *instr, int *i);
int					update_option(char *options, t_env *env,
						char **argv, int *j);
void				replace_dollar_exp(char **line, char **env);
void				replace_tilde_exp(char **line, char **env,
						char **dir_stack);
int					is_valid_bin(t_cmd *cmd, char **env);
int					is_valid_builtin(t_cmd *cmd, char ***env, t_shell *shell);
int					is_relative_path(char *path);
t_cmd				*free_and_next_cmd(t_cmd **cmd);
int					check_empty(int fd, char *str);
int					print_prompt(char **env, int cmd_ret);
void				add_history_command(t_hist **history, char *cmd);
t_hist				*get_history(char *home);
void				save_history(t_hist *history, char *home);
void				autocomplete(char cmd[], int *curs,
						char **env, char **dir_stack);
char				*find_bin_dir(char *dir_path, char *name);
char				*find_file(char *path, char *comp,
						char **env, char **dir_stack);
char				*find_bin_command(char **path, char **env);
void				ft_echo(t_cmd *cmd);
void				ft_exit(t_cmd *cmd, char **env, t_shell *shell);
int					ft_cd(t_cmd *cmd, char **env, t_shell *shell);
int					check_cd_error(char **argv, int i, int p, char **env);
void				ft_dirs(char **env, char **dir_stack);
int					ft_setenv(t_cmd *cmd, char ***env);
int					ft_unsetenv(t_cmd *cmd, char **env);
int					ft_env(t_cmd *cmd, char **env);
char				**build_new_env(char **env_vars, t_env *data,
						char **args, int *index);
char				**build_param(t_env *data, char **arg, int *index);
char				*get_bin_path(char **param, t_env *data);
int					check_is_file(char *path);
void				add_dir_to_stack(char ***dir_stack, char *new_path);
int					is_valid_env_var(char *var_name);
char				*find_env_val(char **env, char *var_name);
void				update_env_val(char **env, char *var_name, char *new_val);
void				add_env_val(char ***env, char *new_env_val);
void				remove_env_var(char **vars, char **env, int start);
void				free_command(t_cmd *cmd);
void				free_env_struct(t_env *data);
void				ctrl(int sig);
int					is_tilde_number(char *str);
int					launch_exec(char *name, char **argv,
						char **env, char *bin_path);
void				go_to_end(char cmd[], t_cmd_hdlr *data, t_shell *shell);

#endif
