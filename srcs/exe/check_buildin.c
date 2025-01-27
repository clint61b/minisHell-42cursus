/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_buildin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:53:16 by krwongwa          #+#    #+#             */
/*   Updated: 2025/01/25 16:24:13 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_build_in_command(char *word, int *a)
{
	if (ft_strcmp(word, "echo") == 0)
		*a = 0;
	else if (ft_strcmp(word, "cd") == 0)
		*a = 0;
	else if (ft_strcmp(word, "pwd") == 0)
		*a = 0;
	else if (ft_strcmp(word, "export") == 0)
		*a = 0;
	else if (ft_strcmp(word, "unset") == 0)
		*a = 0;
	else if (ft_strcmp(word, "env") == 0)
		*a = 0;
	else if (ft_strcmp(word, "exit") == 0)
		*a = 0;
	else
		*a = 1;
}

void	is_build_in_command(t_ast *ast, int *a)
{
	char	*word;

	if (!ast || *a == 0 || *a == 1)
		return ;
	if (ast->type == CMD)
	{
		if (ast->left == NULL)
			word = ast->args[0];
		else
			word = ast->left->args[0];
		check_build_in_command(word, a);
		return ;
	}
	else
	{
		is_build_in_command(ast->left, a);
		is_build_in_command(ast->right, a);
	}
}

void	exe_single_cmd(t_ast *ast, t_p *list)
{
	int	status;

	status = 1;
	prepare_cmd(ast, list, &status);
	if (status == -1)
	{
		*list->code = 1;
		return ;
	}
	*list->code = msh_execute_builtin(list);
}
