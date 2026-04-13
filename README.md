# Euchre Game Engine & Statistics Library (C++)

## Overview
This project implements a fully functional Euchre card game engine in C++ using object-oriented design principles. It simulates multi-player gameplay with both AI and human-controlled strategies, and includes a custom statistics library for data analysis and evaluation.

## Features
- Complete Euchre game simulation with turn-based logic and scoring
- Support for multiple player strategies (Simple AI and Human input)
- Modular class design (Player, Card, Pack)
- Trump selection logic and trick-taking system
- Command-line interface for running games
- Integrated statistics library for data analysis
- Unit testing for validation and debugging

## System Design

### Game Engine
Manages:
- Game flow (rounds, dealing, scoring)
- Player turns and trick execution
- Win conditions and point tracking

### Player System
- `SimplePlayer`: AI-based decision-making using rule-based logic
- `HumanPlayer`: Interactive input-based gameplay
- Factory pattern used to create player types dynamically

### Card & Pack System
- `Card`: Handles rank, suit, and comparison logic (including trump rules)
- `Pack`: Represents a deck of cards with shuffle, deal, and reset functionality

### Statistics Module
Includes implementations for:
- Mean, median, standard deviation
- Percentiles and filtering
- Bootstrap resampling
- Confidence interval estimation

### Testing
- Unit tests implemented for core components (Player, Card, Pack, Statistics)
- Ensures correctness and robustness of game logic

## File Structure
