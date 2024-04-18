// module;

export module FatBST;

#if (_MSVC_LANG > 202002L)
export import std;
#else
#if (_MSVC_LANG == 202002L)
#ifdef NDEBUG
export import std.core;
#else
import <iostream>;
export import <concepts>;
#endif // NDEBUG
#else
#error C++20 or greater version required
#endif // (_MSVC_LANG == 202002L)
#endif // (_MSVC_LANG > 202002L)

export namespace fatpound::tree
{
    template <std::totally_ordered T>
    class BST
    {
    public:
        BST() = default;
        BST(const BST<T>& src)
        {
            if (src.root_ != nullptr)
            {
                root_ = src.Clone_(src.root_);
                node_count_ = src.node_count_;
            }
        }
        BST(BST<T>&& src) noexcept
        {
            if (src.root_ != nullptr)
            {
                root_ = src.root_;
                node_count_ = src.node_count_;

                src.root_ = nullptr;
                src.node_count_ = 0ull;
            }
        }
        BST<T>& operator = (const BST<T>& src)
        {
            if (this != std::addressof(src) && src.root_ != nullptr)
            {
                if (root_ != nullptr)
                {
                    Delete_(root_);

                    root_ = nullptr;
                    node_count_ = 0ull;
                }

                root_ = src.Clone_(src.root_);
                node_count_ = src.node_count_;
            }

            return *this;
        }
        BST<T>& operator = (BST<T>&& src) noexcept
        {
            if (this != std::addressof(src) && src.root_ != nullptr)
            {
                if (root_ != nullptr)
                {
                    Delete_(root_);

                    root_ = nullptr;
                    node_count_ = 0ull;
                }

                root_ = src.root_;
                node_count_ = src.node_count_;

                src.root_ = nullptr;
                src.node_count_ = 0ull;
            }

            return *this;
        }
        virtual ~BST() noexcept
        {
            DeleteTree_(root_);
            root_ = nullptr;
            node_count_ = 0u;
        }


    public:
        std::int64_t GetTotalNodeCount() const
        {
            return node_count_;
        }

        bool Contains(T item)       const
        {
            return Find_(root_, item) == nullptr
                ? false
                : true
                ;
        }

        void ListPreorder()         const
        {
            ListPreorder_(root_);
            std::cout << '\n';
        }
        void ListPreorderReverse()  const
        {
            ListPreorderReverse_(root_);
            std::cout << '\n';
        }
        void ListInorder()          const
        {
            ListInorder_(root_);
            std::cout << '\n';
        }
        void ListInorderReverse()   const
        {
            ListInorderReverse_(root_);
            std::cout << '\n';
        }
        void ListPostorder()        const
        {
            ListPostorder_(root_);
            std::cout << '\n';
        }
        void ListPostorderReverse() const
        {
            ListPostorderReverse_(root_);
            std::cout << '\n';
        }
        void ListLeaves()           const
        {
            ListLeaves_(root_);
            std::cout << '\n';
        }
        void ListLeavesReverse()    const
        {
            ListLeavesReverse_(root_);
            std::cout << '\n';
        }
        void ListLevelorder()       const
        {
            const std::int64_t height = GetDepth_(root_, 0);

            for (std::int64_t i = 1; i <= height; i++)
            {
                std::cout << "Level " << i << " : ";

                ListLevelorder_(root_, i);

                std::cout << '\n';
            }

            std::cout << '\n';
        }

        virtual void Insert(T new_item)
        {
            BST<T>::Node_* new_root = Insert_(nullptr, root_, new_item);

            if (root_ == nullptr)
            {
                root_ = new_root;
            }

            ++node_count_;
        }
        virtual void Delete(T old_item)
        {
            BST<T>::Node_* node = Find_(root_, old_item);

            if (node != nullptr)
            {
                static_cast<void>(Delete_(node));
            }
        }
        void Mirror()
        {
            Mirror_(root_);
        }


