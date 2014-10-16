#include "BigInt.h"
#include "iostream"
#include "string"
#include "cmath"

using namespace std;

//copy konstruktor
BigInt::BigInt(const BigInt& s){

	if (s.first == NULL) BigInt();
		
	
	else{
		size = s.size;	
		Node* cur = first = last=NULL;
		Node* temp = NULL;
		for (BigInt::const_iterator it = s.begin(); it != s.end(); ++it) {
			last = cur = new Node(*it, NULL,temp );
			if (first == NULL)first =cur;
			else cur->prev->next = cur;
			temp = cur;
		}



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
	if (s[0] == '-') throw NOTBIG; //ha negat�v
	Node* cur;
	int j=s[0];
	if (j >= 48 && j <= 57)
	{
		cur = first = last = new Node(j - 48, NULL, NULL);
		size = s.length();
	}
	else
		throw WRONG_VALUE;

	
	for (int i = 1; i < size; i++)
	{

		j = s[i];
		if (j >= 48 && j <= 57)
		{
			last = cur->next = new Node(j - 48, NULL, cur);
			cur = cur->next;
		}

		else
			throw WRONG_VALUE;
	}


}
//lista fel�l�r�sa
void BigInt::ChangeNumber(string s)
{

	
	if (s[0] == '-') throw NOTBIG; //ha negat�v
	while (first != NULL){ Node *p = first; first = p->next; delete p; }
	Node* cur;
	int j = s[0];
	if (j >= 48 && j <= 57)
	{
		cur = first = last = new Node(j - 48, NULL, NULL);
		size = s.length();
	}
	else throw WRONG_VALUE;


	for (int i = 1; i < size; i++)
	{

		j = s[i];
		if (j >= 48 && j <= 57)
		{
			last = cur->next = new Node(j - 48, NULL, cur);
			cur = cur->next;
		}

		else
			throw WRONG_VALUE;
	}

}
//ki�r�s
ostream& operator<<(std::ostream& s, const BigInt& a)
{
	//lista bej�r�sa �s aktu�lis elem ki�r�sa
	for (BigInt::const_iterator it = a.begin(); it != a.end(); it++) {
		s << *it;
	};

	return s;
}
//�rt�kad�s
//az oper�tor �rt�k�l adja a bal oldalon �ll� list�nak a jobb oldalon �ll� list�t
BigInt& BigInt::operator=(const BigInt& s){
	if (&s == this) return *this;
	while (first != NULL){ Node *p = first; first = p->next; delete p; }
	
		
	size = s.size;
	Node* cur = first = last = NULL;
	Node* temp = NULL;
	for (BigInt::const_iterator it = s.begin(); it != s.end(); ++it) {
		last = cur = new Node(*it, NULL, temp);
		if (first == NULL)first = cur;
		else cur->prev->next = cur;
		temp = cur;
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
	if (a.first == NULL) throw BigInt::NOTINIT;
	else if (b.first ==NULL) throw BigInt::NOTINIT;
	else if (b.first == NULL && a.first == NULL)throw BigInt::NOTINIT;
	else
	{
		
		int carrier = 0;	// a marad�k t�rol�s�ra l�trehozott v�ltoz�
		BigInt::Node *q;
		BigInt::Node* g = a.last;
		BigInt::Node* p = b.last;
		BigInt::Node* temp;
		carrier = carrier + p->value;
		p = p->prev;
		carrier = carrier + g->value;
		g = g->prev;
		c.first=c.last=temp= q = new BigInt::Node(carrier % 10, NULL, NULL); //�j listaelem
		carrier = (carrier / 10);
		
		while (p !=NULL || g != NULL) //am�g mindkett� el nem fogy
		{
			
			if (p !=NULL) //ha b nem fogy el
			{
				carrier = carrier + p->value;
				p = p->prev;
			}
			if (g !=NULL) //ha a nem fogy el
			{
				carrier = carrier + g->value;
				g = g->prev;
			}
			q = new BigInt::Node(carrier % 10, temp, NULL); //�j listaelem
			c.size++;
			c.first=temp->prev = q;
			carrier = (carrier / 10); //marad�k
			temp = q;
			


		}
		if (carrier > 0)  //ha mink�t sz�m elfogyott �s van marad�k
		{
			
			q = new BigInt::Node(carrier, temp, c.first); //marad�k hozz�f�z�se a lista v�g�hez
			c.size++;
			temp->prev = c.first = q;
		}
		
	}
	cout << c.Size() << endl;
	return c;
}
//BigInt szorz�sa int-el
//Bemenet: const BigInt&, const int
//kimenet: BigInt
BigInt operator*(const BigInt& a, const int c)
{
	BigInt r;
	r.size = 0;
	long long carrier=0;
	r.size++;
	BigInt::Node* q;
	BigInt::Node* g = a.last;
	BigInt::Node* temp;
	carrier = carrier + g->value*c;
	q = new BigInt::Node(carrier % 10, NULL, NULL);
	r.size++;
	carrier = (carrier / 10);
	r.first = q;
	temp = q;
	g = g->prev;

	while (g != NULL)
	{
		

		carrier = carrier + g->value*c;
		q = new BigInt::Node(carrier % 10, temp, NULL);
		r.size++;
		carrier = (carrier / 10);
		temp->prev=r.first= q;
		temp = q;
		g = g->prev;
		
	}
	while (carrier>0) //a marad�k sz�mjegyeinek hozz�f�z�se a lista v�g�hez
	{
		
		q = new BigInt::Node(carrier % 10, temp,NULL);
		r.size++;
		carrier = (carrier / 10);
		temp->prev = r.first= q;
		temp = q;
	}
	return r;
}
//szorz�s
//bemenet:const BigInt&, const BigInt&
//kimenet:BigInt
//Az oper�tor k�t BigInt-et szoroz �ssze.
BigInt operator*(const BigInt& a, const BigInt& b)
{  
	BigInt t, r;
	BigInt::Node* pr;
	BigInt::Node* pt;	
	BigInt::Node* g = b.last;
	r.size = 0;
	BigInt::Node* temp;
	t = (a*g->value);
	pt = t.last;
	temp=r.first=pr = new BigInt::Node(pt->value, NULL, NULL);
	r.size++;	
	if(pt!=t.first)pt->prev->next = NULL;
	t.last = pt->prev;
	delete pt;	
	g = g->prev;
	while (g!=NULL)
	{			
		t=(t + (a*g->value));
		pt = t.last;		
		temp->prev = r.first =pr = new BigInt::Node(pt->value,temp,NULL);
		r.size++;	
		temp = pr;
		t.last = pt->prev;
		if(pt!=t.first)pt->prev->next = NULL;		
		delete pt;
		g = g->prev;
	}
	pt = t.last;	
	while (pt != NULL)
	{
		
		
		pr = new BigInt::Node(pt->value, temp, NULL);
		r.size++;		
		temp->prev = r.first= pr;
		temp = pr;
		pt = pt->prev;
	}
	t.~BigInt();
	return r;
	
	
	
}
