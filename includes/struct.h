/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:38:01 by jikarunw          #+#    #+#             */
/*   Updated: 2024/11/19 22:01:36 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRCUT_H
# define STRCUT_H

#include "./minishell.h"

typedef enum s_type
{
	CMD, // command, built-in
	ARG, // argument
	ENV_VAR, // -> "$HOME"
	EMPTY,	// ""
	INDIRECT, // <
	REDIRECT, // >
	PIPE, // |
	APPEND, // >>
	HEREDOC, // <<
	END // ; -> maybe this's not use for now.
	/** Maybe this two type to use the lexer
	 * &&
	 * ||
	 */
}	t_type;

/***************
 * PARSER TYPE *
 ***************/
typedef struct s_token
{
	// char			*str;
	char			*cmd;
	t_type			type;
	struct s_token	*next;
	int				count_pipe;
}	t_token;

typedef struct s_ast
{
	t_type				type;
	char				**args;
	struct s_ast		*left;
	struct s_ast		*right;
}	t_ast;

/******************
 * EXECUTION TYPE *
 ******************/
typedef struct tuple
{
	char		*key;
	char		*value;
	struct	tuple *next;
	struct	tuple *tail;
} t_tuple;

typedef struct p_pipe
{
	int		*process_pid;
	char	**env;
	char	**path;
	char	*cmd;
	int		fd_in;
	int		fd_out;
}	t_p;

/*****************
 * PROGRAM TRAIN *
 *****************/

typedef struct	s_msh
{
	t_tuple	*tuple;
	t_token *token;

	char	*home_path;
	int		code; // -> status code
	t_p		*list;
	char	**env;
	char	*cwd;
}	t_msh;

#endif
