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
//lsta felépítése paraméterül kapott string alapján
BigInt::BigInt(string s)
{
	if (s[0] == '-') throw NOTBIG; //ha negatív
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
//lista felülírása
void BigInt::ChangeNumber(string s)
{

	
	if (s[0] == '-') throw NOTBIG; //ha negatív
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
//kiírás
ostream& operator<<(std::ostream& s, const BigInt& a)
{
	//lista bejárása és aktuális elem kiírása
	for (BigInt::const_iterator it = a.begin(); it != a.end(); it++) {
		s << *it;
	};

	return s;
}
//értékadás
//az operátor értékül adja a bal oldalon álló listának a jobb oldalon álló listát
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
	if (a.first == NULL) throw BigInt::NOTINIT;
	else if (b.first ==NULL) throw BigInt::NOTINIT;
	else if (b.first == NULL && a.first == NULL)throw BigInt::NOTINIT;
	else
	{
		
		int carrier = 0;	// a maradék tárolására létrehozott változó
		BigInt::Node *q;
		BigInt::Node* g = a.last;
		BigInt::Node* p = b.last;
		BigInt::Node* temp;
		carrier = carrier + p->value;
		p = p->prev;
		carrier = carrier + g->value;
		g = g->prev;
		c.first=c.last=temp= q = new BigInt::Node(carrier % 10, NULL, NULL); //új listaelem
		carrier = (carrier / 10);
		
		while (p !=NULL || g != NULL) //amíg mindkettõ el nem fogy
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
			q = new BigInt::Node(carrier % 10, temp, NULL); //új listaelem
			c.size++;
			c.first=temp->prev = q;
			carrier = (carrier / 10); //maradék
			temp = q;
			


		}
		if (carrier > 0)  //ha minkét szám elfogyott és van maradék
		{
			
			q = new BigInt::Node(carrier, temp, c.first); //maradék hozzáfûzése a lista végéhez
			c.size++;
			temp->prev = c.first = q;
		}
		
	}
	cout << c.Size() << endl;
	return c;
}
//BigInt szorzása int-el
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
	while (carrier>0) //a maradék számjegyeinek hozzáfûzése a lista végéhez
	{
		
		q = new BigInt::Node(carrier % 10, temp,NULL);
		r.size++;
		carrier = (carrier / 10);
		temp->prev = r.first= q;
		temp = q;
	}
	return r;
}
//szorzás
//bemenet:const BigInt&, const BigInt&
//kimenet:BigInt
//Az operátor két BigInt-et szoroz össze.
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
