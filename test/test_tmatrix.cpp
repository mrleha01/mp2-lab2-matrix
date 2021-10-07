#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
  TMatrix<int> m(5);

  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
	const int size = 10;
	TMatrix<int> m1(size);
	for (int i = 0; i < size; ++i)
	{
		for (int j = i; j < size; ++j)
		{
			m1[i][j] = i * size + j;
		}
	}
	TMatrix<int> m2(m1);
	ASSERT_EQ(m1, m2);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	const int size = 10;
	TMatrix<int> m1(size);
	for (int i = 0; i < size; ++i)
	{
		for (int j = i; j < size; ++j)
		{
			m1[i][j] = i * size + j;
		}
	}
	TMatrix<int> m2(m1);
	ASSERT_NE(&(m1[0][0]), &(m2[0][0]));
}

TEST(TMatrix, can_get_size)
{
	TMatrix<int> m(10);
	ASSERT_EQ(m.GetSize(), 10);
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int> m(10);
	m[2][3] = 5;
	ASSERT_EQ(m[2][3], 5);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int> m(10);
    ASSERT_ANY_THROW(m[-1][-1] = 5);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	TMatrix<int> m(10);
	ASSERT_ANY_THROW(m[10][10] = 5);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix<int> v(10);
	for (int i = 0; i < 10; ++i)
	{
		for (int j = i; j < 10; ++j)
		{
			v[i][j] = i * 10 + j;
		}
		
	}
	TMatrix<int> v1(v);
	v = v;
	ASSERT_EQ(v, v1);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	TMatrix<int> v(10);
	for (int i = 0; i < 10; ++i)
	{
		for (int j = i; j < 10; ++j)
		{
			v[i][j] = i * 10 + j;
		}

	}
	TMatrix<int> v1(10);
	v1 = v;
	ASSERT_EQ(v, v1);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	TMatrix<int> v(10);
	TMatrix<int> v1(5);
	v1 = v;
	ASSERT_EQ(v1.GetSize(), 10);
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	TMatrix<int> v(10);
	for (int i = 0; i < 10; ++i)
	{
		for (int j = i; j < 10; ++j)
		{
			v[i][j] = i * 10 + j;
		}

	}
	TMatrix<int> v1(5);
	ASSERT_NO_THROW(v1 = v);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	TMatrix<int> v(10);
	for (int i = 0; i < 10; ++i)
	{
		for (int j = i; j < 10; ++j)
		{
			v[i][j] = i * 10 + j;
		}

	}
	TMatrix<int> v1(v);
	ASSERT_EQ(v, v1);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int> v(10);
	for (int i = 0; i < 10; ++i)
	{
		for (int j = i; j < 10; ++j)
		{
			v[i][j] = i * 10 + j;
		}

	}
	ASSERT_EQ(v, v);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int> v(10);
	TMatrix<int> v1(5);
	ASSERT_NE(v, v1);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int> v(10);
	TMatrix<int> v1(10);
	ASSERT_NO_THROW(v + v1);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> v(10);
	TMatrix<int> v1(15);
	ASSERT_ANY_THROW(v + v1);
}

/*

 / \\\\\\\\\
/   \\\\\\\\\
=====        |
|   |        |
=====     -

*/
TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix<int> v(10);
	TMatrix<int> v1(10);
	ASSERT_NO_THROW(v - v1);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> v(10);
	TMatrix<int> v1(15);
	ASSERT_ANY_THROW(v - v1);
}

