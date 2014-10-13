#ifndef MENU_H
#define MENU_H
#include "BigInt.h"
#include <string>

class Menu{
public:
	Menu()
	{
		bool r;
		do{
			r = true;
			try
			{
				cout << "a: ";
				cin >> a;
			}
			catch (BigInt::Exeptions ex)
			{
				if (ex == BigInt::WRONG_VALUE)cout << "Wrong number!!!" << endl;
				if (ex == BigInt::NOTBIG)cout << "Negative nuber is not big!!!" << endl;
				r = false;

			}
		} while (!r);

		do{
			r = true;
			try
			{
				cout << "b: ";
				cin >> b;
			}
			catch (BigInt::Exeptions ex)
			{
				if (ex == BigInt::WRONG_VALUE)cout << "Wrong number!!!" << endl;
				if (ex == BigInt::NOTBIG)cout << "Negative nuber is not big!!!" << endl;
				r = false;

			}
		} while (!r);
	}
	void Run();
private:
	void MenuWrite();
	BigInt a;
	BigInt b;
	int IsNaN(string text);
};

#endif // MENU_H