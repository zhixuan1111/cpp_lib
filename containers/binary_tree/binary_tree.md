# 二叉树知识点总结
## 二叉树概念
### （1）满二叉树
如果一棵二叉树只有度为0的结点和度为2的结点，并且度为0的结点在同一层上，则这棵二叉树为满二叉树。也可以说深度为k，有2^k-1个节点的二叉树。

![满二叉树](/image/binary_tree/满二叉树.png)

### （2）完全二叉树
在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。若最底层为第 h 层（h从1开始），则该层包含 1~ 2^(h-1) 个节点。

![完全二叉树](/image/binary_tree/完全二叉树.png)

### （3）二叉搜索树（BST）
又名二叉排序树。二叉搜索树是有数值的了，二叉搜索树是一个有序树。

![二叉搜索树](/image/binary_tree/二叉搜索树.png)

- 若它的左子树不空，则左子树上**所有结点的值**均小于它的根结点的值；
- 若它的右子树不空，则右子树上**所有结点的值**均大于它的根结点的值；
- 它的左、右子树也分别为二叉排序树

### （3）平衡二叉搜索树  
又被称为AVL（Adelson-Velsky and Landis）树，且具有以下性质：它是一棵空树或它的左右两个子树的高度差的绝对值不超过1，并且左右两个子树都是一棵平衡二叉树。

![](/image/binary_tree/平衡二叉搜索树.png)

上图第三个不是平衡二叉搜索树，因为左右子树高度差超过1

平衡二叉搜索树在 BST 基础上增加了 “平衡约束”，通过旋转等操作维持树的高度平衡（左右子树高度差在可控范围内），保证所有操作的时间复杂度稳定在 O (log n)。常见的平衡 BST 包括：
- 红黑树
- AVL 树
- 平衡二叉 B 树  

C++中 `map`、`set`、`multimap`，`multiset` 的底层实现都是平衡二叉搜索树，所以 `map`、`set` 的增删操作时间时间复杂度是logn。`unordered_map`、`unordered_set`，`unordered_map`、`unordered_set`底层实现是哈希表。

## 二叉树遍历方式
二叉树主要有两种遍历方式：深度优先遍历：先往深走，遇到叶子节点再往回走。广度优先遍历：一层一层的去遍历。
- 深度优先遍历
    - 前序遍历（递归法，迭代法）
    - 中序遍历（递归法，迭代法）
    - 后序遍历（递归法，迭代法）
- 广度优先遍历
    - 层次遍历（迭代法）

### 二叉树定义
```cpp
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
```

### 二叉树的递归遍历
以中序遍历为例，遍历的路径是：根->左->右。代码实现思路：

```cpp
void traversal(TreeNode* root, std::vector<int>& result){
    if(root==nullptr) return;
    traversal(root->left, result);  // 递归左子树
    result.push_back(root->val);    // 访问根节点
    traversal(root->right, result); // 递归右子树
}
```
执行流程如下：

1. 首先判断当前节点`root`是否为空，若为空则直接返回，这是递归的终止条件

2. 执行`traversal(root->left, result)`：递归遍历当前节点的左子树
   - 这个过程会不断深入左子树，直到遇到最左侧的叶子节点（该节点的左子树为空）
   - 此时递归触底返回，开始执行后续操作

3. 当左子树遍历完成后，执行`result.push_back(root->val)`：
   - 将当前节点的值存入结果容器`result`中
   - 这体现了中序遍历"左-根-右"的核心思想，在左子树遍历完成后才访问根节点

4. 最后执行`traversal(root->right, result)`：递归遍历当前节点的右子树
   - 右子树会以同样的方式进行中序遍历
   - 先遍历右子树的左子树，再访问右子树的根节点，最后遍历右子树的右子树

整个过程就像沿着树的左侧一路向下，触底后开始收集节点值，然后再处理右侧分支，最终得到的`result`容器会按从小到大的顺序（对于二叉搜索树）存储所有节点值，这也是中序遍历的典型应用场景。

### 二叉树的迭代遍历

以中序的迭代遍历为例子
```cpp
void inorderTraversal(TreeNode* root,std::vector<int>& result){
    std::stack<TreeNode*> st;
    TreeNode* curr = root;
    while(!st.empty() || curr != nullptr){
        while(curr != nullptr){
            st.push(curr);;
            curr = curr->left;
        }

        curr = st.top();
        st.pop();
        result.push_back(curr->val);
        curr = curr->right;
    }
}
```
整个过程的核心逻辑是：
1. 利用内层循环将所有左孩子入栈，确保每次处理节点时其左子树已完全遍历
2. 弹出栈顶节点并记录值（处理根节点）
3. 转向右子树，重复上述过程




## 基于二叉树的容器实现 `std::map`
std::map 不允许重复键,按键自动排序（默认升序）。查找、插入、删除的效率皆为O(log n)，内存占用	较低（红黑树结构紧凑）

