#include "BigInt.h"
#include "iostream"
#include "string"
#include "cmath"

using namespace std;

//copy konstruktor
BigInt::BigInt(const BigInt& s){
	if (s.first == NULL){
		first = last = NULL;
	}
	else{
		Node* q = new Node(s.first->value, NULL, NULL);
		first = q;
		for (Node* p = s.first->next; p != NULL; p = p->next){
			q = new Node(p->value, NULL, q);
			q->prev->next = q;
		}
		last = q;

	}



}

//destruktor
BigInt::~BigInt()
{
	while (first != NULL){ Node *p = first; first = p->next; delete p; }
}
//konstruktor
//lsta fel�p�t�se param�ter�l kapott string alapj�n
BigInt::BigInt(string s)
{
	if (s[0] = '-') throw NOTBIG; //ha negat�v

	first = new Node(s[0] - 48);
	last = first;
	size = s.length();

	int j;
	for (int i = 1; i < size; i++)
	{

		j = s[i];
		if (j >= 48 && j <= 57)
		{
			last->next = new Node(j - 48, NULL, last);
			last = last->next;
		}

		else
			throw WRONG_VALUE;
	}


}
//lista fel�l�r�sa
void BigInt::ChangeNumber(string s)
{
	if (s[0] == '-') throw NOTBIG;

	first = new Node(s[0] - 48);
	last = first;
	size = s.length();

	int j;
	for (int i = 1; i < size; i++)
	{
		j = s[i];
		if (j >= 48 && j <= 57)
		{
			last->next = new Node(j - 48, NULL, last);
			last = last->next;
		}

		else
			throw WRONG_VALUE;
	}

}
//ki�r�s
ostream& operator<<(std::ostream& s, BigInt& a)
{
	//lista bej�r�sa �s aktu�lis elem ki�r�sa
	for (a.First(); !a.End(); a.Next()){
		cout << a.Current();
	}

	return s;
}
//�rt�kad�s
//az oper�tor �rt�k�l adja a bal oldalon �ll� list�nak a jobb oldalon �ll� list�t
BigInt& BigInt::operator=(const BigInt& s){
	if (&s == this) return *this;
	Node* p = first;
	while (p != NULL){
		Node* q = p->next;
		delete p;
		p = q;
	}
	if (s.first == NULL){
		first = last = NULL;
	}
	else{
		Node* q = new Node(s.first->value, NULL, NULL);
		first = q;
		for (Node* p = s.first->next; p != NULL; p = p->next){
			q = new Node(p->value, NULL, q);
			q->prev->next = q;
		}
		last = q;

	}


	return *this;
}
//beolvas�s
istream& operator>>(istream& s, BigInt& a)
{
	string str;
	s >> str;
	a.ChangeNumber(str);
	return s;
}
//k�t BigInt-et ad �ssze
//
BigInt operator+(const BigInt& a, const BigInt& b)
{
	BigInt c;
	if (a.last == NULL)c = b;
	else if (b.last == NULL)c = a;
	else if (b.last == NULL && a.last == NULL);
	else
	{
		unsigned long long carrier = 0;	// a marad�k t�rol�s�ra l�trehozott v�ltoz�
		BigInt::Node *q = new BigInt::Node((a.last->value + b.last->value) % 10,NULL, NULL);
		carrier = (a.last->value + b.last->value) / 10;
		c.size++;
		c.last = q;
		BigInt::Node* g = a.last->prev;
		BigInt::Node* p = b.last->prev;
		BigInt::Node* temp = q;
		while (p != NULL || g != NULL) //am�g mindkett� el nem fogy
		{

			if (p != NULL) //ha b nem fogy el
			{
				carrier = carrier + p->value;
				p = p->prev;
			}
			if (g != NULL) //ha a nem fogy el
			{
				carrier = carrier + g->value;
				g = g->prev;
			}
			q = new BigInt::Node(carrier % 10, temp, NULL); //�j listaelem
			c.size++;
			carrier = (carrier / 10); //marad�k
			temp = q;
			q->next->prev = q;


		}
		if (carrier > 0)  //ha mink�t sz�m elfogyott �s van marad�k
		{
			
			q = new BigInt::Node(carrier, temp, NULL); //marad�k hozz�f�z�se a lista v�g�hez
			c.size++;
			c.first = q->next->prev = q;
		}
		else
		{
			c.first = q; //ha nincs marad�k
		}
	}

	return c;
}
//BigInt szorz�sa konstansal
BigInt operator*(const BigInt& a, const int c)
{
	BigInt r;
	r.size = 0;
	unsigned long long carrier;
	BigInt::Node *q = new BigInt::Node((a.last->value*c) % 10, NULL, NULL);
	carrier = (a.last->value*c) / 10;
	r.size++;
	r.last = q;
	BigInt::Node* g = a.last->prev;
	BigInt::Node* temp = q;

	while (g != NULL)
	{
		

		carrier = carrier + g->value*c;
		q = new BigInt::Node(carrier % 10, temp, NULL);
		r.size++;
		carrier = (carrier / 10);
		temp = q;
		g = g->prev;
		q->next->prev = q;
	}
	while (carrier>0) //a marad�k sz�mjegyeinek hozz�f�z�se a lista v�g�hez
	{
		
		q = new BigInt::Node(carrier % 10, temp, NULL);
		r.size++;
		carrier = (carrier / 10);
		temp = q;
		q->next->prev = q;
	}
	r.first = q;
	return r;
}
//szorz�s
BigInt operator*(const BigInt& a, const BigInt& b)
{  
	BigInt t, r;
	BigInt::Node* pt;	
	BigInt::Node* g = b.last;

	BigInt::Node* temp;
	t = (a*g->value);

	pt = t.last;

	BigInt::Node* pr = new BigInt::Node(pt->value, NULL, NULL);
	r.last = pr;
	
	temp = pr;
	g = g->prev;
	while (g!=NULL)
	{		
		
		t.last = t.last->prev;
		
		
		t.last->next = NULL;
		t=(t + (a*g->value));		
		
		BigInt::Node* pt = t.last;
		
		temp = pr;
		pr = new BigInt::Node(pt->value,temp, NULL);
		
		g = g->prev;
		temp->prev = pr;
	}
	pt = t.last->prev;
	
	while (pt->prev != NULL)
	{
		
		temp = pr;
		pr = new BigInt::Node(pt->value, temp, NULL);
		
		pt = pt->prev;
		temp->prev = pr;
	}
	temp = pr;
	pr = new BigInt::Node(pt->value, temp, NULL);
	r.first = pr;
	return r;
	
	
	
}
