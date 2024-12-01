# Battle Ship Game Bot Against A player
## Discription
The Battleship Game Bot is a strategic game where a bot plays against a human player. The players place his ships (Destroyer, Carrier, Submarine, Battleship) on a 10x10 grid. The goal is to sink all of the bot’s ships before it sinks yours. It is a turn-based game. In this repository we recreate a terminal version of this game.
## Game features:

This game deviates from the traditional approach as it uses 4 ships rather than these ships are

Ship Types:

Destroyer

Carrier

Submarine

Battleship

It is also considered a more advanced version with a wider variety of moves which are:

Special Moves:

Fire: Fires at a specified coordinate on the opponent's grid.

Torpedo: Unlocked after sinking 3 of the opponent's ships. Fires across a whole row or column.

Artillery: Unlocked after sinking an opponent's ship. Fires a 2x2 grid.

Radar: Can be used 3 times to check if there is at least one hit in a specified 2x2 grid.

Smoke: Can be used as many times as the number of ships you’ve sunk. Covers a 2x2 grid to prevent the opponent's radar from detecting hits within that area.

The game continues until all the ships of one side ,either player or bot, are sunk

## How to play

1. Start: You get an empty grid to place your ships.

2. Place Ships: Pick a spot (e.g., A1) and a direction (vertical or horizontal), and enter it in the formate(A1,vertical)

3. Track Progress: After each turn, see your hits/misses on the grid. The enemy’s grid stays hidden.

4. Make Moves: Guess a spot (e.g., move A1) to attack the enemy.
