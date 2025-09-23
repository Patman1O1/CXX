#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

#include "singly_list/singly_list.hpp"


/* -------------------------------------------Definitions---------------------------------------------------- */
using value_type = int;

using size_type = std::size_t;

using difference_type = std::ptrdiff_t;

using allocator_type = std::allocator<value_type>;

using container_type = std::vector<value_type, allocator_type>;

using reference = value_type&;

using const_reference = const value_type&;

using pointer = std::allocator_traits<allocator_type>::pointer;

using const_pointer = std::allocator_traits<allocator_type>::const_pointer;

using singly_list = adt::singly_list<value_type, allocator_type>;

using iterator = singly_list::iterator;

using const_iterator = singly_list::const_iterator;

using node_type = singly_list::node_type;

/* -------------------------------------------------Variables-------------------------------------------------------- */
constexpr std::initializer_list<value_type> empty_init;

constexpr std::initializer_list<value_type> single_init = {1};

constexpr std::initializer_list<value_type> filled1_init = {1, 2, 3, 4, 5, 6};

constexpr std::initializer_list<value_type> filled2_init = {6, 7, 8, 9, 10, 11};

constexpr std::initializer_list<value_type> range_init = {1, 2, 3, 4, 5, 6};

constexpr size_type empty_size = 0;

constexpr size_type single_size = 1;

constexpr size_type filled1_size = filled1_init.size();

constexpr size_type filled2_size = filled2_init.size();

constexpr size_type range_size = range_init.size();

constexpr std::array<value_type, empty_size> empty_matcher;

constexpr std::array<value_type, single_size> single_matcher = {1};

constexpr std::array<value_type, filled1_size> filled1_matcher = {1, 2, 3, 4, 5, 6};

constexpr std::array<value_type, filled2_size> filled2_matcher = {6, 7, 8, 9, 10, 11};

const container_type range_container = range_init;

singly_list empty_list;

singly_list single_list = single_init;

singly_list filled1_list = filled1_init;

singly_list filled2_list = filled1_init;

const_iterator list_cit;

iterator list_it;

node_type list_node;

value_type list_value = 101;

/* ------------------------------------Constant Iterator Constructors Tests------------------------------------------ */
TEST(singly_list__const_iterator__constructors, default_constructor) {
	const_iterator cit;

	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit++, std::runtime_error);
}

TEST(singly_list__const_iterator__constructors, nullptr_constructor) {
	const_iterator cit(nullptr);

	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit++, std::runtime_error);
}

/* ----------------------------Constant Iterator Overloaded Operators Tests---------------------------------- */
TEST(singly_list__const_iterator__operators, addition_operator__filled_list) {
	list_cit = filled1_list.cbegin();
	for (size_type i = 0; i < filled1_size - 1; i++) {
		EXPECT_EQ(*(list_cit + i), filled1_matcher[i]);
	}

	EXPECT_THROW(static_cast<void>(*(list_cit + filled1_size)), std::runtime_error);
}

TEST(singly_list__const_iterator__operators, addition_operator__empty_list) {
	list_cit = empty_list.cbegin();

	EXPECT_EQ(list_cit, empty_list.cend());

	EXPECT_THROW(static_cast<void>(*list_cit), std::runtime_error);
	EXPECT_THROW(list_cit++, std::runtime_error);
}

TEST(singly_list__const_iterator__operators, addition_assignment_operator__filled_list) {
	const_iterator cbegin = filled1_list.cbegin();
	const_iterator cend = filled1_list.cend();

	list_cit = cbegin;

	for (size_type i = 0; i < filled1_size - 1; i++) {
		EXPECT_NE(list_cit, cend);
		EXPECT_NO_THROW(list_cit += i);
		EXPECT_EQ(*list_cit, i + 1);

		list_cit = cbegin;
	}

	EXPECT_NO_THROW(list_cit += filled1_size);
	EXPECT_EQ(list_cit, cend);

	EXPECT_THROW(static_cast<void>(list_cit += (filled1_size + 1)), std::runtime_error);
}

TEST(singly_list__const_iterator__operators, addition_assignment_operator__empty_list) {
	list_cit = empty_list.cbegin();

	EXPECT_EQ(list_cit, empty_list.cend());

	EXPECT_THROW(static_cast<void>(*list_cit), std::runtime_error);
	EXPECT_THROW(list_cit++, std::runtime_error);
}

TEST(singly_list__const_iterator__operators, assignment_operator__nullptr) {
	list_cit = nullptr;

	EXPECT_EQ(list_cit, nullptr);
	EXPECT_THROW(static_cast<void>(*list_cit), std::runtime_error);
	EXPECT_THROW(list_cit++, std::runtime_error);
}

/* -------------------------------------Iterator Constructors Tests------------------------------------------ */
TEST(singly_list__iterator__constructors, default_constructor) {
	iterator it;

	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(it++, std::runtime_error);
}

TEST(singly_list__iterator__constructors, nullptr_constructor) {
	iterator it(nullptr);

	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(it++, std::runtime_error);
}

/* ---------------------------------Iterator Overloaded Operators Tests-------------------------------------- */
TEST(singly_list__iterator__operators, addition_operator__filled_list) {
	iterator end = filled1_list.end();

	list_it = filled1_list.begin();

	for (size_type i = 0; i < filled1_size - 1; i++) {
		EXPECT_NE(list_it, end);
		EXPECT_EQ(*(list_it + i), i + 1);
	}

	EXPECT_THROW(static_cast<void>(*(list_it + filled1_size)), std::runtime_error);
}

TEST(singly_list__iterator__operators, addition_operator__empty_list) {
	list_it = empty_list.begin();

	EXPECT_EQ(list_it, nullptr);

	EXPECT_THROW(static_cast<void>(*list_it), std::runtime_error);
	EXPECT_THROW(list_it++, std::runtime_error);
}

TEST(singly_list__iterator__operators, addition_assignment_operator__filled_list) {
	iterator begin = filled1_list.begin();
	iterator end = filled1_list.end();

	list_it = filled1_list.begin();

	EXPECT_NE(list_it, end);
	for (size_type i = 0; i < filled1_size - 1; i++) {
		list_it = begin;
		EXPECT_NO_THROW(list_it += i);
		EXPECT_EQ(*list_it, i + 1);
	}

	list_it = begin;
	EXPECT_NO_THROW(list_it += filled1_size);
	EXPECT_EQ(list_it, end);

	list_it = begin;
	EXPECT_THROW(list_it += (filled1_size + 1), std::runtime_error);
}

TEST(singly_list__iterator__operators, addition_assignment_operator__empty_list) {
	list_it = empty_list.begin();

	EXPECT_EQ(list_it, empty_list.end());
	EXPECT_THROW(static_cast<void>(*list_it), std::runtime_error);
	EXPECT_THROW(list_it++, std::runtime_error);
}

TEST(singly_list__iterator__operators, assignment_operator__nullptr) {
	list_it = nullptr;

	EXPECT_EQ(list_it, nullptr);
	EXPECT_THROW(static_cast<void>(*list_it), std::runtime_error);
	EXPECT_THROW(list_it++, std::runtime_error);
}

/* ------------------------------------Node Type Constructors Tests----------------------------------------- */
TEST(singly_list__node_type__constructors, default_constructor) {
	node_type node;

	EXPECT_EQ(node, nullptr);
	EXPECT_TRUE(node.empty());

	EXPECT_THROW(static_cast<void>(node.value()), std::runtime_error);
}

TEST(singly_list__node_type__constructors, nullptr_constructor) {
	node_type node(nullptr);

	EXPECT_TRUE(node.empty());
	EXPECT_EQ(node, nullptr);

	EXPECT_THROW(static_cast<void>(node.value()), std::runtime_error);
}

TEST(singly_list__node_type__constructors, move_constructor__empty_list) {
	node_type src;
	node_type dst(std::move(src));

	EXPECT_TRUE(src.empty());
	EXPECT_EQ(src, nullptr);

	EXPECT_THROW(static_cast<void>(src.value()), std::runtime_error);

	EXPECT_TRUE(dst.empty());
	EXPECT_EQ(dst, nullptr);

	EXPECT_THROW(static_cast<void>(dst.value()), std::runtime_error);
}

TEST(singly_list__node_type__constructors, move_constructor__filled_list) {
	singly_list list = filled1_init;

	for (size_type i = 0; i < filled1_size; i++) {
		list_node = list.extract_after(list.cbefore_begin());
		node_type node = std::move(list_node);

		EXPECT_FALSE(node.empty());
		EXPECT_NE(node, nullptr);

		EXPECT_EQ(node.value(), filled1_matcher[i]);
	}
}

/* ---------------------------------------Node Type Destructor Tests----------------------------------------- */
TEST(singly_list__node_type__destructor, destructor) {
	singly_list list = single_init;

	list_node = list.extract_after(list.cbefore_begin());

	EXPECT_FALSE(list_node.empty());
	EXPECT_NO_THROW(static_cast<void>(list_node.value()));

	list_node.~node_type();

	EXPECT_TRUE(list_node.empty());
	EXPECT_THROW(static_cast<void>(list_node.value()), std::runtime_error);
}

