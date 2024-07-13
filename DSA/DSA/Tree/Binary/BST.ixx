module;

export module FatPound.DSA.Tree.Binary.BST;

import std;

export namespace fatpound::dsa::tree::binary
{
    template <std::totally_ordered T>
    class BST
    {
    public:
        using SizeType = std::size_t;


    public:
        BST() = default;
        BST(const BST& src) noexcept
        {
            if (src.root_ != nullptr)
            {
                root_ = src.Clone_(src.root_);
                node_count_ = src.node_count_;
            }
        }
        BST& operator = (const BST& src) noexcept
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

        BST(BST&& src) noexcept
        {
            if (src.root_ != nullptr)
            {
                root_ = src.root_;
                node_count_ = src.node_count_;

                src.root_ = nullptr;
                src.node_count_ = 0ull;
            }
        }
        BST& operator = (BST&& src) noexcept
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
        virtual SizeType GetTotalNodeCount() const final
        {
            return node_count_;
        }

        virtual bool Contains(T item)       const final
        {
            return Find_(root_, item) != nullptr;
        }

        virtual void ListPreorder()         const final
        {
            ListPreorder_(root_);
            std::cout << '\n';
        }
        virtual void ListPreorderReverse()  const final
        {
            ListPreorderReverse_(root_);
            std::cout << '\n';
        }
        virtual void ListInorder()          const final
        {
            ListInorder_(root_);
            std::cout << '\n';
        }
        virtual void ListInorderReverse()   const final
        {
            ListInorderReverse_(root_);
            std::cout << '\n';
        }
        virtual void ListPostorder()        const final
        {
            ListPostorder_(root_);
            std::cout << '\n';
        }
        virtual void ListPostorderReverse() const final
        {
            ListPostorderReverse_(root_);
            std::cout << '\n';
        }
        virtual void ListLeaves()           const final
        {
            ListLeaves_(root_);
            std::cout << '\n';
        }
        virtual void ListLeavesReverse()    const final
        {
            ListLeavesReverse_(root_);
            std::cout << '\n';
        }
        virtual void ListLevelorder()       const final
        {
            const auto height = GetDepth_(root_, 0);

            for (SizeType i = 1u; i <= height; ++i)
            {
                std::cout << "Level " << i << " : ";

                ListLevelorder_(root_, i);

                std::cout << '\n';
            }

            std::cout << '\n';
        }

        virtual void Insert(const T& new_item)
        {
            [[maybe_unused]] Node_* new_node = Insert_(nullptr, root_, new_item);

            if (root_ == nullptr) [[unlikely]]
            {
                root_ = new_node;
            }

            ++node_count_;
        }
        virtual void Delete(const T& old_item)
        {
            Node_* node = Find_(root_, old_item);

            if (node != nullptr)
            {
                static_cast<void>(Delete_(node));
            }
        }
        virtual void Mirror() final
        {
            Mirror_(root_);
        }


    protected:
        struct Node_ final
        {
            Node_* left   = nullptr;
            Node_* right  = nullptr;
            Node_* parent = nullptr;

            T item;

            Node_(T new_item, Node_* new_parent)
                :
                parent(new_parent),
                item(new_item)
            {

            }
        };


