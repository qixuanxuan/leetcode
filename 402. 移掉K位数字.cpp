class Solution {

public:
    string removeKdigits(string num, int k) {
		string p;
		for(auto &s:num){
			while(!p.empty() && k>0 && (s-'0')<(p.back()-'0')){
				p.erase(p.end()-1);
				k -= 1;

			}
			p.push_back(s);
		}
		//规则处理后，k没有使用结束
		while(!p.empty() && k>0){
			p.erase(p.end()-1);
			k--;
		}
		//消除前面多余的零
		while(p.front()=='0') p.erase(p.begin());
		if(p.empty()) return "0";
        return p;
    }
};