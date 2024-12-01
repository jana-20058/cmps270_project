# Battleship Game Bot Against a Player

## Description

The Battleship Game Bot is a strategic game where a bot plays against a human player. The players place their ships (Destroyer, Carrier, Submarine, Battleship) on a 10x10 grid. The goal is to sink all of the bot’s ships before it sinks yours. It is a turn-based game. This repository recreates a terminal version of this game.

### Game Features:
- **4 Ship Types**:
  - **Destroyer**
  - **Carrier**
  - **Submarine**
  - **Battleship**

- **Special Moves**:
  - **Fire**: Fires at a specified coordinate on the opponent's grid.
  - **Torpedo**: Unlocked after sinking 3 of the opponent's ships. Fires across a whole row or column.
  - **Artillery**: Unlocked after sinking an opponent's ship. Fires a 2x2 grid.
  - **Radar**: Can be used 3 times to check if there is at least one hit in a specified 2x2 grid.
  - **Smoke**: Can be used as many times as the number of ships you’ve sunk. Covers a 2x2 grid to prevent the opponent's radar from detecting hits within that area.

The game continues until all ships of one side (either player or bot) are sunk.

## How to Play

1. **Start**: You get an empty grid to place your ships.
2. **Place Ships**: Pick a spot (e.g., A1) and a direction (vertical or horizontal), and enter it in the format (A1, vertical).
3. **Track Progress**: After each turn, see your hits/misses on the grid. The enemy’s grid stays hidden.
4. **Make Moves**: Guess a spot (e.g., A1) to attack the enemy.

## Strategy Used to Implement the Bot

We used a **heat map strategy** with some optimizations to improve the bot's decision-making in the game. The bot keeps track of possible hits by marking locations on the board with a heat map. This allows it to prioritize its guesses based on where it has previously hit or missed.


For a more detailed explanation, check out the following video that discusses the idea of heat maps:

[Watch the YouTube Video](https://www.youtube.com/watch?v=yourvideoID)

## How to Use

### Prerequisites
Before playing, make sure you have the following installed:
- **C Compiler**: (e.g., GCC or Clang)

### Running the Game
1. **Clone the repository**:
   ```bash
   https://github.com/jana-20058/cmps270_project.git
