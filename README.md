# Kaleidoscope-ShapeShifter

![status][st:stable] [![Build Status][travis:image]][travis:status]

 [travis:image]: https://travis-ci.org/keyboardio/Kaleidoscope-ShapeShifter.svg?branch=master
 [travis:status]: https://travis-ci.org/keyboardio/Kaleidoscope-ShapeShifter

 [st:stable]: https://img.shields.io/badge/stable-✔-black.svg?style=flat&colorA=44cc11&colorB=494e52
 [st:broken]: https://img.shields.io/badge/broken-X-black.svg?style=flat&colorA=e05d44&colorB=494e52
 [st:experimental]: https://img.shields.io/badge/experimental----black.svg?style=flat&colorA=dfb317&colorB=494e52

`ShapeShifter` is a plugin that makes it considerably easier to change what
symbol is input when a key is pressed together with `Shift`. If one wants to
rearrange the symbols on the number row for example, without modifying the
layout on the operating system side, this plugin is where one can turn to.

What it does, is very simple: if any key in its dictionary is found pressed
while `Shift` is held, it will press another key instead of the one triggering
the event. For example, if it sees `Shift + 1` pressed together, which normally
results in a `!`, it will press `4` instead of `1`, inputting `$`.

## Using the plugin

To use the plugin, one needs to include the header, create a dictionary, and
configure the provided `ShapeShifter` object to use the dictionary:

```c++
#include <Kaleidoscope.h>
#include <Kaleidoscope-ShapeShifter.h>


// define layer mapping for ShapeShifter
// SHSH_LAYER(base, shift) is used, where base is the layer which should have different shift'ed keys
// and shift is the layer index which contains the replacement keys
SHSH_LAYERS(
            // SHSH_LAYER(DVORAK, DVORAK_SHIFT),
            SHSH_LAYER(0, 1)
);

KALEIDOSCOPE_INIT_PLUGINS(ShapeShifter);

void setup() {
  Kaleidoscope.setup();

  // Register / use defined layer mapping
  SHSH_USE_LAYERS();
}
```

The `SHSH_LAYERS`, `SHSH_LAYER`, and `SHSH_USE_LAYERS` are helper macros for easier usage.

Any key can be unshifted with the `SHSH_UNSHIFT` or by using the `LSHIFT` modifier.
Unfortunately it works only for single keypresses, repeated may be sent with the SHIFT modifier,

## Plugin methods

The plugin provides the `ShapeShifter` object, with the following methods and
properties:

### `.layers`

> Set this property to the dictionary `ShapeShifter` should use. The layers
> is an array of `kaleidoscope::ShapeShifter::layer_t` elements, which is
> just a very verbose way of saying that its a pair of layer indices.
> The first one is the layer that may have replacement keys defined in
> a layer having index stored in the second layer index.
>
> Be aware that the replacement key will be pressed with `Shift` held, so do
> keep that in mind!

## Further reading

Starting from the [example][plugin:example] is the recommended way of getting
started with the plugin.

 [plugin:example]: https://github.com/keyboardio/Kaleidoscope-ShapeShifter/blob/master/examples/ShapeShifter/ShapeShifter.ino
