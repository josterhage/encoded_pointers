#ifndef AVL_TREE_NODE_POINTER_HPP
#define AVL_TREE_NODE_POINTER_HPP

#include <concepts>
#include <type_traits>

typedef __UINTPTR_TYPE__	uintptr_t;
typedef signed char			balance_factor_t;

static inline uintptr_t pointer_to_int(void* p)
{
	return (uintptr_t)(p);
}

template <typename T>
concept Comparable = requires (T a, T b)
{
	{ a == b } -> std::convertible_to<bool>;
	{ a != b } -> std::convertible_to<bool>;
	{ a < b } -> std::convertible_to<bool>;
	{ a > b } -> std::convertible_to<bool>;
	{ a <= b } -> std::convertible_to<bool>;
	{ a >= b } -> std::convertible_to<bool>;
};

template <typename T>
concept DataType = std::is_trivially_copyable_v<T> || std::is_move_assignable_v<T> || std::is_move_constructible_v<T>;

template <Comparable Key, DataType Value>
class AVL_TreeNode;

template <Comparable Key, DataType Value>
class AVL_TreeNodePointer {
public:
	constexpr AVL_TreeNodePointer() noexcept : m_pointer(0) { }

	AVL_TreeNodePointer(AVL_TreeNode<Key, Value>* node_p, balance_factor_t balance_factor = 0)
		: m_pointer(pointer_to_int(node_p) | balance_factor)
	{ }

private:
	uintptr_t m_pointer;
};

#endif /* AVL_TREE_NODE_POINTER_HPP */