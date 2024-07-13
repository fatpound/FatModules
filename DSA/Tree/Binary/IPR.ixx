module;

export module FatPound.DSA.Tree.Binary.IPR;

import FatPound.DSA.Tree.Binary.AVL;

import std;

export namespace fatpound::dsa::tree::binary
{
    template <std::totally_ordered T>
    class IPR final : public AVL<T>
    {
        using typename BST<T>::SizeType;
        using typename BST<T>::Node_;

        using AVL<T>::Balance_;

    public:
        virtual void Insert(const T& new_item) override final
        {
            [[maybe_unused]] Node_* new_node = AVL<T>::Insert_(nullptr, this->root_, new_item);

            if (this->root_ == nullptr) [[unlikely]]
                {
                    this->root_ = new_node;
                }
            else [[likely]]
                {
                    Balance_();
                }

                ++this->node_count_;
        }


    protected:


    private:
        virtual void Balance_(Node_* const latest) override final
        {
            if (latest == nullptr)
            {
                return;
            }

            Node_* last = latest; // Y

            while (last->parent != nullptr) // Going up
            {
                decltype(SizeType{}) na, nb, nc;

                // false => left, true => right
                bool a_location;

                if (last->parent->item < last->item)
                {
                    na = BST<T>::GetNodeCount_(last->parent->left);
                    a_location = false;
                }
                else
                {
                    na = BST<T>::GetNodeCount_(last->parent->right);
                    a_location = true;
                }

                if (a_location == false)
                {
                    nb = BST<T>::GetNodeCount_(last->left);
                    nc = BST<T>::GetNodeCount_(last->right);
                }
                else
                {
                    nb = BST<T>::GetNodeCount_(last->right);
                    nc = BST<T>::GetNodeCount_(last->left);
                }

                /*
                std::cout << "parent  : " << last->parent->item << '\n';
                std::cout << "node    : " << last->item << '\n';
                std::cout << "na      : " << na << '\n';
                std::cout << "nb      : " << nb << '\n';
                std::cout << "nc      : " << nc << '\n' << '\n';
                */

                if (nc > na && a_location == false)
                {
                    AVL<T>::RotateLeft_(last->parent, last);
                }
                else if (nc > na && a_location == true)
                {
                    AVL<T>::RotateRight_(last->parent, last);
                }
                else if (nb > na && a_location == false)
                {
                    AVL<T>::RotateRight_(last, last->left);
                    AVL<T>::RotateLeft_(last->parent->parent, last->parent);
                }
                else if (nb > na && a_location == true)
                {
                    AVL<T>::RotateLeft_(last, last->right);
                    AVL<T>::RotateRight_(last->parent->parent, last->parent);
                }

                if (last->parent == nullptr)
                {
                    break;
                }

                last = last->parent;
            }
        }
    };
}