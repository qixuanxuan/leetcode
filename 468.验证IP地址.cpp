class Solution {
public:
    string validIPAddress(string IP) {
		smatch result;
		regex  pattern1("([0-9]+)\.([0-9]+)\.([0-9]+)\.([0-9]+)");
		regex  pattern2("([0-9a-fA-F]+):([0-9a-fA-F]+):([0-9a-fA-F]+):([0-9a-fA-F]+):([0-9a-fA-F]+):([0-9a-fA-F]+):([0-9a-fA-F]+):([0-9a-fA-F]+)");
		if(IP.size()>=40) return "Neither";
		if(regex_match(IP,result,pattern1)){
			string temp;
			for(int i=1;i<5;i++){
				temp = result[i];
				if(temp.size()>3 || stoi(temp)>255 || (temp.size()!=1 && temp[0]=='0')){
					return "Neither";
				}
			}
			return "IPv4";
		}
		else{
			if(regex_match(IP,result,pattern2)){
				for(int i=1;i<=8;i++){
					string temp = result[i];
					if(temp.size()>4) return "Neither";
				}
				return "IPv6";
			}
			else{
				return "Neither";
			}
		}
			
    }
};