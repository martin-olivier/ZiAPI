#include "ziapi/Version.hpp"

#include <gtest/gtest.h>

TEST(Version, equal)
{
    ziapi::Version a{1, 0, 3};
    ziapi::Version b{1, 0, 3};

    ASSERT_TRUE(a == b);

    a = ziapi::Version{1, 1, 3};
    b = ziapi::Version{1, 0, 3};

    ASSERT_FALSE(a == b);

    a = ziapi::Version{2, 0, 3};
    b = ziapi::Version{1, 1, 3};

    ASSERT_FALSE(a == b);
}

TEST(Version, not_equal)
{
    ziapi::Version a{1, 0, 0};
    ziapi::Version b{1, 0, 0};

    ASSERT_FALSE(a != b);

    a = ziapi::Version{1, 1, 0};
    b = ziapi::Version{1, 0, 0};

    ASSERT_TRUE(a != b);

    a = ziapi::Version{2, 0, 0};
    b = ziapi::Version{1, 1, 0};

    ASSERT_TRUE(a != b);
}

TEST(Version, greater)
{
    ziapi::Version a{1, 0, 3};
    ziapi::Version b{1, 0, 3};

    ASSERT_FALSE(a > b);

    a = ziapi::Version{1, 1, 2};
    b = ziapi::Version{1, 1, 0};

    ASSERT_TRUE(a > b);

    a = ziapi::Version{2, 0, 2};
    b = ziapi::Version{3, 1, 2};

    ASSERT_FALSE(a > b);
}

TEST(Version, less)
{
    ziapi::Version a{1, 0, 1};
    ziapi::Version b{1, 0, 0};

    ASSERT_FALSE(a < b);

    a = ziapi::Version{1, 1, 0};
    b = ziapi::Version{3, 4, 0};

    ASSERT_TRUE(a < b);

    a = ziapi::Version{2, 0, 1};
    b = ziapi::Version{1, 0, 0};

    ASSERT_FALSE(a < b);
}

TEST(Version, greater_or_equal)
{
    ziapi::Version a{1, 0, 0};
    ziapi::Version b{1, 0, 0};

    ASSERT_TRUE(a >= b);

    a = ziapi::Version{4, 0, 0};
    b = ziapi::Version{1, 4, 0};

    ASSERT_TRUE(a >= b);

    a = ziapi::Version{1, 6, 0};
    b = ziapi::Version{3, 6, 1};

    ASSERT_FALSE(a >= b);
}

TEST(Version, less_or_equal)
{
    ziapi::Version a{1, 0, 0};
    ziapi::Version b{1, 0, 0};

    ASSERT_TRUE(a <= b);

    a = ziapi::Version{1, 1, 2};
    b = ziapi::Version{4, 0, 0};

    ASSERT_TRUE(a <= b);

    a = ziapi::Version{2, 4, 42};
    b = ziapi::Version{1, 7, 0};

    ASSERT_FALSE(a < b);
    ASSERT_FALSE(a <= b);
}
