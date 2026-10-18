#include <iostream>
#include <memory>
#include <type_traits>
#include <vector>
#include <stack>
#include <random>
#include <iterator>

template <typename T>
class BSTree
{
    static_assert(std::is_arithmetic_v<T>,
                  "BSTree supports only arithmetic types");
private:
    struct Node
    {
        T val;
        std::unique_ptr<Node> left, right;
        Node(const T& val) : val(val) {}
    };
    std::unique_ptr<Node> root;
    int count(const std::unique_ptr<Node>& node) const
    {
        if (!node) return 0;
        return 1 + count(node->left) + count(node->right);
    }
    void insert(std::unique_ptr<Node>& node, T value)
    {
        if (!node) 
        {
            node = std::make_unique<Node>(value);
            return;
        }

        if (value < node.get()->val)
            insert(node->left, value);
        else insert(node->right, value);
    }
    std::vector<T> inorder(const std::unique_ptr<Node>& node) const
    {
        if (!node) return {};

        std::vector<T> result;
        std::stack<Node*> s1;
        Node* cur = node.get();

        while (cur || !s1.empty())
        {
            while (cur)
            {
                s1.push(cur);
                cur = cur->left.get();                
            }
            cur = s1.top();
            result.push_back(cur->val);
            s1.pop();
            cur = cur->right.get();            
        }
        return result;
    }
    std::vector<T> postorder_visited(const std::unique_ptr<Node>& node) const
    {
        if (!node) return {};

        std::stack<Node*> s1;
        std::vector<T> result;
        Node* cur = node.get();
        Node* visited = nullptr;

        while (cur || !s1.empty())
        {
            while (cur)
            {
                s1.push(cur);
                cur = cur->left.get();
            }
            Node* top = s1.top();

            if (top->right && visited != top->right.get())
                cur = top->right.get();
            else
            {
                result.push_back(top->val);
                s1.pop();
                visited = top;
            }
        }
        return result;
    }

    std::vector<T> postorder(const std::unique_ptr<Node>& node) const
    {
        if (!node) return {};
        std::stack<Node*> s1, s2;
        std::vector<T> result;
        Node* cur = node.get();
        s1.push(cur);
        
        while (!s1.empty())
        {            
            cur = s1.top();
            s1.pop();
            s2.push(cur);
            if (cur->left.get()) s1.push(cur->left.get());
            if (cur->right.get()) s1.push(cur->right.get());
            
            
        }
        while (!s2.empty())
        {
            result.push_back(s2.top()->val);
            s2.pop();
        }
        return result;

    }
    std::vector<T> preorder(const std::unique_ptr<Node>& node) const
    {
        if (!node) return {};
        std::stack<Node*> s1;
        std::vector<T> result{};
        s1.push(node.get());

        while (!s1.empty())
        {
            Node* top = s1.top();
            result.push_back(top->val);
            s1.pop();
            if (top->right.get()) s1.push(top->right.get());
            if (top->left.get()) s1.push(top->left.get());
        }
        return result;
    }

public:
    BSTree() = default;
    explicit BSTree(std::initializer_list<T> list)
    {
        for (const auto& el : list) this->insert(el);
    }
    template<typename It>
    explicit BSTree(const It& ItFirst, const It& ItLast)
    {
        static_assert(std::is_base_of_v<std::input_iterator_tag,
                                      typename std::iterator_traits<It>::iterator_category>,
                    "It must be an input iterator");
        static_assert(std::is_convertible_v<typename std::iterator_traits<It>::value_type, T>,
                        "Element type must be a suitable to BSTree implementation");

        for (auto it = ItFirst; it != ItLast; ++it)
            insert(*it);
    }

    BSTree& operator=(const BSTree&) = delete;
    BSTree(const BSTree&) = delete;
    BSTree& operator=(BSTree&& other) noexcept
    {
        if (this != &other)
            root = std::move(other.root);
        return *this;
    }
    BSTree(BSTree&& other) noexcept : root(std::move(other.root))
    {}

    void insert(T value)
    {
        insert(root, value);
    }
    void print() const
    {
        if (!root) return;

        auto result = inorder(root);

        std::cout << "Inorder:" ;

        for (const auto& v : result)
            std::cout << v << " ";
        
        result = postorder_visited(root);
        std::cout << "\n" << "Postorder:";

        for (const auto& v : result)
            std::cout << v << " ";
            
        result = preorder(root);
        std::cout << "\n" << "preorder:";

        for (const auto& v : result)
            std::cout << v << " ";
    }
    int size() const
    {
        return count(root);
    }

};




int main()
{
    return 0;
}
