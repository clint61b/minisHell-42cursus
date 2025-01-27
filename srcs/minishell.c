/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 08:25:02 by krwongwa          #+#    #+#             */
/*   Updated: 2025/01/15 23:23:58 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static volatile sig_atomic_t	g_signal;

void	check_signal(int signal)
{
	if (signal == SIGINT && g_signal == 0)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	if (signal == SIGQUIT)
	{
		rl_redisplay();
		return ;
	}
}

void	setup_signal(void)
{
	struct sigaction	act;

	g_signal = 0;
	ft_bzero(&act, sizeof(sigaction));
	act.sa_handler = &check_signal;
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	ft_bzero(&act, sizeof(sigaction));
}

char	*ft_readline(t_msh *var)
{
	char	*input;
	char	*promt;

	promt = get_promt(var);
	input = readline(promt);
	if (promt)
		free(promt);
	add_history(input);
	return (input);
}

void msh_loop(t_msh *msh)
{
	while (1)
	{
		msh->input = ft_readline(msh);
		if (!msh->input)
		{
			printf("%sEXIT!%s💥\n", RED, RESET);
			exit(1);
		}
		msh->token = msh_parsing_input(msh);
		if (msh->token)
		{
			msh->ast = msh_get_tokens(&msh->token);
			// if (msh->ast)
			// {
			// 	printf("\nAbstract Syntax Tree:\n");
			// 	display_ast_table(msh->ast, 0);
			// }
			main_exe(msh);
			free_ast(msh->ast);
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_msh	*msh;
	t_ast	*ast;
	char	*input;
	int		status;

	msh = malloc(sizeof(t_msh));
	if (!msh)
		return (1);
	init_minishell(msh, env);
	setup_signal();
	msh_loop(msh);
	free(ast->args);
	free(ast->args[0]);
	ft_free(msh);
	rl_clear_history();
	return (0);
}
