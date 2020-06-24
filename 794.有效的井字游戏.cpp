class Solution {
public:
	bool CheckLine(vector<string> & board, const char & c){
		for(int i=0;i<3;i++){
			if(board[i][0]==c && board[i][1]==c && board[i][2]==c){
				return true;
			}
			if(board[0][i]==c && board[1][i]==c && board[2][i]==c){
				return true;
			}
		}
		if(board[0][0]==c && board[1][1]==c && board[2][2]==c){
			return true;
		}
		if(board[0][2]==c && board[1][1]==c && board[2][0]==c){
			return true;
		}
		return false;
	}
	int CountXO(vector<string>& board){
		int count = 0;
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				if(board[i][j]=='X') count++;
				if(board[i][j]=='O') count--;
			}
		}
		return count;
	}

    bool validTicTacToe(vector<string>& board) {
		int count = CountXO(board);

		if(count<0 || count>1) return false;
		bool WinX = CheckLine(board,'X'); 
		bool WinO = CheckLine(board,'O');
		if(WinX && !WinO) return 1==count; 
		else if(WinO && !WinX) return 0==count;
		else if(WinO && WinX)  return false;
		else return true;
		
    }
};