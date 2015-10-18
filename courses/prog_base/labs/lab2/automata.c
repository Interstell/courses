int run(int moves[], int movesLen, int res[], int resLen){
	enum op{ POP = 1, CONTINUE, REPEAT, BREAK,EMPTY };
	struct AUTOMATA{
		enum op cmd;
		int move;
	};
	int i, currInput, currState = 0, currColumn, currInputPos = 0,currOutputPos=0;
	int breakFlag = 0, repeatFlag = 0;
	for (i = 0; i < resLen; i++){
		res[i] = 0;
	}
	struct AUTOMATA table[4][4];
	table[0][0].cmd = 12;
	table[0][0].move = 1;
	table[0][1].cmd = CONTINUE;
	table[0][1].move = 1;
	table[0][2].cmd = 13;
	table[0][2].move = 2;
	table[0][3].cmd = BREAK;
	table[0][3].move = EMPTY;
	table[1][0].cmd = EMPTY;
	table[1][0].move = EMPTY;
	table[1][1].cmd = CONTINUE;
	table[1][1].move = 2;
	table[1][2].cmd = 14;
	table[1][2].move = 3;
	table[1][3].cmd = POP;
	table[1][3].move = 2;
	table[2][0].cmd = POP;
	table[2][0].move = 3;
	table[2][1].cmd = CONTINUE;
	table[2][1].move = 3;
	table[2][2].cmd = POP;
	table[2][2].move = 0;
	table[2][3].cmd = 15;
	table[2][3].move = 1;
	table[3][0].cmd = 18;
	table[3][0].move = 0;
	table[3][1].cmd = CONTINUE;
	table[3][1].move = 0;
	table[3][2].cmd = 16;
	table[3][2].move = 2;
	table[3][3].cmd = REPEAT;
	table[3][3].move = 1;
	while (currInputPos < movesLen){
		currInput = moves[currInputPos];
		switch (currInput){
		case 9:
			currColumn = 0;
			break;
		case 17:
			currColumn = 1;
			break;
		case 27:
			currColumn = 2;
			break;
		case 207:
			currColumn = 3;
			break;
		default:
			breakFlag = 1;
			break;
		}
		if (breakFlag){
			break;
		}
		switch (table[currState][currColumn].cmd){
		case POP:
			if (!currOutputPos){
				breakFlag = 1;
			}
			else {
				res[currOutputPos-1] = 0; 
				currOutputPos--;
			}
			break;
		case CONTINUE:
			//WHAT TO DO?
			break;
		case REPEAT:
			repeatFlag = 1;
			break;
		case BREAK:
		case EMPTY:
			breakFlag = 1;
			break;
		default:
			res[currOutputPos] = table[currState][currColumn].cmd;
			currOutputPos++;
			if (currOutputPos == resLen){
				breakFlag = 1;
			}
			break;
		}

		if (!repeatFlag){
			currInputPos++;
		}
		else {
			repeatFlag = 0;
		}
		currState = table[currState][currColumn].move;
		if (breakFlag){
			break;
		}
	} 

	return currOutputPos;
}