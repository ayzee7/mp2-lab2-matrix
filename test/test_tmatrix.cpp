#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	//ADD_FAILURE();
	TDynamicMatrix<int> m(10);
	//TDynamicMatrix<int> m1(m);
	TDynamicMatrix<int> m1 = m;
	EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(10);
	TDynamicMatrix<int> m1(m);
	EXPECT_NE(&m, &m1);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(4);

	EXPECT_EQ(4, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(4);
	m[1][3] = 4;

	EXPECT_EQ(4, m[1][3]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(4);
	ASSERT_ANY_THROW(m.at(-1).at(0) = 1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(4);
	ASSERT_ANY_THROW(m.at(4).at(0) = 1);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(10);
	ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m(10);
	TDynamicMatrix<int> m1(10);
	ASSERT_NO_THROW(m1 = m);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m(10);
	TDynamicMatrix<int> m1(5);
	m1 = m;
	EXPECT_EQ(m1.size(), m.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m(10);
	TDynamicMatrix<int> m1(5);
	ASSERT_NO_THROW(m1 = m);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(2);

	m[0][0] = 1;
	m[0][1] = 3;
	m[1][0] = 2;
	m[1][1] = 4;

	m1[0][0] = 1;
	m1[0][1] = 3;
	m1[1][0] = 2;
	m1[1][1] = 4;

	EXPECT_EQ(true, m1 == m);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(2);

	m[0][0] = 1;
	m[0][1] = 3;
	m[1][0] = 2;
	m[1][1] = 4;

	EXPECT_EQ(true, m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(4);
	EXPECT_NE(m, m1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(3);
	ASSERT_NO_THROW(m + m1);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(4);
	ASSERT_ANY_THROW(m + m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(3);
	ASSERT_NO_THROW(m - m1);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(4);
	ASSERT_ANY_THROW(m - m1);
}

//	Additional tests
TEST(TDynamicMatrix, cant_create_matrix_with_null_length) {
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(0));
}

TEST(TDynamicMatrix, can_move_matrix) {
	ASSERT_NO_THROW(TDynamicMatrix<int> m(TDynamicMatrix<int>(10)));
}

TEST(TDynamicMatrix, can_assign_move_matrix) {
	TDynamicMatrix<int> m(10);
	ASSERT_NO_THROW(TDynamicMatrix<int> m1 = std::move(m));
}

TEST(TDynamicMatrix, moved_matrix_has_no_memory_pointer) {
	TDynamicMatrix<int> m(10);
	TDynamicMatrix<int> m1 = std::move(m);
	EXPECT_TRUE(m.isEmpty());
}

TEST(TDynamicMatrix, matrix_memory_pointer_moved_to_new_one) {
	TDynamicMatrix<int> m(10);
	TDynamicVector<int>* pm = &m[0];
	TDynamicMatrix<int> m1 = std::move(m);
	ASSERT_EQ(pm, &m1[0]);
}

TEST(TDynamicMatrix, moved_matrix_equal_to_source) {
	TDynamicMatrix<int> m(2);
	m[0][0] = 1;
	m[0][1] = 2;
	m[1][0] = 3;
	m[1][1] = 4;
	TDynamicMatrix<int> m_copy(m);
	TDynamicMatrix<int> m1 = std::move(m);
	ASSERT_EQ(m_copy, m1);
}

TEST(TDynamicMatrix, can_multiply_scalar_by_matrix) {
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> expM(2);

	m[0][0] = 1;
	m[0][1] = 2;
	m[1][0] = 3;
	m[1][1] = 4;
	expM[0][0] = 2;
	expM[0][1] = 4;
	expM[1][0] = 6;
	expM[1][1] = 8;

	ASSERT_EQ(expM, m * 2);
}

TEST(TDynamicMatrix, can_multiply_vector_by_matrix) {
	TDynamicMatrix<int> m(2);
	TDynamicVector<int> v(2);
	TDynamicVector<int> expV(2);

	m[0][0] = 1;
	m[0][1] = 2;
	m[1][0] = 3;
	m[1][1] = 4;
	v[0] = 1;
	v[1] = 2;
	expV[0] = 5;
	expV[1] = 11;

	ASSERT_EQ(expV, m * v);
}

TEST(TDynamicMatrix, cant_multiply_vector_by_matrix_with_not_equal_sizes) {
	TDynamicMatrix<int> m(4);
	TDynamicVector<int> v(2);
	ASSERT_ANY_THROW(m * v);
}

TEST(TDynamicMatrix, can_multiply_matrixes) {
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> expM(2);

	m[0][0] = 1;
	m[0][1] = 2;
	m[1][0] = 3;
	m[1][1] = 4;

	m1[0][0] = 3;
	m1[0][1] = 1;
	m1[1][0] = 2;
	m1[1][1] = 4;

	expM[0][0] = 7;
	expM[0][1] = 9;
	expM[1][0] = 17;
	expM[1][1] = 19;

	ASSERT_EQ(expM, m * m1);
}

TEST(TDynamicMatrix, cant_multiply_matrixes_with_not_equal_sizes) {
	TDynamicMatrix<int> m(4);
	TDynamicMatrix<int> m1(2);
	ASSERT_ANY_THROW(m * m1);
}