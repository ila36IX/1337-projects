# minitalk

[Imgur](https://i.imgur.com/5KJF2zM.png)

## Overview
Minitalk is a Small data exchange program that transmits text between a client and server program using UNIX signals.


## Key Features
- Uses only SIGUSR1 and SIGUSR2 signals for communication
- Client sends text by converting characters to bit-level signals
- Server reconstructs and prints the received text
- Supports multiple client connections

## How It Works
1. Server starts first and displays its Process ID (PID)
2. Client takes server's PID and text as parameters
3. Text is transmitted bit by bit using signals
4. Server receives and reconstructs the original message

## Usage
```bash
# Start server first
./server

# In another terminal, send message
./client [SERVER_PID] "Hello, Signals!"
```
