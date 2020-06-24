class Solution {
public:
    bool isSymmetric(TreeNode* root){
		if (root==NULL) return true;
		vector<TreeNode*> p;
		TreeNode* left;
		TreeNode* right;
		p.push_back(root->left);
		p.push_back(root->right);
		while(!p.empty()){
			left = p.front();
			right = p.back();
			if(left==NULL || right==NULL){
				if(left!=right) return false;
				p.erase(p.begin());
				p.erase(p.end()-1);
			}
			else{
				if(left->val != right->val) return false;
				p.erase(p.begin());
				p.erase(p.end()-1);
				p.insert(p.begin(),left->right);
				p.insert(p.end(),right->left);
				p.insert(p.begin(),left->left);
				p.insert(p.end(),right->right);
			}
		}
		return true;
	}

};

//递归法
class Solution {
public:
    bool check(TreeNode *p, TreeNode *q) {
        if (!p && !q) return true;// 两者都为NULL
        if (!p || !q) return false;// 有一个为NULL
		//两者都不为NULL ，他们的孩子必须是对称的
        return p->val == q->val && check(p->left, q->right) && check(p->right, q->left);
    }

    bool isSymmetric(TreeNode* root) {
        return check(root, root);
    }
};