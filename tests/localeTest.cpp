// Copyright (c) 2017-2025, University of Cincinnati, developed by Henry Schreiner
// under NSF AWARD 1414736 and by the respective contributors.
// All rights reserved.
//
// SPDX-License-Identifier: BSD-3-Clause

#include "app_helper.hpp"

#include <complex>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <locale>
#include <iomanip>
#include <numeric>


// Custom facet for thousands separator
class CustomThousandsSeparator : public std::numpunct<char> {
protected:
    char do_thousands_sep() const override { return '|'; }  // Space separator
    std::string do_grouping() const override { return "\2"; } // Group digits in sets of 2
};

//derived from https://github.com/CLIUtils/CLI11/pull/1160
TEST_CASE_METHOD(TApp, "locale", "[separators]") {
    std::locale customLocale(std::locale::classic(), new CustomThousandsSeparator);
    std::locale::global(customLocale);  // Set as the default system-wide locale

    // Ensure standard streams use the custom locale automatically
    std::cout.imbue(std::locale());
    std::int64_t foo;

    app.add_option("FOO", foo, "Foo option")
        ->default_val(1234567)->force_callback();

    CHECK_NOTHROW(run());
    CHECK(foo==1234567);

}
