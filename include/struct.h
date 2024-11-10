/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:54:38 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/11/09 16:46:28 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

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

typedef struct s_token {
	char			*word;
	t_token_kind	kind;
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
	int				filefd;
	int				stashed_targetfd;
	// PIPE
	int				inpipe[2];
	int				outpipe[2];
	struct s_node	*command;
}	t_node ;

// Redirecting output example
// command          : "echo hello 1 > out"
// targetfd         : 1
// filename         : "out"
// filefd           : open("out")
// stashed_targetfd : dup(targetfd)

typedef int	t_bool;

#endif