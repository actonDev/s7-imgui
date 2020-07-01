#pragma once

#include "s7.h"

namespace aod {
namespace s7 {

/**
 * Created the *c-bindings* environment (sublet?) which can be used to create
 * heap allocated c-objects.
 * In scheme, (c-object? x) will return true
 * In c, you can get the int* or bool* pointer by calling s7_c_object_value(obj)
 *
 * See c_primitives_test.cpp for a more detailed view.
 *
 * Usage
 *
 * - (define data-b (with-let *c-primitives* (bool #t)))
 * - (define data-i (with-let *c-primitives* (int 10)))
 *
 * Other style of calling:
 * - (define data-i ((*c-primitives* 'int) 20))
 *
 *
 * Reading:
 * - (data-b)
 * - (data-i)
 *
 * Writing:
 * - (set! (data-b) #t)
 * - (set! (data-i) 10)
 */
void bind_primitives(s7_scheme *sc);

} // ! s7
} // ! aod
