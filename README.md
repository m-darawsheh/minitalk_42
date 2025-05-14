# 📨 Minitalk - 42 School Project

Minitalk is a 42 School project that explores interprocess communication using UNIX signals. The goal is to create a simple client-server communication protocol using only `SIGUSR1` and `SIGUSR2`.

## 📌 Project Overview

- The **server** receives signals and reconstructs the message bit by bit.
- The **client** encodes characters into binary and sends each bit as a signal to the server.
- Signals used: `SIGUSR1` for binary 0 and `SIGUSR2` for binary 1.

## 🛠️ Features

- Bitwise encoding/decoding of messages
- Robust signal handling
- Simple and reliable communication protocol
- Support for long and complex messages
