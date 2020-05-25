# Play around with 2D rectangles

- should be created a 2D plan, no larger than 80x25
- one can create rectangles by given the start x, y position as well, width and height
- one can move rectangles to the left and right by given the start x, y position as well how many positions should it move
- one can rotate the intire plan content 90 degrees
- rectangles should move with gravity, meaning that if nothing below them, should "drop" until find another object or the plan limit
- vertical lines should use `|`, horizontal lines should use `-` and all intersections should use `+`

## Commands

commands that need to be implemented

- `create x,y+w,h`
- `moveright x,y+p`
- `moveleft x,y+p`
- `rotate`

Commands should be either read from a file, or as a menu

## Example

The commands

```bash
create 1,3+12,5
create 9,5+11,3
create 18,9+6,3
moveleft 12,6+3
```
should draw, in a `30x15` plan:

```bash
*------------------------------*
|                              |
|                              |
|                              |
|                              |
|                              |
|                              |
|                              |
|      +---------+             |
|      |         |             |
| +----+-----+---+             |
| |          |                 |
| |          |                 |
| |          |     +----+      |
| |          |     |    |      |
| +----------+     +----+      |
*------------------------------*
```

## Compiling

to compile, use the command

```bash
clear && gcc -Wall -Werror -o rectangles main.c && ./rectangles
```
