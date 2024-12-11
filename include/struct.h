/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:54:38 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/12/11 12:25:31 by tkitahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "minishell.h"

typedef enum	e_token_kind {
	TK_WORD,
	TK_RESERVED,
	TK_OP,
	TK_EOF,
} t_token_kind;

typedef enum	e_node_kind {
	ND_PIPELINE,
	ND_SIMPLE_CMD,
	ND_REDIR_OUT,
	ND_REDIR_IN,
	ND_REDIR_APPEND,
	ND_REDIR_HEREDOC,
} t_node_kind;

typedef enum	e_setget_kind {
	SET,
	GET,
} t_setget_kind;

typedef struct s_token {
	char			*word;
	t_token_kind	kind;
	bool			is_expanded;
	struct s_token	*next;
}	t_token ;

typedef struct s_node {
	t_node_kind		kind;
	struct s_node	*next;
	// CMD
	t_token			*args;
	struct s_node	*redirects;
	// REDIR
	int				targetfd;
	t_token			*filename;
	t_token			*delimiter;
	bool			is_delim_unquoted;
	int				filefd;
	int				stashed_targetfd;
	// PIPE
	int				inpipe[2];
	int				outpipe[2];
	struct s_node	*command;
}	t_node ;

typedef struct s_item {
	char			*key;
	char			*value;
	struct s_item	*next;
}	t_item;

typedef struct s_map {
	t_item	item_head;
}	t_map;

extern bool	g_syntax_error;
extern int		g_last_status;
// TODO: グローバル変数を使わずともenvironを常に参照できるようにする. 
extern t_map	*g_env;
extern bool	g_readline_interrupted;
extern volatile sig_atomic_t	g_sig;
extern int	_rl_echo_control_chars;

#endif