    protected:
        struct Node_
        {
            Node_* left = nullptr;
            Node_* right = nullptr;
            Node_* parent = nullptr;

            T item;

            Node_(T new_item, Node_* new_parent)
                :
                item(new_item),
                parent(new_parent)
            {

            }
        };


    protected:
        BST<T>::Node_* Insert_(BST<T>::Node_* __restrict parent, BST<T>::Node_* __restrict node, T new_item)
        {
            if (node == nullptr)
            {
                return new BST<T>::Node_(new_item, parent);
            }

            if (new_item < node->item)
            {
                node->left = Insert_(node, node->left, new_item);
            }
            else if (new_item > node->item)
            {
                node->right = Insert_(node, node->right, new_item);
            }

            return node;
        }
        BST<T>::Node_* Clone_(BST<T>::Node_* node) const
        {
            if (node == nullptr)
            {
                return nullptr;
            }

            BST<T>::Node_* new_node = new BST<T>::Node_(node->item, node->parent);

            new_node->left = Clone_(node->left);
            new_node->right = Clone_(node->right);

            return new_node;
        }
        BST<T>::Node_* Find_(BST<T>::Node_* node, T item) const
        {
            if (node == nullptr)
            {
                return nullptr;
            }

            if (node->item == item)
            {
                return node;
            }

            BST<T>::Node_* left_address = Find_(node->left, item);

            if (left_address != nullptr)
            {
                return left_address;
            }

            BST<T>::Node_* right_address = Find_(node->right, item);

            if (right_address != nullptr)
            {
                return right_address;
            }
        }
        BST<T>::Node_* Delete_(BST<T>::Node_* node)
        {
            if (node == nullptr)
            {
                return nullptr;
            }

            BST<T>::Node_* latest = nullptr;

            if (node->parent != nullptr)
            {
                if (node->right != nullptr)
                {
                    BST<T>::Node_* leftmost = GetMin_(node->right);

                    if (leftmost != nullptr)
                    {
                        leftmost->left = node->left;

                        if (node->left != nullptr)
                        {
                            node->left->parent = leftmost;
                        }
                    }
                    else
                    {
                        node->right->left = node->left;

                        if (node->left != nullptr)
                        {
                            node->left->parent = node->right;
                        }
                    }

                    node->right->parent = node->parent;
                    latest = node->right;
                }
                else
                {
                    if (node->left != nullptr)
                    {
                        node->left->parent = node->parent;
                        latest = node->left;
                    }
                    else
                    {
                        latest = node->parent;
                    }
                }

                if (node->parent->item < node->item)
                {
                    node->parent->right = node->right;
                }
                else
                {
                    node->parent->left = node->right;
                }
            }
            else
            {
                root_ = node->right;
            }

            delete node;

            return latest;
        }

        BST<T>::Node_* GetMin_(BST<T>::Node_* node)
        {
            if (node == nullptr)
            {
                return nullptr;
            }

            while (node->left != nullptr)
            {
                node = node->left;
            }

            return node;
        }
        BST<T>::Node_* GetMax_(BST<T>::Node_* node)
        {
            if (node == nullptr)
            {
                return nullptr;
            }

            while (node->right != nullptr)
            {
                node = node->right;
            }

            return node;
        }
        BST<T>::Node_* GetInorderSuccessor_(BST<T>::Node_* node)
        {
            if (node->right != nullptr)
            {
                return GetMin_(node->right);
            }

            BST<T>::Node_* prnt = node->parent;

            while (prnt != nullptr && prnt->right == node)
            {
                node = prnt;
                prnt = prnt->parent;
            }

            return prnt;
        }

