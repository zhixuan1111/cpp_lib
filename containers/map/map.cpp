#include <iostream>

template<typename K, typename V>
class Map 
{
private:
    struct Node 
    {
        K key;
        V value;
        Node* left;
        Node* right;
        Node(K k, V v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // 插入：递归插入一个键值对
    Node* insert(Node* node, K key, V value) 
    {
        if (!node) return new Node(key, value);
        if (key < node->key)
            node->left = insert(node->left, key, value);
        else if (key > node->key)
            node->right = insert(node->right, key, value);
        else
            node->value = value; // key相同就更新value
        return node;
    }

    // 查找
    Node* find(Node* node, K key) const 
    {
        if (!node) return nullptr;
        if (key == node->key) return node;
        if (key < node->key) return find(node->left, key);
        else return find(node->right, key);
    }

    // 中序遍历：用于查看内容
    void inorder(Node* node) const 
    {
        if (!node) return;
        inorder(node->left);
        std::cout << node->key << " : " << node->value << std::endl;
        inorder(node->right);
    }

    // 析构函数辅助
    void destroy(Node* node) 
    {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    Map() : root(nullptr) {}

    ~Map() 
    {
        destroy(root);
    }

    void insert(K key, V value) 
    {
        root = insert(root, key, value);
    }

    bool contains(K key) const 
    {
        return find(root, key) != nullptr;
    }

    V get(K key) const 
    {
        Node* node = find(root, key);
        if (!node) throw std::runtime_error("Key not found");
        return node->value;
    }

    void print() const 
    {
        inorder(root);
    }
};


int main() 
{
    Map<int, std::string> myMap;

    myMap.insert(3, "apple");
    myMap.insert(1, "banana");
    myMap.insert(5, "cherry");

    std::cout << "Map contents:" << std::endl;
    myMap.print();

    std::cout << "Key 3: " << myMap.get(3) << std::endl;

    if (myMap.contains(5)) 
    {
        std::cout << "Key 5 exists!" << std::endl;
    }

    return 0;
}
