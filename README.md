# irc-serveur
### Version 1.0
## Description
This project is an implementation of an IRC (Internet Relay Chat) server. The goal is to recreate the behavior of an IRC server that can communicate with any current IRC client. The server is capable of handling multiple simultaneous clients and supports basic IRC functionalities like authentication, joining channels, sending private messages, and more.
## Features
- Handles multiple clients simultaneously without blocking.
- Full support for TCP/IP (IPv4 and IPv6) communication.
- Authentication with username and password.
- Basic IRC commands:
  - NICK: Set your nickname.
  - USER: Set your username.
  - JOIN: Join a channel.
  - PRIVMSG: Send private messages.
  - QUIT: Exit the server.
- Channel management commands for operators:
  - KICK: Remove a user from the channel.
  - INVITE: Invite a user to the channel.
  - TOPIC: Set or view the channel topic.
  - MODE: Change channel modes (invite-only, topic restriction, etc.).
Supports popular IRC clients for testing and interaction.
## Installation and Usage

All instructions for building, configuring, and running the server are provided through the output of the Makefile.

### To Install:

Clone the repository:
```
git clone https://github.com/yourusername/ft_irc.git
```
Navigate to the project directory:
```
cd ft_irc
```
Compile the project:
```
make
```
The Makefile will provide all the necessary instructions on how to launch and configure the server.

### Usage Example
To launch the server, use the following format:
```
./ircserv <port> <password>
<port>: The port number on which the server will listen for incoming connections.
<password>: The password required by IRC clients to connect to the server.
```
### Compatibility
The server works seamlessly with all current IRC clients, making it easy to test using popular clients such as:
- HexChat
- mIRC
- WeeChat

## Bonus Features
The project also includes:
- File sending: Enable clients to share files.
- Bot support: Add a bot to manage channels or automate tasks.
