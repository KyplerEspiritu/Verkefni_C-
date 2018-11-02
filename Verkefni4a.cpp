#include <iostream>
#include <sstream>
#include <iomanip> //Nota iomanip til �ess a� f� setprecision.
#include <math.h> //Nota math.h fyrir ceil.
using namespace std;

class FlightBooking {
public:
	FlightBooking(int id, int capacity, int reserved);
	void printStatus();
	bool reserveSeats(int number_of_seats);
	bool cancelReservations(int number_of_seats);
private:
	int id;
	int capacity;
	int reserved;
};

void FlightBooking::printStatus()
{

	float procentage = (float(reserved) / float(capacity)) * 100; //Breyti b��i breytunum � float svo a� �g get reikna� pr�sentuna.
	cout << "\n" << "Flight " << id << " : " << reserved << "/" << capacity << " (" << fixed << setprecision(0) << procentage << "%)  seats reserved" << "\n";
	//Kalla �essa runu til �ess a� prenta �t allt sem �g �arf + l�ka pr�sentut�luna me� �v� a� nota "setprecision(0)" til a� round-a t�luna
	//svo a� pr�sentan ver�ur ekki me� neina aukastafi, og "fixed" til �ess a� f� 'fixed floating-point notation'.
}
FlightBooking::FlightBooking(int id, int capacity, int reserved)
{
	FlightBooking::id = id;
	FlightBooking::capacity = capacity;
	FlightBooking::reserved = reserved;
}

bool FlightBooking::reserveSeats(int number_of_seats)
{
	float newReserved = float(reserved) + float(number_of_seats); //Geri n�ja breytu me� newReserved til �ess a� sleppa �v� a� sko�a tvisvar hvort �a� s� pl�ss fyrir fleiri reservations.
	float procentage = ceil((float(newReserved) / float(capacity)) * 100);
	//�essi breyta er notu� fyrir ne�an til a� sko�a hvort �a� s� h�gt a� b�ta vi� auka reservations.
	//�g nota l�ka "ceil" til a� round-a ni�ur svo a� �a� ver�ur ekki 15.x pr�sent. (�g m�tti r��a a� nota floor e�a ceiling.)
	if (procentage <= 105)
	{
		FlightBooking::reserved += number_of_seats; //B�ti vi� reservations.
		return true;
	}
	else
		return false;
}

bool FlightBooking::cancelReservations(int number_of_seats)
{
	int checkReserved = (reserved - number_of_seats); //Nota �essa breytu fyrir ne�an til �ess a� sko�a hvort �g er me� n�g af resrvations til �ess a� fjarl�ga � burtu.
	if (checkReserved >= 0)
	{
		FlightBooking::reserved -= number_of_seats; //Fjarl�gi reservations ef �a� eru ekki undir 0.
		return true;
	}
	else if (checkReserved < 0) //Ef s�tin eru negat�f eftir �a� er b�i� a� fjarl�ga fr�, vistast s�tin sem 0.
	{
		FlightBooking::reserved = 0;
		return true;
	}
	else //Ef eitthva� fer �rskei�is.
		return false;
}


int main() {
	bool loop = true;
	int reserved = 0,
		capacity = 0;
	cout << "Provide flight capacity: ";
	cin >> capacity;
	cout << "Provide number of reserved seats: ";
	cin >> reserved;

	FlightBooking booking(1, capacity, reserved);

	booking.printStatus();

	while (loop == true)
	{
		string fEdit; // Strengur sem heldur � user-input. fEdit stendur fyrir "Flight Edit"
		cout << "----------------------------------- \n";
		cout << "Welcome User. \n";
		cout << "You have 3 procedures available: \n";
		cout << "add [integer] \n";
		cout << "cancel [integer] \n";
		cout << "quit" << "\n \n";
		cout << "An example procedure would be: \n";
		cout << "add 4 \n";
		cout << "or \n";
		cout << "cancel 20 \n \n";
		cout << "Choose Procedure: ";
		cin >> fEdit;

		cout << "-----------------------------------";
		loop = false;
	}

	return 0;
}