/* ----------------------------------Node Type Overloaded Operators Tests------------------------------------ */
TEST(singly_list__node_type__operators, move_assignment_operator__empty_list_to_empty_list) {
	node_type src;
	node_type dst;

	dst = std::move(src);

	EXPECT_TRUE(src.empty());
	EXPECT_TRUE(dst.empty());

	EXPECT_EQ(src, nullptr);
	EXPECT_EQ(dst, nullptr);

	EXPECT_THROW(static_cast<void>(src.value()), std::runtime_error);
	EXPECT_THROW(static_cast<void>(dst.value()), std::runtime_error);

}

TEST(singly_list__node_type__operators, move_assignment_operator__empty_list_to_filled_list) {
	singly_list list = single_init;

	node_type src;
	node_type dst = list.extract_after(list.cbefore_begin());

	dst = std::move(src);

	EXPECT_TRUE(src.empty());
	EXPECT_EQ(src, nullptr);

	EXPECT_THROW(static_cast<void>(src.value()), std::runtime_error);

	EXPECT_TRUE(dst.empty());
	EXPECT_EQ(dst, nullptr);

	EXPECT_THROW(static_cast<void>(dst.value()), std::runtime_error);
}

TEST(singly_list__node_type__operators, move_assignment_operator__filled_list_to_empty_list) {
	singly_list list = single_init;

	node_type src = list.extract_after(list.cbefore_begin());
	node_type dst;

	dst = std::move(src);

	EXPECT_TRUE(src.empty());
	EXPECT_EQ(src, nullptr);

	EXPECT_THROW(static_cast<void>(src.value()), std::runtime_error);

	EXPECT_FALSE(dst.empty());
	EXPECT_NE(dst, nullptr);

	EXPECT_EQ(dst.value(), single_matcher[0]);
}

TEST(singly_list__node_type__operators, move_assignment_operator__filled_list_to_filled_list) {
	singly_list list1 = filled1_init;
	singly_list list2 = filled2_init;

	node_type src = list1.extract_after(list1.cbefore_begin());
	node_type dst = list2.extract_after(list2.cbefore_begin());

	dst = std::move(src);

	EXPECT_TRUE(src.empty());
	EXPECT_EQ(src, nullptr);

	EXPECT_THROW(static_cast<void>(src.value()), std::runtime_error);

	EXPECT_FALSE(dst.empty());
	EXPECT_NE(dst, nullptr);

	EXPECT_EQ(dst.value(), filled1_matcher[0]);
}

TEST(singly_list__node_type__operators, nullptr_assignment_operator__empty_list) {
	list_node = nullptr;

	EXPECT_TRUE(list_node.empty());
	EXPECT_EQ(list_node, nullptr);

	EXPECT_THROW(static_cast<void>(list_node.value()), std::runtime_error);
}

TEST(singly_list__node_type__operators, nullptr_assignment_operator__filled_list) {
	list_node = nullptr;

	EXPECT_TRUE(list_node.empty());
	EXPECT_EQ(list_node, nullptr);

	EXPECT_THROW(static_cast<void>(list_node.value()), std::runtime_error);
}

TEST(singly_list__node_type__operators, dereference_operator__empty_node) {
	list_node = nullptr;

	EXPECT_TRUE(list_node.empty());
	EXPECT_EQ(list_node, nullptr);

	EXPECT_THROW(static_cast<void>(list_node.value()), std::runtime_error);
}

TEST(singly_list__node_type__operators, bool_operator__empty_node) {
	list_node = nullptr;
	EXPECT_FALSE(list_node);
}

TEST(singly_list__node_type__operators, bool_operator__filled_node) {
	singly_list list = single_init;

	list_node = list.extract_after(list.cbefore_begin());

	EXPECT_FALSE(list_node.empty());
	EXPECT_EQ(list_node.value(), single_matcher[0]);
}

/* ----------------------------------------Node Type Methods Tests------------------------------------------- */
TEST(singly_list__node_type__methods, empty__empty_node) {
	list_node = nullptr;

	EXPECT_TRUE(list_node.empty());
}

TEST(singly_list__node_type__methods, empty__filled_node) {
	singly_list list = single_init;

	list_node = list.extract_after(list.cbefore_begin());

	EXPECT_FALSE(list_node.empty());
}

TEST(singly_list__node_type__methods, value__empty_node) {
	list_node = nullptr;

	EXPECT_THROW(static_cast<void>(list_node.value()), std::runtime_error);
}

TEST(singly_list__node_type__methods, value__filled__node) {
	singly_list list = single_list;
	list_node = list.extract_after(list.cbefore_begin());

	EXPECT_EQ(list_node.value(), single_matcher[0]);
}

TEST(singly_list__node_type__methods, swap__empty_and_empty) {
	node_type node1;
	node_type node2;

	node1.swap(node2);

	EXPECT_TRUE(node1.empty());
	EXPECT_TRUE(node2.empty());

	EXPECT_EQ(node1, nullptr);
	EXPECT_EQ(node2, nullptr);

	EXPECT_THROW(static_cast<void>(node1.value()), std::runtime_error);
	EXPECT_THROW(static_cast<void>(node2.value()), std::runtime_error);
}

TEST(singly_list__node_type__methods, swap__empty_and_filled) {
	singly_list list = single_init;
	node_type node1 = list.extract_after(list.cbefore_begin());
	node_type node2;

	node1.swap(node2);

	EXPECT_TRUE(node1.empty());
	EXPECT_FALSE(node2.empty());

	EXPECT_EQ(node1, nullptr);
	EXPECT_NE(node2, nullptr);

	EXPECT_THROW(static_cast<void>(node1.value()), std::runtime_error);
	EXPECT_EQ(node2.value(), single_matcher[0]);
}

TEST(singly_list__node_type__methods, swap__filled_and_empty) {
	singly_list list = single_init;
	node_type node1;
	node_type node2 = list.extract_after(list.cbefore_begin());

	node1.swap(node2);

	EXPECT_FALSE(node1.empty());
	EXPECT_TRUE(node2.empty());

	EXPECT_NE(node1, nullptr);
	EXPECT_EQ(node2, nullptr);

	EXPECT_EQ(node1.value(), single_matcher[0]);
	EXPECT_THROW(static_cast<void>(node2.value()), std::runtime_error);
}

TEST(singly_list__node_type__methods, swap__filled_and_filled) {
	singly_list list = filled1_init;
	node_type node1 = list.extract_after(list.cbefore_begin());
	node_type node2 = list.extract_after(list.cbefore_begin());

	node1.swap(node2);

	EXPECT_FALSE(node1.empty());
	EXPECT_FALSE(node2.empty());

	EXPECT_NE(node1, nullptr);
	EXPECT_NE(node2, nullptr);

	EXPECT_EQ(node1.value(), filled1_matcher[1]);
	EXPECT_EQ(node2.value(), filled1_matcher[0]);
}

/* -------------------------------------Singly List Constructors Tests--------------------------------------- */
TEST(singly_list__constructors, default_constructor) {
	singly_list list;
	list_cit = list.cbegin();

	EXPECT_TRUE(list.empty());
	EXPECT_EQ(list.size(), 0);
	EXPECT_EQ(list_cit, list.cend());
	EXPECT_THROW(static_cast<void>(*list_cit), std::runtime_error);
}

TEST(singly_list__constructors, initializer_list_constructor) {
	singly_list list = filled1_init;

	EXPECT_FALSE(list.empty());
	EXPECT_EQ(list.size(), filled1_size);

	list_cit = list.cbegin();
	for (size_type i = 0; i < filled1_size; i++) {
		EXPECT_EQ(*list_cit, filled1_matcher[i]);
		list_cit++;
	}
}

TEST(singly_list__constructors, size_constructor) {
	singly_list list(3);

	EXPECT_FALSE(list.empty());
	EXPECT_EQ(list.size(), 3);

	list_cit = list.cbegin();
	for (size_type i = 0; i < 3; i++) {
		EXPECT_EQ(*list_cit, 0);
		list_cit++;
	}
}

TEST(singly_list__constructors, copy_constructor) {
	singly_list filled1_copy = filled1_list;

	EXPECT_FALSE(filled1_copy.empty());
	EXPECT_EQ(filled1_copy.size(), filled1_size);

	EXPECT_FALSE(filled1_list.empty());
	EXPECT_EQ(filled1_list.size(), filled1_size);

	EXPECT_EQ(filled1_list, filled1_copy);
}

TEST(singly_list__constructors, move_constructor) {
	singly_list src = filled1_init;
	singly_list dst = std::move(src);

	EXPECT_FALSE(dst.empty());
	EXPECT_EQ(dst.size(), filled1_size);

	EXPECT_TRUE(src.empty());
	EXPECT_EQ(src.size(), 0);

	EXPECT_EQ(src, empty_list);
	EXPECT_EQ(dst, filled1_list);
}

TEST(singly_list__constructors, iterator_constructor) {
	singly_list list(filled1_list.begin(), filled1_list.end());

	EXPECT_FALSE(list.empty());
	EXPECT_EQ(list.size(), filled1_size);

	EXPECT_EQ(list, filled1_list);
}

TEST(singly_list__constructors, range_constructor) {
	singly_list list(std::from_range, range_container);

	EXPECT_FALSE(range_container.empty());
	EXPECT_EQ(range_container.size(), range_size);

	EXPECT_FALSE(list.empty());
	EXPECT_EQ(list.size(), range_size);

	EXPECT_EQ(list, range_container);
}

TEST(singly_list__constructors, size_and_value_constructor__zero_size) {
	EXPECT_THROW(static_cast<void>(singly_list(0, list_value)), std::invalid_argument);
}

