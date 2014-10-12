#ifndef BIGINT_H
#define BIGINT_H
#include <iostream>
#include <string>
using namespace std;
class BigInt
{

public:
	//kivételek
	enum Exeptions{ WRONG_VALUE, NOTBIG };
	//konstruktor
	//nulla hosszú lista létrehozása
	BigInt() : first(NULL), last(NULL), current(NULL), size(0){}
	//konstruktor
	//a paraméterül kapott stringnek megfelelõ lista létrehozása
	BigInt(string s);
	//copy konstruktor
	//értékül kapott BigInt lemásolása
	BigInt(const BigInt& s);
	//destruktor
	~BigInt();
	//értékadás operátor
	BigInt& operator=(const BigInt& s);
	//szám felülírása
	void ChangeNumber(string s);
	//méret lekérdezése
	int Size(){ return size; }
	//friend mûveletek:

	//beolvasás
	friend istream& operator>>(istream& s, BigInt& a);
	//kiírás
	friend ostream& operator<<(ostream& s, BigInt& a);

	//matematikai mûveletek
	friend BigInt operator+(const BigInt& a, const BigInt& b);
	friend BigInt operator*(const BigInt& a, const int c);
	friend BigInt operator*(const BigInt& a,const BigInt& b);
	//összehasonlító mûveletek
	friend bool operator!=(const BigInt& a, const BigInt& b);
	friend bool operator==(const BigInt& a, const BigInt& b);






	////////////////////////////////TODO: iterátor/////////////////////////

	//bejáró mûveletek
	int Current() const { return current->value; }
	void First(){ current = first; }
	bool End()  const { return current == NULL; }
	void Next() { current = current->next; }


private:
	
	//listaelem
	struct Node
	{
		
		int value;//érték
		Node* next;//következõ
		Node* prev;//elõzõ


		Node(int v, Node* n = NULL, Node *p = NULL) : value(v), next(n), prev(p) {};
	};
	
	int size;//lista mérete
	Node* first;//lista elsõ eleme
	Node* last;//lista utolsó eleme
	Node* current;//bejáráskor lista aktuális eleme
};


#endif
