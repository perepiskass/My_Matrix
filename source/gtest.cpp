#include <gtest/gtest.h>
#include "version_lib.h"
#include "matrix.h"
#include <utility>



// Тест кейсы на проверку версий
TEST(version_test_case, version_test_patch)
{
    ASSERT_GE(version_patch(), 1);
}
TEST(version_test_case, version_test_minor)
{
    EXPECT_EQ(version_minor(), 1);
}
TEST(version_test_case, version_test_major)
{
    EXPECT_EQ(version_major(), 1);
}

TEST(matrix_test_case, add_element_test)
{
    Matrix<int,0> matrix;
    matrix[0][0] = 0;
    matrix[0][1] = 1;
    matrix[1][0] = 2;
    matrix[1][1] = 3;

    EXPECT_EQ(matrix[0][0],0);
    EXPECT_EQ(matrix[0][1],1);
    EXPECT_EQ(matrix[1][0],2);
    EXPECT_EQ(matrix[1][1],3);
}

TEST(matrix_test_case, size_matrix_test)
{
    Matrix<int,0> matrix;
    matrix[0][0] = 1;
    matrix[0][1] = 2;
    matrix[1][0] = 3;

    EXPECT_EQ(matrix.size(),3);
}

TEST(matrix_test_case, operator_assign_test)
{
    constexpr int defaultValues = 0;
    Matrix<int,defaultValues> matrix;
    matrix[0][0] = 1;
    matrix[0][1] = 2;
    matrix[1][0] = 3;

    (matrix[0][1] = defaultValues) = 4;
    matrix[1][0] = defaultValues;

    EXPECT_EQ(matrix[0][1],4);
    EXPECT_EQ(matrix.size(),2);
}

TEST(matrix_test_case, tupel_from_iterator_test)
{
    Matrix<int,0> matrix;
    matrix[77][55] = 33;

    auto it = matrix.begin();

    int x,y,v;
    std::tie(x,y,v) = *it;

    EXPECT_EQ(x,77);
    EXPECT_EQ(y,55);
    EXPECT_EQ(v,33);
}

TEST(matrix_test_case, ranged_based_for_test)
{
    Matrix<int,0> matrix;
    matrix[0][0] = 1;
    matrix[0][1] = 2;
    matrix[1][0] = 3;

    int value;
    auto count = 0;
    auto sum = 0;
    for(auto it : matrix)
    {
        std::tie(std::ignore,std::ignore,value) = it;
        sum += value;
        ++count;
    }

    EXPECT_EQ(count,3);
    EXPECT_EQ(sum,6);
    EXPECT_EQ(value,3);

}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}