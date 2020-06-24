class Solution {
public:
    int romanToInt(string s) {
		unordered_map<char,int> p;
		p['I'] = 1;
		p['V'] = 5;
		p['X'] = 10;
		p['L'] = 50;
		p['C'] = 100;
		p['D'] = 500;
		p['M'] = 1000;
		int len = s.size();
		int result = 0;
		int i=0;
		while(i<len-1){
			if(s[i]=='I'){
				if(s[i+1]=='V'){
					i++;
					result += 4; 
				}
				else if(s[i+1]=='X'){
					i++;
					result += 9; 
				}
				else{
					result += 1;
				}
			}
			else if(s[i]=='X'){
				if(s[i+1]=='L'){
					i++;
					result += 40; 
				}
				else if(s[i+1]=='C'){
					i++;
					result += 90; 
				}
				else{
					result += 10;
				}
			}
			else if(s[i]=='C'){
				if(s[i+1]=='D'){
					i++;
					result += 400; 
				}
				else if(s[i+1]=='M'){
					i++;
					result += 900; 
				}
				else{
					result += 100;
				}
			}
			else{
				result += p[s[i]];
			}
		i++;	
		}
		result += p[s[i]];
		return result;
    }
};