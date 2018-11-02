#include <iostream>
#include <sstream>
#include <iomanip> //Nota iomanip til þess að fá setprecision.
#include <math.h> //Nota math.h fyrir ceil.
using namespace std;

class FlightBooking {
public:
	FlightBooking(int id, int capacity, int reserved);
	void printStatus();
	bool reserveSeats(int flightID, int number_of_seats);
	bool cancelReservations(int flightID, int number_of_seats);
private:
	int id;
	int capacity;
	int reserved;
};

void FlightBooking::printStatus()
{

	float procentage = (float(reserved) / float(capacity)) * 100; //Breyti bæði breytunum í float svo að ég get reiknað prósentuna.
	cout << "\n" << "Flight " << id << " : " << reserved << "/" << capacity << " (" << fixed << setprecision(0) << procentage << "%)  seats reserved" << "\n\n";
	//Kalla þessa runu til þess að prenta út allt sem ég þarf + líka prósentutöluna með því að nota "setprecision(0)" til að round-a töluna
	//svo að prósentan verður ekki með neina aukastafi, og "fixed" til þess að fá 'fixed floating-point notation'.
}
FlightBooking::FlightBooking(int id, int capacity, int reserved)
{
	FlightBooking::id = id;
	FlightBooking::capacity = capacity;
	FlightBooking::reserved = reserved;
}

bool FlightBooking::reserveSeats(int flightID, int number_of_seats)
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

bool FlightBooking::cancelReservations(int flightID, int number_of_seats)
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
	string failedString = "\n Cannot perform this operation \n\n";
	string fEdit; // Strengur sem heldur á user-input. fEdit stendur fyrir "Flight Edit"
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
		cout << "----------------------------------- \n";
		cout << "Welcome User. \n";
		cout << "You have 3 procedures available: \n";
		cout << "add [ID] [integer] \n";
		cout << "cancel [ID] [integer] \n";
		cout << "quit" << "\n \n";
		cout << "An example procedure would be: \n";
		cout << "add 1 4 \n";
		cout << "or \n";
		cout << "cancel 3 20 \n";
		cout << "----------------------------------- \n";

		cout << "Choose Procedure: ";
		getline(cin, fEdit);

		int id; // Velja flight number ID
		int cap; // Hversu marga á að taka eða setja inn.
		string procedure; // Taka fram hvað procedure ég nota.
		stringstream procedureString; // Setja svo í string stream.
		procedureString << fEdit;
		procedureString >> procedure >> id >> cap;
		if (procedure == "add") // Fyrir að bæta við
		{
			if (booking.reserveSeats(id, cap) == true) // Þessi if-setning keyrir fallið í rauninni, þannig að ég þarf ekki að kalla það tvisvar, og þá fæ ég líka að sjá hvort það er true eða false.
				booking.printStatus();

			else
				cout << failedString; //Prentar út fail string þegar það virkar ekki.
		}

		else if (procedure == "cancel") // Fyrir að taka frá.
		{
			if (booking.cancelReservations(id, cap) == true)
				booking.printStatus();

			else
				cout << failedString;
		}

		else if (procedure == "quit") // Fer úr loop, og hættir að keyra forrit.
		{
			cout << "Logging out of service.";
			loop = false;

		}
		else
			cout << failedString;
	}

	return 0;
}



// NEW CODE HERE
// NEW
// NEW
// NEW 
// NEW
// NEW
// NEW 
// NEW


#include <iostream>
#include <sstream>
#include <iomanip> //Nota iomanip til þess að fá setprecision.
#include <math.h> //Nota math.h fyrir ceil.
using namespace std;

class FlightBooking {
public:
	FlightBooking(int id = 0, int capacity = 0, int reserved = 0);
	FlightBooking();
	void createFlight();
	void printStatus();
	bool reserveSeats(int flightID, int number_of_seats);
	bool cancelReservations(int flightID, int number_of_seats);
	int getID(int flightID);

private:
	int id;
	int capacity;
	int reserved;
};


