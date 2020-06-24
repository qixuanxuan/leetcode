/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string res;
        dfs_s(root, res);
        return res;
    }

    // 前序遍历序列转化为字符串
    void dfs_s(TreeNode* root, string& res) {
        if (!root) {
            res += "null ";
            return;
        }
        res += to_string(root->val) + ' ';
        dfs_s(root->left, res);
        dfs_s(root->right, res);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        // 开始遍历索引
        int u = 0;
        return dfs_d(data, u);
    }

    TreeNode* dfs_d(string& data, int& u) {
        if (u >= data.size()) return NULL;
        if (data[u] == 'n') {
            u = u + 5;
            return NULL;
        }
        int val = 0, sign = 1;
        if (data[u] == '-') sign = -1, u ++ ;
        while(data[u] != ' '){val = val * 10 + data[u] - '0'; u++;}
        val *= sign;
        u = u + 1 ;

        auto root = new TreeNode(val);
        root->left = dfs_d(data, u);
        root->right = dfs_d(data, u);

        return root;
    }
};


// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
