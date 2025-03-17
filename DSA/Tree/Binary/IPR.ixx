module;

export module FatPound.DSA.Tree.Binary.IPR;

import FatPound.DSA.Tree.Binary.BST;
import FatPound.DSA.Tree.Binary.AVL;

import std;

export namespace fatpound::dsa::tree::binary
{
    template <std::totally_ordered T>
    class IPR final : public AVL<T>
    {
        using AVL<T>::Balance_;

    public:
        using Size_t = AVL<T>::Size_t;


    public:
        virtual void Insert(const T& new_item) override final
        {
            [[maybe_unused]] Node_* const new_node = AVL<T>::Insert_(nullptr, this->m_pRoot_, new_item);

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


    protected:
        using typename BST<T>::Node_;


    private:
        virtual void Balance_(Node_* const latest) noexcept override final
        {
            if (latest == nullptr)
            {
                return;
            }

            Node_* last = latest; // Y

            while (last->parent not_eq nullptr) // Going up
            {
                Size_t na{};
                Size_t nb{};
                Size_t nc{};

                // false => left, true => right
                bool a_location{};

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

                if (a_location)
                {
                    nb = BST<T>::GetNodeCount_(last->right);
                    nc = BST<T>::GetNodeCount_(last->left);
                }
                else
                {
                    nb = BST<T>::GetNodeCount_(last->left);
                    nc = BST<T>::GetNodeCount_(last->right);
                }

                /*
                std::cout << "parent  : " << last->parent->item << '\n';
                std::cout << "node    : " << last->item << '\n';
                std::cout << "na      : " << na << '\n';
                std::cout << "nb      : " << nb << '\n';
                std::cout << "nc      : " << nc << '\n' << '\n';
                */

                // NOLINTBEGIN(readability-simplify-boolean-expr)
                if      ((nc > na) and (a_location == false))
                {
                    AVL<T>::RotateLeft_(last->parent, last);
                }
                else if ((nc > na) and (a_location == true))
                {
                    AVL<T>::RotateRight_(last->parent, last);
                }
                else if ((nb > na) and (a_location == false))
                {
                    AVL<T>::RotateRight_(last, last->left);
                    AVL<T>::RotateLeft_(last->parent->parent, last->parent);
                }
                else if ((nb > na) and (a_location == true))
                {
                    AVL<T>::RotateLeft_(last, last->right);
                    AVL<T>::RotateRight_(last->parent->parent, last->parent);
                }
                // NOLINTEND(readability-simplify-boolean-expr)

                if (last->parent == nullptr)
                {
                    break;
                }

                last = last->parent;
            }
        }
    };
}

module : private;
