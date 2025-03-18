module;

export module FatPound.DSA.Tree.Binary.AVL;

import FatPound.DSA.Tree.Binary.BST;

import std;

export namespace fatpound::dsa::tree::binary
{
    template <std::totally_ordered T>
    class AVL : public BST<T>
    {
    public:
        using Size_t = BST<T>::Size_t;


    public:
        // NOLINTBEGIN(clang-analyzer-cplusplus.NewDeleteLeaks)
        virtual void Insert(const T& new_item) override
        {
            [[maybe_unused]] Node_* new_node = Insert_(nullptr, this->m_pRoot_, new_item);

            if (this->m_pRoot_ == nullptr)
            {
                this->m_pRoot_ = new_node;
            }
            else
            {
                Balance_();
            }

            ++(this->m_node_count_);
        }
        // NOLINTEND(clang-analyzer-cplusplus.NewDeleteLeaks)

        virtual void Delete(const T& old_item) noexcept override
        {
            Node_* node = BST<T>::Find_(this->m_pRoot_, old_item);

            if (node == this->m_pRoot_)
            {
                // inorder_successor
                Node_* iosuc = BST<T>::GetInorderSuccessor_(node);

                node->item = iosuc->item;

                Balance_(BST<T>::Delete_(iosuc));
            }
            else
            {
                Balance_(BST<T>::Delete_(node));
            }
        }


    protected:
        using typename BST<T>::Node_;


    protected:
        virtual auto Insert_(Node_* const __restrict parent, Node_* const __restrict node, const T& new_item) -> Node_* override final
        {
            if (node == nullptr)
            {
                m_last_added_ = new Node_(new_item, parent);

                return m_last_added_;
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

        virtual void Balance_() noexcept
        {
            Balance_(m_last_added_);
        }
        virtual void Balance_(Node_* const latest) noexcept
        {
            if (latest == nullptr)
            {
                return;
            }

            Node_* last = latest; // Y

            while (last->parent not_eq nullptr) // Going up
            {
                const auto  left_val = BST<T>::GetDepth_(last->parent->left,  0);
                const auto right_val = BST<T>::GetDepth_(last->parent->right, 0);

                const auto balanceFactor = static_cast<::std::int64_t>(right_val - left_val);

                /*
                std::cout << "parent  : " << last->parent->item << '\n';
                std::cout << "node    : " << last->item << '\n';
                std::cout << "left    : " << left_val << '\n';
                std::cout << "right   : " << right_val << '\n';
                std::cout << "Balance : " << balanceFactor << "\n\n";
                */

                if ((balanceFactor > 1) and (latest->item > last->item))
                {
                    RotateLeft_(last->parent, last);
                }
                else if ((balanceFactor < -1) and (latest->item < last->item))
                {
                    RotateRight_(last->parent, last);
                }
                else if ((balanceFactor >  1) and (latest->item < last->item))
                {
                    RotateRight_(last, last->left);
                    RotateLeft_(last->parent->parent, last->parent);
                }
                else if ((balanceFactor < -1) and (latest->item > last->item))
                {
                    RotateLeft_(last, last->right);
                    RotateRight_(last->parent->parent, last->parent);
                }

                if (last->parent == nullptr)
                {
                    break;
                }

                last = last->parent;
            }
        }

        void RotateLeft_ (Node_* X, Node_* Y) noexcept
        {
            Node_* parent_of_parent = X->parent;

            X->right = Y->left;

            if (X->right not_eq nullptr)
            {
                X->right->parent = X;
            }

            Y->left = X;

            X->parent = Y;
            Y->parent = parent_of_parent;

            if (parent_of_parent == nullptr)
            {
                this->m_pRoot_ = Y;
            }
            else
            {
                if (parent_of_parent->item < X->item)
                {
                    parent_of_parent->right = Y;
                }
                else
                {
                    parent_of_parent->left = Y;
                }
            }
        }
        void RotateRight_(Node_* X, Node_* Y) noexcept
        {
            Node_* parent_of_parent = X->parent;

            X->left = Y->right;

            if (X->left not_eq nullptr)
            {
                X->left->parent = X;
            }

            Y->right = X;

            X->parent = Y;
            Y->parent = parent_of_parent;

            if (parent_of_parent == nullptr)
            {
                this->m_pRoot_ = Y;
            }
            else
            {
                if (parent_of_parent->item < X->item)
                {
                    parent_of_parent->right = Y;
                }
                else
                {
                    parent_of_parent->left = Y;
                }
            }
        }


    protected:
        Node_* m_last_added_ = nullptr;


    private:
    };
}

module : private;
