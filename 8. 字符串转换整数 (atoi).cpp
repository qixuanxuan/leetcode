class Solution {
public:
	void trimStart(string &s)
    {
        if (!s.empty())
        {
            s.erase(0, s.find_first_not_of(" "));
            //s.erase(s.find_last_not_of(" ") + 1);
        }
    }

  int myAtoi(string str) {
        trimStart(str);
        regex ShuZiRex("^([\\+\\-\\d])(\\d*)");
		smatch ShuZiMatch;
		if(regex_search(str, ShuZiMatch, ShuZiRex)){
			if(ShuZiMatch[1]=="+"){
				int64_t temp = 0;
				string Substr = ShuZiMatch[2];
				for(int i=0;i<Substr.size();i++){
					temp = temp*10 + Substr[i]-'0';
					if(temp>INT_MAX) return INT_MAX;
				}
                return temp;
			}
			else if(ShuZiMatch[1]=="-"){
                int64_t  temp = 0;

				string Substr = ShuZiMatch[2];
				cout<< Substr <<endl;
				for(int i=0;i<Substr.size();i++){
					temp = temp*10 + Substr[i]-'0';
					cout<< temp <<endl;
					if((temp-1)>INT_MAX) return INT_MIN;
				}
                return -temp;


			}
			else{
                string Substr = ShuZiMatch[1];
                int64_t temp = Substr[0]-'0';
                Substr = ShuZiMatch[2];
				for(int i=0;i<Substr.size();i++){
					temp = temp*10 + Substr[i]-'0';
					if(temp>INT_MAX) return INT_MAX;
				}
                return temp;
			}
		}
		else{
			return 0;
		}
    }
};