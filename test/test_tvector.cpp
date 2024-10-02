#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v(10);
	TDynamicVector<int> v1(v);
	EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v(10);
	TDynamicVector<int> v1(v);
	EXPECT_NE(&v, &v1);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v.at(-1) = 1);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v.at(4) = 1);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(10);
	ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v(10);
	TDynamicVector<int> v1(10);
	ASSERT_NO_THROW(v1 = v);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v(10);
	TDynamicVector<int> v1(5);
	v1 = v;
	EXPECT_EQ(v1.size(), v.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v(10);
	TDynamicVector<int> v1(5);
	ASSERT_NO_THROW(v1 = v);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v(2);
	TDynamicVector<int> v1(2);

	v[0] = 1;
	v[1] = 3;
	v1[0] = 1;
	v1[1] = 3;

	EXPECT_EQ(true, v1 == v);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(2);

	v[0] = 1;
	v[1] = 3;

	EXPECT_EQ(true, v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v(2);
	TDynamicVector<int> v1(4);
	EXPECT_NE(v, v1);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v_exp(3);
	//	v = {1, 2, 3}, v_exp = {3, 4, 5}
	v[0] = 1;
	v[1] = 2;
	v[2] = 3;
	v_exp[0] = 3;
	v_exp[1] = 4;
	v_exp[2] = 5;
	
	EXPECT_EQ(v_exp, v + 2);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v_exp(3);
	//	v = {3, 4, 5}, v_exp = {1, 2, 3}
	v[0] = 3;
	v[1] = 4;
	v[2] = 5;
	v_exp[0] = 1;
	v_exp[1] = 2;
	v_exp[2] = 3;

	EXPECT_EQ(v_exp, v - 2);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v_exp(3);
	//	v = {1, 2, 3}, v_exp = {2, 4, 6}
	v[0] = 1;
	v[1] = 2;
	v[2] = 3;
	v_exp[0] = 2;
	v_exp[1] = 4;
	v_exp[2] = 6;

	EXPECT_EQ(v_exp, v * 2);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(3);
	ASSERT_NO_THROW(v + v1);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(6);
	ASSERT_ANY_THROW(v + v1);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(3);
	ASSERT_NO_THROW(v - v1);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(6);
	ASSERT_ANY_THROW(v - v1);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(3);
	ASSERT_NO_THROW(v * v1);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(6);
	ASSERT_ANY_THROW(v * v1);
}

//	Additional tests
TEST(TDynamicVector, cant_create_vector_with_null_length) {
	ASSERT_ANY_THROW(TDynamicVector<int> v(0));
}

TEST(TDynamicVector, can_move_vector) {
	ASSERT_NO_THROW(TDynamicVector<int> v(TDynamicVector<int>(10)));
}

TEST(TDynamicVector, can_assign_move_vector) {
	TDynamicVector<int> v(10);
	ASSERT_NO_THROW(TDynamicVector<int> v1 = std::move(v));
}

TEST(TDynamicVector, moved_vector_has_no_memory_pointer) {
	TDynamicVector<int> v(10);
	TDynamicVector<int> v1 = std::move(v);
	EXPECT_TRUE(v.isEmpty());
}

TEST(TDynamicVector, vector_memory_pointer_moved_to_new_one) {
	TDynamicVector<int> v(10);
	int* pv = &v[0];
	TDynamicVector<int> v1 = std::move(v);
	ASSERT_EQ(pv, &v1[0]);
}

TEST(TDynamicVector, moved_vector_equal_to_source) {
	TDynamicVector<int> v(3);
	v[0] = 1;
	v[1] = 2;
	v[2] = 3;
	TDynamicVector<int> v_copy(v);
	TDynamicVector<int> v1 = std::move(v);
	ASSERT_EQ(v_copy, v1);
}

TEST(TDynamicVector, can_swap_vectors) {
	TDynamicVector<int> v1(2);
	TDynamicVector<int> v2(2);
	//	v1 = {1, 2}, v2 = {3, 4}
	v1[0] = 1;
	v1[1] = 2;
	v2[0] = 3;
	v2[1] = 4;
	//	v3 = v1
	TDynamicVector<int> v3(v1);
	swap(v1, v2);
	ASSERT_EQ(v2, v3);
}