FlightBooking::FlightBooking(int id, int capacity, int reserved)
{
	FlightBooking::id = id;
	FlightBooking::capacity = capacity;
	FlightBooking::reserved = reserved;
}

void FlightBooking::printStatus()
{

	float procentage = (float(reserved) / float(capacity)) * 100; //Breyti bæði breytunum í float svo að ég get reiknað prósentuna.
	cout << "\n" << "Flight " << id << " : " << reserved << "/" << capacity << " (" << fixed << setprecision(0) << procentage << "%)  seats reserved" << "\n\n";
	//Kalla þessa runu til þess að prenta út allt sem ég þarf + líka prósentutöluna með því að nota "setprecision(0)" til að round-a töluna
	//svo að prósentan verður ekki með neina aukastafi, og "fixed" til þess að fá 'fixed floating-point notation'.
}

bool FlightBooking::reserveSeats(int flightID, int number_of_seats)
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

bool FlightBooking::cancelReservations(int flightID, int number_of_seats)
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

int FlightBooking::getID(int flightID)
{
	return this->id;
}


int main() {
	int arrsize = 1; // Heldur á array-size.
	int counter = 0; // Heldur á value í array.
	string failedString = "\n Cannot perform this operation \n\n";
	string fEdit; // Strengur sem heldur á user-input. fEdit stendur fyrir "Flight Edit"
	bool loop = true;
	int reserved = 0,
		capacity = 0;
	cout << "Provide flight capacity: ";
	cin >> capacity;
	cout << "Provide number of reserved seats: ";
	cin >> reserved;

	FlightBooking id1(1, capacity, reserved);
	FlightBooking *flightIDs[1]; // Bý til nýtt array.
	flightIDs[0] = new FlightBooking(1, capacity, reserved);
	counter += 1;
	id1.printStatus();
	flightIDs[0]->printStatus();

	while (loop == true)
	{
		cout << "----------------------------------- \n";
		cout << "Welcome User. \n";
		cout << "You have 3 procedures available: \n";
		cout << "add [ID] [integer] \n";
		cout << "cancel [ID] [integer] \n";
		cout << "quit" << "\n \n";
		cout << "An example procedure would be: \n";
		cout << "add 1 4 \n";
		cout << "or \n";
		cout << "cancel 3 20 \n";
		cout << "----------------------------------- \n";

		cout << "Choose Procedure: ";
		getline(cin, fEdit);

		int id; // Velja flight number ID
		int cap; // Hversu marga á að taka eða setja inn.
		string procedure; // Taka fram hvað procedure ég nota.
		stringstream procedureString; // Setja svo í string stream.
		procedureString << fEdit;
		procedureString >> procedure >> id >> cap;

		if (procedure == "create")
		{
			bool idExist = false; // Boolean sem segir hvort id er til.
			for (unsigned int i = 0; i < sizeof(flightIDs) / sizeof(flightIDs[0]); i++)
			{
				if ((flightIDs[i]->getID(id)) == id)
				{
					idExist = true;
				}
			}

		}

		else if (procedure == "add") // Fyrir að bæta við
		{
			if (id1.reserveSeats(id, cap) == true) // Þessi if-setning keyrir fallið í rauninni, þannig að ég þarf ekki að kalla það tvisvar, og þá fæ ég líka að sjá hvort það er true eða false.
				id1.printStatus();

			else
				cout << failedString; //Prentar út fail string þegar það virkar ekki.
		}

		else if (procedure == "cancel") // Fyrir að taka frá.
		{
			if (id1.cancelReservations(id, cap) == true)
				id1.printStatus();

			else
				cout << failedString;
		}

		else if (procedure == "quit") // Fer úr loop, og hættir að keyra forrit.
		{
			cout << "Logging out of service.";
			loop = false;

		}
		else
			cout << failedString;
	}

	return 0;
}