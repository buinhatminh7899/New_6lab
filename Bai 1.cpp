#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>

#define MAXEXAM 5

#define BoxX 5
#define BoxY 3
#define BoxS 25
#define BoxS1 108
#define BoxXE 78
#define BoxYE 38
#define BoxW 29

bool update = true;

using namespace std;

void setcolor(short x) 
{
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, x);
}

struct NODEMEAN 
{
	string data;
	NODEMEAN *Next;
};

struct Word 
{
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
	for (int i = 1; i < BoxS1 + 2; i++)	cout << char(205);
	cout << char(187);
	gotoxy(BoxX + BoxS + 1, BoxY);
	cout << char(203);

	gotoxy(BoxX, BoxY + 1);
	cout << char(186) << " Search: ";
	gotoxy(BoxX + BoxS + 38, BoxY + 1);
	cout << "INFORMATION";

	gotoxy(BoxX + BoxS + 1, BoxY + 1);
	cout << char(186);
	gotoxy(BoxX + BoxS1 + 2, BoxY + 1);
	cout << char(186);

	gotoxy(BoxX, BoxY + 2);
	cout << char(204);
	for (int i = 1; i < BoxS1 + 2; i++)	cout << char(205);
	cout << char(185);
	gotoxy(BoxX + BoxS + 1, BoxY + 2);
	cout << char(206);

	for (int i = 0; i < BoxW; i++)
	{
		gotoxy(BoxX, i + BoxY + 3);
		cout << char(186);
		gotoxy(BoxX + BoxS + 1, i + BoxY + 3);
		cout << char(186);
		gotoxy(BoxX + BoxS1 + 2, i + BoxY + 3);
		cout << char(186);
	}

	gotoxy(BoxX, BoxY + BoxW + 3);
	cout << char(204);
	for (int i = 1; i < BoxS1 + 2; i++)	cout << char(205);
	cout << char(185);
	gotoxy(BoxX + BoxS + 1, BoxY + BoxW + 3);
	cout << char(202);
	
	gotoxy(BoxX, BoxY + BoxW + 4);
	cout << char(186);
	gotoxy(BoxX + BoxS1 + 2, BoxY + BoxW + 4);
	cout << char(186);
	
	gotoxy(BoxX, BoxY + BoxW + 5);
	cout << char(200);
	for (int i = 1; i < BoxS1 + 2; i++)	cout << char(205);
	cout << char(188);
}

void Del_Menu(void)
{
	gotoxy(BoxX + 1, BoxY + BoxW + 4);
	for(int i = 0; i <=  BoxS1; i++)
		cout<<" ";
}

void Command_Menu(void)
{
	Del_Menu();
	gotoxy(BoxX, BoxY + BoxW + 4);
	cout << "\t\tTab: Add new !\t\tEsc: Exit ! \t\tEnter: Edit !\t\tDelete: Delete this word!";
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
		setcolor(161);
		cout << " " << Curr->data.This;	//" " to mau
		for (int j = Curr->data.This.length(); j < BoxS - 1; j++)	cout << " ";	//To mau phan con lai
		setcolor(115);
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
				gotoxy(BoxX + 1, BoxY + 3 + i);	//Di den dong dau tien 
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
			if (Text[i] >= 'A' && Text[i] <= 'Z')
				Text[i] += 32;
		return Text;
	}
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

void stringout(string text, int max, int Line)		//ham tu dong xuong dong, dong co max ki tu
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
			x = max;
			gotoxy(BoxX + BoxS + 8, ++Line);
		}
		else
		{
			gotoxy(BoxX + BoxS + 8, ++Line);
			cout<<str<<" ";
			x = max - str.length() - 1;
		}
		if( i == text.length())
				break;
		i++;
		str="";
	}
}

void DelDetail()
{
	for(short i = 0; i < BoxW; i++)
	{
		gotoxy(BoxX + BoxS + 2, BoxY + 3 + i);
		for(short j = 0; j < BoxS1 - BoxS; j++)
			cout<<" ";
	}
		
}