        std::int64_t GetDepth_(BST<T>::Node_* node, std::int64_t depth) const
        {
            if (node == nullptr)
            {
                return depth;
            }

            const std::int64_t  left_val = GetDepth_(node->left, depth + 1);
            const std::int64_t right_val = GetDepth_(node->right, depth + 1);

            return std::max(left_val, right_val);
        }
        std::int64_t GetDepthLeft_(BST<T>::Node_* node, std::int64_t depth) const
        {
            return node ? GetDepthLeft_(node->left, depth + 1) : depth;
        }
        std::int64_t GetDepthRight_(BST<T>::Node_* node, std::int64_t depth) const
        {
            return node ? GetDepthRight_(node->right, depth + 1) : depth;
        }
        std::int64_t GetNodeCount_(BST<T>::Node_* node) const
        {
            if (node == nullptr)
            {
                return 0;
            }

            const std::int64_t  left_val = GetNodeCount_(node->left);
            const std::int64_t right_val = GetNodeCount_(node->right);

            return 1 + left_val + right_val;
        }

        void Mirror_(BST<T>::Node_* node)
        {
            if (node != nullptr)
            {
                std::swap(node->left, node->right);

                Mirror_(node->left);
                Mirror_(node->right);
            }
        }

        void ListPreorder_(const BST<T>::Node_* node) const
        {
            if (node != nullptr)
            {
                std::cout << node->item << ' ';
                ListPreorder_(node->left);
                ListPreorder_(node->right);
            }
        }
        void ListPreorderReverse_(const BST<T>::Node_* node) const
        {
            if (node != nullptr)
            {
                std::cout << node->item << ' ';
                ListPreorderReverse_(node->right);
                ListPreorderReverse_(node->left);
            }
        }
        void ListInorder_(const BST<T>::Node_* node) const
        {
            if (node != nullptr)
            {
                ListInorder_(node->left);
                std::cout << node->item << ' ';
                ListInorder_(node->right);
            }
        }
        void ListInorderReverse_(const BST<T>::Node_* node) const
        {
            if (node != nullptr)
            {
                ListInorderReverse_(node->right);
                std::cout << node->item << ' ';
                ListInorderReverse_(node->left);
            }
        }
        void ListPostorder_(const BST<T>::Node_* node) const
        {
            if (node != nullptr)
            {
                ListPostorder_(node->left);
                ListPostorder_(node->right);
                std::cout << node->item << ' ';
            }
        }
        void ListPostorderReverse_(const BST<T>::Node_* node) const
        {
            if (node != nullptr)
            {
                ListPostorderReverse_(node->right);
                ListPostorderReverse_(node->left);
                std::cout << node->item << ' ';
            }
        }
        void ListLeaves_(const BST<T>::Node_* node) const
        {
            if (node != nullptr)
            {
                if (node->left == nullptr && node->right == nullptr)
                {
                    std::cout << node->item << ' ';
                    return;
                }

                ListLeaves_(root_->left);
                ListLeaves_(root_->right);
            }
        }
        void ListLeavesReverse_(const BST<T>::Node_* node) const
        {
            if (node != nullptr)
            {
                if (node->left == nullptr && node->right == nullptr)
                {
                    std::cout << node->item << ' ';
                    return;
                }

                ListLeavesReverse_(root_->right);
                ListLeavesReverse_(root_->left);
            }
        }
        void ListLevelorder_(const BST<T>::Node_* node, std::int64_t level) const
        {
            if (node != nullptr)
            {
                if (level == 1)
                {
                    std::cout << node->item << ' ';
                }
                else if (level > 1)
                {
                    ListLevelorder_(node->left, level - 1);
                    ListLevelorder_(node->right, level - 1);
                }
            }
            else if (level == 1)
            {
                std::cout << "x ";
            }
        }


    protected:
        Node_* root_ = nullptr;

        std::size_t node_count_ = 0u;


    private:
        void DeleteTree_(BST<T>::Node_* root) noexcept
        {
            if (root != nullptr)
            {
                DeleteTree_(root->left);
                DeleteTree_(root->right);

                delete root;
            }
        }
    };
}