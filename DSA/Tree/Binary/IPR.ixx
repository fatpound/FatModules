module;

export module FatPound.DSA.Tree.Binary.IPR;

import FatPound.DSA.Tree.Binary.AVL;

import std;

export namespace fatpound::dsa::tree::binary
{
    template <std::totally_ordered T>
    class IPR final : public AVL<T>
    {
    public:
        using typename BST<T>::Node_;

        using AVL<T>::Balance_;

        using SizeType = AVL<T>::SizeType;


    public:
        virtual void Insert(const T new_item) override final
        {
            [[maybe_unused]] Node_* new_node = AVL<T>::Insert_(nullptr, this->m_root_, new_item);

            if (this->m_root_ == nullptr)
            {
                this->m_root_ = new_node;
            }
            else
            {
                Balance_();
            }

            ++this->m_node_count_;
        }


    protected:


    private:
        // NOLINTBEGIN(readability-identifier-length)
        virtual void Balance_(Node_* const latest) override final
        {
            if (latest == nullptr)
            {
                return;
            }
            Node_* last = latest; // Y

            while (last->parent not_eq nullptr) // Going up
            {
                decltype(SizeType{}) na{};
                decltype(SizeType{}) nb{};
                decltype(SizeType{}) nc{};

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

                if ((nc > na) and (a_location == false))
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

                if (last->parent == nullptr)
                {
                    break;
                }

                last = last->parent;
            }
        }
        // NOLINTEND(readability-identifier-length)
    };
}