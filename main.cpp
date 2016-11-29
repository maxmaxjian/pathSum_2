#include <iostream>
#include <memory>
#include <vector>
#include <queue>
#include <iterator>
#include <algorithm>

struct TreeNode {
    int val;
    std::shared_ptr<TreeNode> left, right;
    TreeNode(int v, const std::shared_ptr<TreeNode> & lchild=nullptr, const std::shared_ptr<TreeNode> & rchild=nullptr)
        : val(v), left(lchild), right(rchild) {}
        
    void print() {
        if (left != nullptr || right != nullptr) {
            std::cout << "val = " << val
                      << "\t left -> " << (left != nullptr ? std::to_string(left->val) : "null") << "\n"
                      << "\t right -> " << (right != nullptr ? std::to_string(right->val) : "null") << "\n";
        }
    }
};

using pNode = std::shared_ptr<TreeNode>;

void printBFS(const pNode & root) {
    std::queue<pNode> qu;
    qu.push(root);
    while (!qu.empty()) {
        auto curr = qu.front();
        qu.pop();
        if (curr != nullptr) {
            curr->print();
            qu.push(curr->left);
            qu.push(curr->right);
        }
    }
}

class solution {
  public:
    std::vector<std::vector<int>> pathSum(const pNode & root, int sum) {
        std::vector<std::vector<int>> result;
        if (root != nullptr) {
            if (root->left == nullptr && root->right == nullptr) {
                if (root->val == sum)
                    result.push_back(std::vector<int>{root->val});
            }
            else {
                if (root->left != nullptr) {
                    auto leftpath = pathSum(root->left, sum-root->val);
                    std::transform(leftpath.begin(), leftpath.end(), std::inserter(result, result.end()),
                                   [&](const std::vector<int> & vec){
                                       auto cpy = vec;
                                       cpy.insert(cpy.begin(), root->val);
                                       return cpy;
                                   });
                }
                if (root->right != nullptr) {
                    auto rightpath = pathSum(root->right, sum-root->val);
                    std::transform(rightpath.begin(), rightpath.end(), std::inserter(result, result.end()),
                                   [&](const std::vector<int> & vec){
                                       auto cpy = vec;
                                       cpy.insert(cpy.begin(), root->val);
                                       return cpy;
                                   });
                }
            }
        }
        return result;
    }
};

int main() {
    pNode root = std::make_shared<TreeNode>(5);
    root->left = std::make_shared<TreeNode>(4);
    root->right = std::make_shared<TreeNode>(8);
    root->left->left = std::make_shared<TreeNode>(11);
    root->left->left->left = std::make_shared<TreeNode>(7);
    root->left->left->right = std::make_shared<TreeNode>(2);
    root->right->left = std::make_shared<TreeNode>(13);
    root->right->right = std::make_shared<TreeNode>(4);
    root->right->right->left = std::make_shared<TreeNode>(5);
    root->right->right->right = std::make_shared<TreeNode>(1);
    printBFS(root);

    solution soln;
    auto paths = soln.pathSum(root, 22);
    for (auto& path : paths) {
        std::copy(path.begin(), path.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }
}
