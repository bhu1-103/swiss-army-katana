# TIC-80 Game Prototypes

This directory contains a collection of small game prototypes and experiments developed for the [TIC-80](https://tic80.com/) fantasy console.

## Projects

The `.tic` files in this directory are self-contained game cartridges. They are written in Lua and focus on implementing core platformer mechanics:

-   **Movement:** Basic left/right movement and sprite handling.
-   **Gravity:** A simple physics implementation to simulate gravity.
-   **Jumping:** Various iterations on jump mechanics, including a `better-double-jump.tic` file that refines the feel of the jump.
-   **Sprite Wrapping:** Code to make the player character wrap around the screen when they go off the edge.