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
	//kiv�telek
	enum Exeptions{ WRONG_VALUE, NOTBIG, NOTINIT };
	//konstruktor
	//nulla hossz� lista l�trehoz�sa
	BigInt()
	{
		first = NULL;
		last = NULL;
	}
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
	friend ostream& operator<<(ostream& s,  const BigInt& a);

	//matematikai m�veletek
	friend BigInt operator+(const BigInt& a, const BigInt& b);
	friend BigInt operator*(const BigInt& a, const int c);
	friend BigInt operator*(const BigInt& a,const BigInt& b);
	//�sszehasonl�t� m�veletek
	friend bool operator!=(const BigInt& a, const BigInt& b);
	friend bool operator==(const BigInt& a, const BigInt& b);
	
	////////////////////////////////TODO: iter�tor/////////////////////////
	
	//bej�r� m�veletek-helytt k�ne iter�tor
	


private:
	
	
	//listaelem
	struct Node
	{
		
	
		int value;//�rt�k
		Node* next;//k�vetkez�
		Node* prev;//el�z�

		Node(){ value = 0; next = NULL; prev = NULL; }
		Node(int v, Node* n = NULL, Node *p = NULL) : value(v), next(n), prev(p) {};
	
		friend struct iterator;
		friend struct const_iterator;
	};
	
	int size;//lista m�rete
	Node* first;//lista els� eleme
	Node* last;//lista utols� eleme


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
