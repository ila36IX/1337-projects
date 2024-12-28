# minitalk

![Imgur](https://i.imgur.com/5KJF2zM.png)

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
## My implementation in short

My idea was to send signals `SIGUSR1` and `SIGUSR2` to represent `1` and `0`. It worked in some cases but failed in others. There is always a possibility of losing a signal, which makes the rest of the payload meaningless. Why?

Linux systems do NOT queue signals when you already have pending signals of the same type!

So, I tried using a bigger delay between sending signals. That reduced the chance of losing signals but caused a massive performance issue. Increasing the delay made sending larger messages possible but very slow (e.g., it took more than `10s` to send just 1600 characters).

That was not the solution. The next idea was to send each bit and wait for the server to acknowledge receiving it. This approach did the trick and, surprisingly, was more performant than I expected—it allowed me to send 16,000 characters in just 1 second.