TEST(singly_list__constructors, size_and_value_constructor__nonzero_size) {
	singly_list* list_p = nullptr;

	EXPECT_NO_THROW(list_p = ::new singly_list(5, list_value));

	EXPECT_FALSE(list_p->empty());
	EXPECT_EQ(list_p->size(), 5);

	for (list_cit = list_p->cbegin(); list_cit != list_p->cend(); list_cit++) {
		EXPECT_EQ(*list_cit, list_value);
	}

	::delete list_p;
}

/* --------------------------------------Singly List Destructor Tests--------------------------------------- */
TEST(singly_list__destructor, destructor) {
	singly_list list = filled1_init;

	list.~singly_list();

	EXPECT_TRUE(list.empty());
	EXPECT_EQ(list.size(), 0);

	EXPECT_EQ(list, empty_list);
}

/* ---------------------------------Singly List Overloaded Operators Tests---------------------------------- */
TEST(singly_list__operators, assignment_operator__self_assignment) {
	singly_list list = filled1_init;
	singly_list& list_r = list;

	list_r = list;

	EXPECT_EQ(&list, &list_r);
	EXPECT_EQ(list, list_r);

	EXPECT_FALSE(list.empty());
	EXPECT_EQ(list.size(), filled1_size);

	EXPECT_FALSE(list_r.empty());
	EXPECT_EQ(list_r.size(), filled1_size);
}

TEST(singly_list__operators, assignment_operator__empty_to_empty) {
	singly_list list;

	list = empty_list;

	EXPECT_TRUE(list.empty());
	EXPECT_EQ(list.size(), 0);

	EXPECT_TRUE(empty_list.empty());
	EXPECT_EQ(empty_list.size(), 0);

	EXPECT_EQ(list, empty_list);
}

TEST(singly_list__operators, assignment_operator__filled_to_empty) {
	singly_list src = filled1_init;
	singly_list dst;

	dst = src;

	EXPECT_FALSE(dst.empty());
	EXPECT_EQ(dst.size(), filled1_size);

	EXPECT_FALSE(src.empty());
	EXPECT_EQ(src.size(), filled1_size);

	EXPECT_EQ(src, dst);
}

TEST(singly_list__operators, assignment_operator__filled_to_filled) {
	singly_list src = filled1_init;
	singly_list dst = filled2_init;

	dst = src;

	EXPECT_FALSE(src.empty());
	EXPECT_EQ(src.size(), filled2_size);

	EXPECT_FALSE(dst.empty());
	EXPECT_EQ(dst.size(), filled2_size);

	EXPECT_EQ(dst, src);
}

TEST(singly_list__operators, move_operator__empty_to_empty) {
	singly_list src, dst;

	dst = std::move(src);

	EXPECT_TRUE(src.empty());
	EXPECT_EQ(src.size(), 0);

	EXPECT_TRUE(dst.empty());
	EXPECT_EQ(dst.size(), 0);

	EXPECT_EQ(src, empty_list);
	EXPECT_EQ(dst, empty_list);
	EXPECT_EQ(src, dst);
}

TEST(singly_list__operators, move_operator__empty_to_filled) {
	singly_list src;
	singly_list dst = filled1_init;

	dst = std::move(src);

	EXPECT_TRUE(src.empty());
	EXPECT_EQ(src.size(), 0);

	EXPECT_TRUE(dst.empty());
	EXPECT_EQ(dst.size(), 0);

	EXPECT_EQ(src, empty_list);
	EXPECT_EQ(dst, empty_list);
	EXPECT_EQ(src, dst);
}

TEST(singly_list__operators, move_operator__filled_to_filled) {
	singly_list src = filled1_init;
	singly_list dst = filled2_init;

	dst = std::move(src);

	EXPECT_TRUE(src.empty());
	EXPECT_EQ(src.size(), 0);

	EXPECT_FALSE(dst.empty());
	EXPECT_EQ(dst.size(), filled1_size);

	EXPECT_EQ(src, empty_list);
	EXPECT_EQ(dst, filled1_list);
	EXPECT_NE(src, dst);
}

TEST(singly_list__operators, equals_operator__singly_list__both_empty) {
	adt::singly_list<int> lhs, rhs;

	EXPECT_TRUE(lhs.empty());
	EXPECT_TRUE(rhs.empty());
	EXPECT_NE(&lhs, &rhs);
	EXPECT_EQ(lhs, rhs);
	EXPECT_EQ(lhs.size(), rhs.size());
}

TEST(singly_list__operators, equals_operator__singly_list__same_values) {
	adt::singly_list<int> lhs = {1, 2, 3, 4},
						  rhs = {1, 2, 3, 4};

	EXPECT_NE(&lhs, &rhs);
	EXPECT_EQ(lhs, rhs);
	EXPECT_EQ(lhs.size(), rhs.size());
}

TEST(singly_list__operators, equals_operator__singly_list__different_values) {
	adt::singly_list<int> lhs = {1, 2, 3, 4},
						  rhs = {5, 6, 7};

	EXPECT_NE(&lhs, &rhs);
	EXPECT_NE(lhs, rhs);
	EXPECT_NE(lhs.size(), rhs.size());
}

TEST(singly_list__operators, equals_operator__ranges__both_empty) {
	adt::singly_list<int> lhs;
	std::initializer_list<int> rhs;

	EXPECT_TRUE(lhs.empty());
	EXPECT_TRUE(rhs.size() == 0);
	EXPECT_NE(static_cast<void*>(&lhs), static_cast<void*>(&rhs));
	EXPECT_EQ(lhs, rhs);
	EXPECT_EQ(lhs.size(), rhs.size());
}

TEST(singly_list__operators, equals_operator__ranges__same_values) {
	adt::singly_list<int> lhs = {1, 2, 3, 4};
	std::initializer_list<int> rhs = {1, 2, 3, 4};

	EXPECT_NE(static_cast<void*>(&lhs),static_cast<void*>(&rhs));
	EXPECT_EQ(lhs, rhs);
	EXPECT_EQ(lhs.size(), rhs.size());
}

TEST(singly_list__operators, equals_operator__ranges__different_values) {
	adt::singly_list<int> lhs = {1, 2, 3, 4};
	std::initializer_list<int> rhs = {5, 6, 7};

	EXPECT_NE(static_cast<void*>(&lhs), static_cast<void*>(&rhs));
	EXPECT_NE(lhs, rhs);
	EXPECT_NE(lhs.size(), rhs.size());
}

/* --------------------------------------Singly List Methods Tests------------------------------------------- */
TEST(singly_list__methods, assign__value__empty_list) {
	adt::singly_list<int> list;
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> matcher = {101, 101, 101, 101, 101, 101, 101, 101, 101, 101};

	// Check size before calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);

	EXPECT_NO_THROW(list.assign(10, 101));

	// Check size after calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign__value__count_equals_list_size) {
	adt::singly_list<int> list(5);
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> matcher = {69, 69, 69, 69, 69};

	// Check size before calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(list.assign(5, 69));

	// Check size after calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign__value__count_greater_than_list_size) {
	adt::singly_list<int> list(5, 69);
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> matcher = {101, 101, 101, 101, 101, 101, 101, 101, 101, 101};

	// Check size before calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(list.assign(10, 101));

	// Check size after calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign__value__count_less_than_list_size) {
	adt::singly_list<int> list(10, 101);
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> matcher = {69, 69, 69, 69, 69, 101, 101, 101, 101, 101};

	// Check size before calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_NO_THROW(list.assign(5, 69));

	// Check size after calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign__iterators__empty_list_filled_container) {
	adt::singly_list<int> list;
	adt::singly_list<int>::size_type sz;
	std::vector<int> vec = {1, 2, 3, 4};
	std::initializer_list<int> matcher = {1, 2, 3, 4};

	// Check size before calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);

	EXPECT_NO_THROW(list.assign(vec.begin(), vec.end()));

	// Check size after calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 4);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign__iterators__filled_list_empty_container) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5};
	adt::singly_list<int>::const_iterator cit;
	adt::singly_list<int>::size_type sz;
	std::vector<int> vec;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5};

	// Check size before calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(list.assign(vec.begin(), vec.end()));
	EXPECT_NO_THROW(cit = list.cbegin());

	// Check size after calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign__iterators__list_size_equals_container_size) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5};
	adt::singly_list<int>::size_type sz;
	std::vector<int> vec = {5, 4, 3, 2, 1};
	std::initializer_list<int> matcher = {5, 4, 3, 2, 1};

	// Check size before calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(list.assign(vec.begin(), vec.end()));

	// Check size after calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign__iterators__list_size_greater_than_container_size) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	adt::singly_list<int>::size_type size;
	std::vector<int> vec = {5, 4, 3, 2, 1};
	std::initializer_list<int> matcher = {5, 4, 3, 2, 1, 6, 7, 8, 9, 10};

	// Check size before calling assign()
	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 10);

	EXPECT_NO_THROW(list.assign(vec.begin(), vec.end()));

	// Check size after calling assign()
	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 10);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign__iterators__list_size_less_than_container_size) {
	adt::singly_list<int> list = {5, 4, 3, 2, 1};
	adt::singly_list<int>::size_type sz;
	std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	// Check size before calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(list.assign(vec.begin(), vec.end()));

	// Check size after calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign__initializer_list__empty_list_empty_init_list) {
	adt::singly_list<int> list;
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> values, matcher;

	EXPECT_NO_THROW(list.assign(values));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign__initializer_list__empty_list_filled_init_list) {
	adt::singly_list<int> list;
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> values = {1, 2, 3, 4, 5},
							   matcher = {1, 2, 3, 4, 5};

	// Check size before call to assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);

	EXPECT_NO_THROW(list.assign(values));

	// Check size after call to assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign__initializer_list__list_size_equals_init_list_size) {
	adt::singly_list<int> list = {6, 7, 8, 9, 10};
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> values = {1, 2, 3, 4, 5},
							   matcher = {1, 2, 3, 4, 5};

	// Check size before call to assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(list.assign(values));

	// Check size after call to assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(list.size(), 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign__initializer_list__list_size_greater_than_init_list_size) {
	adt::singly_list<int> list = {15, 16, 14, 13, 12, 11, 10, 9, 8, 7, 6};
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> values = {1, 2, 3, 4, 5},
							   matcher = {1, 2, 3, 4, 5, 11, 10, 9, 8, 7, 6};

	// Check size before call to assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 11);

	EXPECT_NO_THROW(list.assign(values));

	// Check size after call to assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 11);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign__initializer_list__list_size_less_than_init_list_size) {
	adt::singly_list<int> list = {43, 21, 390, 4, 5000};
	adt::singly_list<int>::size_type size;
	std::initializer_list<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
							   matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

	// Check size before call to assign()
	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 5);

	EXPECT_NO_THROW(list.assign(values));

	// Check size after call to assign()
	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 11);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign_range__empty_list_empty_container) {
	std::vector<int> vec;
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator cit;

	EXPECT_NO_THROW(list.assign_range(vec));
	EXPECT_NO_THROW(cit = list.cbegin());

	EXPECT_EQ(list.size(), 0);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit++, std::runtime_error);
}

