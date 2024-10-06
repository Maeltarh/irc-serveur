/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:50:39 by marvin            #+#    #+#             */
/*   Updated: 2023/07/08 15:50:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

std::string	findNickname(std::vector<std::string> words)
{
	std::string msg = words[0];
	size_t pos = msg.find('!');
	std::string nickname = msg.substr(1, pos - 1);
	return (nickname);
}

void	moderation(int sock, std::vector<std::string> words, std::string channelName)
{
	words[3].erase(0, 1);
	std::string banWords[1] = {"CON"};
	for (size_t i = 0; i < words.size(); i++)
	{
		for (size_t x = 0; x < words[i].length(); x++)
		{
			words[i][x] = std::toupper(words[i][x]);
		}
		for (int y = 0; y < 1; y++)
		{
			if (words[i] == banWords[y])
			{
				std::string nickname = findNickname(words);
				std::string msg = "KICK #" + channelName + " " + nickname + "\r\n";
				send(sock, msg.c_str(), msg.length(), 0);
				return;
			}
		}
	}
}

void	running(int sock, std::string channelName)
{
	std::string input;
	char buffer[256];
	while (true)
	{
		fd_set readfds;
		FD_ZERO(&readfds);
		FD_SET(sock, &readfds);
		FD_SET(STDIN_FILENO, &readfds);
		int maxFd = std::max(sock, STDIN_FILENO) + 1;
		if (select(maxFd, &readfds, NULL, NULL, NULL) < 0)
		{
			std::cerr << "[Error]: Select failed." << std::endl;
			exit (EXIT_FAILURE);
		}
		if (FD_ISSET(sock, &readfds))
		{
			memset(buffer, 0, 256);
			int i = recv(sock, buffer, 256, 0);
			if (i < 0)
			{
				std::cerr << "[Error]: Receive failed." << std::endl;
				break;
			}
			else if (i == 0)
			{
				std::cerr << "[Error]: Server closed connection." << std::endl;
				break;
			}
			else
			{
				std::cout << buffer << std::endl;
				std::vector<std::string> words;
				std::string currentWord;
				size_t lenght = strlen(buffer);
				for (size_t i = 0; i < lenght; i++)
				{
					char c = buffer[i];
					if (c == ' ' || c == '\n')
					{
						if (!currentWord.empty())
						{
							words.push_back(currentWord);
							currentWord.clear();
						}
						if (c == '\n')
						{
							if (words.size() >= 4)
							{
								if (words[3][1] == '!')
									commandHandle(sock, words, channelName);
								else
									moderation(sock, words, channelName);
							}
							words.clear();
						}
					}
					else if (c != '\r')
						currentWord.push_back(c);
				}
			}
		}
		if (FD_ISSET(STDIN_FILENO, &readfds))
		{
			std::getline(std::cin, input);
			for (size_t x = 0; x < input.length(); x++)
			{
				input[x] = std::toupper(input[x]);
			}
			if (input == "QUIT")
			{
				std::string quit = "QUIT :Leaving\r\n";
				send(sock, quit.c_str(), quit.length(), 0);
				close(sock);
				exit (0);
			}
		}
	}
}
