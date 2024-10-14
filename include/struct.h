/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:54:38 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/10/14 13:57:48 by yuotsubo         ###   ########.fr       */
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

typedef struct s_token {
	char			*word;
	t_token_kind	kind;
	struct s_token	*next;
}	t_token ;

#endif