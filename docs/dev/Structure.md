# Code structure

This is roughly the target structure.

## Math

Primarily applies to detached math and physics, i.e. math and physics that can be defined without depending on the engine-specific classes.

## Data

Raw data, primarily for stuff like settings, constants, etc.

## Render engine

Contains the render core, as well as rendering-related stuff; this means input, math and physics heavily related to rendering or byproducts of rendering (raycasting), etc.

## Core

Contains the game itself. For the most part, no brand new rendering schemes should be defined here. 
