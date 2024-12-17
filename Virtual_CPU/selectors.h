#pragma once

bool mux_2_to_1(bool a, bool b, bool selector) {
    return OR(AND(a, NOT(selector)), AND(b, selector));
}
