#include "menu.h"
#include "BigInt.h"
#include <iostream>
#include <string>

using namespace std;

void Menu::MenuWrite(){
	cout << endl << endl;

	cout << " 1. - write a " << endl;
	cout << " 2. - write b " << endl;
	cout << " 3. - a+b " << endl;
	cout << " 4. - a*b " << endl;
	cout << " 5. - a*const" << endl;
	cout << " 6. - b*const" << endl;
	cout << " 7. - change a" << endl;
	cout << " 8. - change b" << endl;
	cout << " 0. - quit" << endl;
}

void Menu::Run(){
	int v;

	int n;


	do{

		MenuWrite();
		v = Menu::IsNaN("Menu: ");
		switch (v){
		case 1: //Write a
			cout << "a = " << a << endl;
			break;
		case 2: //write b
			cout << "b= " << b << endl;
			break;
		case 3: //a+b
			cout << "a+b= " << a + b << endl;
			break;
		case 4: //a*b
			cout << "a*b= " << a*b << endl;
			break;
			
		case 5: //a*const
			n = Menu::IsNaN("const: ");
			cout << a << "*" << n << "= " << a*n << endl;
			break;
		case 6: //b*const
			n = Menu::IsNaN("const: ");
			cout << b << "*" << n << "= " << b*n << endl;
			break;
		case 7: //change a;
			cout << "a: ";
			cin >> a;
			break;
		case 8: //change b;
			cout << "b: ";
			cin >> b;
			break;
		case 0:
			cout << "QUIT!!!" << endl;
			break;
		default: cout << "Wrong menu!" << endl;
			break;


		}



	} while (v != 0);
}
int Menu::IsNaN(string text)
{
	int num;
	bool wrong;
	string s;
	do
	{
		cout << text;
		cin >> num;

		wrong = cin.fail();

		if (wrong)
		{

			cin.clear();
			getline(cin, s);
		}

	} while (wrong);

	return num;
}
