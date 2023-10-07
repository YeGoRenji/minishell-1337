/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 20:57:10 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/07 21:01:13 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 15:19:22 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/07 20:49:33 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<signals.h>

void sigint_handler(int sig)
{
	(void)sig;
	puts("called handler");
	printf("\n");
	if (waitpid(-1, &sig, WNOHANG) == 0)
	{
		puts("called child handler");
		return;
	}
	puts("called parent handler");
	puts("printing prompts from handler");
	prompt_pwd();
	rl_on_new_line(); // Regenerate the prompt on a newline
	rl_replace_line("", 0); // Clear the previous text
	rl_redisplay();
	puts("setting last status to 69");
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

void install_signal_handler(int sig, void (*handler)(int), struct sigaction *old_handler)
{
	struct sigaction action;
	action.sa_flags = 0;
	sigemptyset(&action.sa_mask);
	action.sa_handler = handler;
	if (sigaction(sig, &action, old_handler))
		perror("sigaction");
}

void handle_default_sig_handlers(int action)
{
	static struct sigaction old_sigint_handler;
	if (action == SET)
	{
		install_signal_handler(SIGINT, sigint_handler, &old_sigint_handler);
	}
	else
	{
		//signal(SIGINT, SIG_DFL);
		install_signal_handler(SIGINT, old_sigint_handler.sa_handler, NULL);
	}
	return;
//	static struct sigaction old_sigint_handler;
	static struct sigaction old_sigquit_handler;

	if (action == SET)
	{
		install_signal_handler(SIGINT, sigint_handler, &old_sigint_handler);
		install_signal_handler(SIGQUIT, SIG_IGN, &old_sigquit_handler);
	}
	else
	{
		install_signal_handler(SIGINT, old_sigint_handler.sa_handler, NULL);
		install_signal_handler(SIGQUIT, old_sigquit_handler.sa_handler, NULL);
	}
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
