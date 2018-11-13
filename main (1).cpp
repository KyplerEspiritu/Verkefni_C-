#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

class Afangi {
private:
	class AfangiNode {
	public:
		Afangi *undanfari;
		AfangiNode *naesti;
		AfangiNode(Afangi *undanfari) : undanfari(undanfari), naesti(nullptr) {}
	};
	int numer;
	string nafn;
	AfangiNode *undanfarar; // virkar eins og head
public:
	Afangi() : numer(0), nafn(""), undanfarar(nullptr) { }
	Afangi(int numer, string nafn) : numer(numer), nafn(nafn), undanfarar(nullptr) { }

	void baetaVidUndanfara(Afangi *undanfari) {
		AfangiNode *nyrUndanfari = new AfangiNode(undanfari);

		if (undanfarar == nullptr)
		{
			undanfarar = nyrUndanfari;
		}
		AfangiNode *tempUndanfarar = undanfarar;
		while (true)
		{
			if (tempUndanfarar == nullptr)
			{
				tempUndanfarar->naesti = nyrUndanfari;
				break;
			}
			tempUndanfarar = tempUndanfarar->naesti;
		}

		// Ef enginn undanfari er skráðu á áfangann
		// á að tengja nyrUndanfari við undanfarar breytuna
		// Annars á að setja nyrUndanfari aftast í listann 
		// Ekki þarf að bregðast við ef sami áfangi er 
		// þegar í listanum
	}

	void prentaAfanga() {
		cout << "Numer: " << this->numer << " Nafn: " << this->nafn << endl;
		AfangiNode *undanfarinn = undanfarar;
		while (undanfarinn) {
			cout << "Undanfari: " << undanfarinn->undanfari->nafn << endl;
			undanfarinn = undanfarinn->naesti;
		}
	}
};

int main() {
	Afangi *forr1 = new Afangi(11, "Forritun IA");
	Afangi *forr2 = new Afangi(12, "Forritun II");
	Afangi *gagn1 = new Afangi(21, "Gagnasafnsfr. I");

	gagn1->baetaVidUndanfara(forr1);
	gagn1->prentaAfanga();
	cout << endl;

	Afangi *forr3 = new Afangi(13, "Forritun III");
	forr3->baetaVidUndanfara(forr1);
	forr3->baetaVidUndanfara(forr2);
	forr3->baetaVidUndanfara(gagn1);
	forr3->prentaAfanga();

	/*
	Ætti að skrifa út:

	Numer: 21 Nafn: Gagnasafnsfr. I
	Undanfari: Forritun IA

	Numer: 13 Nafn: Forritun III
	Undanfari: Forritun IA
	Undanfari: Forritun II
	Undanfari: Gagnasafnsfr. I
	*/

	return 0;
}