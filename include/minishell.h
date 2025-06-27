/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:02:17 by dtunega           #+#    #+#             */
/*   Updated: 2025/06/03 23:40:40 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAX_COMMANDS_IN_PIPELINE 256
# define MAX_PATH_LENGTH 1024

extern int	g_exit;

typedef struct s_data
{
	char	**commands;
	char	*user_name;
	int		last_command;
	char	***args;
	int		infile;
	char	*delimiter;
	char	**redirs;
	int		outfile;
	int		saved_stdin;
	int		saved_stdout;
	char	**minishell_env;
}			t_data;

typedef struct s_executor_state
{
	int		cmd_idx;
	pid_t	pids[MAX_COMMANDS_IN_PIPELINE];
	int		num_children;
	int		pipe_fds[2];
	int		prev_fd_read;
	bool	is_last_cmd;
	t_data	*shell_data;
}			t_executor_state;

typedef struct s_pipe_data
{
	int		pipe_fd_read;
	int		*pipe_fds;
	bool	is_last_cmd;
}			t_pipe_data;

typedef struct s_redir_state
{
	int		i;
	int		done;
	int		count;
}			t_redir_state;

void		ms_setup_shell_data(t_data *shell_data);
void		ms_process_input(t_data *shell_data);
void		ms_reset_command_data(t_data *shell_data);
void		execute_single_builtin(t_data *shell_data);
void		execute_child_in_pipeline(t_data *s_data, int c_idx,
				t_pipe_data *pipe_data);
void		manage_parent_pipes_for_next_iteration(int *p_fd_r_io,
				int *cur_pipe_fds, bool pipe_was_created);
void		setup_pipe_and_fork(t_executor_state *s);
void		lexer(char **token_array, t_data *shell_data);
void		wait_for_all_children(pid_t *pids, int n_child);
void		ft_open_append(t_data *data, char *filename);
void		ft_open_trunc(t_data *data, char *filename);
bool		check_consecutive_redirs(char **token_array);
bool		check_newline_error(char **token_array);

void		ft_parser(const char *user_input, t_data *shell_data);
bool		ms_is_rd_tk(char *token);
char		**ms_filter_redirection_tokens(char **token_array);
int			ms_count_non_redir_tokens(char **token_array);
bool		ms_validate_redirection_syntax(char **token_array);

char		*prepare_quoted_string(const char *input);
char		**parse_quated_strings(char **words);
void		copy_quoted_content(char *word, char *result, int *i, int *j);
void		process_single_word(char **words, int i);
char		*prepare_quoted_string_helper(char *result);
char		*prepare_quoted_string_main(const char *input);
char		*remove_quotes_from_word(char *word);
void		ft_move_brackets(char *copy, int *i, char bracket);
void		ft_parser(const char *user_input, t_data *shell_data);

char		*add_spaces_around_redirections(const char *input);
void		handle_quotes(const char *input, char *result, int *i, int *j);
void		add_space_before(char *result, int *j);
void		handle_double_redir(const char *input, char *result, int *i,
				int *j);
void		handle_single_redir(const char *input, char *result, int *i,
				int *j);
void		process_character_in_redirection(const char *input, char *result,
				int *i, int *j);

char		**replace_env_var_nonquated(char **words);
char		*env_replacement(char *word, int i, int j);
char		*dollar_check(char *word);
char		**status_var_check(char **words);

char		*tilda_replace(char *word);
char		*status_replace(char *word);
void		tokenize_outfile(char **words, t_data *data);
void		handle_trunc_redir(char **words, t_data *data,
				t_redir_state *state);
void		handle_append_redir(char **words, t_data *data,
				t_redir_state *state);

int			redir_count(char **words, char *redir_frst, char *redir_scnd);
void		tokenize_infile_heredoc(char **words, t_data *data);
void		tokenize_outfile(char **words, t_data *data);

int			ms_is_valid_command(char *token);
bool		ms_is_pipe_operator(char *token);
void		tokenize_command(char **token_array, t_data *shell_data);

void		tokenize_arg(char **words, t_data *data, int count);
char		***argument_parser(char **commands, char ***args);
char		**copy_args(char **arr_src, char *command);
char		***allocate_argument_arrays(int cmd_count);
void		allocate_single_command_args(char ***argument_arrays, int cmd_idx,
				int arg_count);
void		process_single_command_args(char ***argument_arrays,
				char **token_array, int *token_idx, int cmd_idx);
int			ms_count_command_args(char **token_array, int start_idx);
void		ms_fill_command_arguments(char ***args, char **token_array,
				int *token_idx, int cmd_idx);

char		*join_env(char *var, char *value);
void		ft_cd_fork(char **args, t_data *data);
int			ft_cd_nonfork(char **args, t_data *data);

void		ft_pwd_fork(char **args, t_data *data);
int			ft_pwd_nonfork(char **args);

void		ft_echo_fork(char **args, t_data *data);
int			ft_echo_nonfork(char **args);
void		ft_echoprint(char **words, int i);

void		ft_write_expander_char(char *word);
void		ft_write_expander_num(int start_int, int end_int);
void		ft_echo_expander(char *word);

void		ft_env_fork(t_data *data);
int			ft_env_nonfork(void);

void		ft_rewrite(int index, char *var, t_data *data);
void		ft_add(char *var, t_data *data);
void		ft_export_fork(char **words, t_data *data);
int			ft_export_nonfork(char **args, t_data *data);

int			ft_checkforexisting(char *var);
char		*ft_checkarg(char *arg);

void		ft_unset_fork(char **words, t_data *data);
int			ft_unset_nonfork(char **words, t_data *data);

void		ft_exit(t_data *shell_data);

void		ft_executor(t_data *shell_data);
void		ms_execute_single_command(char *cmd_path, int cmd_position,
				t_data *shell_data);
void		executor_experim(t_data *data);
void		ft_executor_binary_exp(t_data *data);
void		save_restore_std(t_data *data, int i);
void		set_infile(t_data *data);
void		set_outfile(t_data *data);

void		builtin_redirection_fork(char *command, char **args, t_data *data);
void		builtin_nonfork_redirection(char *command, char **args,
				t_data *data);

void		ft_heredoc(char *delimiter);

bool		ft_is_builtin(char *command);
bool		ft_is_pathx(char *command);
bool		ft_isnopathx(char *command);
char		*ft_return_path(char *command);
void		ft_command_check(t_data *data);

int			ft_isnopathx_util(void);

int			commands_counting(char **words);
void		free_split(char **args);
void		free_args(char ***args);
void		free_command_table(t_data *data);
int			ft_isdigit_array(char **arg);
void		fork_exit(int status, t_data *data);
extern char	**environ;
void		fork_exit(int status, t_data *data);

void		ft_sigint_handler(int signal);
void		ft_setup_interactive_signals(void);
void		ft_setup_child_signals(void);

#endif
