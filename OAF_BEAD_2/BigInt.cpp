#include "BigInt.h"
#include "iostream"
#include "string"
#include "cmath"

using namespace std;

//copy konstruktor
BigInt::BigInt(const BigInt& s){

	if (s.first->next == s.last) BigInt();
		
	
	else{
		size = s.size;	
		first = new Node();
		last = new Node();
		Node* cur = first;
		for (BigInt::const_iterator it = s.begin(); it != s.last; ++it) {
			last->prev = cur->next = new Node(*it, last, cur);
			cur = cur->next;
		}



	}
}

//destruktor
BigInt::~BigInt()
{
	while (first->next != last){ Node *p = first->next; first->next = p->next; delete p; }
	delete first;
	delete last;
}
//konstruktor
//lsta felépítése paraméterül kapott string alapján
BigInt::BigInt(string s)
{
	if (s[0] == '-') throw NOTBIG; //ha negatív

	int j;
	first = new Node();
	last = new Node();
	Node* cur = first;
	size = s.length();

	
	for (int i = 0; i < size; i++)
	{

		j = s[i];
		if (j >= 48 && j <= 57)
		{
			last->prev = cur->next = new Node(j - 48, last, cur);
			cur = cur->next;
		}

		else
			throw WRONG_VALUE;
	}


}
//lista felülírása
void BigInt::ChangeNumber(string s)
{
	Node* p = first->next;
	while (p != last){
		Node* q = p->next;
		delete p;
		p = q;
	}
	if (s[0] == '-') throw NOTBIG; //ha negatív

	int j;
	first = new Node();
	last = new Node();
	Node* cur = first;
	size = s.length();
	

	for (int i = 0; i < size; i++)
	{

		j = s[i];
		if (j >= 48 && j <= 57)
		{
			last->prev = cur->next = new Node(j - 48, last, cur);
			cur = cur->next;
		}

		else
			throw WRONG_VALUE;
	}

}
//kiírás
ostream& operator<<(std::ostream& s, const BigInt& a)
{
	//lista bejárása és aktuális elem kiírása
	for (BigInt::const_iterator it = a.begin(); it != a.last; it++) {
		s << *it;
	};

	return s;
}
//értékadás
//az operátor értékül adja a bal oldalon álló listának a jobb oldalon álló listát
BigInt& BigInt::operator=(const BigInt& s){
	if (&s == this) return *this;
	Node* p = first->next;
	while (p != last){
		Node* q = p->next;
		delete p;
		p = q;
	}	
	
		
		Node* cur = first;
		size = s.size;
		for (BigInt::const_iterator it = s.begin(); it != s.last; ++it) {
			last->prev = cur->next = new Node(*it, last, cur);
			cur = cur->next;
		}



	


	return *this;
}
//beolvasás
istream& operator>>(istream& s, BigInt& a)
{
	string str;
	s >> str;
	a.ChangeNumber(str);
	return s;
}
//két BigInt-et ad össze
//
BigInt operator+(const BigInt& a, const BigInt& b)
{
	BigInt c;
	if (a.first->next == a.last) throw BigInt::NOTINIT;
	else if (b.first->next == b.last) throw BigInt::NOTINIT;
	else if (b.first->next == b.last && a.first->next == a.last)throw BigInt::NOTINIT;
	else
	{
		
		int carrier = 0;	// a maradék tárolására létrehozott változó
		BigInt::Node *q;
		BigInt::Node* g = a.last->prev;
		BigInt::Node* p = b.last->prev;
		BigInt::Node* temp = c.last;
		while (p !=b.first || g != a.first) //amíg mindkettõ el nem fogy
		{
			

			if (p !=b.first) //ha b nem fogy el
			{
				carrier = carrier + p->value;
				p = p->prev;
			}
			if (g !=a.first) //ha a nem fogy el
			{
				carrier = carrier + g->value;
				g = g->prev;
			}
			q = new BigInt::Node(carrier % 10, temp, c.first); //új listaelem
			c.size++;
			temp->prev=c.first->next = q;
			carrier = (carrier / 10); //maradék
			temp = q;
			


		}
		if (carrier > 0)  //ha minkét szám elfogyott és van maradék
		{
			
			q = new BigInt::Node(carrier, temp, c.first); //maradék hozzáfûzése a lista végéhez
			c.size++;
			temp->prev = c.first->next = q;
		}
		
	}
	return c;
}
//BigInt szorzása konstansal
BigInt operator*(const BigInt& a, const int c)
{
	BigInt r;
	r.size = 0;
	long long carrier=0;
	r.size++;
	BigInt::Node* q;
	BigInt::Node* g = a.last->prev;
	BigInt::Node* temp = r.last;

	while (g != a.first)
	{
		

		carrier = carrier + g->value*c;
		q = new BigInt::Node(carrier % 10, temp, r.first);
		r.size++;
		carrier = (carrier / 10);
		temp->prev = r.first->next = q;
		temp = q;
		g = g->prev;
		
	}
	while (carrier>0) //a maradék számjegyeinek hozzáfûzése a lista végéhez
	{
		
		q = new BigInt::Node(carrier % 10, temp, r.first);
		r.size++;
		carrier = (carrier / 10);
		temp->prev = r.first->next = q;
		temp = q;
	}
	return r;
}
//szorzás
BigInt operator*(const BigInt& a, const BigInt& b)
{  
	BigInt t("0"), r;
	BigInt::Node* pr;
	BigInt::Node* pt;	
	BigInt::Node* g = b.last->prev;
	r.size = 0;
	BigInt::Node* temp=r.last;
	while (g!=b.first)
	{		
			
		
		t=(t + (a*g->value));
		pt = t.last->prev;		
		pr = new BigInt::Node(pt->value,temp, r.first);
		r.size++;		
		temp->prev = r.first->next = pr;
		temp = pr;
		t.last->prev = pt->prev;
		pt->prev->next = t.last;
		g = g->prev;
		delete pt;
	}
	pt = t.last->prev;	
	while (pt != t.first)
	{
		
		
		pr = new BigInt::Node(pt->value, temp, r.first);
		r.size++;		
		temp->prev = r.first->next = pr;
		temp = pr;
		pt = pt->prev;
	}	
	
	return r;
	
	
	
}
