#ifndef BIGINT_H
#define BIGINT_H
#include <iostream>
#include <string>
using namespace std;
class BigInt
{

public:
	//kiv�telek
	enum Exeptions{ WRONG_VALUE, NOTBIG };
	//konstruktor
	//nulla hossz� lista l�trehoz�sa
	BigInt() : first(NULL), last(NULL), current(NULL), size(0){}
	//konstruktor
	//a param�ter�l kapott stringnek megfelel� lista l�trehoz�sa
	BigInt(string s);
	//copy konstruktor
	//�rt�k�l kapott BigInt lem�sol�sa
	BigInt(const BigInt& s);
	//destruktor
	~BigInt();
	//�rt�kad�s oper�tor
	BigInt& operator=(const BigInt& s);
	//sz�m fel�l�r�sa
	void ChangeNumber(string s);
	//m�ret lek�rdez�se
	int Size(){ return size; }
	//friend m�veletek:

	//beolvas�s
	friend istream& operator>>(istream& s, BigInt& a);
	//ki�r�s
	friend ostream& operator<<(ostream& s, BigInt& a);

	//matematikai m�veletek
	friend BigInt operator+(const BigInt& a, const BigInt& b);
	friend BigInt operator*(const BigInt& a, const int c);
	friend BigInt operator*(const BigInt& a,const BigInt& b);
	//�sszehasonl�t� m�veletek
	friend bool operator!=(const BigInt& a, const BigInt& b);
	friend bool operator==(const BigInt& a, const BigInt& b);






	////////////////////////////////TODO: iter�tor/////////////////////////

	//bej�r� m�veletek
	int Current() const { return current->value; }
	void First(){ current = first; }
	bool End()  const { return current == NULL; }
	void Next() { current = current->next; }


private:
	
	//listaelem
	struct Node
	{
		
		int value;//�rt�k
		Node* next;//k�vetkez�
		Node* prev;//el�z�


		Node(int v, Node* n = NULL, Node *p = NULL) : value(v), next(n), prev(p) {};
	};
	
	int size;//lista m�rete
	Node* first;//lista els� eleme
	Node* last;//lista utols� eleme
	Node* current;//bej�r�skor lista aktu�lis eleme
};


#endif
