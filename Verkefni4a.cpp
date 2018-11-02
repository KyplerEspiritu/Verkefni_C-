#include <iostream>
#include <sstream>
#include <iomanip> //Nota iomanip til þess að fá setprecision.
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

	float procentage = (float(reserved) / float(capacity)) * 100; //Breyti bæði breytunum í float svo að ég get reiknað prósentuna.
	cout << "\n" << "Flight " << id << " : " << reserved << "/" << capacity << " (" << fixed << setprecision(0) << procentage << "%)  seats reserved" << "\n";
	//Kalla þessa runu til þess að prenta út allt sem ég þarf + líka prósentutöluna með því að nota "setprecision(0)" til að round-a töluna
	//svo að prósentan verður ekki með neina aukastafi, og "fixed" til þess að fá 'fixed floating-point notation'.
}
FlightBooking::FlightBooking(int id, int capacity, int reserved)
{
	FlightBooking::id = id;
	FlightBooking::capacity = capacity;
	FlightBooking::reserved = reserved;
}

bool FlightBooking::reserveSeats(int number_of_seats)
{
	float newReserved = float(reserved) + float(number_of_seats); //Geri nýja breytu með newReserved til þess að sleppa því að skoða tvisvar hvort það sé pláss fyrir fleiri reservations.
	float procentage = ceil((float(newReserved) / float(capacity)) * 100);
	//Þessi breyta er notuð fyrir neðan til að skoða hvort það sé hægt að bæta við auka reservations.
	//Ég nota líka "ceil" til að round-a niður svo að það verður ekki 15.x prósent. (Ég mátti ráða að nota floor eða ceiling.)
	if (procentage <= 105)
	{
		FlightBooking::reserved += number_of_seats; //Bæti við reservations.
		return true;
	}
	else
		return false;
}

bool FlightBooking::cancelReservations(int number_of_seats)
{
	int checkReserved = (reserved - number_of_seats); //Nota þessa breytu fyrir neðan til þess að skoða hvort ég er með nóg af resrvations til þess að fjarlæga í burtu.
	if (checkReserved >= 0)
	{
		FlightBooking::reserved -= number_of_seats; //Fjarlægi reservations ef það eru ekki undir 0.
		return true;
	}
	else if (checkReserved < 0) //Ef sætin eru negatíf eftir það er búið að fjarlæga frá, vistast sætin sem 0.
	{
		FlightBooking::reserved = 0;
		return true;
	}
	else //Ef eitthvað fer úrskeiðis.
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
		string fEdit; // Strengur sem heldur á user-input. fEdit stendur fyrir "Flight Edit"
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