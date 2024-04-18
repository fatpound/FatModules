// module;

export module FatAVL;

export import FatBST;

export namespace fatpound::tree
{
    template <std::totally_ordered T>
    class AVL : public BST<T>
    {
    public:
        virtual void Insert(T new_item) override
        {
            typename BST<T>::Node_* new_root = BST<T>::Insert_(nullptr, this->root_, new_item);

            if (this->root_ == nullptr)
            {
                this->root_ = new_root;
            }
            else
            {
                this->Balance_(new_root);
            }

            this->node_count_++;
        }
        virtual void Delete(T old_item) override final
        {
            typename BST<T>::Node_* node = BST<T>::Find_(this->root_, old_item);

            if (node == this->root_)
            {
                typename BST<T>::Node_* iosuc = BST<T>::GetInorderSuccessor_(node);
                node->item = iosuc->item;

                Balance_(BST<T>::Delete_(iosuc));
            }
            else
            {
                Balance_(BST<T>::Delete_(node));
            }
        }


    protected:
        virtual void Balance_(BST<T>::Node_* latest)
        {
            if (latest == nullptr)
            {
                return;
            }

            typename BST<T>::Node_* last = latest; // Y

            while (last->parent != nullptr) // Going up
            {
                const int  left_val = BST<T>::GetDepth_(last->parent->left, 0);
                const int right_val = BST<T>::GetDepth_(last->parent->right, 0);

                const int balanceFactor = right_val - left_val;

                /*
                std::cout << "parent  : " << last->parent->item << '\n';
                std::cout << "node    : " << last->item << '\n';
                std::cout << "left    : " << left_val << '\n';
                std::cout << "right   : " << right_val << '\n';
                std::cout << "Balance : " << balanceFactor << "\n\n";
                */

                if (balanceFactor > 1 && latest->item > last->item)
                {
                    RotateLeft_(last->parent, last);
                }
                else if (balanceFactor < -1 && latest->item < last->item)
                {
                    RotateRight_(last->parent, last);
                }
                else if (balanceFactor > 1 && latest->item < last->item)
                {
                    RotateRight_(last, last->left);
                    RotateLeft_(last->parent->parent, last->parent);
                }
                else if (balanceFactor < -1 && latest->item > last->item)
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
        void RotateLeft_(BST<T>::Node_* X, BST<T>::Node_* Y)
        {
            typename BST<T>::Node_* parent_of_parent = X->parent;

            X->right = Y->left;

            if (X->right != nullptr)
            {
                X->right->parent = X;
            }

            Y->left = X;

            X->parent = Y;
            Y->parent = parent_of_parent;

            if (parent_of_parent == nullptr)
            {
                this->root_ = Y;
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
        void RotateRight_(BST<T>::Node_* X, BST<T>::Node_* Y)
        {
            typename BST<T>::Node_* parent_of_parent = X->parent;

            X->left = Y->right;

            if (X->left != nullptr)
            {
                X->left->parent = X;
            }

            Y->right = X;

            X->parent = Y;
            Y->parent = parent_of_parent;

            if (parent_of_parent == nullptr)
            {
                this->root_ = Y;
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


    private:
    };
}