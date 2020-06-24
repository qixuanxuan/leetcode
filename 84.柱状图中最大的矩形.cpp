class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
		vector<int> Left(heights.size());
		vector<int> Right(heights.size());
        stack<int> Temp;
		int result = 0;
		for(int i=0;i<heights.size();++i){
			while(!Temp.empty() && heights[i]<=heights[Temp.top()]){
				Temp.pop();
			}
			Left[i] = Temp.empty() ? -1:Temp.top();
			Temp.push(i);
		}
		Temp = stack<int>();
		for(int i=heights.size()-1;i>=0;--i){
			while(!Temp.empty() && heights[i]<=heights[Temp.top()]){
				Temp.pop();
			}
			Right[i] = Temp.empty() ? heights.size():Temp.top();
			Temp.push(i);
		}
		for(int i=0;i<heights.size();i++){
			if(heights[i]*(Right[i]-Left[i]-1)>result){
				result  = heights[i]*(Right[i]-Left[i]-1);
			}  
		}
		return result;
    }
};