string Uppercase(string Text)
{
	for(int i = 0; i < Text.length(); i++)
		Text[i]-=32;
	return Text;
}

void Detail(NODEWORD *Curr)
{
	DelDetail();
	int Line = 5;
	short k = 0;
	gotoxy(BoxX + BoxS + 3, BoxY + 4);
	cout<<Uppercase(Curr->data.Type);
	
	NODEMEAN *Mean = Curr->data.First;
	string Text = " => ";
	while(Mean != NULL)
	{
		gotoxy(BoxX + BoxS + 3, BoxY + Line + k);
		Text = Text + Mean->data;
		Mean = Mean->Next;
		cout<<Text;
		k++;
		Text = " => ";
	}
	
	for(short i=0; i<MAXEXAM; i++)
	{
		if(Curr->data.Exam[i] != NULL)
		{
			gotoxy(BoxX + BoxS + 3, BoxY + Line + k);
			Line += stringlineout("   > " + *Curr->data.Exam[i], BoxS1 - BoxS - 7);
			stringout("   > " + *Curr->data.Exam[i], BoxS1 - BoxS - 3, BoxY + Line + k - 2);
		}
	}
	
	
}

bool ConfirmDel(NODEWORD *Curr)
{
	system("cls");
	gotoxy(BoxX, BoxY);
	cout<<"Do you really want to delete the word "<< Curr->data.This << " ?";
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

void DeleteWord(HTable *&Dict, NODEWORD *&Del)
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
		for(int i = 0; i < MAXEXAM; i++)
		{
			if(Del->data.Exam[i] != NULL)
			{
				Del->data.Exam[i] = NULL;
				delete Del->data.Exam[i];
			}
		}
		Del = NULL;
		delete Del;
		Dict[x].Head = Head;
		Dict[x].Tail = Tail;
		updated = true;
	}
}

