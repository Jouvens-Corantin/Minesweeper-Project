Minesweeper

A high-performance implementation of the classic Minesweeper puzzle game developed in C++ using the Simple and Fast Multimedia Library (SFML). This project emphasizes Object-Oriented Programming (OOP) design patterns and efficient game-loop management.

Project Overview

This program recreates the logic-based gameplay of Minesweeper. The software utilizes a modular architecture to separate the game logic from the rendering layer, allowing for easy expansion (such as adding new difficulty levels or custom skins).

Technical Features

  - Clean OOP Design: Managed through dedicated classes for the Game Engine, Board, and Cells.

  - Recursive Reveal Algorithm: Uses an efficient flood-fill approach to reveal contiguous empty tiles.

  - State Management: Handles distinct game states including Menu, Active Play, Victory, and Game Over.

  - Resource Optimization: Centralized texture loading to minimize memory footprint.

  - Real-time Input Handling: Precise coordinate mapping for mouse clicks on the game grid.

