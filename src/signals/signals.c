/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 00:00:00 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/31 00:00:00 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_last_signal = 0;

void	sigint_handler(int sig)
{
	g_last_signal = 0;
	g_last_signal = sig;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	heredoc_sigint_handler(int sig)
{
	g_last_signal = 0;
	g_last_signal = sig;
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_done = 1;
}

void	signal_distributor(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

// void	setup_heredoc_signals(void)
// {
// 	struct sigaction	sa_int;
// 	struct sigaction	sa_quit;

// 	sa_int.sa_handler = heredoc_sigint_handler;
// 	sigemptyset(&sa_int.sa_mask);
// 	sa_int.sa_flags = 0;
// 	sigaction(SIGINT, &sa_int, NULL);
// 	sa_quit.sa_handler = SIG_IGN;
// 	sigemptyset(&sa_quit.sa_mask);
// 	sa_quit.sa_flags = 0;
// 	sigaction(SIGQUIT, &sa_quit, NULL);
// }

void	exec_distributor(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
}

void	sig_ignore(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}
