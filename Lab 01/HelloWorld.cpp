#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>

#define MAXEXAM 5

#define BoxX 12
#define BoxY 6
#define BoxS 54
#define BoxW 10

bool update = true;

using namespace std;

struct NODEMEAN {
	string data;
	NODEMEAN *Next;
};

struct Word {
	string This;
	string Type;
	string *Exam[MAXEXAM];
	NODEMEAN *First;
};

struct NODEWORD {
	Word data;
	NODEWORD *Left;
	NODEWORD *Right;
};

struct HTable 
{
	NODEWORD *Head;
	NODEWORD *Tail;
};

int Address(string Word) 
{
	return Word[0] - 97;
}

bool updated = false;

void Add_Mean_Head(NODEMEAN *&First, string Mean) 
{
	NODEMEAN *p = new NODEMEAN();
	p->data = Mean;
	p->Next = NULL;
	
	if (First == NULL) 
	{
		First = p;
	}
	else 
	{	
		p->Next = First;
		First = p;
	}
}

void AddTail(HTable *&Dict, NODEWORD *p) 
{
	int i = Address(p->data.This);
	
	if (Dict[i].Head == NULL) 
	{
		Dict[i].Head = Dict[i].Tail = p;
	}
	else 
	{
		Dict[i].Tail->Right = p;
		p->Left = Dict[i].Tail;
		Dict[i].Tail = p;
	}
}


NODEWORD* SplitInfo(string Line) 
{
	
	NODEWORD *p = new NODEWORD();
	
	int i, pos;
	i = 0;
	
	string Text = "";
	while (Line[i] != '/') 
	{
		Text += Line[i++];
	}
	p->data.This = Text;
	
	i++;
	Text = "";
	while (Line[i] != '/') 
	{
		Text += Line[i++];
	}
	p->data.Type = Text;
	
	i++;
	p->data.First = NULL;
	Text = "";
	while (Line[i] != '/') 
	{
		Text += Line[i++];
		if (Line[i] == ';') 
		{
			Add_Mean_Head(p->data.First, Text);
			Text = "";
			i++;	
		}
	}
	
	i++;
	Text = ""; 
	pos = 0;
	while (Line[i] != '/') 
	{
		Text += Line[i++];
		if (Line[i] == ';') 
		{ 
			string *tmp = new string;
			*tmp = Text;
			p->data.Exam[pos++] = tmp;
			Text = "";
			i++;
		}
	}	
		
	return p;
}

void ReadFile(HTable *&Dict) {
	ifstream File("Dulieu.txt");
	string Line;
	
	if (File.is_open()) 
	{
		while (getline(File, Line)) 
		{
			NODEWORD *p = SplitInfo(Line);
			AddTail(Dict, p);
		}
		File.close(); 
	}
}

void setcolor(short x) { //Ham thay doi textcolor va backgroundcolor
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, x);
}

