#include <iostream>
#include <sstream>
#include <iomanip> //Nota iomanip til þess að fá setprecision.
#include <math.h> //Nota math.h fyrir ceil.
using namespace std;

class FlightBooking { // Allar breytur
private:
	int id;
	int capacity;
	int reserved;
public:
	FlightBooking(int id = 0, int capacity = 0, int reserved = 0) // Constructor
  {
    this->id = id;
    this->capacity = capacity;
    this->reserved = reserved;
  }

	void printStatus(); // Öll föll sem ég nota
  int returnID();
	bool reserveSeats(int flightID, int number_of_seats);
	bool cancelReservations(int flightID, int number_of_seats);
};

int FlightBooking::returnID()
{
  return FlightBooking::id; //Þetta er notað til að bera saman ID.
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


int main() {

	string failedString = "\n Cannot perform this operation \n\n";
	string fEdit; // Strengur sem heldur á user-input. fEdit stendur fyrir "Flight Edit"
	bool loop = true; // Keyrir aðal-forritið.
  int arrsize = 2, counter = 0; // Bý til teljaran og array-size.
	FlightBooking* booking = new FlightBooking[arrsize]; // Bý til array-ið með tvö stök.

	while (loop == true)
	{
		cout << "----------------------------------- \n";
		cout << "Welcome User. \n";
		cout << "You have 6 procedures available: \n";
    cout << "create [ID] [integer] \n";
    cout << "delete [ID] \n";
		cout << "add [ID] [integer] \n";
		cout << "cancel [ID] [integer] \n";
    cout << "show \n";
		cout << "quit" << "\n \n";
		cout << "An example procedure would be: \n";
		cout << "add 1 4 \n";
		cout << "or \n";
		cout << "cancel 3 20 \n";
		cout << "----------------------------------- \n";

		cout << "Choose Procedure:";
		getline(cin, fEdit);

		int id; // Velja flight number ID
		int cap; // Hversu marga á að taka eða setja inn.
    int whichID; // Segir hvaða ID við erum að vinna með
    bool exists = false; // Skoðar hvort þetta ID er til.
		string procedure; // Taka fram hvað procedure ég nota.
		stringstream procedureString; // Setja svo í string stream.
		procedureString << fEdit;
		procedureString >> procedure >> id >> cap;

    for (int i = 0; i < arrsize; i++) //Skoðar í hvert sinn hvort ID-ið er til í array.
    {
      if (booking[i].returnID() == id)
      {
        whichID = i; // Segir hvaða stak á að taka til að fá þetta ID ef það er til.
        exists = true;
      }
    }
		if (procedure == "add" && exists == true) // Fyrir að bæta við
		{
			if (booking[whichID].reserveSeats(id, cap) == true) // Þessi if-setning keyrir fallið í rauninni, þannig að ég þarf ekki að kalla það tvisvar, og þá fæ ég líka að sjá hvort það er true eða false.
				booking[whichID].printStatus();

			else
				cout << failedString; //Prentar út fail string þegar það virkar ekki.
		}

		else if (procedure == "cancel" && exists == true) // Fyrir að taka frá.
		{
			if (booking[whichID].cancelReservations(id, cap) == true)
				booking[whichID].printStatus();

			else
				cout << failedString;
		}

    else if (procedure == "create" && exists == false) //Býr til nýtt object, skoðar fyrst ef það sé til eða ekki.
    {
      if (arrsize <= counter) //Skoðar hvort array-ið er eins stórt eða minna, og ef það er þannig, þá er tvöfaldað stærðin á array með því að nota temp_array.
      {
        FlightBooking* tmp_array = new FlightBooking[arrsize];

        for (int k = 0; k < counter; k++)
          tmp_array[k] = booking[k];
      
        delete[]booking;

        arrsize *= 2;
        booking = new FlightBooking[arrsize];
        for (int k = 0; k < counter; k++)
          booking[k] = tmp_array[k];
        
        delete[]tmp_array;
      }

      booking[counter] = FlightBooking(id, cap, 0);
      booking[counter].printStatus();
      counter += 1;

    }

    else if (procedure == "delete" && exists == true) //Hendir út stakinu með því að færa allt til vinstri og svo henda counter-inum út þannig að hann mun aldrei teljast með. Ef það kemur nýtt stak, þá mun það skrifa yfir gamla.
    {
      for (int i = whichID; i < counter; i++)
        booking[i] = booking[i+1];
      counter -= 1;
      cout << "Successfully deleted. \n";
      
    }

		else if (procedure == "quit") // Fer úr loop, og hættir að keyra forrit.
		{
			cout << "Logging out of service.";
			loop = false;

		}

    else if (procedure == "show") // Sýnir öll flug.
    {
      for (int i = 0; i < counter; i++)
        booking[i].printStatus();
    }

		else // Ef eitthvað fer úrskeiðis þá prentar það út error.
			cout << failedString;
    
    exists = false; //Endurstilla "exists" breytuna.
	}

	return 0;
}
