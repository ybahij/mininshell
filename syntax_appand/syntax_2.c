/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 00:27:38 by ybahij            #+#    #+#             */
/*   Updated: 2024/09/23 00:28:14 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pars_pipe_(lexer_t *tmp, char *newline)
{
	if (!tmp->next)
	{
		printf(RED "minishell: syntax error near unexpected token `%s'\n" RESET,
			newline);
		return (exit_s(2), 0);
	}
	if (cm_strchr("|&o", tmp->next->type))
	{
		printf(RED "minishell: syntax error near unexpected token `%s'\n" RESET,
			tmp->next->content);
		return (exit_s(2), 0);
	}
	return (1);
}