TEST(singly_list__methods, assign_range__empty_list_filled_container) {
	adt::singly_list<int> list;
	adt::singly_list<int>::size_type sz;
	std::vector<int> vec = {1, 2, 3, 4, 5};
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5};

	// Check size before call to assign_range()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);

	EXPECT_NO_THROW(list.assign_range(vec));

	// Check size after call to assign_range()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign_range__list_size_equals_container_size) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5};
	adt::singly_list<int>::size_type sz;
	std::vector<int> vec = {5, 4, 3, 2, 1};
	std::initializer_list<int> matcher = {5, 4, 3, 2, 1};

	// Check size before calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(list.assign_range(vec));

	// Check size after calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign_range__list_size_greater_than_container_size) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	adt::singly_list<int>::size_type sz;
	std::vector<int> vec = {5, 4, 3, 2, 1};
	std::initializer_list<int> matcher = {5, 4, 3, 2, 1, 6, 7, 8, 9, 10};

	// Check size before calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_NO_THROW(list.assign_range(vec));

	// Check size after calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign_range__list_size_less_than_container_size) {
	adt::singly_list<int> list = {5, 4, 3, 2, 1};
	adt::singly_list<int>::size_type sz;
	std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	// Check size before calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(list.assign_range(vec));

	// Check size after calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, front__empty) {
	adt::singly_list<int> list;

	EXPECT_THROW(static_cast<void>(list.front()), std::runtime_error);
}

TEST(singly_list__methods, front__filled) {
	adt::singly_list<int> list = {1, 2, 3};
	adt::singly_list<int>::value_type value;

	EXPECT_NO_THROW(value = list.front());
	EXPECT_EQ(value, 1);
}

TEST(singly_list__methods, back__empty) {
	adt::singly_list<int> list;

	EXPECT_THROW(static_cast<void>(list.back()), std::runtime_error);
}

TEST(singly_list__methods, back__filled) {
	adt::singly_list<int> list = {1, 2, 3};
	adt::singly_list<int>::value_type value;

	EXPECT_NO_THROW(value = list.back());
	EXPECT_EQ(value, 3);
}

TEST(singly_list__methods, resize__empty) {
	adt::singly_list<int> list;
	adt::singly_list<int>::value_type value;

	EXPECT_NO_THROW(list.resize(0));
	EXPECT_TRUE(list.empty() == true);
	EXPECT_THROW(value = *list.cbegin(), std::runtime_error);

	EXPECT_NO_THROW(list.resize(1));
	EXPECT_TRUE(list.size() == 1);
	EXPECT_NO_THROW(value = *list.cbegin());
	EXPECT_EQ(value, 0);

	EXPECT_NO_THROW(list.resize(10));
	EXPECT_TRUE(list.size() == 10);
	EXPECT_TRUE(*(list.cbegin() + 9) == 0);
}

TEST(singly_list__methods, resize__filled) {
	adt::singly_list<int> list = {1, 2, 3};
	adt::singly_list<int>::const_iterator cit;
	adt::singly_list<int>::size_type size;
	adt::singly_list<int>::value_type value;

	// Test 0
	EXPECT_NO_THROW(list.resize(4));

	cit = list.cbegin();
	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 4);

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 1);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 2);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 3);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 0);


	// Test 1
	EXPECT_NO_THROW(list.resize(5));

	cit = list.cbegin();
	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 5);

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 1);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 2);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 3);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 0);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 0);

	EXPECT_NO_THROW(cit++);
	EXPECT_THROW(value = *cit, std::runtime_error);


	// Test 2
	EXPECT_NO_THROW(list.resize(4));

	cit = list.cbegin();
	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 4);

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 1);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 2);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 3);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 0);

	EXPECT_NO_THROW(cit++);
	EXPECT_THROW(value = *cit, std::runtime_error);


	// Test 3
	EXPECT_NO_THROW(list.resize(0));

	cit = list.cbegin();
	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 0);
	EXPECT_THROW(cit++, std::runtime_error);
}

TEST(singly_list__methods, remove__empty) {
	adt::singly_list<int> list;
	adt::singly_list<int>::size_type vals_removed;

	EXPECT_NO_THROW(vals_removed = list.remove(101));
	EXPECT_EQ(vals_removed, 0);
}

TEST(singly_list__methods, remove__single) {
	adt::singly_list<int> list = {1};
	adt::singly_list<int>::const_iterator cit;
	adt::singly_list<int>::value_type value;
	adt::singly_list<int>::size_type size, vals_removed;

	EXPECT_NO_THROW(vals_removed = list.remove(1));
	EXPECT_EQ(vals_removed, 1);

	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 0);

	EXPECT_NO_THROW(cit = list.cbegin());
	EXPECT_TRUE(cit == nullptr);
	EXPECT_THROW(value = *cit, std::runtime_error);

	static_cast<void>(value);
}

TEST(singly_list__methods, remove__consecutive__front) {
	adt::singly_list<int> list = {1, 1, 1, 1, 1, 2, 3, 4, 5};
	adt::singly_list<int>::size_type size, vals_removed;
	std::initializer_list<int> matcher = {2, 3, 4, 5};

	EXPECT_NO_THROW(vals_removed = list.remove(1));
	EXPECT_EQ(vals_removed, 5);

	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 4);
	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, remove__consecutive__back) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5, 5, 5, 5, 5, 5};
	adt::singly_list<int>::size_type size, vals_removed;
	std::initializer_list<int> matcher = {1, 2, 3, 4};

	EXPECT_NO_THROW(vals_removed = list.remove(5));
	EXPECT_EQ(vals_removed, 6);

	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 4);
	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, remove__every_other) {
	adt::singly_list<int> list = {1, 1, 1, 1, 1, 2, 3, 3, 3, 3, 3, 4, 5, 5, 5, 5, 5, 6, 7, 7, 7, 7, 7, 8, 9, 9, 9, 9, 9, 10};
	adt::singly_list<int>::size_type size, vals_removed;
	std::initializer_list<int> matcher = {2, 3, 3, 3, 3, 3, 4, 5, 5, 5, 5, 5, 6, 7, 7, 7, 7, 7, 8, 9, 9, 9, 9, 9, 10};

	// Removing all 1's
	EXPECT_NO_THROW(vals_removed = list.remove(1));
	EXPECT_EQ(vals_removed, 5);

	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 25);

	EXPECT_EQ(list, matcher);

	// Removing all 3's
	matcher = {2, 4, 5, 5, 5, 5, 5, 6, 7, 7, 7, 7, 7, 8, 9, 9, 9, 9, 9, 10};
	EXPECT_NO_THROW(vals_removed = list.remove(3));
	EXPECT_EQ(vals_removed, 5);

	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 20);

	EXPECT_EQ(list, matcher);

	// Removing all 5's
	matcher = {2, 4, 6, 7, 7, 7, 7, 7, 8, 9, 9, 9, 9, 9, 10};
	EXPECT_NO_THROW(vals_removed = list.remove(5));
	EXPECT_EQ(vals_removed, 5);

	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 15);

	EXPECT_EQ(list, matcher);

	// Removing all 7's
	matcher = {2, 4, 6, 8, 9, 9, 9, 9, 9, 10};
	EXPECT_NO_THROW(vals_removed = list.remove(7));
	EXPECT_EQ(vals_removed, 5);

	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 10);

	EXPECT_EQ(list, matcher);

	// Removing all 9's
	matcher = {2, 4, 6, 8, 10};
	EXPECT_NO_THROW(vals_removed = list.remove(9));
	EXPECT_EQ(vals_removed, 5);

	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, remove_if__empty) {
	adt::singly_list<int> list;
	adt::singly_list<int>::size_type vals_removed;

	EXPECT_NO_THROW(vals_removed = list.remove_if([](adt::singly_list<int>::value_type value) -> bool {
		return value % 2 == 0;
	}));
	EXPECT_EQ(vals_removed, 0);
}

