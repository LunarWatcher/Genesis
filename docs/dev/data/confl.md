# Confl

Settings are stored in a primitive format; `.confl`. This is a creative adaption of the `.conf`/`.ini` and `.properties`-formats.

The general syntax is `identifying-key-in-any-case=value`. There's no spaces between the key and the value - this is necessary to facilitate prefixed spaces in the value, by reducing the amount of syntactic sugar.

As already mentioned, this is a light, compact, computer-readable format. This means there's no sections, no comments, and no section-based hierarchy. Contextual hierarchy can be inferred from names containing dots (i.e. `screen.width` - note that this isn't used at the time of writing), but this is just a glorified name.

These files aren't meant to be edited by humans, so there's absolutely no need for readable context.

Types are inferred per-field. This is the primary reason a custom format is used: no need to rely on strings and slow, type-predictive parsing. This also means we can have substantially faster parsing, because we already know the type. No need to guess the type when parsing. This also gives flexibility for certain types of contextual fields, where we can store less information.

One example of this is the resolution; we can store `res=720`, and from that infer the width (because we're using a constant aspect ratio, because I don't wanna find out how I implement different aspect ratios at this time). When we parse, we additionally don't have to store `res` at all. We can save it directly as width and height, leaving us with usable data, and discarding the template.

Whether this is useful or not is yet to be determined - this is an ahead-of-time system to address the problems I see coming with saving at the time of writing.
