## Terrain generation
* Caves: Should work with 3D perlin noise

## Saving
* Run length encoding should reduce data use, but throwing zlib on top of that should reduce problems
    * ... and throwing zlib on top of that should reduce the world to a few megabytes instead of however big it gets when throwing the chunks at it.
    * ... or LZ4 instead of zlib. Probably better given that zlip looks pretty abandoned
* A second "compression" method could be to not save chunks that are a part of the world, but are undiscovered. This does present several challenges for AI
