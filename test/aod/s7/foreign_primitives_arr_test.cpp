#include "gtest/gtest.h"
#include "s7.h"
#include "aod/s7/foreign_primitives.hpp"
#include "aod/s7/foreign_primitives_arr.hpp"
#include "aod/s7.hpp"
#include <string>
#include <stdio.h>

TEST ( foreign_primitives_arr_gen, bool_arr ) {
    s7_scheme *sc = s7_init();
    aod::s7::set_print_stderr(sc);

    aod::s7::foreign::bind_primitives_arr(sc);

    s7_pointer x = s7_eval_c_string(sc,
            "(define x ((*foreign* 'new-bool[]) 3))");

    bool *arr = (bool*) s7_c_object_value(x);
    ASSERT_EQ(false, arr[0]);
    ASSERT_EQ(false, arr[1]);
    ASSERT_EQ(false, arr[2]);

    ASSERT_EQ(false, s7_boolean(sc, s7_eval_c_string(sc, "(x 0)")));
    ASSERT_EQ(false, s7_boolean(sc, s7_eval_c_string(sc, "(x 1)")));
    ASSERT_EQ(false, s7_boolean(sc, s7_eval_c_string(sc, "(x 2)")));

    arr[0] = true;
    arr[2] = true;

    ASSERT_EQ(true, s7_boolean(sc, s7_eval_c_string(sc, "(x 0)")));
    ASSERT_EQ(false, s7_boolean(sc, s7_eval_c_string(sc, "(x 1)")));
    ASSERT_EQ(true, s7_boolean(sc, s7_eval_c_string(sc, "(x 2)")));

    s7_eval_c_string(sc, "(set! (x 1) #t)");
    ASSERT_EQ(true, arr[1]);

}

TEST ( foreign_primitives_arr_gen, int_arr ) {
    s7_scheme *sc = s7_init();
    aod::s7::set_print_stderr(sc);

    aod::s7::foreign::bind_primitives_arr(sc);

    s7_pointer x = s7_eval_c_string(sc,
            "(define x ((*foreign* 'new-int[]) 3))");

    int *arr = (int*) s7_c_object_value(x);
    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 2;

    ASSERT_EQ(0, s7_number_to_integer(sc, s7_eval_c_string(sc, "(x 0)")));
    ASSERT_EQ(1, s7_number_to_integer(sc, s7_eval_c_string(sc, "(x 1)")));
    ASSERT_EQ(2, s7_number_to_integer(sc, s7_eval_c_string(sc, "(x 2)")));

    s7_eval_c_string(sc, "(set! (x 0) 10)");
    s7_eval_c_string(sc, "(set! (x 1) 11)");
    s7_eval_c_string(sc, "(set! (x 2) 12)");

    ASSERT_EQ(10, arr[0]);
    ASSERT_EQ(11, arr[1]);
    ASSERT_EQ(12, arr[2]);
}

TEST ( foreign_primitives_arr_gen, float_arr ) {
    s7_scheme *sc = s7_init();
    aod::s7::set_print_stderr(sc);

    // can we bing all together in *foreign* ?
    s7_pointer env = aod::s7::make_env(sc);
    aod::s7::foreign::bind_primitives_arr(sc, env);
    aod::s7::foreign::bind_primitives(sc, env);


    s7_pointer x = s7_eval_c_string(sc,
            "(define x ((*foreign* 'new-float[]) 3))");

    float *arr = (float*) s7_c_object_value(x);
    arr[0] = 0.0;
    arr[1] = 1.1;
    arr[2] = 2.2;

    ASSERT_EQ(0.0f, s7_number_to_real(sc, s7_eval_c_string(sc, "(x 0)")));
    ASSERT_EQ(1.1f, s7_number_to_real(sc, s7_eval_c_string(sc, "(x 1)")));
    ASSERT_EQ(2.2f, s7_number_to_real(sc, s7_eval_c_string(sc, "(x 2)")));

    s7_eval_c_string(sc, "(set! (x 0) 10.0)");
    s7_eval_c_string(sc, "(set! (x 1) 11.1)");
    s7_eval_c_string(sc, "(set! (x 2) 12.2)");

    ASSERT_EQ(10.0f, arr[0]);
    ASSERT_EQ(11.1f, arr[1]);
    ASSERT_EQ(12.2f, arr[2]);
}