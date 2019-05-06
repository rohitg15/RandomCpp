#include <memory>
#include <vector>

template <typename T>
struct Node
{
    T val_;
    std::unique_ptr<Node> left_, right_;

    Node(T const& val);
    // ~Node();
};

template <typename T>
Node<T>::Node(T const& val)
    :
        val_(val),
        left_(nullptr),
        right_(nullptr)
{}

// template <typename T>
// Node<T>::~Node()
// {
//     std::cout << "destructing : " << val_ << std::endl;
// }

template <typename T>
class Tree
{
    public:
        // proot is a sink here
        Tree(std::unique_ptr<Node<T> > proot);

        std::vector<T> MorrisTraversal();

    private:
        std::unique_ptr<Node<T> > proot_;
};


template <typename T>
Tree<T>::Tree(std::unique_ptr<Node<T> > proot)
    :
        proot_(std::move(proot))
{}

template <typename T>
std::vector<T> Tree<T>::MorrisTraversal()
{
    std::vector<T> results;
    Node<T> *cur = proot_.get();
    while (cur != nullptr)
    {
        if (cur->left_ == nullptr)
        {
            results.emplace_back(cur->val_);
            cur = cur->right_.get();
        }
        else
        {
            // find inorder predecessor
            Node<T> *pre = cur->left_.get();
            while (pre != nullptr && pre->right_ != nullptr && pre->right_.get() != cur )
            {
                pre = pre->right_.get();
            }

            if (pre->right_ == nullptr)
            {
                // this is the inorder predecessor
                //std::cout << "reset - pre : " << pre->right_->val_ << std::endl;
                pre->right_.reset(cur);
                cur = cur->left_.get();
            }
            else
            {
                // this is the second trip, remove the link
                pre->right_.release();
                results.emplace_back(cur->val_);
                cur = cur->right_.get();
            }
        }
        
    }
    return results;
}