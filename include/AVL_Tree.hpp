#ifndef AVL_TREE_NODE_POINTER_HPP
#define AVL_TREE_NODE_POINTER_HPP

#include <concepts>
#include <type_traits>

typedef __UINTPTR_TYPE__	uintptr_t;
typedef signed int			balance_factor_t;

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

// Forward declaration
template <Comparable Key, DataType Value>
class AVL_TreeNode;

/**
 * @brief Bit-mask for extracting the balance factor from an encoded
 * @c AVL_TreeNodePointer .
 */
static constexpr uintptr_t bf_mask = 7;
/**
 * @brief Bit-mask for removing the balance factor or, by extension,
 * extracting the pointer value from a @c AVL_TreeNodePointer .
 */
static constexpr uintptr_t bf_delete_mask = ~bf_mask;

/**
 * @brief Casts a pointer to uintptr_t.
 * @param p Pointer to cast.
 * @return Integer value of the pointer suitable for arithmetic and bitwise
 * boolean operations.
 */
static inline uintptr_t pointer_to_int(void* p)
{
	return reinterpret_cast<uintptr_t>(p); //NOLINT
}

/**
 * @brief Casts an encoded integer to a pointer, removing any encoded information
 * in the process.
 * @param coded_int Encoded integer value.
 * @return Pointer to an AVL_TreeNode<Key,Value>
 */
template <Comparable Key, DataType Value>
static inline AVL_TreeNode<Key, Value>* coded_int_to_pointer(uintptr_t coded_int)
{
	return reinterpret_cast<AVL_TreeNode<Key, Value>*>(coded_int & bf_delete_mask); //NOLINT
}

/**
 * @brief Type for encoding the AVL Node balance factor into its pointer.
 * @tparam Key Type of the key for the containing @c AVL_Tree .
 * @tparam Value Type of the value for the containing @c AVL_Tree .
 */
template <Comparable Key, DataType Value>
class AVL_TreeNodePointer {
public:
	/**
	 * @brief Default constructor.
	 * @post object == nullptr && object.bf() == 0
	 */
	constexpr AVL_TreeNodePointer() noexcept : m_pointer(2) { }

	/**
	 * @brief State-setting constructor.
	 * @param node_p Pointer to an AVL_TreeNode<Key,Value> that this object
	 * will manage.
	 * @param balance_factor Initial balance factor of the node. Default value is 0
	 * @post object == node_p && object.bf() == balance_factor
	 */
	AVL_TreeNodePointer(AVL_TreeNode<Key, Value>* node_p, balance_factor_t balance_factor = 0)
		: m_pointer(pointer_to_int(node_p) | (balance_factor + 2))
	{ }

	operator AVL_TreeNode<Key, Value>* ()
	{
		return reinterpret_cast<AVL_TreeNode<Key, Value>*>(m_pointer & bf_delete_mask); //NOLINT
	}

	AVL_TreeNode<Key, Value>& operator*()
	{
		return *coded_int_to_pointer<Key, Value>(m_pointer);
	}

	AVL_TreeNode<Key, Value>* operator->()
	{
		return coded_int_to_pointer<Key, Value>(m_pointer);
	}

	AVL_TreeNodePointer& operator=(const AVL_TreeNode<Key, Value>* other)
	{
		m_pointer &= bf_mask;
		m_pointer |= pointer_to_int(other);
		return *this;
	}

	balance_factor_t bf()
	{
		return (m_pointer & bf_mask) - 2;
	}

	void bf(const balance_factor_t& bf)
	{
		m_pointer &= bf_delete_mask;
		m_pointer |= ((bf + 2) & bf_mask);
	}
private:
	uintptr_t m_pointer;
};

template <Comparable Key, DataType Value>
class AVL_TreeNode {
public:
	constexpr AVL_TreeNode() noexcept : m_parent(0) { }

	AVL_TreeNode(Key key, Value value) noexcept : m_key(key), m_value(value) { }

	Key& key() { return m_key; }
	Value& value() { return m_value; }
private:
	Key m_key;
	Value m_value;
	AVL_TreeNodePointer<Key, Value> m_parent;
};
#endif /* AVL_TREE_NODE_POINTER_HPP */