void DeleteCurrent(HTable *&Dict, NODEWORD *&Curr)
{
	if(Curr != NULL)
	{
		NODEWORD *LeftWord =Left(Dict,Curr), *RightWord = Right(Dict,Curr), *tmp = Curr;
		if(LeftWord == NULL && RightWord == NULL )		//Just one
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
		DeleteWord(Dict, tmp);
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

short CountExam(NODEWORD *Curr)
{
	short x = 0;
	for(short i = 0; i < 5; i++)
	{
		if(Curr->data.Exam[i] != NULL)
			x++;
	}
	return x;
}

void Edit_Menu(void)
{
	Del_Menu();
	gotoxy(BoxX + 1, BoxY + BoxW + 4);
	cout<<"\t"<<char(94)<<": Up\t"<<char(118)<<": Down    Backspace: Edit !\tInsert: Add Exam or Mean !\tDelete: Delete!   Esc: Return!";
}

void EditBox(void)
{
	gotoxy(BoxXE,BoxYE);
	cout<<char(201);
	for(int i = 1; i <  BoxS1 - BoxXE + 7; i++)
		cout<<char(205);
	cout<<char(187);
	
	for(int i = 1; i <= 3; i++)
	{
		gotoxy(BoxXE, BoxYE + i);
		cout<<char(186);
		gotoxy(BoxS1 + 7, BoxYE + i);
		cout<<char(186);
	}
	
	gotoxy(BoxXE, BoxYE + 4);
	cout<<char(200);
	for(int i = 1; i < BoxS1 - BoxXE + 7; i++)
		cout<<char(205);
	cout<<char(188);
}

void Del_EditBox(void)
{
	for(int i = 0; i < 5; i++)
	{
		gotoxy(BoxXE, BoxYE + i);
		for(int i = 0; i < BoxS1 - BoxXE + 8; i++)
			cout<<" ";
	}
}

void Confirm_Edit_Menu(void)
{
	gotoxy(BoxX, BoxY + BoxW + 4);
	cout<<"\t\t\t\tEnter: Save changes !\t\t\tEsc: Return !";
}

void Add_Menu(void)
{
	Del_Menu();
	gotoxy(BoxX, BoxY + BoxW + 4);
	cout<<"\t\t\t1.Add meaning !\t\t\t2.Add examples!";
}

void Delete_mean_info(NODEMEAN *&First, string Text)
{
	NODEMEAN *p = First;
	if( First == NULL )
		return;
	if( First->data == Text)
	{
		First = p->Next;
		delete p;
		return;
	}
	NODEMEAN *q;
	for( p = First ; p->Next != NULL && p->Next->data != Text; p = p->Next)
	{
		if( p->Next != NULL )
		{
			q = p->Next;
			p->Next = q->Next;
			delete q;
			return;
		}
	}
	return;
}

void Edit(HTable *&Dict, NODEWORD *&Curr)
{
	bool changed = false;
	Del_Menu();
	Edit_Menu();
	short x = 0,i,dem,tmp = 0;
	string Text = "";
	short Input = 0;
	short Line = 4;
	while(Input != 27)
	{
		x = CountMean(Curr) + 1 + CountExam(Curr);
		if( changed )
		{
			Detail(Curr);
			changed = false;
		}
		if(Line == 4)
		{
			Text = Curr->data.Type;
			gotoxy(BoxX + BoxS + 3 + Curr->data.Type.length(), BoxY + Line);
		}
		else if(Line < x + 4 && Line > x + 3 - CountExam(Curr))
			{
				tmp = x - (Line - 3);
				Text = *Curr->data.Exam[CountExam(Curr) - tmp - 1];
				gotoxy(BoxX + BoxS + 8 + Text.length(), BoxY + Line);
			}
		else
		{
			NODEMEAN *First = Curr->data.First;
			short k = 0;
			while(k < CountMean(Curr) && k != Line - 5)
			{
				First = First->Next;
				k++;
			}
			Text = "";
			Text = First->data;
			gotoxy(BoxX + BoxS + 7 + Text.length(), BoxY + Line);
		}	
			
			
			
		Input = getch();
		switch(Input)
		{
			case 224:	//Up Down
			{
				Input = getch();
				if (Input == 72 && Line > 4)	Line--;
				else if (Input == 80 && Line < x + 3) 	Line++;
				
				
				if( Input == 83)	//Delete
				{
					if(Line == 4)
					{
						EditBox();
						gotoxy(BoxXE + 2, BoxYE + 2);
						cout<<"YOU CAN DELETE TYPE OF THE WORD !";
						gotoxy(BoxXE + 2, BoxYE + 3);
						cout<<"Press any key to continue !";
						getch();
						Del_EditBox();
					}
					else if(Line < x + 4 && Line > x + 3 - CountExam(Curr))
					{
						tmp = x - (Line - 3);
						Curr->data.Exam[4 - tmp] = NULL;
						delete Curr->data.Exam[4 - tmp];
						Line = 4;
						changed = true;
						break;					
					}
					else
					{
						if( CountMean(Curr) > 1)
						{
							NODEMEAN *First = Curr->data.First;
							short k = 0;
							while(k < CountMean(Curr) && k != Line - 5)
							{
								First = First->Next;
								k++;
							}
							changed = true;
							update = true;	
						}
						else
						{
							EditBox();
							gotoxy(BoxXE + 2, BoxYE + 1);
							cout<<"The word must have at least one";
							gotoxy(BoxXE + 2, BoxYE + 2);
							cout<<"maeaning !";
							gotoxy(BoxXE + 2, BoxYE + 3);
							cout<<"Press any key to continue !";
							getch();
							Del_EditBox();
						}			
					}
				}
				if( Input == 82)	//Insert
				{
					short tmp;
					Add_Menu();
					tmp = getch();
					switch (tmp)
					{
						case 49:		//mean
						{
							EditBox();
							gotoxy(BoxXE + 2, BoxYE + 2);
							string Mean = "";
							getline(cin,Mean);
							Add_Mean_Head(Curr->data.First,Mean);
							updated = true;
							changed = true;
							Del_EditBox();
							break;
						}
						
						case 50:		//exam
						{
							EditBox();
							if(CountExam(Curr) >= 5)
							{
								gotoxy(BoxXE + 2, BoxYE + 1);
								cout<<"The examples is full !";
								gotoxy(BoxXE + 2, BoxYE + 2);
								cout<<"Press any key to continue !";
								getch();
								Del_EditBox();
							}
							else
							{
								string Exam = "";
								EditBox();
								gotoxy(BoxXE + 2, BoxYE + 2);
								getline(cin, Exam);
								string *tmp = new string;
								*tmp = Exam;
								for(int i = 0; i < MAXEXAM; i++)
								{
									if(Curr->data.Exam[i] == NULL)
									{
										Curr->data.Exam[i] = tmp;
										break;
									}
								}
								updated = true;
								changed = true;
								Del_EditBox();
							}
							break;
						}
					}
					Edit_Menu();
				}
				break;
			}
			
			case 8:
			{
				Del_Menu();
				Confirm_Edit_Menu();
				short input = 0;
				while( input != 27 && input != 13)
				{
					EditBox();
					gotoxy(BoxXE + 2, BoxYE + 2);
					
					if (Text.length() < BoxS1 - BoxXE + 5)
					{
							cout << Text;
							for(int i = Text.length(); i < BoxS1 - BoxXE + 4; i++)	cout<<" ";
					}
					else	for (int i = Text.length() - (BoxS1 - BoxXE + 5) + 1; i< Text.length(); i++)	cout << Text[i];
					
					if (Text.length() < BoxS1 - BoxXE + 4)	gotoxy(BoxXE + Text.length() + 2, BoxYE + 2);
					else gotoxy(BoxS1 + 6, BoxYE + 2);
					
					input = getch();cout<<input;
					switch( input )
					{
						case 8:		//Backspace
						{
							if (Text.length() > 0)
							{
								Text = Text.substr(0, Text.size() - 1);
							}
							break;
						}
						
						case 13:
						{
							break;
						}
						
						default:
						{
							if((input < 123 && input > 96) || (input < 91 && input > 64) || input == 39 || input == 45 || input == 32 || input == 63)
							{
								Text += char(input);
							}
						}
					}
				}
				
				if( input == 13)
				{
					changed = true;
					if(Line == 4)
					{
						Curr->data.Type = Text;
					}
					else if(Line < x + 4 && Line > x + 3 - CountExam(Curr))
						{
							tmp = x - (Line - 3);
							*Curr->data.Exam[CountExam(Curr) - tmp - 1] = Text;
						}
					else
					{
						NODEMEAN *First = Curr->data.First;
						short k = 0;
						while(k < CountMean(Curr) && k != Line - 5)
						{
							First = First->Next;
							k++;
						}
						First->data = Text;
					}
					updated = true;
				}
				Del_EditBox();
				Edit_Menu();
				break;
			}
		}		
	}
	Del_Menu();
	Command_Menu();

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
	if(k==4)
	{
		if(text == ""){
			return 5;
		}
	}
	return 0;
}


void delerror()
{
	gotoxy(BoxX + 15, BoxY + 15);
	for(int i=0; i<40; i++) cout<<" ";
}

void printerror(short k)
{
	if(k==1)
	{
		gotoxy(BoxX + 30, BoxY+BoxW + 4); cout << "ERROR: " <<"Vui long nhap tu!";
	}
	else if(k==2)
	{
		gotoxy(BoxX + 30, BoxY +BoxW + 4); cout << "ERROR: " <<"Tu nay da co trong tu dien, xin kiem tra lai!";
	}
	else if(k==3)
	{
		gotoxy(BoxX + 30, BoxY +BoxW+ 4); cout << "ERROR: " <<"Vui long nhap loai tu!";	
	}
	else if(k==4)
	{
		gotoxy(BoxX + 30, BoxY + BoxW+4); cout << "ERROR: " << "Vui long nhap nghia cua tu!";
	}
	else if(k==5)
	{
		gotoxy(BoxX + 30, BoxY + BoxW+4); cout << "ERROR: " << "Vui long nhap vi du cho tu!";
	}
}

void printtextfield(string t, short k){
	gotoxy(BoxX + BoxS + 11, BoxY + 2+k);
	if(t.length() > BoxS1-35) {
		for (int i = t.length() - (BoxS1-35); i< t.length(); i++)	cout << t[i];
	}
	else if(t.length() < BoxS1-35) {
		cout << t;
		for(int i = 0; i < BoxS1-35 - t.length(); i++) cout << " ";
	}
}


void Add_Word_In_HTable(NODEWORD *&Head, NODEWORD *&Tail, NODEWORD *&NewWord)
{
	NODEWORD *run = Head;
	if(Head == NULL)
	{
		Head = Tail = NewWord;
	}
	else if (run == Head && run->data.This.compare(NewWord->data.This) > 0) // them vao dau
		{
			NewWord->Left = run;
			run->Right = NewWord;
			Head = NewWord;
		}
	else while(run != NULL)
		{
			if(run->data.This.compare(NewWord->data.This) < 0) //so sanh tung kí tu cua tu
			{
				if(run->Right == NULL) // them vao cuoi
				{
					run->Right = NewWord;
					NewWord->Left = run;
					Tail = NewWord;
					break;
				}
				else if(run->Right->data.This.compare(NewWord->data.This) > 0) // them vao giua sau run
				{
					NODEWORD *tmp = run->Right;
					tmp->Left = NewWord;
					NewWord->Right = tmp;
					NewWord->Left = run;
					run->Right = NewWord;
					break; 
				}
			}
			run = run->Right;
		}
}

void ComfilAddBox()
{
	gotoxy(BoxX+BoxS+38, BoxY+1);
	cout<<"            ";
	gotoxy(BoxX+BoxS+38, BoxY+1);
	cout<<" ADD WORD ";
	gotoxy(BoxX+BoxS+3, BoxY+3);
	cout<<"     Tu:";
	gotoxy(BoxX+BoxS+3, BoxY+4);
	cout<<"Loai tu:";
	gotoxy(BoxX+BoxS+3, BoxY+5);
	cout<<"  Nghia:";
	gotoxy(BoxX+BoxS+3, BoxY+6);
	cout<<"Vi du 1:";
	gotoxy(BoxX+BoxS+3, BoxY+7);
	cout<<"Vi du 2:";
	gotoxy(BoxX+BoxS+3, BoxY+8);
	cout<<"Vi du 3:";
	gotoxy(BoxX+BoxS+3, BoxY+9);
	cout<<"Vi du 4:";
	gotoxy(BoxX+BoxS+3, BoxY+10);
	cout<<"Vi du 5:";
}


void Box_save_word()
{
	for(int i=0; i<7; i++)
	{
		gotoxy(33,10+i);
		for(int j=0; j<66;j++)
			cout<<" ";
	}
	gotoxy(33,10);
	cout<<char(201);
	for(int i=0; i<50; i++)
	{
		cout<<char(205);
	}
	cout<<char(187);
	for(int i=0;i<6;i++)
	{
		gotoxy(33,11+i);
		cout<<char(186);
		gotoxy(84,11+i);
		cout<<char(186);
	}
	gotoxy(33, 17);
	cout<<char(200);
	for(int i=0; i<50; i++)
	cout<<char(205);
	cout<<char(188);	
}

void confim_add()
{
	gotoxy(35, 12);
	cout<<"Xac nhan luu tu moi!";
	gotoxy(35, 15);
	cout<<"Enter: Save "<<"    "<<" Esc: Quit"<<"    "<<" Another key: Back";
}

void Addword(HTable *&Dict){
	//system("cls");
	DelDetail();
	string text;
	string field[8] = {""};
	int k = 1;
	int Input = 0;
	text = field[k-1];
	int dem = field[k-1].length();
	gotoxy(BoxX+BoxS +5, BoxY +BoxW + 2 );
	cout<<"Luu y: Moi nghia cach nhau 1 dau cham phay!";
	Del_Menu();
		while(Input !=27){
			Again:
			ComfilAddBox();
			gotoxy(BoxX + BoxS +11, BoxY +2+ k);
			if (dem < BoxS1-35 )	
			{
				cout << text;
				for (int i = 0; i < BoxS1-35-dem ; i++)	cout << " ";
			}
			
			else for (int i = dem - (BoxS1-35); i< dem; i++)	cout << text[i];
			if(dem < BoxS1-35) gotoxy(BoxX + BoxS + 11 + dem, BoxY +2+ k); //Xuat ra vi tri con tro khi khung nhap chua bi tran
			else gotoxy(BoxS1+6, BoxY +2+ k);
			Input = getch();
			gotoxy(1,1);
			cout<<Input;
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
						printtextfield(text, k);
						field[k-1] = text;
						Del_Menu();
						k++;
						if(k==8) goto Saveadd;
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
							printtextfield(text, k);
							field[k-1] = text;
							Del_Menu();
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
							printtextfield(text, k);
							field[k-1] = text;
							Del_Menu();
							if(k<8) k++;
							//else if(k==17) break;
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
					}
					break;
				}
			default: //alphabet
				{
					if((Input < 123 && Input > 96) || (Input < 91 && Input > 64) || Input == 32 || Input == 39 || Input == 45 || Input == 59)
					{
						text += char(Input);
						dem++;
						gotoxy(BoxX +BoxS+ 11, BoxY +2+ k);
						if (dem < BoxS1-35)
						{
							cout << text;
						}
						else
						{
							for (int i = dem - (BoxS1-35); i< dem; i++)	cout << text[i];
						}
					}
				}
			}
			}
			if(field[0]!="" && field[1] !="" && field[2]!=""){
				Saveadd:
				Box_save_word();
				confim_add();
				Input = getch();
				if(Input == 13)
				{
					gotoxy(5, 1);
					cout<<Input;
					NODEWORD *Tu1 = new NODEWORD;
					Tu1->data.This = field[0];
					Tu1->data.Type = field[1];
					string t = field[2];
					string tmp = "";
					Tu1->data.First = NULL;
					for(int i=0; i<=t.length(); i++)
					{
						if(t[i] == ';')
						{
							Add_Mean_Head(Tu1->data.First, tmp); // them vao dau moi nghia
							tmp = "";
							i++;
						}
						//tmp += t[i];
						if(t[i] == '\0')
						{
							Add_Mean_Head(Tu1->data.First, tmp);
						}
						tmp += t[i];
					}
					for(int i=0;i<5; i++)
					{
						if(field[i+3] != "")
						{
							Tu1->data.Exam[i]=new string;
							*(Tu1->data.Exam[i]) = field[i+3];
						}
					}
					updated = true;
					Add_Word_In_HTable(Dict[Address(Tu1->data.This)].Head, Dict[Address(Tu1->data.This)].Tail, Tu1);
				}
				else if((Input < 123 && Input > 96) || (Input < 91 && Input > 64) || Input == 32 || Input == 39 || Input == 45 || Input == 59)
				{
					for(int i=0; i<8; i++)
					{
						gotoxy(33,10+i);
						for(int j=0; j<55;j++)
						cout<<" ";
					}
					goto Again;
				}
			}
		}
