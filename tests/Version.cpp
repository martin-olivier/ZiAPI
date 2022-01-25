#include "ziapi/Version.hpp"

#include <gtest/gtest.h>

TEST(Version, equal)
{
    ziapi::Version a{1, 0};
    ziapi::Version b{1, 0};

    ASSERT_TRUE(a == b);

    a = ziapi::Version{1, 1};
    b = ziapi::Version{1, 0};

    ASSERT_FALSE(a == b);

    a = ziapi::Version{2, 0};
    b = ziapi::Version{1, 1};

    ASSERT_FALSE(a == b);
}

TEST(Version, not_equal)
{
    ziapi::Version a{1, 0};
    ziapi::Version b{1, 0};

    ASSERT_FALSE(a != b);

    a = ziapi::Version{1, 1};
    b = ziapi::Version{1, 0};

    ASSERT_TRUE(a != b);

    a = ziapi::Version{2, 0};
    b = ziapi::Version{1, 1};

    ASSERT_TRUE(a != b);
}

TEST(Version, greater)
{
    ziapi::Version a{1, 0};
    ziapi::Version b{1, 0};

    ASSERT_FALSE(a > b);

    a = ziapi::Version{1, 1};
    b = ziapi::Version{1, 0};

    ASSERT_TRUE(a > b);

    a = ziapi::Version{2, 0};
    b = ziapi::Version{3, 1};

    ASSERT_FALSE(a > b);
}

TEST(Version, lower)
{
    ziapi::Version a{1, 0};
    ziapi::Version b{1, 0};

    ASSERT_FALSE(a < b);

    a = ziapi::Version{1, 1};
    b = ziapi::Version{3, 4};

    ASSERT_TRUE(a < b);

    a = ziapi::Version{2, 0};
    b = ziapi::Version{1, 0};

    ASSERT_FALSE(a < b);
}

TEST(Version, upper_eq)
{
    ziapi::Version a{1, 0};
    ziapi::Version b{1, 0};

    ASSERT_TRUE(a >= b);

    a = ziapi::Version{3, 1};
    b = ziapi::Version{1, 4};

    ASSERT_TRUE(a >= b);

    a = ziapi::Version{1, 6};
    b = ziapi::Version{3, 6};

    ASSERT_FALSE(a >= b);
}

TEST(Version, lower_eq)
{
    ziapi::Version a{1, 0};
    ziapi::Version b{1, 0};

    ASSERT_TRUE(a <= b);

    a = ziapi::Version{1, 1};
    b = ziapi::Version{3, 1};

    ASSERT_TRUE(a <= b);

    a = ziapi::Version{2, 4};
    b = ziapi::Version{1, 7};

    ASSERT_FALSE(a <= b);
}