/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 20:57:10 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/10 16:09:01 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signals.h>

void	sigint_handler(int sig)
{
	(void)sig;
	if (waitpid(-1, &sig, WNOHANG) == 0)
		return ;
	printf("\n");
	prompt_pwd();
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 1;
	g_last_signal = 69;
}

void	nop(int sig)
{
	(void)sig;
}

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	puts("here handler called!");
}

void	handle_default_sig_handlers(int action)
{
	if (action == SET)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, nop);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	return ;
}

void	reset_default_sig_handlers(void)
{
	handle_default_sig_handlers(RESET);
}

void	install_default_sig_handlers(void)
{
	handle_default_sig_handlers(SET);
}