TEST(singly_list__methods, remove_if__single) {
	adt::singly_list<int> list = {2};
	adt::singly_list<int>::const_iterator cit;
	adt::singly_list<int>::value_type value;
	adt::singly_list<int>::size_type size, vals_removed;

	EXPECT_NO_THROW(vals_removed = list.remove_if([](adt::singly_list<int>::value_type value) -> bool {
		return value % 2 == 0;
	}));

	EXPECT_EQ(vals_removed, 1);

	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 0);

	EXPECT_NO_THROW(cit = list.cbegin());
	EXPECT_TRUE(cit == nullptr);
	EXPECT_THROW(value = *cit, std::runtime_error);

	static_cast<void>(value);
}

TEST(singly_list__methods, remove_if__consecutive__front) {
	adt::singly_list<int> list = {2, 2, 2, 2, 2, 3};
	adt::singly_list<int>::size_type size, vals_removed;
	std::initializer_list<int> matcher = {3};

	EXPECT_NO_THROW(vals_removed = list.remove_if([](adt::singly_list<int>::value_type value) -> bool {
		return value % 2 == 0;
	}));
	EXPECT_EQ(vals_removed, 5);

	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 1);
	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, remove_if__consecutive__back) {
	adt::singly_list<int> list = {5, 6, 6, 6, 6, 6};
	adt::singly_list<int>::size_type size, vals_removed;
	std::initializer_list<int> matcher = {5};

	EXPECT_NO_THROW(vals_removed = list.remove_if([](adt::singly_list<int>::value_type value) -> bool {
		return value % 2 == 0;
	}));
	EXPECT_EQ(vals_removed, 5);

	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 1);
	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, remove_if__every_other) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	adt::singly_list<int>::size_type size, vals_removed;
	std::initializer_list<int> matcher = {1, 3, 5, 7, 9};

	EXPECT_NO_THROW(vals_removed = list.remove_if([](adt::singly_list<int>::value_type value) -> bool {
		return value % 2 == 0;
	}));

	EXPECT_EQ(vals_removed, 5);

	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, clear) {
	adt::singly_list<int> list;

	EXPECT_NO_THROW(list.clear());

	list = {1, 2, 3};
	EXPECT_NO_THROW(list.clear());
	EXPECT_TRUE(list.cbegin() == nullptr);
	EXPECT_TRUE(list.empty() == true);
}

TEST(singly_list__methods, insert_after__lref__segmentation_fault) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbegin();
	adt::singly_list<int>::value_type value = 101;

	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.insert_after(pos, value), std::runtime_error);
}

TEST(singly_list__methods, insert_after__lref__different_instance) {
	adt::singly_list<int> list;
	adt::singly_list<int> other;
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();
	adt::singly_list<int>::value_type lvalue = 101;

	EXPECT_THROW(list.insert_after(pos, lvalue), std::invalid_argument);
}

TEST(singly_list__methods, insert_after__lref__consecutive) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);
	EXPECT_NE(pos, nullptr);

	for (adt::singly_list<int>::value_type i = 1; i <= 5; i++) {
		EXPECT_NO_THROW(it = list.insert_after(pos, i));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, i);
		EXPECT_NO_THROW(pos++);
	}

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, insert_after__lref__every_other) {
	adt::singly_list<int> list = {2, 4, 6, 8, 10};
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	for (adt::singly_list<int>::value_type i = 1; i < 10; i += 2) {
		EXPECT_NO_THROW(it = list.insert_after(pos, i));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, i);
		EXPECT_NO_THROW(pos += 2);
	}

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);
	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, insert_after__rref__segmentation_fault) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbegin();
	adt::singly_list<int>::value_type value = 101;
	adt::singly_list<int>::reference& value_ref = value;

	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.insert_after(pos, value_ref), std::runtime_error);
}

TEST(singly_list__methods, insert_after__rref__different_instance) {
	adt::singly_list<int> list;
	adt::singly_list<int> other;
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();
	adt::singly_list<int>::value_type value = 101;
	adt::singly_list<int>::reference& value_ref = value;

	EXPECT_THROW(list.insert_after(pos, value_ref), std::invalid_argument);
}

TEST(singly_list__methods, insert_after__rref__consecutive) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);
	EXPECT_NE(pos, nullptr);

	for (adt::singly_list<int>::value_type i = 1; i <= 5; i++) {
		adt::singly_list<int>::reference& i_ref = i;
		EXPECT_NO_THROW(it = list.insert_after(pos, i_ref));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, i);
		EXPECT_NO_THROW(pos++);
	}

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, insert_after__rref__every_other) {
	adt::singly_list<int> list = {2, 4, 6, 8, 10};
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	for (adt::singly_list<int>::value_type i = 1; i < 10; i += 2) {
		adt::singly_list<int>::reference& i_ref = i;
		EXPECT_NO_THROW(it = list.insert_after(pos, i_ref));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, i);
		EXPECT_NO_THROW(pos += 2);
	}

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, matcher.size());

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, insert_after__lref_and_count__segmentation_fault) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbegin();
	adt::singly_list<int>::value_type value = 101;

	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.insert_after(pos, 3, value), std::runtime_error);
}

TEST(singly_list__methods, insert_after__lref_and_count__different_instance) {
	adt::singly_list<int> list;
	adt::singly_list<int> other;
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();
	adt::singly_list<int>::value_type value = 101;

	EXPECT_THROW(list.insert_after(pos, 3, value), std::invalid_argument);
}

TEST(singly_list__methods, insert_after__lref_and_count__consecutive) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);
	EXPECT_NE(pos, nullptr);

	for (adt::singly_list<int>::value_type i = 1; i <= 5; i++) {
		EXPECT_NO_THROW(it = list.insert_after(pos, 3, i));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, i);
		EXPECT_NO_THROW(pos += 3);
	}

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 15);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, insert_after__lref_and_count__every_other) {
	adt::singly_list<int> list = {2, 4, 6, 8, 10};
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher = {1, 1, 1, 2, 3, 3, 3, 4, 5, 5, 5, 6, 7, 7, 7, 8, 9, 9, 9, 10};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	for (adt::singly_list<int>::value_type i = 1; i < 10; i += 2) {
		EXPECT_NO_THROW(it = list.insert_after(pos, 3, i));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, i);
		EXPECT_NO_THROW(pos += 4);
	}

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, matcher.size());

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, insert_after__iterators__segmentation_fault) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbegin();
	std::vector<int> vec = {1, 2, 3};

	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.insert_after(pos, vec.cbegin(), vec.cend()), std::runtime_error);
}

TEST(singly_list__methods, insert_after__iterators__different_instance) {
	adt::singly_list<int> list;
	adt::singly_list<int> other;
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();
	std::vector<int> vec = {1, 2, 3};

	EXPECT_THROW(list.insert_after(pos, vec.cbegin(), vec.cend()), std::invalid_argument);
}

TEST(singly_list__methods, insert_after__iterators__consecutive) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);
	EXPECT_NE(pos, nullptr);

	for (adt::singly_list<int>::value_type i = 1; i <= 5; i++) {
		EXPECT_NO_THROW(it = list.insert_after(pos, 3, i));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, i);
		EXPECT_NO_THROW(pos += 3);
	}

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 15);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, insert_after__iterators__every_other) {
	adt::singly_list<int> list = {2, 4, 6, 8, 10};
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher = {1, 1, 1, 2, 3, 3, 3, 4, 5, 5, 5, 6, 7, 7, 7, 8, 9, 9, 9, 10};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	for (adt::singly_list<int>::value_type i = 1; i < 10; i += 2) {
		EXPECT_NO_THROW(it = list.insert_after(pos, 3, i));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, i);
		EXPECT_NO_THROW(pos += 4);
	}

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, matcher.size());

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, insert_after__initializer_list__segmentation_fault) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbegin();
	std::initializer_list<int> values = {1, 2, 3, 4, 5};

	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.insert_after(pos, values), std::runtime_error);
}

TEST(singly_list__methods, insert_after__initializer_list__different_instance) {
	adt::singly_list<int> list;
	adt::singly_list<int> other;
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();
	std::initializer_list<int> values = {1, 2, 3, 4, 5};

	EXPECT_THROW(list.insert_after(pos, values), std::invalid_argument);
}

TEST(singly_list__methods, insert_after__initializer_list__front) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> values = {1, 2, 3, 4, 5},
							   matcher = {1, 2, 3, 4, 5};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);
	EXPECT_NE(pos, nullptr);

	EXPECT_NO_THROW(it = list.insert_after(pos, values));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(*it, 5);
	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, insert_after__initializer_list__in_between) {
	adt::singly_list<int> list = {1, 10};
	adt::singly_list<int>::const_iterator pos = list.cbegin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	std::vector<int> values = {2, 3, 4, 5, 6, 7, 8, 9};
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 2);

	EXPECT_NO_THROW(it = list.insert_range_after(pos, values));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_EQ(list, matcher);
	EXPECT_EQ(*it, 9);
}

