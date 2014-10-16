#ifndef BIGINT_H
#define BIGINT_H
#include <iostream>
#include <string>
using namespace std;
class BigInt
{
	struct iterator;
	struct const_iterator;
public:
	//kivételek
	enum Exeptions{ WRONG_VALUE, NOTBIG, NOTINIT };
	//konstruktor
	//nulla hosszú lista létrehozása
	BigInt()
	{
		first = NULL;
		last = NULL;
	}
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
	friend ostream& operator<<(ostream& s,  const BigInt& a);

	//matematikai mûveletek
	friend BigInt operator+(const BigInt& a, const BigInt& b);
	friend BigInt operator*(const BigInt& a, const int c);
	friend BigInt operator*(const BigInt& a,const BigInt& b);
	//összehasonlító mûveletek
	friend bool operator!=(const BigInt& a, const BigInt& b);
	friend bool operator==(const BigInt& a, const BigInt& b);
	
	////////////////////////////////TODO: iterátor/////////////////////////
	
	//bejáró mûveletek-helytt kéne iterátor
	


private:
	
	
	//listaelem
	struct Node
	{
		
	
		int value;//érték
		Node* next;//következõ
		Node* prev;//elõzõ

		Node(){ value = 0; next = NULL; prev = NULL; }
		Node(int v, Node* n = NULL, Node *p = NULL) : value(v), next(n), prev(p) {};
	
		friend struct iterator;
		friend struct const_iterator;
	};
	
	int size;//lista mérete
	Node* first;//lista elsõ eleme
	Node* last;//lista utolsó eleme


	struct iterator
	{
		Node* rep;
	public:
		friend struct const_iterator;
		friend class BigInt;

		iterator(Node* x = 0) :rep(x){}
		iterator(const iterator& x) : rep(x.rep) {}
		iterator& operator=(const iterator& x)
		{
			rep = x.rep; return *this;
		}
		iterator& operator++()
		{
			rep = rep->next; return *this;
		}
		iterator operator++(int)
		{
			iterator tmp(*this); rep = rep->next; return tmp;
		}
		int& operator*() const { return rep->value; }
		bool operator==(const iterator& x) const
		{
			return rep == x.rep;
		}
		bool operator!=(const iterator& x) const
		{
			return rep != x.rep;
		}

	};

	struct const_iterator
	{
		const Node* rep;
	public:
		friend struct iterator;

		const_iterator(const Node* x = 0) :rep(x){}
		const_iterator(const const_iterator& x) : rep(x.rep) {}
		const_iterator(const iterator& x) : rep(x.rep){}
		const_iterator& operator=(const const_iterator& x)
		{
			rep = x.rep; return *this;
		}
		const_iterator& operator=(const iterator& x)
		{
			rep = x.rep; return *this;
		}
		const_iterator& operator++()
		{
			rep = rep->next; return *this;
		}
		const_iterator operator++(int)
		{
			const_iterator tmp(*this); rep = rep->next; return tmp;
		}
		
		const int& operator*() const { return rep->value; }
		bool operator==(const const_iterator& x) const
		{
			return rep == x.rep;
		}
		bool operator!=(const const_iterator& x) const
		{
			return rep != x.rep;
		}

	};
	iterator begin() { return first; }
	iterator end() { return NULL; }
	const_iterator begin() const { return first; }
	const_iterator end() const { return NULL; }

	
};


#endif
