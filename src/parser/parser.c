/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 00:32:00 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/22 23:42:01 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int	debug_tree(t_ast_cmd *head, FILE *f, int index)
{
	char *lol[3] = {"&&", "||", "|"};

	if (head->type == P_AND || head->type == P_OR || head->type == P_PIPE)
	{
		fprintf(f, "n%d[label=\"%s\"] ;\n", index, lol[head->type]);
		fprintf(f, "n%d -> n%d ;\n", index, 10 * index + 1);
		fprintf(f, "n%d -> n%d ;\n", index, 10 * index + 2);
		debug_tree(((t_ast_and*) head)->left, f, 10 * index + 1);
		debug_tree(((t_ast_and*) head)->right, f, 10 * index + 2);
	}
	else if (head->type == P_EXEC)
		fprintf(f, "n%d[label=\"%s\"] ;\n", index, ((t_ast_exec *)head)->argv[0]);
	return (0);
}

bool parser(t_list *tokens)
{
	t_ast_cmd *head;
	// printf("Hello from parser %s\n", ((t_token *)tokens->content)->value);
	head = parse_cmd(tokens, NULL);

	FILE *f = fopen("tree.dot", "w");
	if (!f)
		return (printf("Couldn't open file !"));
	fprintf(f, "digraph yep {\n");
	debug_tree(head, f, 0);
	fprintf(f, "}\n");
	fclose(f);
	return (true);
}