TEST(singly_list__methods, insert_range_after__segmentation_fault) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbegin();
	std::vector<int> vec = {1, 2, 3, 4};

	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.insert_range_after(pos, vec), std::runtime_error);
}

TEST(singly_list__methods, insert_range_after__different_instance) {
	adt::singly_list<int> list;
	adt::singly_list<int> other;
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();
	std::vector<int> vec = {1, 2, 3, 4};

	EXPECT_THROW(list.insert_range_after(pos, vec), std::invalid_argument);
}

TEST(singly_list__methods, insert_range_after__front) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	std::vector<int> vec = {1, 2, 3, 4, 5};
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);
	EXPECT_NE(pos, nullptr);

	EXPECT_NO_THROW(it = list.insert_range_after(pos, vec));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(*it, 5);
	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, emplace_after__segmentation_fault) {
	adt::singly_list<int> list, other = {1, 2, 3};
	adt::singly_list<int>::const_iterator pos = list.cbegin();

	EXPECT_THROW(list.emplace_after(pos, std::forward<int>(101)), std::runtime_error);
}

TEST(singly_list__methods, emplace_after__different_instance) {
	adt::singly_list<int> list;
	adt::singly_list<int> other;
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();
	std::vector<int> vec = {1, 2, 3, 4};

	EXPECT_THROW(list.insert_range_after(pos, vec), std::invalid_argument);
}

TEST(singly_list__methods, emplace_after__consecutive) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);
	EXPECT_NE(pos, nullptr);

	for (adt::singly_list<int>::value_type i = 1; i <= 5; i++) {
		EXPECT_NO_THROW(it = list.emplace_after(pos, std::forward<int>(i)));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, i);
		EXPECT_NO_THROW(pos++);
	}

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, emplace_after__every_other) {
	adt::singly_list<int> list = {2, 4, 6, 8, 10};
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	for (adt::singly_list<int>::value_type i = 1; i < 10; i += 2) {
		EXPECT_NO_THROW(it = list.emplace_after(pos, std::forward<int>(i)));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, i);
		EXPECT_NO_THROW(pos += 2);
	}

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, erase_after__single_iterator__segmentation_fault) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbegin();

	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.erase_after(pos), std::runtime_error);

	list = {1};
	pos = list.cbegin();

	EXPECT_NE(pos, nullptr);
	EXPECT_EQ(pos + 1, nullptr);
	EXPECT_THROW(list.erase_after(pos), std::runtime_error);
}

TEST(singly_list__methods, erase_after__single_iterator__different_instance) {
	adt::singly_list<int> list;
	adt::singly_list<int> other = {101};
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();

	EXPECT_THROW(list.erase_after(pos), std::invalid_argument);
}

TEST(singly_list__methods, erase_after__single_iterator__consecutive) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5};
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher;

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);
	EXPECT_NE(pos, nullptr);

	for (adt::singly_list<int>::value_type i = 0; i < 4; i++) {
		EXPECT_NO_THROW(it = list.erase_after(pos));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, i + 2);
	}

	EXPECT_NO_THROW(it = list.erase_after(pos));
	EXPECT_EQ(it, nullptr);

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, erase_after__single_iterator__every_other) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher = {2, 4, 6, 8, 10};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	adt::singly_list<int>::value_type j = 2;
	for (adt::singly_list<int>::value_type i = 0; i < 5; i++) {
		EXPECT_NO_THROW(it = list.erase_after(pos));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, j);
		EXPECT_NO_THROW(pos++);
		j += 2;
	}

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);
	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, erase_after__iterator_range__segmentation_fault) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator first = list.cbegin(),
										  last = list.cend();

	EXPECT_EQ(first, nullptr);
	EXPECT_THROW(list.erase_after(first, last), std::runtime_error);
}

TEST(singly_list__methods, erase_after__iterator_range__different_instance) {
	adt::singly_list<int> list;
	adt::singly_list<int> other = {101};

	adt::singly_list<int>::const_iterator first = other.cbefore_begin();
	adt::singly_list<int>::const_iterator last = other.cend();

	EXPECT_THROW(list.erase_after(first, last), std::invalid_argument);
}

TEST(singly_list__methods, erase_after__iterator_range__consecutive) {
	adt::singly_list<int> list = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5};
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 15);

	for (adt::singly_list<int>::value_type i = 0; i < 5; i++) {
		EXPECT_NO_THROW(it = list.erase_after(pos, pos + 3));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, i + 1);
		EXPECT_NO_THROW(pos++);
	}

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, erase_after__iterator_range__every_other) {
	adt::singly_list<int> list = {1, 1, 1, 2, 3, 3, 3, 4, 5, 5, 5, 6, 7, 7, 7, 8, 9, 9, 9, 10};
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher = {2, 4, 6, 8, 10};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 20);

	adt::singly_list<int>::value_type j = 2;
	for (adt::singly_list<int>::value_type i = 0; i < 5; i++) {
		EXPECT_NO_THROW(it = list.erase_after(pos, pos + 4));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, j);
		EXPECT_NO_THROW(pos++);
		j += 2;
	}

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, splice_after__lref__segmentation_fault) {
	adt::singly_list<int> list, other;
	adt::singly_list<int>::const_iterator pos = list.cbegin();

	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.splice_after(pos, other), std::runtime_error);
}

TEST(singly_list__methods, splice_after__lref__different_instance) {
	adt::singly_list<int> list, other;
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();

	EXPECT_THROW(list.splice_after(pos, other), std::invalid_argument);
}

TEST(singly_list__methods, splice_after__lref__same_instance) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.before_begin();

	EXPECT_NE(pos, nullptr);
	EXPECT_THROW(list.splice_after(pos, list), std::invalid_argument);
}

TEST(singly_list__methods, splice_after__lref__empty_other) {
	adt::singly_list<int> list = {1, 2, 3}, other;
	adt::singly_list<int>::const_iterator pos = list.cbegin();
	adt::singly_list<int>::size_type sz;

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 3);

	EXPECT_NE(pos, nullptr);
	EXPECT_NO_THROW(list.splice_after(pos, other));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 3);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 0);
}

TEST(singly_list__methods, splice_after__lref__filled_other) {
	adt::singly_list<int> list = {1, 2, 3},
						  other = {4, 5, 6};
	adt::singly_list<int>::const_iterator pos = list.cbegin() + 2;
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6};

	EXPECT_NE(pos, nullptr);

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 3);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 3);

	EXPECT_NO_THROW(list.splice_after(pos, other));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 6);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 0);

	EXPECT_EQ(list, matcher);
	EXPECT_EQ(other.cbegin(), nullptr);
}

TEST(singly_list__methods, splice_after__rref__segmentation_fault) {
	adt::singly_list<int> list, other;
	adt::singly_list<int>::const_iterator pos = list.cbegin();

	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.splice_after(pos, std::forward<adt::singly_list<int>>(other)), std::runtime_error);
}

TEST(singly_list__methods, splice_after__rref__different_instance) {
	adt::singly_list<int> list, other;
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();

	EXPECT_THROW(list.splice_after(pos, std::forward<adt::singly_list<int>>(other)), std::invalid_argument);
}

TEST(singly_list__methods, splice_after__rref__same_instance) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.before_begin();

	EXPECT_NE(pos, nullptr);
	EXPECT_THROW(list.splice_after(pos, std::forward<adt::singly_list<int>>(list)), std::invalid_argument);
}

TEST(singly_list__methods, splice_after__rref__empty_other) {
	adt::singly_list<int> list = {1, 2, 3},
						  other;
	adt::singly_list<int>::const_iterator pos = list.cbegin();
	adt::singly_list<int>::size_type sz;

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 3);

	EXPECT_NE(pos, nullptr);
	EXPECT_NO_THROW(list.splice_after(pos, std::forward<adt::singly_list<int>>(other)));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 3);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 0);
}

TEST(singly_list__methods, splice_after__rref__filled_other) {
	adt::singly_list<int> list = {1, 2, 3},
						  other = {4, 5, 6};
	adt::singly_list<int>::const_iterator pos = list.cbegin() + 2;
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6};

	EXPECT_NE(pos, nullptr);

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 3);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 3);

	EXPECT_NO_THROW(list.splice_after(pos, std::forward<adt::singly_list<int>>(other)));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 6);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 0);

	EXPECT_EQ(list, matcher);
	EXPECT_EQ(other.cbegin(), nullptr);
}

TEST(singly_list__methods, splice_after__lref_and_iterator__segmentation_fault) {
	adt::singly_list<int> list, other;
	adt::singly_list<int>::const_iterator pos = list.cbegin();
	adt::singly_list<int>::iterator it;

	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.splice_after(pos, other, it), std::runtime_error);
}

TEST(singly_list__methods, splice_after__lref_and_iterator__different_instance) {
	adt::singly_list<int> list;
	adt::singly_list<int> other = {1, 2, 3, 4, 5};
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();
	adt::singly_list<int>::iterator it = other.begin();

	EXPECT_THROW(list.splice_after(pos, other, it), std::invalid_argument);
}

