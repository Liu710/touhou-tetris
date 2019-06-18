## Introduction

This is a class project for GaTech CS 2110

This is a Touhou doujin game. Original touhou games and characters are designed by ZUN.

## Game Description

### Objective
Defeat all opposite characters by increase the score to 2450.

### Score
The Score increase will be the the rows that eliminated times the difficulty (from 1 to 6, respect to the 6 opposite characters.

### Skill Point
Skill point is the energy for character to use skill. Incease when rows are eliminated. It will be full when eliminate 20 rows.

### Control (GBA)
```
	UP -> rotate the current piece
	DOWN -> speed up the falling
	LEFT -> move the current piece to left
	right -> move the current piece to right
	A -> make choices or pass the start picture and text
	START -> Use in tile 
	SELECT -> restart the game, when the game is playing, game over or game clear.
	R -> use the kill of the character, if the the skill is ready
```

### Characters
#### Reimu
##### Skill
  - Fantasy Seal: Eliminate the 3 rows at bottom.

    - Example:
		
		```
		xxxxx
		xxxxx
		xxxxx
		```

#### Cirno
##### Skill
  - I'am the strongest: Eliminate two triangle shapes at left side and right side, this skill just eliminate the shape, it won't let the rest falling down.
    - Example:	
		
		```
		xooox
		xxxxx
		xooox
		```

