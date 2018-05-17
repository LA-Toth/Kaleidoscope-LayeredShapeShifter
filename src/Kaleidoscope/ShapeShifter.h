/* -*- mode: c++ -*-
 * Kaleidoscope-ShapeShifter -- Change the shifted symbols on any key of your choice
 * Copyright (C) 2016, 2017  Gergely Nagy
 * Copyright 2018  László Attila Tóth
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <Kaleidoscope.h>

#define SHSH_NO_LAYER 255

#define SHSH_LAYER(base, shift)  { base, shift }
#define SHSH_LAYERS(layers...) \
  static const kaleidoscope::ShapeShifter::layer_t shape_shifter_layers[] PROGMEM = { \
    layers, \
    SHSH_LAYER(SHSH_NO_LAYER, SHSH_NO_LAYER ),       \
  }

#define SHSH_USE_LAYERS() \
  ShapeShifter.layers = shape_shifter_layers

namespace kaleidoscope {

class ShapeShifter : public KaleidoscopePlugin {
 public:
  typedef struct {
    uint8_t base, shift;
  } layer_t;

  ShapeShifter(void) {}

  static const layer_t *layers;

  EventHandlerResult onKeyswitchEvent(Key &mapped_key, byte row, byte col, uint8_t key_state);
  EventHandlerResult beforeReportingState();

#if KALEIDOSCOPE_ENABLE_V1_PLUGIN_API
 protected:
  void begin();
  static Key legacyEventHandler(Key mapped_key, byte row, byte col, uint8_t key_state);
  static void legacyLoopHook(bool is_post_clear);
#endif

 private:
  static bool mod_active_;
};

}

extern kaleidoscope::ShapeShifter ShapeShifter;