TEST(singly_list__methods, splice_after__lref_and_iterator__consecutive) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5},
						  other = {6, 7, 8, 9, 10};
	adt::singly_list<int>::const_iterator pos = list.cbegin() + 4;
	adt::singly_list<int>::iterator it = other.before_begin();
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> list_matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
							   other_matcher = {};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 5);

	for (std::size_t i = 0; i < 5; i++) {
		EXPECT_NO_THROW(list.splice_after(pos, other, it));
		pos++;
	}

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 0);

	EXPECT_EQ(list, list_matcher);
	EXPECT_EQ(other, other_matcher);
}

TEST(singly_list__methods, splice_after__lref_and_iterator__every_other) {
	adt::singly_list<int> list = {2, 4, 6, 8, 10},
						  other = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it = other.before_begin();
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> list_matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
							   other_matcher = {2, 4, 6, 8, 10};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 10);

	for (std::size_t i = 0; i < 5; i++) {
		EXPECT_NO_THROW(list.splice_after(pos, other, it));
		pos += 2;
		it++;
	}

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, list_matcher);
	EXPECT_EQ(other, other_matcher);
}

TEST(singly_list__methods, splice_after__rref_and_iterator__segmentation_fault) {
	adt::singly_list<int> list, other;
	adt::singly_list<int>::const_iterator pos = list.cbegin();
	adt::singly_list<int>::iterator it;

	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.splice_after(pos, std::forward<adt::singly_list<int>>(other), it), std::runtime_error);
}

TEST(singly_list__methods, splice_after__rref_and_iterator__different_instance) {
	adt::singly_list<int> list, other = {1, 2, 3};
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();
	adt::singly_list<int>::iterator it = other.begin();

	EXPECT_THROW(list.splice_after(pos, std::forward<adt::singly_list<int>>(other), it), std::invalid_argument);
}

TEST(singly_list__methods, splice_after__rref_and_iterator__consecutive) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5},
						  other = {6, 7, 8, 9, 10};
	adt::singly_list<int>::const_iterator pos = list.cbegin() + 4;
	adt::singly_list<int>::iterator it = other.before_begin();
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> list_matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
							   other_matcher = {};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 5);

	for (std::size_t i = 0; i < 5; i++) {
		EXPECT_NO_THROW(list.splice_after(pos, std::forward<adt::singly_list<int>>(other), it));
		pos++;
	}

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 0);

	EXPECT_EQ(list, list_matcher);
	EXPECT_EQ(other, other_matcher);
}

TEST(singly_list__methods, splice_after__rref_and_iterator__every_other) {
	adt::singly_list<int> list = {2, 4, 6, 8, 10},
						  other = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it = other.before_begin();
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> list_matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
							   other_matcher = {2, 4, 6, 8, 10};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 10);

	for (std::size_t i = 0; i < 5; i++) {
		EXPECT_NO_THROW(list.splice_after(pos, std::forward<adt::singly_list<int>>(other), it));
		pos += 2;
		it++;
	}

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, list_matcher);
	EXPECT_EQ(other, other_matcher);
}

TEST(singly_list__methods, splice_after__lref_and_iterator_range__segmentation_fault) {
	adt::singly_list<int> list, other = {1, 2, 3};
	adt::singly_list<int>::const_iterator pos = list.cbegin(),
										  first = other.cbegin(),
										  last = other.cend();
	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.splice_after(pos, other, first, last), std::runtime_error);
}

TEST(singly_list__methods, splice_after__lref_and_iterator_range__different_instance) {
	adt::singly_list<int> list, other = {1, 2, 3};
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();
	adt::singly_list<int>::const_iterator first = other.cbegin();
	adt::singly_list<int>::const_iterator last = other.cend();

	EXPECT_THROW(list.splice_after(pos, other, first, last), std::invalid_argument);
}

TEST(singly_list__methods, splice_after__lref_and_iterator_range__consecutive) {
	adt::singly_list<int> list, other = {1, 2, 3, 4, 5};
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin(),
										  first = other.cbefore_begin(),
										  last = other.cend();
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> list_matcher = {1, 2, 3, 4, 5},
							   other_matcher = {};

	EXPECT_NO_THROW(list.splice_after(pos, other, first, last));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 0);

	EXPECT_EQ(list, list_matcher);
	EXPECT_EQ(other, other_matcher);
}

TEST(singly_list__methods, splice_after__lref_and_iterator_range__every_other) {
	adt::singly_list<int> list = {1, 2, 3, 7, 8, 9, 13, 14, 15},
						  other = {4, 5, 6, 10, 11, 12};
	adt::singly_list<int>::const_iterator pos = list.cbegin() + 2,
										  first = other.cbefore_begin(),
										  last = first + 4;
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> list_matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 13, 14, 15},
							   other_matcher = {10, 11, 12};

	EXPECT_NO_THROW(list.splice_after(pos, other, first, last));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 12);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 3);

	EXPECT_EQ(list, list_matcher);
	EXPECT_EQ(other, other_matcher);

	list_matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	other_matcher = {};
	pos += 6;
	first = other.cbefore_begin();
	last = first + 4;

	EXPECT_NO_THROW(list.splice_after(pos, other, first, last));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 15);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 0);

	EXPECT_EQ(list, list_matcher);
	EXPECT_EQ(other, other_matcher);

}

TEST(singly_list__methods, splice_after__rref_and_iterator_range__segmentation_fault) {
	adt::singly_list<int> list, other = {1, 2, 3};
	adt::singly_list<int>::const_iterator pos = list.cbegin(),
										  first = other.cbegin(),
										  last = other.cend();
	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.splice_after(pos, other, first, last), std::runtime_error);
}

TEST(singly_list__methods, splice_after__rref_and_iterator_range__different_instance) {
	adt::singly_list<int> list, other = {1, 2, 3};
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin(),
										  first = other.cbegin(),
										  last = other.cend();

	EXPECT_THROW(list.splice_after(pos, other, first, last), std::invalid_argument);
}

TEST(singly_list__methods, splice_after__rref_and_iterator_range__consecutive) {
	adt::singly_list<int> list, other = {1, 2, 3, 4, 5};
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin(),
										  first = other.cbefore_begin(),
										  last = other.cend();
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> list_matcher = {1, 2, 3, 4, 5},
							   other_matcher = {};

	EXPECT_NO_THROW(list.splice_after(pos, std::forward<adt::singly_list<int>>(other), first, last));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 0);

	EXPECT_EQ(list, list_matcher);
	EXPECT_EQ(other, other_matcher);
}

TEST(singly_list__methods, splice_after__rref_and_iterator_range__every_other) {
	adt::singly_list<int> list = {1, 2, 3, 7, 8, 9, 13, 14, 15},
						  other = {4, 5, 6, 10, 11, 12};
	adt::singly_list<int>::const_iterator pos = list.cbegin() + 2,
										  first = other.cbefore_begin(),
										  last = first + 4;
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> list_matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 13, 14, 15},
							   other_matcher = {10, 11, 12};

	EXPECT_NO_THROW(list.splice_after(pos, std::forward<adt::singly_list<int>>(other), first, last));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 12);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 3);

	EXPECT_EQ(list, list_matcher);
	EXPECT_EQ(other, other_matcher);

	list_matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	other_matcher = {};
	pos += 6;
	first = other.cbefore_begin();
	last = first + 4;

	EXPECT_NO_THROW(list.splice_after(pos, std::forward<adt::singly_list<int>>(other), first, last));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 15);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 0);

	EXPECT_EQ(list, list_matcher);
	EXPECT_EQ(other, other_matcher);

}

TEST(singly_list__methods, push_back__empty) {
	adt::singly_list<int> list;
	adt::singly_list<int>::value_type value;

	list.push_back(1);
	EXPECT_NO_THROW(value = *list.begin());

	EXPECT_TRUE(list.size() == 1);
	EXPECT_EQ(value, 1);
}

TEST(singly_list__methods, push_back__filled) {
	adt::singly_list<int> list = {1, 2, 3};
	adt::singly_list<int>::value_type value;

	list.push_back(4);
	EXPECT_NO_THROW(value = *(list.begin() + 3));

	EXPECT_TRUE(list.size() == 4);
	EXPECT_EQ(value, 4);
}

TEST(singly_list__methods, push_front__empty) {
	adt::singly_list<int> list;
	adt::singly_list<int>::value_type value;

	list.push_front(0);
	EXPECT_NO_THROW(value = *list.begin());

	EXPECT_TRUE(list.size() == 1);
	EXPECT_EQ(value, 0);
}

TEST(singly_list__methods, push_front__filled) {
	adt::singly_list<int> list = {1, 2, 3};
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::value_type value;

	list.push_front(-1);
	it = list.begin();

	EXPECT_TRUE(list.size() == 4);

	EXPECT_NO_THROW(value = *it);

	EXPECT_EQ(value, -1);

	EXPECT_NO_THROW(it++);
	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 1);
}

TEST(singly_list__methods, pop_back__empty) {
	adt::singly_list<int> list;

	EXPECT_THROW(list.pop_back(), std::runtime_error);
}

TEST(singly_list__methods, pop_back__filled__single) {
	adt::singly_list<int> list(1, -1);
	adt::singly_list<int>::iterator it;

	EXPECT_NO_THROW(list.pop_back());

	it = list.begin();
	EXPECT_TRUE(list.size() == 0);

	EXPECT_TRUE(it == nullptr);
}

