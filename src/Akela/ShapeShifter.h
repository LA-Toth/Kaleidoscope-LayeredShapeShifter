/* -*- mode: c++ -*-
 * Akela -- Animated Keyboardio Extension Library for Anything
 * Copyright (C) 2016, 2017  Gergely Nagy
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

#include <Akela-Core.h>

namespace Akela {
  class ShapeShifter : public KeyboardioPlugin {
  public:
    typedef struct {
      Key original, replacement;
    } dictionary_t;

    ShapeShifter (void);

    virtual void begin (void) final;

    static void configure (const dictionary_t dictionary[]);

    void on (void);
    void off (void);

  private:
    static const dictionary_t *dictionary;
    static bool modActive;

    static Key eventHandlerHook (Key mappedKey, byte row, byte col, uint8_t keyState);
    static Key noOpHook (Key, byte row, byte col, uint8_t keyState);

    static void loopHook (bool postClear);
    static void noOpLoopHook (bool postClear);
  };
};

extern Akela::ShapeShifter ShapeShifter;