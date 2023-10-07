/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 15:19:22 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/07 16:19:52 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<signals.h>

void sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	prompt_pwd();
    rl_on_new_line(); // Regenerate the prompt on a newline
    rl_replace_line("", 0); // Clear the previous text
    rl_redisplay();
	return;
}

void sigquit_handler(int sig)
{
	(void)sig;
	return;
}

void install_signal_handler(int signal, void (*handler)(int))
{
	struct sigaction action;
	action.sa_flags = 0;
	sigemptyset(&action.sa_mask);
	action.sa_handler = handler;
	if (sigaction(signal, &action, NULL))
		perror("sigaction");
}

void install_default_sig_handlers()
{
	install_signal_handler(SIGINT, sigint_handler);
	install_signal_handler(SIGQUIT, SIG_IGN);
}
