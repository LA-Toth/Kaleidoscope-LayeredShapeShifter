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

#include <Kaleidoscope-ShapeShifter.h>
#include <kaleidoscope/hid.h>
#include "layers.h"

namespace kaleidoscope {

const ShapeShifter::layer_t *ShapeShifter::layers = NULL;
bool ShapeShifter::mod_active_;

EventHandlerResult ShapeShifter::beforeReportingState() {
  mod_active_ = hid::isModifierKeyActive(Key_LeftShift) ||
                hid::isModifierKeyActive(Key_RightShift);
  return EventHandlerResult::OK;
}

EventHandlerResult ShapeShifter::onKeyswitchEvent(Key &mapped_key, byte row, byte col, uint8_t key_state) {
  if (!layers)
    return EventHandlerResult::OK;

  // If Shift is not active, bail out early.
  if (!mod_active_)
    return EventHandlerResult::OK;

  uint8_t active_layer = Layer.lookupActiveLayer(row, col);
  uint8_t i = 0;
  uint8_t base;

  do {
    base = pgm_read_word(&(layers[i].base));
    ++i;
  }  while (base != SHSH_NO_LAYER && base != active_layer);

  if (base == SHSH_NO_LAYER) 
    return EventHandlerResult::OK;

  uint8_t shift_layer = pgm_read_word(&(layers[i - 1].shift));

  Key repl = Layer.getKeyFromPROGMEM(shift_layer, row, col);

  if (repl.raw == Key_Transparent.raw)
    return EventHandlerResult::OK;

  mapped_key = repl;
  return EventHandlerResult::OK;
}

// Legacy V1 API
#if KALEIDOSCOPE_ENABLE_V1_PLUGIN_API
void ShapeShifter::begin() {
  Kaleidoscope.useEventHandlerHook(legacyEventHandler);
  Kaleidoscope.useLoopHook(legacyLoopHook);
}

Key ShapeShifter::legacyEventHandler(Key mapped_key, byte row, byte col, uint8_t key_state) {
  EventHandlerResult r = ::ShapeShifter.onKeyswitchEvent(mapped_key, row, col, key_state);
  if (r == EventHandlerResult::OK)
    return mapped_key;
  return Key_NoKey;
}

void ShapeShifter::legacyLoopHook(bool is_post_clear) {
  if (is_post_clear)
    return;
  ::ShapeShifter.beforeReportingState();
}
#endif

}

kaleidoscope::ShapeShifter ShapeShifter;
