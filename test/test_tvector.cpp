#include "utmatrix.h"

#include <gtest.h>

namespace
{
	template <class Type>
	Type IdentityFunction(int i)
	{
		return i;
	}

	template <class Type>
	Type ConstantFunction(int i, Type theConstant)
	{
		return theConstant;
	}

	// Returns a vector TVector<Type>, each element of which is initialized with a functor theFunc
	// that takes one required argument - the index of the currently initialized element.
	// Also, this functor can have an arbitrary number of other arguments - theArgs.
	template <class Type, class Functor, class... ArgsType>
	TVector<Type> CreateVector(const int theSize, Functor theFunc, ArgsType... theArgs)
	{
		TVector<Type> aVector(theSize);
		for (int i = 0; i < theSize; ++i)
		{
			aVector[i] = theFunc(i, theArgs...);
		}
		return aVector;
	}
}

TEST(TVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
  ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector)
{
  TVector<int> v(10);

  ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one)
{
	TVector<int> v(10);
	ASSERT_EQ(TVector<int>(v), v);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
	const int size = 10;
	TVector<int> v(size);
	TVector<int> v1(v);
	ASSERT_NE(&(v[0]), &(v1[0]));
}

TEST(TVector, can_get_size)
{
  TVector<int> v(4);

  EXPECT_EQ(4, v.GetSize());
}

TEST(TVector, can_get_start_index)
{
  TVector<int> v(4, 2);

  EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVector, can_set_and_get_element)
{
  TVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
	TVector<int> v(10);
	ASSERT_ANY_THROW(v[-1] = 0);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
	TVector<int> v(10);
	ASSERT_ANY_THROW(v[10] = 0);
}

TEST(TVector, can_assign_vector_to_itself)
{
	TVector<int> v = CreateVector<int>(10, IdentityFunction<int>);
	TVector<int> v1(v);
	v = v;
	ASSERT_EQ(v, v1);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
	TVector<int> v = CreateVector<int>(10, IdentityFunction<int>);
	TVector<int> v1(10);
	v1 = v;
	ASSERT_EQ(v, v1);
}

TEST(TVector, assign_operator_change_vector_size)
{
	TVector<int> v = CreateVector<int>(5, IdentityFunction<int>);
	TVector<int> v1(10);
	v1 = v;
	ASSERT_EQ(5, v1.GetSize());
}

TEST(TVector, can_assign_vectors_of_different_size)
{
	TVector<int> v = CreateVector<int>(5, IdentityFunction<int>);
	TVector<int> v1(10);
	v1 = v;
	ASSERT_EQ(v1, v);
}

TEST(TVector, compare_equal_vectors_return_true)
{
	TVector<int> v = CreateVector<int>(10, IdentityFunction<int>);
	TVector<int> v1(v);
	ASSERT_TRUE(v == v1);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
	TVector<int> v = CreateVector<int>(10, IdentityFunction<int>);
	ASSERT_TRUE(v == v);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	TVector<int> v = CreateVector<int>(10, ConstantFunction<int>, 0);
	TVector<int> v1 = CreateVector<int>(12, ConstantFunction<int>, 0);
	ASSERT_NE(v, v1);
}

TEST(TVector, can_add_scalar_to_vector)
{
	TVector<int> v = CreateVector<int>(10, IdentityFunction<int>);
	int scalar = 10;

	TVector<int> expected = CreateVector<int>(10, [](int i, int scalar) {return IdentityFunction<int>(i) + scalar; }, scalar);

	TVector<int> actual = v + scalar;
	ASSERT_EQ(actual, expected);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	TVector<int> v = CreateVector<int>(10, IdentityFunction<int>);
	int scalar = 10;

	TVector<int> expected = CreateVector<int>(10, [](int i, int scalar) {return IdentityFunction<int>(i) - scalar; }, scalar);

	TVector<int> actual = v - scalar;
	ASSERT_EQ(actual, expected);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	TVector<int> v = CreateVector<int>(10, IdentityFunction<int>);
	int scalar = 10;

	TVector<int> expected = CreateVector<int>(10, [](int i, int scalar) {return IdentityFunction<int>(i) * scalar; }, scalar);

	TVector<int> actual = v * scalar;
	ASSERT_EQ(actual, expected);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	TVector<int> v = CreateVector<int>(10, IdentityFunction<int>);
	int value = 5;
	TVector<int> v1 = CreateVector<int>(10, ConstantFunction<int>, value);

	TVector<int> expected = CreateVector<int>(10, [](int i, int constant) { return IdentityFunction<int>(i) + ConstantFunction(i, constant); }, value);

	TVector<int> actual = v + v1;

	ASSERT_EQ(actual, expected);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	TVector<int> v(10);
	TVector<int> v1(12);
	ASSERT_ANY_THROW(v + v1);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
	TVector<int> v = CreateVector<int>(10, IdentityFunction<int>);
	int value = 5;
	TVector<int> v1 = CreateVector<int>(10, ConstantFunction<int>, value);

	TVector<int> expected = CreateVector<int>(10, [](int i, int constant) { return IdentityFunction<int>(i) - ConstantFunction(i, constant); }, value);

	TVector<int> actual = v - v1;

	ASSERT_EQ(actual, expected);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	TVector<int> v(10);
	TVector<int> v1(12);
	ASSERT_ANY_THROW(v - v1);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	TVector<int> v = CreateVector<int>(5, IdentityFunction<int>);
	int value = 6;
	TVector<int> v1 = CreateVector<int>(5, ConstantFunction<int>, value);

	int expected = (1 + 2 + 3 + 4) * 6;

	int actual = v * v1;

	ASSERT_EQ(actual, expected);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	TVector<int> v(10);
	TVector<int> v1(12);
	ASSERT_ANY_THROW(v * v1);
}