    protected:
        virtual Node_* Insert_(Node_* __restrict parent, Node_* __restrict node, const T& new_item)
        {
            if (node == nullptr)
            {
                return new Node_(new_item, parent);
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
        virtual Node_* Clone_(Node_* node) const final
        {
            if (node == nullptr)
            {
                return nullptr;
            }

            Node_* new_node = new Node_(node->item, node->parent);

            new_node->left  = Clone_(node->left);
            new_node->right = Clone_(node->right);

            return new_node;
        }
        virtual Node_* Find_(Node_* node, const T& item) const final
        {
            if (node == nullptr)
            {
                return nullptr;
            }

            if (node->item == item)
            {
                return node;
            }

            Node_* left_address = Find_(node->left, item);

            if (left_address != nullptr)
            {
                return left_address;
            }

            Node_* right_address = Find_(node->right, item);

            if (right_address != nullptr)
            {
                return right_address;
            }

            return nullptr;
        }
        virtual Node_* Delete_(Node_* node) final
        {
            if (node == nullptr)
            {
                return nullptr;
            }

            Node_* latest = nullptr;

            if (node->parent != nullptr)
            {
                if (node->right != nullptr)
                {
                    Node_* leftmost = GetMin_(node->right);

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

        virtual Node_* GetMin_(Node_* node) final
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
        virtual Node_* GetMax_(Node_* node) final
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
        virtual Node_* GetInorderSuccessor_(Node_* node) final
        {
            if (node->right != nullptr)
            {
                return GetMin_(node->right);
            }

            // parent_of_node
            Node_* prnt = node->parent;

            while (prnt != nullptr && prnt->right == node)
            {
                node = prnt;
                prnt = prnt->parent;
            }

            return prnt;
        }

        virtual SizeType GetDepth_      (Node_* node, SizeType depth) const final
        {
            if (node == nullptr)
            {
                return depth;
            }

            const auto  left_val = GetDepth_(node->left,  depth + 1);
            const auto right_val = GetDepth_(node->right, depth + 1);

            return std::max(left_val, right_val);
        }
        virtual SizeType GetDepthLeft_  (Node_* node, SizeType depth) const final
        {
            return node ? GetDepthLeft_(node->left, depth + 1) : depth;
        }
        virtual SizeType GetDepthRight_ (Node_* node, SizeType depth) const final
        {
            return node ? GetDepthLeft_(node->right, depth + 1) : depth;
        }
        virtual SizeType GetNodeCount_  (Node_* node) const final
        {
            if (node == nullptr)
            {
                return 0;
            }

            const auto  left_val = GetNodeCount_(node->left);
            const auto right_val = GetNodeCount_(node->right);

            return 1 + left_val + right_val;
        }
        
        virtual void Mirror_(Node_* node) final
        {
            if (node != nullptr)
            {
                std::swap(node->left, node->right);

                Mirror_(node->left);
                Mirror_(node->right);
            }
        }

        virtual void ListPreorder_         (const Node_* node) const final
        {
            if (node != nullptr)
            {
                std::cout << node->item << ' ';
                ListPreorder_(node->left);
                ListPreorder_(node->right);
            }
        }
        virtual void ListPreorderReverse_  (const Node_* node) const final
        {
            if (node != nullptr)
            {
                std::cout << node->item << ' ';
                ListPreorderReverse_(node->right);
                ListPreorderReverse_(node->left);
            }
        }
        virtual void ListInorder_          (const Node_* node) const final
        {
            if (node != nullptr)
            {
                ListInorder_(node->left);
                std::cout << node->item << ' ';
                ListInorder_(node->right);
            }
        }
        virtual void ListInorderReverse_   (const Node_* node) const final
        {
            if (node != nullptr)
            {
                ListInorderReverse_(node->right);
                std::cout << node->item << ' ';
                ListInorderReverse_(node->left);
            }
        }
        virtual void ListPostorder_        (const Node_* node) const final
        {
            if (node != nullptr)
            {
                ListPostorder_(node->left);
                ListPostorder_(node->right);
                std::cout << node->item << ' ';
            }
        }
        virtual void ListPostorderReverse_ (const Node_* node) const final
        {
            if (node != nullptr)
            {
                ListPostorderReverse_(node->right);
                ListPostorderReverse_(node->left);
                std::cout << node->item << ' ';
            }
        }
        virtual void ListLeaves_           (const Node_* node) const final
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
        virtual void ListLeavesReverse_    (const Node_* node) const final
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
        virtual void ListLevelorder_       (const Node_* node, SizeType level) const final
        {
            if (node != nullptr)
            {
                if (level == 1)
                {
                    std::cout << node->item << ' ';
                }
                else if (level > 1)
                {
                    ListLevelorder_(node->left,  level - 1);
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

        SizeType node_count_ = 0u;


    private:
        virtual void DeleteTree_(Node_* root) noexcept final
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