//	}
//			
//}

//		  =========== End Detail =============

void SearchBox(HTable *&Dict, NODEWORD *&Curr)
{
	int Input = 0;
	bool changed = false;
	string Text = "";
	string Str = "Enter Text";
	int Count = 0;
	
	while(1)
	{
		DictBox();
		Command_Menu();
		gotoxy(BoxX + 12, BoxY + 1);
		
		if(Text == "")
			cout << Str;
		else
		{
			if (Count < BoxS - 12)	cout << Text;
			else	for (int i = Count - (BoxS - 12); i< Count; i++)	cout << Text[i];
		}
		
		
		if (changed)
		{
			if (FixText(Text) != "")
				Curr = Search(Dict, FixText(Text));
			else	FindFirst(Dict, Curr);
			changed = false;
		}
		
		if( Curr != NULL)
			Detail(Curr);
		else
			DelDetail();
		
		DisplayWord(Dict,Curr);
		
		
		if (Count < BoxS - 12)	gotoxy(BoxX + 12 + Count, BoxY + 1);
		else gotoxy(BoxX + BoxS, BoxY + 1);
			
		Input = getch();
		switch(Input)
		{
			case 13:	//Enter
			{
				Edit(Dict,Curr);
				break;
			}
		
			case 8:		//Backspace
			{
				changed = true;
				if (Count>0)
				{
					Count--;
					Text = Text.substr(0, Text.size() - 1);
					gotoxy(BoxX + 12, BoxY + 1);
					if (Count < BoxS - 12)
					{
						cout << Text;
						for (int i = BoxX + 11; i < BoxS - 7; i++)	cout << " ";
					}
					else
					{
						for (int i = Count - 5; i<Count; i++)	cout << Text[i];
					}
				}
				break;
			}
		
			case 9:		//Tab
			{
				Addword(Dict);
				break;
			}
		
			case 224:	//Up Down
			{
				Input = getch();
				if (Input == 72)
				{
					if (Left(Dict, Curr) != NULL)
						Curr = Left(Dict, Curr);
				}
				else if (Input == 80)
				{
					if (Right(Dict, Curr) != NULL)
						Curr = Right(Dict, Curr);
				}
				
				else if (Input == 83)	//Delete
				{
					if(ConfirmDel(Curr))
						DeleteCurrent(Dict,Curr);
					DictBox();
					Command_Menu();
				}
				break;
			}
		
			case 27:	//Esc
			{
				if(Confirm(Input))
					return;
				else
				{
					system("cls");
					DictBox();
					Command_Menu();
				}
				break;
			}
			
			default:
			{
				if((Input < 123 && Input > 96) || (Input < 91 && Input > 64) || Input == 39 || Input == 45)
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

void xuat(int &i, NODEMEAN *Curr)
{
	if(Curr != NULL)
	{
		gotoxy(BoxX, BoxY + i);
		i++;
		cout<<Curr->data;
		Curr = Curr->Next;
		xuat(i,Curr);
	}
	return;
}

void WriteFile(HTable *Dict)
{
	ofstream File("Dulieu.txt");
	if(File.is_open())
	{
		for(int i = 0; i < 26; i++)
		{
			NODEWORD *Curr = Dict[i].Head;
			if(Curr == NULL)
				continue;
			while(	Curr != NULL)
			{
				File << Curr->data.This << "/";
				File << Curr->data.Type	<< "/";
				
				NODEMEAN *Mean = Curr->data.First;
				while( Mean != NULL)
				{
					File << Mean->data << ";";
					Mean = Mean->Next;
				}
				File << "/";
				
				for(int i = 0; i < MAXEXAM; i++)
				{
					if(Curr->data.Exam[i] != NULL)
						File << *Curr->data.Exam[i] << ";";
				}
				File << "/\n";
				Curr = Curr->Right;
			}
		}
		File.close();
	}
	
}

int main() 
{
	system("color 73");
	HTable *Dict = new HTable[26];
	
	for (int i = 0; i < 26; i++) 
	{
		Dict[i].Head = NULL;
		Dict[i].Tail = NULL;
	}
	ReadFile(Dict);
	NODEWORD *Curr = NULL;
	FindFirst(Dict,Curr);
	SearchBox(Dict,Curr);
	if(updated)
		WriteFile(Dict);
	//Addword(Dict);
	return 0;
}
