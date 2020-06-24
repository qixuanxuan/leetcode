class Solution {
public:
	string StringMultiplyN(string p,int N){
		string result;
		while(N>0){
			result = result + p;
			N--;
		}
		return result;
	}
    string intToRoman(int num) {
		int EndNum;
		string result,temp;
		unordered_map<int,string> p;
		p[1] = "I";
		p[4] = "IV";
		p[5] = "V";
		p[9] = "IX";
		p[10] = "X";
		p[40] = "XL";
		p[50] = "L";
		p[90] = "XC";
		p[100] = "C";
		p[400] = "CD";
		p[500] = "D";
		p[900] = "CM";
		p[1000] = "M";
		int base = 1;
		string StringBase;
        while(num!=0){
			EndNum = num%10;
			if(EndNum<4 && EndNum>0){
				StringBase = p[base];
				temp = StringMultiplyN(StringBase,EndNum);
			}
			else if(EndNum==4 || EndNum==5 || EndNum==9){
				temp = p[EndNum*base];
			}
			else if(EndNum>5 && EndNum<9){
				temp = p[5*base];
				StringBase = p[base];
				temp += StringMultiplyN(StringBase,EndNum-5);
			}
			else{
				
			}
			base = base*10;
			num = num/10;
			result = temp + result;
			temp.clear();
		}
		return result;
    }
};