TEST(singly_list__methods, pop_back__filled__multiple) {
	adt::singly_list<int> list = {1, 2, 3};
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::value_type value;

	EXPECT_NO_THROW(list.pop_back());

	it = list.begin();

	EXPECT_TRUE(list.size() == 2);

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(1, value);
	EXPECT_NO_THROW(it++);

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(2, value);
	EXPECT_NO_THROW(it++);

	EXPECT_TRUE(it == nullptr);
}

TEST(singly_list__methods, pop_front__empty) {
	adt::singly_list<int> list;

	EXPECT_THROW(list.pop_front(), std::runtime_error);
}

TEST(singly_list__methods, pop_front__filled) {
	adt::singly_list<int> list = {1, 2, 3};
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::value_type value;

	EXPECT_NO_THROW(list.pop_front());

	it = list.begin();

	EXPECT_TRUE(list.size() == 2);

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(2, value);
	EXPECT_NO_THROW(it++);

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(3, value);
	EXPECT_NO_THROW(it++);

	EXPECT_TRUE(it == nullptr);
}

TEST(singly_list__methods, emplace_back__empty) {
	adt::singly_list<int> list;
	adt::singly_list<int>::value_type value;

	EXPECT_NO_THROW(value = list.emplace_back(0));

	EXPECT_TRUE(list.size() == 1);
	EXPECT_EQ(value, 0);
}

TEST(singly_list__methods, emplace_back__filled) {
	adt::singly_list<int> list = {1, 2, 3};
	adt::singly_list<int>::value_type value;

	value = list.emplace_back(4);

	EXPECT_TRUE(list.size() == 4);

	EXPECT_EQ(value, 4);


	value = list.emplace_back(5);

	EXPECT_TRUE(list.size() == 5);

	EXPECT_EQ(value, 5);
}

TEST(singly_list__methods, emplace_front__empty) {
	adt::singly_list<int> list;
	adt::singly_list<int>::value_type value;

	EXPECT_NO_THROW(value = list.emplace_front(0));

	EXPECT_TRUE(list.size() == 1);
	EXPECT_EQ(value, 0);
}

TEST(singly_list__methods, emplace_front__filled) {
	adt::singly_list<int> list = {1, 2, 3};
	adt::singly_list<int>::value_type value;

	EXPECT_NO_THROW(value = list.emplace_front(0));

	EXPECT_TRUE(list.size() == 4);
	EXPECT_EQ(value, 0);

	EXPECT_NO_THROW(value = list.emplace_front(-1));
	EXPECT_TRUE(list.size() == 5);
	EXPECT_EQ(value, -1);
}

TEST(singly_list__methods, prepend_range__empty) {
	adt::singly_list<int> list;
	adt::singly_list<int>::size_type sz;
	std::vector<int> values = {1, 2, 3, 4, 5};
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);

	EXPECT_NO_THROW(list.prepend_range(values));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, prepend_range__filled) {
	adt::singly_list<int> list = {6, 7, 8, 9, 10};
	adt::singly_list<int>::size_type sz;
	std::vector<int> values = {1, 2, 3, 4, 5};
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(list.prepend_range(values));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, append_range__empty) {
	adt::singly_list<int> list;
	adt::singly_list<int>::size_type sz;
	std::vector<int> values = {1, 2, 3, 4, 5};
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);

	EXPECT_NO_THROW(list.append_range(values));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, append_range__filled) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5};
	adt::singly_list<int>::size_type sz;
	std::vector<int> values = {6, 7, 8, 9, 10};
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(list.append_range(values));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, swap) {
	adt::singly_list<int> list1 = {1, 2, 3},
						  list2 = {4, 5, 6};
	adt::singly_list<int>::value_type value;

	list1.swap(list2);

	EXPECT_NO_THROW(value = list1.front());
	EXPECT_EQ(value, 4);

	EXPECT_NO_THROW(value = list2.front());
	EXPECT_EQ(value, 1);
}

TEST(singly_list__methods, reverse__empty) {
	adt::singly_list<int> list;
	list.reverse();

	EXPECT_TRUE(list.cbegin() == nullptr);
}

TEST(singly_list__methods, reverse__filled__single) {
	adt::singly_list<int> list(1, 1);
	adt::singly_list<int>::const_iterator cit = list.cbegin();

	list.reverse();

	EXPECT_TRUE(*cit == 1);
	EXPECT_THROW(static_cast<void>(*(cit + 1)), std::runtime_error);
}

TEST(singly_list__methods, reverse__filled__multiple) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5, 6};
	adt::singly_list<int>::const_iterator cit;
	adt::singly_list<int>::value_type value;

	list.reverse();

	EXPECT_NO_THROW(cit = list.cbegin());

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 6);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 5);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 4);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 3);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 2);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 1);
}

TEST(singly_list__methods, unique__empty) {
	adt::singly_list<int> list;
	adt::singly_list<int>::value_type value = list.unique();

	EXPECT_EQ(value, 0);
}

TEST(singly_list__methods, unique__filled__single) {
	adt::singly_list<int> list(1, 1);
	adt::singly_list<int>::value_type value = list.unique();

	EXPECT_EQ(value, 0);
}

TEST(singly_list__methods, unique__filled__all_unique) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5, 6};
	adt::singly_list<int>::value_type value = list.unique();

	EXPECT_EQ(value, 0);
}

TEST(singly_list__methods, unique__filled__all_dups) {
	adt::singly_list<int> list = {1, 1, 1, 1, 1, 1};
	adt::singly_list<int>::value_type value = list.unique();

	EXPECT_EQ(value, 5);
	EXPECT_NO_THROW(value = *list.cbegin());
	EXPECT_EQ(value, 1);
	EXPECT_TRUE(list.size() == 1);
}

TEST(singly_list__methods, unique__filled__mixed) {
	adt::singly_list<int> list = {1, 2, 2, 3, 4, 5, 5, 5, 6};
	adt::singly_list<int>::const_iterator cit;
	adt::singly_list<int>::value_type value;

	EXPECT_EQ(list.unique(), 3);

	cit = list.cbegin();

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 1);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 2);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 3);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 4);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 5);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);

	EXPECT_NO_THROW(cit++);
	EXPECT_THROW(value = *cit, std::runtime_error);

	EXPECT_EQ(list.size(), 6);
}

TEST(singly_list__methods, sort__accending_order) {
	adt::singly_list<int> list = {1, 3, 6, 2, 5, 4};
	adt::singly_list<int>::const_iterator cit;
	adt::singly_list<int>::value_type value;

	// void sort()
	list.sort();
	cit = list.cbegin();

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 1);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 2);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 3);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 4);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 5);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 6);
}

TEST(singly_list__methods, sort__decending_order) {
	adt::singly_list<int> list = {1, 3, 6, 2, 5, 4};
	adt::singly_list<int>::const_iterator cit;
	adt::singly_list<int>::value_type value;

	// template<class Compare>
	// void sort(Compare comp)
	list.sort(std::greater<int>{});
	cit = list.cbegin();

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 6);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 5);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 4);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 3);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 2);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 1);
}

TEST(singly_list__methods, is_sorted__no_argument__empty_list) {
	adt::singly_list<int> list;
	EXPECT_FALSE(list.is_sorted());
}

TEST(singly_list__methods, is_sorted__no_argument__unsorted_list) {
	adt::singly_list<int> list = {1, 5, 3, 7, 9, 100, 69, 101, 2};
	EXPECT_FALSE(list.is_sorted());
}

TEST(singly_list__methods, is_sorted__no_argument__sorted_list) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	EXPECT_TRUE(list.is_sorted());
}

TEST(singly_list__methods, is_sorted__argument__empty_list) {
	adt::singly_list<int> list;
	EXPECT_FALSE(list.is_sorted(std::greater<adt::singly_list<int>::value_type>{}));
}

TEST(singly_list__methods, is_sorted__argument__unsorted_list) {
	adt::singly_list<int> list = {1, 5, 3, 7, 9, 100, 69, 101, 2};
	EXPECT_FALSE(list.is_sorted(std::greater<adt::singly_list<int>::value_type>{}));
}

TEST(singly_list__methods, is_sorted__argument__sorted_list) {
	adt::singly_list<int> list = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	EXPECT_TRUE(list.is_sorted(std::greater<adt::singly_list<int>::value_type>{}));
}

TEST(singly_list__methods, extract_after__const_iterator__segmentation_fault) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbegin();

	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.extract_after(pos), std::runtime_error);
}

TEST(singly_list__methods, extract_after__const_iterator__empty_list) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::node_type node_handle;

	EXPECT_NE(pos, nullptr);
	EXPECT_NO_THROW(node_handle = list.extract_after(pos));

	EXPECT_TRUE(node_handle.empty());
	EXPECT_EQ(node_handle, nullptr);

	EXPECT_THROW(node_handle.value(), std::runtime_error);
}

TEST(singly_list__methods, extract_after__const_iterator__filled_list) {
	adt::singly_list<int> list = {1, 2, 3};
	adt::singly_list<int>::const_iterator pos = list.cbegin();
	adt::singly_list<int>::node_type node_handle;
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> matcher = {1, 3};

	EXPECT_NE(pos, nullptr);
	EXPECT_NO_THROW(node_handle = list.extract_after(pos));

	EXPECT_FALSE(node_handle.empty());
	EXPECT_NE(node_handle, nullptr);

	EXPECT_EQ(node_handle.value(), 2);

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 2);
	EXPECT_EQ(list, matcher);
}
