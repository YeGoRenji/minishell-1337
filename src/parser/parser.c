/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 00:32:00 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/10/10 16:25:07 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <parser.h>

void	print_escape(FILE *f, char *str) // ? Debug
{
	while (*str)
	{
		if (*str == '\'')
			fprintf(f, "%s", "\\\'");
		else if (*str == '\"')
			fprintf(f, "%s", "\\\"");
		else
			fprintf(f, "%c", *str);
		str++;
	}
}

void	print_nosp_tok(FILE *f, t_token *tok) // ? Debug
{
	while (tok)
	{
		print_escape(f, tok->value);
		tok = tok->nospace_next;
	}
}

int	debug_tree(t_ast_cmd *head, FILE *f, int index) // ? Debug
{
	char *binaries[3] = {"&&", "||", "|"};
	char *redirs[4] = {">", ">>", "<", "<<"};

	if (!head)
		fprintf(f, "	n%d[fontcolor=blue label=\"NULL\"];\n", index);
	else if (head->type == P_AND || head->type == P_OR || head->type == P_PIPE)
	{
		fprintf(f, "	n%d[fontcolor=chocolate1 label=\"%s\"];\n", index, binaries[head->type]);
		fprintf(f, "	n%d -> n%d;\n", index, 2 * index + 1);
		fprintf(f, "	n%d -> n%d;\n", index, 2 * index + 2);
		debug_tree(((t_ast_binary*) head)->left, f, 2 * index + 1);
		debug_tree(((t_ast_binary*) head)->right, f, 2 * index + 2);
	}
	else if (head->type == P_REDIR)
	{
		fprintf(f, "	n%d[fontcolor=crimson label=\"%s ",
		  index,
		  redirs[((t_ast_redir *)head)->direction - 3]
		);
		print_nosp_tok(f, ((t_ast_redir *)head)->file_tok);
		fprintf(f, "\"];\n");
		fprintf(f, "	n%d -> n%d;\n", index, 2 * index + 1);
		debug_tree(((t_ast_redir*) head)->cmd, f, 2 * index + 1);
	}
	else if (head->type == P_EXEC)
	{
		t_token	*argv_tok = ((t_ast_exec *)head)->argv_tok;

		fprintf(f, "	n%d[label=\"", index);
		while (argv_tok)
		{
			print_nosp_tok(f, argv_tok);
			fprintf(f, " ");
			argv_tok = argv_tok->next;
		}
		fprintf(f, "\"];\n");
	}
	else if (head->type == P_SUBSH)
	{
		fprintf(f, "	n%d[fontcolor=darkturquoise label=\"%s ",
		  index,
		  "(SUBSH)"
		);
		fprintf(f, "\"];\n");
		fprintf(f, "	n%d -> n%d;\n", index, 2 * index + 1);
		debug_tree(((t_ast_subsh*) head)->cmd, f, 2 * index + 1);
	}
	return (0);
}

bool	parser(t_token *tokens, char *cmd, t_ast_cmd **tree)
{
	t_token		*current;

#ifdef DEBUG
	printf("----- PARSER ------\n"); // ? Debug !
#else
	(void)cmd;
#endif // DEBUG
	*tree = NULL;
	if (!tokens)
		return (false);
	current = tokens;
	if (current->type == NEW_LINE)
		return (free_tok_lst(tokens), true);
	*tree = parse_cmd(&current);
	if (!(*tree) || current->type != NEW_LINE)
	{
		syntax_error(current->value);
		return (free_tok_lst(tokens), false);
	}
	free_tok_lst(tokens);
#ifdef DEBUG
	FILE *f = fopen("tree.dot", "w");
	if (!f)
		return (printf("Couldn't open file !"));
	fprintf(f, "digraph yep {\n");
	fprintf(f, "	label=\""); print_escape(f, cmd); fprintf(f, "\"\n");
	debug_tree(*tree, f, 0);
	fprintf(f, "}\n");
	fclose(f);
#endif // DEBUG
	return (patch_heredoc(*tree));
}