void gotoxy(short x, short y) {
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x, y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

void DictBox()
{
	gotoxy(BoxX, BoxY);
	cout << char(201);

	for (int i = 1; i < BoxS + 1; i++)	cout << char(205);

	cout << char(187);

	gotoxy(BoxX, BoxY + 1);
	cout << char(186) << " Search: ";

	gotoxy(BoxX + BoxS + 1, BoxY + 1);
	cout << char(186);

	gotoxy(BoxX, BoxY + 2);
	cout << char(204);

	for (int i = 1; i < BoxS + 1; i++)	cout << char(205);

	cout << char(185);

	for (int i = 0; i < BoxW; i++)
	{
		gotoxy(BoxX, i + BoxY + 3);
		cout << char(186);
		gotoxy(BoxX + BoxS + 1, i + BoxY + 3);
		cout << char(186);
	}

	gotoxy(BoxX, BoxY + BoxW + 3);
	cout << char(200);

	for (int i = 1; i < BoxS + 1; i++)	cout << char(205);

	cout << char(188);
}

void Command_Menu(void)
{
	gotoxy(12, 2);
	cout << "Tab: Add new !";
	gotoxy(12, 3);
	cout << "Esc: Exit !";
}

bool Confirm(int &Input)
{
	system("cls");
	gotoxy(BoxX, BoxY);
	cout << "ESC again to exit the program";
	gotoxy(BoxX, BoxY + 1);
	cout << "Press any key to return to the program";
	Input = getch();
	if (Input != 27)
	{
		if (Input == 224)
			Input = _getch();
		Input = 0;
		return false;
	}
	return true;
	system("cls");
}

NODEWORD *Right(HTable *Dict, NODEWORD *Curr)
{
	if (Curr != NULL)
	{
		NODEWORD *RightWord = Curr->Right;
		if (RightWord != NULL)
		{
			return Curr->Right;
		}
		else
		{
			short x = Address(Curr->data.This);
			if (x < 25)
			{
				while (x != 25)
				{
					if (Dict[x + 1].Head != NULL)
					{
						return Dict[x + 1].Head;
					}
					x++;
				}
				return NULL;
			}

			return NULL;
		}
	}
	return NULL;
}

void DeleteBox(void)
{
	for (int i = 0; i < BoxW; i++)
	{
		gotoxy(BoxX + 1, BoxY + 3 + i);
		for (int j = 0; j < BoxS; j++)	cout << " ";
	}
}

void PrintCurrentLine(NODEWORD *Curr)
{
	if (Curr != NULL)
	{
		//setcolor(115);
		cout << " " << Curr->data.This;	//" " to mau
		//setcolor(65);
		for (int j = Curr->data.This.length(); j < BoxS - 1; j++)	cout << " ";	//To mau phan con lai
	}
}
void PrintSearchLine(NODEWORD *Word)
{
	if (Word != NULL)
		cout << Word->data.This;
}

void DisplayWord(HTable *Dict, NODEWORD *Curr)
{
	DeleteBox();
	
	if (Curr != NULL)
	{
		for (int i = 0; i < BoxW; i++)
		{
			if (i == 0)
			{
				//setcolor(115);
				gotoxy(BoxX + 1, BoxY + 3);
				//setcolor(65);	//Di den dong dau tien 
				PrintCurrentLine(Curr);
			}
			else
			{
				gotoxy(BoxX + 2, BoxY + 3 + i);
				PrintSearchLine(Curr);
			}
			Curr = Right(Dict, Curr);
		}
	}
}

string FixText(string Text)
{
	if (Text != "")
	{
		while (Text[0] == ' ') Text.erase(0, 1);		//Xoa khoang trang
		while (Text[Text.length() - 1] == ' ')	Text.erase(Text.length() - 1, 1);
		if (Text.length() > 3)
		for (int i = 1; i < Text.length() - 2; i++)
		if (Text[i] == ' ' && Text[i + 1] == ' ')
		{
			Text.erase(i, 1);
			i--;
		}

		for (int i = 0; i < Text.length(); i++)			//Chuyen ve chu thuong
		if (Text[i]>'A' && Text[i] < 'Z')
			Text[i] += 32;
		return Text;
	}
	else
		return Text;
}

bool Compare(string Find, NODEWORD *Run)
{
	string x = Find, y = Run->data.This;
	if (x.length() > y.length())
		return false;
	else
	{
		for (int i = 0; i < x.length(); i++)
		if (x[i] != y[i])
			return false;
		return true;
	}
}

NODEWORD *Search(HTable *Dict, string Word)
{
	int x = Address(Word);
	if (x < 0)
		return NULL;
	else
	{
		NODEWORD *Head = Dict[x].Head;
		while (Head != NULL)
		{
			if (Compare(Word, Head))
				return Head;
			Head = Head->Right;
		}
		return NULL;
	}
}

void FindFirst(HTable *Dict, NODEWORD *&Curr)
{
	for (int i = 0; i < 26; i++)
	if (Dict[i].Head != NULL)
	{
		Curr = Dict[i].Head;
		break;
	}
}

NODEWORD *Left(HTable *Dict, NODEWORD *Curr)
{
	if (Curr != NULL)
	{
		NODEWORD *LeftWord = Curr->Left;
		if (LeftWord != NULL)
			return LeftWord;
		else
		{
			int x = Address(Curr->data.This);
			if (x > 0)
			{
				while (x > 0)
				{
					if (Dict[x - 1].Tail != NULL)
						return Dict[x - 1].Tail;
					x--;
				}
				return NULL;
			}
			return NULL;
		}
	}
	return NULL;
}

//        ===========  Detail ==========

short stringlineout(string text, short max)		//Ham tra ve so dong can de xuat chuoi, dong co max ki tu
{
	short n = 1, x = max;
	short i = 0,count;
	string str="";
	while(1)
	{
		while(text[i] != ' ')
		{
			str += text[i];
			i++;
			if( i == text.length())
				break;
		}
		if(str.length() < x)
		{
			x = x - str.length() - 1;
		}
		else if(str.length() == x)
		{
			x = max;
			n++;
		}
		else
		{
			x = max - str.length() - 1;
			if( x < 0)
			{
				x = max;
			}
			n++;
		}
		if( i == text.length())
				break;
		i++;
		str="";
	}
	return n;
}

void stringout(string text, int max)		//ham tu dong xuong dong, dong co max ki tu
{
	int x = max;
	short i = 0,count;
	string str="";
	while(1)
	{
		while(text[i] != ' ')
		{
			str += text[i];
			i++;
			if( i == text.length())
				break;
		}
		if(str.length() < x)
		{
			cout<<str<<" ";
			x = x - str.length() - 1;
		}
		else if(str.length() == x)
		{
			cout<<str;
			x = x - str.length();
		}
		else
		{
			cout<<endl;
			cout<<str<<" ";
			x = max - str.length() - 1;
		}
		if( i == text.length())
				break;
		i++;
		str="";
	}
}

void Detail(NODEWORD *Curr)
{
	int Line = 3;
	gotoxy(BoxX + 2, BoxY + 1);
	cout<<Curr->data.This;
	gotoxy(BoxX + 2, BoxY + 2);
	cout<<Curr->data.Type;
	
	NODEMEAN *Mean = Curr->data.First;
	string Text = "Mean: ";
	while(Mean != NULL)
	{
		Text = Text + Mean->data;
		Mean = Mean->Next;
		if(Mean != NULL)
			Text += "; ";
	}
	gotoxy(BoxX + 2, BoxY + Line);
	Line += stringlineout(Text, BoxS - 2);
	stringout(Text, BoxS - 2);
	
	for(short i=0; i<MAXEXAM; i++)
	{
		if(Curr->data.Exam[i] != NULL)
		{
			gotoxy(BoxX + 2, BoxY + Line);
			Line += stringlineout("Vi du: " + *Curr->data.Exam[i], BoxS - 2);
			stringout("Vi du: " + *Curr->data.Exam[i], BoxS - 2);
		}
		else
			break;
	}
	
	
}

bool ConfirmDel()
{
	system("cls");
	gotoxy(BoxX, BoxY);
	cout<<"Do you really want to delete this word?";
	gotoxy(BoxX, BoxY + 1);
	cout<<"Press enter to confirm deletion!";
	gotoxy(BoxX, BoxY + 2);
	cout<<"Press Esc to return!";
	short Input;
	while( Input != 13 && Input != 27)	Input = getch();
	system("cls");
	if(Input == 13)
		return true;
	return false;
}

short Empty(NODEMEAN *First)
{
	return(First == NULL);
}

void DelFirst(NODEMEAN *&First)
{
	NODEMEAN *p;
	if(Empty(First))
	{
		return;
	}
	p = First;
	First = p->Next;
	delete p;
}

void DeteleWord(HTable *&Dict, NODEWORD *&Del)
{
	if(Del != NULL)
	{
		int x = Address(Del->data.This);
		NODEWORD *Head = Dict[x].Head, *Tail = Dict[x].Tail;
		if(Head->data.This == Del->data.This)
		{
			if(Head->Right == NULL)
			{
				Head = Tail = NULL;
			}
			else
			{
				Head = Head->Right;
				Head->Left = NULL;
			}
		}
		else if(Del->data.This == Tail->data.This)
		{
			Tail = Tail->Left;
			Tail->Right = NULL;
		}
		else
		{
			NODEWORD *LeftWord = Del->Left, *RightWord = Del->Right;
			LeftWord->Right = RightWord;
			RightWord->Left = LeftWord;
			Del->Left = Del->Right = NULL;
		}
		NODEMEAN *Mean = Del->data.First;
		while(Mean != NULL)
		{
			DelFirst(Mean);
		}
		delete Del;
	}
}

void DeleteCurrent(HTable *&Dict, NODEWORD *&Curr)
{
	if(Curr != NULL)
	{
		NODEWORD *LeftWord =Left(Dict,Curr), *RightWord = Right(Dict,Curr);
		if(LeftWord == NULL && RightWord == NULL )
		{
			Curr = NULL;
		}
		else
		{
			if(LeftWord == NULL)
			{
				Curr = RightWord;
			}
			else
			{
				Curr = LeftWord;
			}
		}
		
	}
}

short CountMean(NODEWORD *Curr)
{
	NODEMEAN *First = Curr->data.First;
	int x=0;
	while(First != NULL)
	{
		x++;
		First = First->Next;
	}
	return x;
}

void Edit(HTable *&Dict, NODEWORD *&Curr)
{
	int x = 0;
	x = x + CountMean(Curr) + 8;
	string Field[x];
	Field[0] = Curr->data.This;
	Field[1] = Curr->data.Type;
	NODEMEAN *First = Curr->data.First;
	for(int i= 0; i< CountMean(Curr); i++)
	{
		Field[i+2] = First->data;
		First = First->Next;
	}
	Field[x-5] = "";
	short i = 0;
	while(Curr->data.Exam != NULL)
	{
		Field[x - 5 + i] = *Curr->data.Exam[i];
		i++;
	}
	if(i < 4)
		for( ; i < 5; i++)
		{
			Field[i] = "";
		}
	
}


short checkerror(HTable *Dict, string text, short k)
{
	text = FixText(text);
	if(k==1)
	{
		if(text == "") {
			return 1;
		}
		else if(Search(Dict, text)!=NULL)
			{
				if(Search(Dict, text)->data.This.length() == text.length()) {
					return 2;
				}
			}
	}
	if(k==2)
	{
		if(text == ""){
			return 3;
		}
	}
	if(k==3)
	{
		if(text == ""){
			return 4;
		}
	}
	return 0;
}


void delerror()
{
	gotoxy(18, BoxY + BoxW + 2);
	for(int i = 0; i < 40; i++) cout << " ";
}

void printerror(short k)
{
	if(k==1)
	{
		gotoxy(18, BoxY + BoxW + 2); cout << "ERROR: " <<"Vui long nhap tu!";
	}
	else if(k==2)
	{
		gotoxy(18, BoxY + BoxW + 2); cout << "ERROR: " <<"Tu nay da co trong tu dien, xin kiem tra lai!";
	}
	else if(k==3)
	{
		gotoxy(18, BoxY + BoxW + 2); cout << "ERROR: " <<"Vui long nhap loai tu!";	
	}
	else if(k==4)
	{
		gotoxy(18, BoxY + BoxW + 2); cout << "ERROR: " << "Vui long nhap nghia cua tu!";
	}
}

void printtextfield(string t, short k){
	gotoxy(BoxX + 12, BoxY + k);
	if(t.length() >= BoxS - 17) {
		for(int i = 0; i < BoxS - 17; i++) cout << t[i];
	}
	else if(t.length() < BoxS - 17) {
		cout << t;
		for(int i = 0; i < BoxS - 12 - t.length(); i++) cout << " ";
	}
}

void Addword(HTable *&Dict){
	system("cls");
	string text;
	string field[8] = {""};
		int k = 1;
		int Input = 0;
		text = field[k-1];
		int dem = field[k-1].length();
			for(int k =1 ; k<9; k++)
	{
		gotoxy(BoxX + 5 , BoxY +k);
		cout<< "  Them:";
	}
		while(1)
		{
			gotoxy(BoxX + 12, BoxY + k);
			if (dem < BoxS - 12)	cout << text;
			else for (int i = dem - (BoxS - 12); i< dem; i++)	cout << text[i];
			
			if(dem < BoxS - 12) gotoxy(BoxX + 12 + dem, BoxY + k); //Xuat ra vi tri con tro khi khung nhap chua bi tran
			else gotoxy(BoxX + BoxS, BoxY + k);
			
			Input = getch();
			switch(Input)
			{
				case 13: //enter
				{
					if(checkerror(Dict, text, k) != 0)
					{
						Input = 0;
						printerror(checkerror(Dict, text, k));
					}
					else
					{
						text = FixText(text);
						//printtextfield(text, k);
						field[k-1] = text;
						delerror();
						if(k>8) break;
						else k++;
						dem = field[k-1].length();
						text = field[k-1];	
					}
					break;
				}
				
			case 224:
				{
					Input = getch();
					if(Input == 72) //up
					{
						if(checkerror(Dict, text, k) != 0)
						{
							Input = 0;
							printerror(checkerror(Dict, text, k));
						}
						else
						{
							text = FixText(text);
							field[k-1] = text;
							delerror();
							if(k>1) k--;
							dem = field[k-1].length();
							text = field[k-1];	
						}
						//break;
					}
					else if(Input == 80) //down
					{
						if(checkerror(Dict, text, k) != 0)
						{
							Input = 0;
							printerror(checkerror(Dict, text, k));
						}
						else
						{
							text = FixText(text);
							//printtextfield(text, k);
							field[k-1] = text;
							delerror();
							if(k<9) k++;
							dem = field[k-1].length();
							text = field[k-1];	
						}
						//break;
					}
					break;
				}
			case 8: //backspace
				{
					if(dem > 0)
					{
						dem--;
						text = text.substr(0, text.size() - 1);
						gotoxy(BoxX + 12, BoxY + k );
						if (dem < BoxS - 12)
						{
							cout << text;
							for (int i = BoxX + 12; i < BoxS; i++)	cout << " ";
						}
						else
						{
							for (int i = dem - 5; i<dem; i++)	cout << text[i];
						}
					}
					break;
				}
			case 27: //esc
				{
					if(Confirm(Input))
						break;
					else
						system("cls");
					break;
				}
			default: //alphabet
				{
					if((Input < 123 && Input > 96) || (Input < 91 && Input > 64) || Input == 32 || Input == 39 || Input == 45)
					{
						text += char(Input);
						dem++;
//						gotoxy(BoxX + 10, BoxY + k);
//						if (dem < BoxS - 12)
//						{
//							cout << text;
//							for (int i = 0; i< BoxS - 12 - dem; i++) cout << " ";
//						}
//						else
//						{
//							for (int i = dem - (BoxS - 12); i<dem; i++)	cout << text[i];
//						}
					}
				}
				
			}
		}
		NODEWORD *Tu = new NODEWORD;
		Tu->data.This = field[0];
		Tu->data.Type = field[1];
		string t = field[2];
		string tmp = "";
		for(int i =0; i<=field[2].length(); i++)
		{
			tmp += t[i];
			if(t[i] = ';')
			{
				Add_Mean_Head(Tu->data.First, tmp);
				tmp = "";
			}
		}
		*Tu->data.Exam[0] = field[3];
		*Tu->data.Exam[1] = field[4];
		*Tu->data.Exam[2] = field[5];
		*Tu->data.Exam[3] = field[6];
		*Tu->data.Exam[4] = field[7];		
}

//		  =========== End Detail =============

void SearchBox(HTable *&Dict, NODEWORD *&Curr)
{
	int Input = 0;
	bool changed = false;
	string Text = "";
	int Count = 0;
	while(1)
	{
		DictBox();
		Command_Menu();
		
		gotoxy(BoxX + 12, BoxY + 1);
		
		if (Count < BoxS - 12)	cout << Text;
		else	for (int i = Count - (BoxS - 12); i< Count; i++)	cout << Text[i];
		
		if (changed)
		{
			if (FixText(Text) != "")
				Curr = Search(Dict, FixText(Text));
			else	FindFirst(Dict, Curr);
		}
		
		
		
		DisplayWord(Dict,Curr);
		
		if (Count < BoxS - 12)	gotoxy(BoxX + 12 + Count, BoxY + 1);
		else gotoxy(BoxX + BoxS, BoxY + 1);
			
		Input = getch();
		switch(Input)
		{
			case 13:	//Enter
			{
				while(Input != 27)
				{
					system("cls");
					Detail(Curr);
					Input = getch();
					switch(Input)
					{
						case 27:	//esc
						{
							break;
						}
						
						case 8:		//backspace
						{
							break;
						}
						
						case 83:	//delete
						{
							if(ConfirmDel())
							{
								DeleteCurrent(Dict,Curr);
								update = true;
								Input = 27;
							}
							break;
						}
					}
				}
				break;
			}
		
			case 8:		//Backspace
			{
				if (Count>0)
				{
					Count--;
					Text = Text.substr(0, Text.size() - 1);
					gotoxy(BoxX + 12, BoxY + 1);
					if (Count < BoxS - 12)
					{
						cout << Text;
						for (int i = BoxX + 11; i < BoxS; i++)	cout << " ";
					}
					else
					{
						for (int i = Count - 5; i<Count; i++)	cout << Text[i];
					}
					changed = true;
				}
				break;
			}
		
			case 9:		//Tab
			{
			
				break;
			}
		
			case 224:	//Up Down
			{
				Input = getch();
				
				if (Input == 72)
				{
					
					if (Left(Dict, Curr) != NULL ){
						Curr = Left(Dict, Curr);
					}
				}
				else if (Input == 80)
				{
					if (Right(Dict, Curr) != NULL)
					{
						Curr = Right(Dict, Curr);
					}
				}
				changed = false;
				break;
			}
		
			case 27:	//Esc
			{
				if(Confirm(Input))
					return;
				else
					system("cls");
				break;
			}
		
			default:
			{
				if((Input < 123 && Input > 96) || (Input < 91 && Input > 64) || Input == 32 || Input == 39 || Input == 45)
				{
					changed = true;
					Text += char(Input);
					Count++;
					gotoxy(BoxX + 12, BoxY + 1);
					if (Count < BoxS - 12)
					{
						cout << Text;
						for (int i = 0; i< BoxS - 11 - Count; i++)	cout << " ";
					}
					else
					{
						for (int i = Count - (BoxS - 12); i<Count; i++)	cout << Text[i];
					}
				}
			}
		
		}
	}
	
}


int main() 
{
	HTable *Dict = new HTable[26];
	
	for (int i = 0; i < 26; i++) 
	{
		Dict[i].Head = NULL;
		Dict[i].Tail = NULL;
	}
	ReadFile(Dict);
	NODEWORD *Curr = NULL;
//	FindFirst(Dict,Curr);
//	//setcolor(115);
//	SearchBox(Dict,Curr);
//	Addword(Dict);
	for(int k =1 ; k<9; k++)
	{
		gotoxy(BoxX , BoxY +k);
		cout<< "  Them:";
	}
	Addword(Dict);
	return 0;
}
