/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 20:57:10 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/07 21:13:09 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<signals.h>

void sigint_handler(int sig)
{
	(void)sig;
	if (waitpid(-1, &sig, WNOHANG) == 0)
		return;
	printf("\n");
	prompt_pwd();
	rl_on_new_line(); // Regenerate the prompt on a newline
	rl_replace_line("", 0); // Clear the previous text
	rl_redisplay();
	g_exit_status = 1;
	g_last_signal = 69;
	return;
}

/*
void sigquit_handler(int sig)
{
	(void)sig;
	printf("\n");
	prompt_pwd();
    rl_on_new_line(); // Regenerate the prompt on a newline
    rl_replace_line("", 0); // Clear the previous text
    rl_redisplay();
	g_exit_status = 1;
	return;
}
*/

void handle_default_sig_handlers(int action)
{
	if (action == SET)
	{
		signal(SIGINT, sigint_handler);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
	}
	return;
//	static struct sigaction old_sigquit_handler;
}

void sigquit_handler(int sig)
{
	(void)sig;
	return;
}

void reset_default_sig_handlers()
{
	handle_default_sig_handlers(RESET);
}

void install_default_sig_handlers()
{
	handle_default_sig_handlers(SET);
}
