# General

* [x] Abstract away text models to a class
    * [ ] ... and make them modifiable
    * [ ] ... and translatable. Using a matrix might be optimal, at least if we also want to fuck around with text effects
    * [ ] Game text (separate shader; uses a world shader instead of a UI shader)
* [x] Figure out the fuck text was so urgently needed for
* [ ] Mouse picking
* [ ] Figure out what the fuck we're doing about naturally generating resources with the noise function being broken af

# Menu

* [ ] Set up basic menus
    * For now:
        * [ ] Scene framework
        * [ ] Menu
        * [ ] The actual game
        * [ ] Command line options for jumping straight to the game

# Rendering
* [ ] Optimize chunks -- either a solid mesh sent to the renderer (potentially incompatible with a multidimensional system, when implemented, due to mining mechanics), or by making sure to only render visible tiles
    * [ ] Bonus: Low-resolution, single-chunk textures for zooming out
* [ ] Check if 430/440 is a better choice wrt. compute shaders
