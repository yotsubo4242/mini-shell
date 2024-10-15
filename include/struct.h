/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:54:38 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/10/16 00:19:54 by yotsubo          ###   ########.fr       */
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
	ND_SIMPLE_CMD,
} t_node_kind;

typedef struct s_token {
	char			*word;
	t_token_kind	kind;
	struct s_token	*next;
}	t_token ;

typedef struct s_node {
	t_token			*args;
	t_node_kind		kind;
	struct s_node	*next;
}	t_node ;

typedef int	t_bool;

#endif