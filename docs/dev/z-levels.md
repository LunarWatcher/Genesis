# Z-levels

To simplify gameplay, a z-level is effectively an abstraction of a floor tile and solid blocks. The height of a floor is undefined, and so is the height of the space on a z-level. The z-level implementation is heavily modelled after Dwarf Fortress due to equivalent gameplay mechanics in this particular area. It's also far easier to work with for players than each z level representing an individual block.

In true Dwarf Fortress fashion, the height of a z-level is whatever it needs to be to fit whatever is placed on it (except multi-level structures, such as trees or buildings). One way to think of a z-level is as a story in a building.

This also means the rendered world is primarily defined in terms of levels, and not chunks. This is to simplify the rendering and mesh generation process, since levels are the primary rendering function.

When 3D graphics are implemented, these will still serve as the main rendering system. How I'll implement 3D rendering is an implementation for future me to deal with.
