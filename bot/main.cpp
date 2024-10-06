/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 02:38:56 by marvin            #+#    #+#             */
/*   Updated: 2023/07/08 02:38:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

int	main(int ac, char *ag[])
{
	if (ac != 4)
	{
		std::cerr << "[Error]: Wrong argument. ./ircbot <port> <password> <channelname>" << std::endl;
		return (-1);
	}
	int	sock;
	sockaddr_in	serv;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		std::cerr << "[Error]: Could not create socket." << std::endl;
		return (-1);
	}
	std::string port = ag[1];
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_family = AF_INET;
	serv.sin_port = htons(atoi(port.c_str()));
	if (connect(sock, (sockaddr*)&serv, sizeof(serv)) < 0)
	{
		std::cerr << "[Error]: Connection failed." << std::endl;
		return (-1);
	}
	std::string password = ag[2];
	std::string channelName = ag[3];
	std::string msg = "PASS " + password + "\r\nNICK chillBot\r\nUser chillBot 0 * :chillBot\r\nJOIN #" + channelName + "\r\n";
	if (send(sock, msg.c_str(), msg.length(), 0) < 0)
	{
		std::cerr << "[Error]: Send failed." << std::endl;
		return (-1);
	}
	srand(static_cast<unsigned int>(time(0)));
	running(sock, channelName);
	close(sock);
	return (0);
}
