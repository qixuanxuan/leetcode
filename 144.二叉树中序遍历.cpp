/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> TreeNodeStack;
        TreeNode* temp;
        if(root==nullptr) return result;
        TreeNodeStack.push(root);
        while(!TreeNodeStack.empty()){
            temp = TreeNodeStack.top();
            TreeNodeStack.pop();
            if(temp!=nullptr){
                if(temp->right) TreeNodeStack.push(temp->right);
                if(temp->left) TreeNodeStack.push(temp->left);
                TreeNodeStack.push(temp);
                TreeNodeStack.push(nullptr);
            }
            else{
                result.push_back(TreeNodeStack.top()->val);
                TreeNodeStack.pop();
            }

        }
        return result;
    }

};
