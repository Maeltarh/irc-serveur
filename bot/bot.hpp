/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 02:30:36 by marvin            #+#    #+#             */
/*   Updated: 2023/07/08 02:30:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
#define BOT_HPP

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/select.h>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <cerrno>
#include <cctype>
#include <ctime>
#include <algorithm>
#include <string>
#include <arpa/inet.h>

void	running(int sock, std::string channelName);
void	commandHandle(int sock, std::vector<std::string> words, std::string channelName);

#endif
