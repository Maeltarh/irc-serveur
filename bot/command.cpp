/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 02:32:23 by marvin            #+#    #+#             */
/*   Updated: 2023/07/09 02:32:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

std::string	result(std::string one, std::string two)
{
	if (one == "Rock!")
	{
		if (two == "ROCK")
			return (" Looks like a draw !");
		else if (two == "PAPER")
			return (" Oh no, i lost.");
		else if (two == "SCISSOR")
			return (" Yes ! I win.");
	}
	else if (one == "Paper!")
	{
		if (two == "ROCK")
			return (" Yes ! I win.");
		else if (two == "PAPER")
			return (" Looks like a draw !");
		else if (two == "SCISSOR")
			return (" Oh no, i lost.");
	}
	else if (one == "SCISSOR")
	{
		if (two == "ROCK")
			return (" Oh no, i lost.");
		else if (two == "PAPER")
			return (" Yes ! I win.");
		else if (two == "SCISSOR")
			return (" Looks like a draw !");
	}
	return ("");
}

void	shifumi(int sock, std::string channelName, std::vector<std::string> words)
{
	if (words.size() != 5)
	{
		std::string error = "PRIVMSG #" + channelName + " :[Error]: Wrong number of argument : !shifumi <Rock/Paper/Scissor>\r\n";
		send(sock, error.c_str(), error.length(), 0);
		return;
	}
	std::string shifumi[3] = {"Rock!", "Paper!", "Scissor!"};
	int r = rand() % 3;
	for (size_t x = 0; x < words[4].length(); x++)
	{
		words[4][x] = std::toupper(words[4][x]);
	}
	std::string sup = result(shifumi[r], words[4]);
	std::string msg = "PRIVMSG #" + channelName + " :" + shifumi[r] + sup + "\r\n";
	send(sock, msg.c_str(), msg.length(), 0);
}

void	commandHandle(int sock, std::vector<std::string> words, std::string channelName)
{
	words[3].erase(0, 2);
	for (size_t x = 0; x < words[3].length(); x++)
	{
		words[3][x] = std::toupper(words[3][x]);
	}
	std::string command[1] = {"SHIFUMI"};
	for (int x = 0; x < 1; x++)
	{
		if (words[3] == command[x])
		{
			switch (x)
			{
				case 0:
					shifumi(sock, channelName, words);
					break;
			}
		}
	}
}
