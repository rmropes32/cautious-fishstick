//
// AL Weather Station Data
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

struct station_data {
	string station_id;
	string station_name;
	string date;
	float mdpr;
	float dapr;
	float prcp;
	float snwd;
	float snow;
	float tavg;
	float tmax;
	float tmin;
	float awnd;
	float wsf2;
	float wsf5;

	station_data* link;
};


// Loading data
void load_data(char input, ifstream& file, string& years_loaded); // Opens file for entering into struct node system
void enter_data(station_data& data, ifstream& file); // Enter data to struct node system
void print_data(station_data& data, ifstream& file); // For debug

// Data procedures

// Check data line
bool check_entry(station_data* current_node, string start_date, string end_date, string station_id, string station_name);

// Temp procedures
float temperature_average(station_data* root_node, string start_date, string end_date, string station_id, string station_name);
float temperature_maximum(station_data* root_node, string start_date, string end_date, string station_id, string station_name, char maximum_type);
float temperature_minimum(station_data* root_node, string start_date, string end_date, string station_id, string station_name, char minimum_type);

// Precipitation procedures
float precipitation_amount(station_data* root_node, string start_date, string end_date, string station_id, string station_name);
float precipitation_snow_depth(station_data* root_node, string start_date, string end_date, string station_id, string station_name);
float precipitation_snow_amount(station_data* root_node, string start_date, string end_date, string station_id, string station_name);

// Wind procedures
float wind_average(station_data* root_node, string start_date, string end_date, string station_id, string station_name);
float wind_two_minute(station_data* root_node, string start_date, string end_date, string station_id, string station_name, char type);
float wind_five_second(station_data* root_node, string start_date, string end_date, string station_id, string station_name, char type);


int main(void)
{
	// Defining nodes for entire data list
	station_data* root_node, * current_node, * new_node;
	current_node = new station_data;

	current_node->link = NULL;
	root_node = current_node;

	//Defining necessary variables
	string years_loaded_str = "";


	// Establishing data to be used. Loads requested data.
	char user_input_year = ' ';
	char repeat = 'Y';
	do
	{
		ifstream data;

		cout << "Please select which year to load: " << endl;
		cout << "A." << setw(40) << right << "2023 (to August 07)" << endl;

		cin >> user_input_year;

		cout << "\nLoading data..." << endl;
		load_data(user_input_year, data, years_loaded_str);


		//put into load_data func
		string dataline;
		getline(data, dataline);
		getline(data, dataline);
		while (!data.eof())
		{
			new_node = new station_data;

			enter_data(*new_node, data);
			//print_data(*new_node, data);

			new_node->link = NULL;

			current_node->link = new_node;

			current_node = new_node;
		}

		cout << "\nWould you like to load more years? (Y/N)" << endl;
		cin >> repeat;

		data.close();
	} while (repeat == 'Y');


	// User Input User Input User Input User Input User Input User Input User Input User Input User Input User Input User Input User Input User Input User Input User Input 

	char user_input_location = ' ';
	char user_input_type = ' ';

	repeat = 'Y';
	cout << "\nAvailable Alabama Weather Station Data from year(s): " << years_loaded_str << endl << endl;
	do
	{
		//Defining necessary user input variables
		char user_input_location = ' ';
		char user_input_type = ' ';
		char user_input_time = ' ';

		//Takes location parameter for data
		string user_input_city = "";
		string user_input_station = "";
		cout << "Please select the scope of the data you are looking for: " << endl;
		cout << "A." << setw(60) << right << "Statewide data" << endl;
		cout << "B." << setw(60) << right << "City data" << endl;
		cout << "C." << setw(60) << right << "Station data" << endl << endl;

		cin >> user_input_location;
		if (user_input_location == 'B')
		{
			cout << "\nPlease input specific city in capital letters:" << endl;
			cin >> user_input_city;
		}
		else if (user_input_location == 'C')
		{
			cout << "\nPlease input specific station ID:" << endl;
			cin >> user_input_station;
		}

		// Takes data type parameters
		cout << "\nPlease select the type of data you are looking for: " << endl;
		cout << "A." << setw(60) << right << "Precipitation data" << endl;
		cout << "B." << setw(60) << right << "Temperature data" << endl;
		cout << "C." << setw(60) << right << "Wind data" << endl << endl;

		cin >> user_input_type;
		char user_input_type_stat = ' ';

		char user_input_temperature_maximum_type = ' ';
		char user_input_temperature_minimum_type = ' ';
		char user_input_wind_type = ' ';

		if (user_input_type == 'A')
		{
			cout << "\nPlease select the specific statistic you are looking for: " << endl;
			cout << "A." << setw(60) << right << "Precipitation amount" << endl;
			cout << "B." << setw(60) << right << "Snow depth" << endl;
			cout << "C." << setw(60) << right << "Snow amount" << endl << endl;

			cin >> user_input_type_stat;
		}
		else if (user_input_type == 'B')
		{
			cout << "\nPlease select the specific statistic you are looking for: " << endl;
			cout << "A." << setw(60) << right << "Average temperature" << endl;
			cout << "B." << setw(60) << right << "Maximum temperature" << endl;
			cout << "C." << setw(60) << right << "Minimum temperature" << endl;

			cin >> user_input_type_stat;

			if (user_input_type_stat == 'B')
			{
				cout << "\nPlease select the specific maximum temperature you are looking for: " << endl;
				cout << "A." << setw(60) << right << "Average maximum temperature" << endl;
				cout << "B." << setw(60) << right << "Absolute maximum temperature" << endl;

				cin >> user_input_temperature_maximum_type;
			}
			if (user_input_type_stat == 'C')
			{
				cout << "\nPlease select the specific minimum temperature you are looking for: " << endl;
				cout << "A." << setw(60) << right << "Average minimum temperature" << endl;
				cout << "B." << setw(60) << right << "Absolute minimum temperature" << endl;

				cin >> user_input_temperature_minimum_type;
			}
		}
		else if (user_input_type == 'C')
		{
			cout << "\nPlease select the specific statistic you are looking for: " << endl;
			cout << "A." << setw(60) << right << "Average wind speed" << endl;
			cout << "B." << setw(60) << right << "Fastest 2-minute wind speed" << endl;
			cout << "C." << setw(60) << right << "Fastest 5-second wind speed" << endl;

			cin >> user_input_type_stat;

			if (user_input_type_stat == 'B' || user_input_type_stat == 'C')
			{
				cout << "\nPlease select the type of stat you are looking for: " << endl;
				cout << "A." << setw(60) << right << "Average wind speed for selected interval" << endl;
				cout << "B." << setw(60) << right << "Highest wind speed for selected interval" << endl;

				cin >> user_input_wind_type;
			}
		}


		// Takes date range parameters for data
		cout << "\nPlease select the period of time for the data you are looking for: " << endl;
		cout << "A." << setw(60) << right << "All loaded data" << endl;
		cout << "B." << setw(60) << right << "Specific date range" << endl;
		cout << "C." << setw(60) << right << "Specific day" << endl << endl;

		string user_start_date = "";
		string user_end_date = "";

		cin >> user_input_time;
		if (user_input_time == 'B' || user_input_time == 'C')
		{

			if (user_input_time == 'B')
			{
				cout << "\nPlease input start date in the following format: YYYYMMDD" << endl;
				cin >> user_start_date;

				cout << "\nPlease input end date in the following format: YYYYMMDD" << endl;
				cin >> user_end_date;
			}
			if (user_input_time == 'C')
			{
				cout << "\nPlease input specific date in the following format: YYYYMMDD" << endl;
				cin >> user_start_date;
				user_end_date = user_start_date;
			}
		}


		// Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output 
		// Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output 
		// Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output 
		// Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output 
		// Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output 
		// Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output 
		// Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output 
		// Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output 
		// Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output 
		// Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output 
		// Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output 
		// Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output 
		// Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output 
		// Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output 
		// Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output Program Output 


		if (user_input_type == 'B' && user_input_type_stat == 'A') { //If user_input_type is temperature data and _stat is average temperature
			cout << "The average temperature with the parameters given is: " <<
				temperature_average(root_node, user_start_date, user_end_date, user_input_station, user_input_city);
		}

		if (user_input_type == 'B' && user_input_type_stat == 'B') { //If user_input_type is temperature data and _stat is maximum temperature
			if (user_input_temperature_maximum_type == 'A') //If maximum_type is average maximum temperature
			{
				cout << "The average maximum temperature is: " <<
					temperature_maximum(root_node, user_start_date, user_end_date, user_input_station, user_input_city, user_input_temperature_maximum_type)
					<< endl << endl;
			}
			else if (user_input_temperature_maximum_type == 'B') //If maximum_type is absolute maximum temperature
			{
				cout << "The absolute maximum temperature is: " <<
					temperature_maximum(root_node, user_start_date, user_end_date, user_input_station, user_input_city, user_input_temperature_maximum_type)
					<< endl << endl;
			}
		}

		if (user_input_type == 'B' && user_input_type_stat == 'C') { //If user_input_type is temperature data and _stat is minimum temperature
			if (user_input_temperature_minimum_type == 'A') //If minimum_type is average minimum temperature
			{
				cout << "The average minimum temperature is: " <<
					temperature_maximum(root_node, user_start_date, user_end_date, user_input_station, user_input_city, user_input_temperature_minimum_type)
					<< endl << endl;
			}
			else if (user_input_temperature_minimum_type == 'B') //If minimum_type is absolute minimum temperature
			{
				cout << "The absolute minimum temperature is: " <<
					temperature_minimum(root_node, user_start_date, user_end_date, user_input_station, user_input_city, user_input_temperature_minimum_type)
					<< endl << endl;
			}
		}

		if (user_input_type == 'A' && user_input_type_stat == 'A') { //If user_input_type is precipitation and _stat is precipitation amount
			cout << "The average precipitation amount with the parameters given is: " <<
				precipitation_amount(root_node, user_start_date, user_end_date, user_input_station, user_input_city)
				<< endl << endl;
		}

		if (user_input_type == 'A' && user_input_type_stat == 'B') { //If user_input_type is precipitation and _stat is snow depth
			cout << "The average snow depth with the parameters given is: " <<
				precipitation_snow_depth(root_node, user_start_date, user_end_date, user_input_station, user_input_city)
				<< endl << endl;
		}

		if (user_input_type == 'A' && user_input_type_stat == 'C') { //If user_input_type is precipitation and _stat is snow amount
			cout << "The average snow amount with the parameters given is: " <<
				precipitation_snow_amount(root_node, user_start_date, user_end_date, user_input_station, user_input_city)
				<< endl << endl;
		}

		if (user_input_type == 'C' && user_input_type_stat == 'A') { //If user_input_type is wind and _stat is wind average
			cout << "The average wind speed for the given parameters is: " <<
				wind_average(root_node, user_start_date, user_end_date, user_input_station, user_input_city)
				<< endl << endl;
		}

		if (user_input_type == 'C' && user_input_type_stat == 'B') { //If user_input_type is wind and _stat is 2 minute wind speed
			if (user_input_wind_type == 'A') //If wind_type is average wind speed
			{
				cout << "The average highest 2 minute wind speed for the given parameters is:" <<
					wind_two_minute(root_node, user_start_date, user_end_date, user_input_station, user_input_city, user_input_wind_type)
					<< endl << endl;
			}
			else if (user_input_wind_type == 'B') //If wind_type is highest wind speed
			{
				cout << "The highest 2 minute wind speed for the given parameters is: " <<
					wind_two_minute(root_node, user_start_date, user_end_date, user_input_station, user_input_city, user_input_wind_type)
					<< endl << endl;
			}
		}

		if (user_input_type == 'C' && user_input_type_stat == 'C') { //If user_input_type is wind and _stat is 5 second wind speed
			if (user_input_wind_type == 'A') //If wind_type is average wind speed
			{
				cout << "The average highest 5 second wind speed for the given parameters is:" <<
					wind_five_second(root_node, user_start_date, user_end_date, user_input_station, user_input_city, user_input_wind_type)
					<< endl << endl;
			}
			else if (user_input_wind_type == 'B') //If wind_type is highest wind speed
			{
				cout << "The highest 5 second wind speed for the given parameters is: " <<
					wind_five_second(root_node, user_start_date, user_end_date, user_input_station, user_input_city, user_input_wind_type)
					<< endl << endl;
			}
		}
		// loop data search?
		cout << "\n\nWould you like to continue to navigate the data and restart the program? (Y/N)" << endl;
		cin >> repeat;

	} while (repeat == 'Y');


	system("pause");
	return 0;
}


//Data establishment Functions

// Opens file for entering into struct node system
void load_data(char input, ifstream& file, string& years_loaded)
{
	if (input == 'A')
	{
		file.open("C:/CS/weather/New/23-01-01--23-08-07.txt");
		if (!file) { cout << "Weather .txt failed to open" << endl; }

		years_loaded += "2023\t";
	}
}

// Enter data to struct node system
void enter_data(station_data& data, ifstream& file)
{
	char ch = ' ';

	file >> data.station_id;

	for (int j = 0; j < 51; j++) {

		file.get(ch);
		data.station_name += ch;
	}

	file >> data.date >> data.mdpr >> data.dapr >> data.prcp >> data.snwd >> data.snow >> data.tavg >> data.tmax >> data.tmin >> data.awnd >> data.wsf2 >> data.wsf5;
}

// for debugging
void print_data(station_data& data, ifstream& file)
{
	cout << data.station_id << setw(6) << data.station_name << setw(6) << data.date << setw(6) << data.mdpr << setw(6) << data.dapr << setw(6) << data.prcp << setw(6) << data.snwd << setw(6) << data.snow;
	cout << setw(6) << data.tavg << setw(6) << data.tmax << setw(6) << data.tmin << setw(6) << data.awnd << setw(6) << data.wsf2 << setw(6) << data.wsf5 << endl;
}


// Data procedures

// Universal check function
bool check_entry(station_data* current_node, string start_date, string end_date, string station_id, string station_name)
{
	if (start_date != "") { if (current_node->date < start_date) { return false; } }
	if (end_date != "") { if (current_node->date > end_date) { return false; } }
	if (station_id != "")
	{
		if (current_node->station_id.find(station_id) == string::npos) { return false; }
	}
	if (station_name != "")
	{
		if (current_node->station_name.find(station_name) == string::npos) { return false; }
	}
	return true;
}

// Temp procedures
float temperature_average(station_data* root_node, string start_date, string end_date, string station_id, string station_name)
{
	float temperature_average = 0.0;
	station_data* current_node = root_node;

	int i = 0;

	while (current_node->link != NULL)
	{
		current_node = current_node->link;
		if (!check_entry(current_node, start_date, end_date, station_id, station_name)) { continue; }
		if (current_node->tavg < 0) { continue; }

		temperature_average += current_node->tavg;
		i++;

		//Debugging
		/*cout << "Name: " << station_name << "\t" << current_node->station_name.find(station_name) << "/t" <<
			current_node->station_name << "\tDate: " << current_node->date << "\tTAVG: " << current_node->tavg << endl;*/

	}

	temperature_average /= i;

	return temperature_average;
}
float temperature_maximum(station_data* root_node, string start_date, string end_date, string station_id, string station_name, char maximum_type)
{
	float temperature_maximum = 0.0;

	station_data* current_node = root_node;

	int i = 0;

	while (current_node->link != NULL)
	{
		current_node = current_node->link;

		if (!check_entry(current_node, start_date, end_date, station_id, station_name)) { continue; }
		if (current_node->tmax < 0) { continue; }

		i++;

		if (maximum_type == 'A') // If maximum type requested is max temp average
		{
			temperature_maximum += current_node->tmax;
		}

		if (maximum_type == 'B') // If maximum type requested is max max temp
		{
			if (current_node->tmax > temperature_maximum)
			{
				temperature_maximum = current_node->tmax;
			}
		}

		// Debugging 
		/*cout << "Name: " << station_name << "\t" << current_node->station_name.find(station_name) << "/t" <<
			current_node->station_name << "\tDate: " << current_node->date << "\tTMAX: " << current_node->tmax << endl;*/
	}

	// Calculate avg if maximum type requested is avg
	if (maximum_type == 'A') { temperature_maximum /= i; }

	return temperature_maximum;
}
float temperature_minimum(station_data* root_node, string start_date, string end_date, string station_id, string station_name, char minimum_type)
{
	float temperature_minimum = 100.0;
	if (minimum_type == 'A') { temperature_minimum = 0; }

	station_data* current_node = root_node;

	int i = 0;

	while (current_node->link != NULL)
	{
		current_node = current_node->link;

		if (!check_entry(current_node, start_date, end_date, station_id, station_name)) { continue; }
		if (current_node->tmin < -100) { continue; }

		i++;

		if (minimum_type == 'A') // If mininmum type requested is min temp average
		{
			temperature_minimum += current_node->tmin;
		}

		if (minimum_type == 'B') // If minimum type requested is min min temp
		{
			if (current_node->tmin < temperature_minimum)
			{
				temperature_minimum = current_node->tmin;
			}
		}

		// Debugging 
		/*std::cout << "Name: " << station_name << "   " << current_node->station_name.find(station_name) << "/t" <<
			current_node->station_name << "\tDate: " << current_node->date << "\tTMIN: " << current_node->tmin << endl;*/
	}

	// Calculate avg if minimum type requested is avg
	if (minimum_type == 'A') { temperature_minimum /= i; }

	return temperature_minimum;
}

// Precipitation procedures
float precipitation_amount(station_data* root_node, string start_date, string end_date, string station_id, string station_name)
{
	float precipitation_amount = 0.0;
	station_data* current_node;
	current_node = root_node;

	int i = 0;
	while (current_node->link != NULL)
	{
		current_node = current_node->link;

		if (!check_entry(current_node, start_date, end_date, station_id, station_name)) { continue; }
		if (current_node->prcp < 0) { continue; }

		precipitation_amount += current_node->prcp;
		i++;
	}

	precipitation_amount /= i;
	return precipitation_amount;
}
float precipitation_snow_depth(station_data* root_node, string start_date, string end_date, string station_id, string station_name)
{
	float precipitation_snow_depth = 0.0;
	station_data* current_node;
	current_node = root_node;

	int i = 0;
	while (current_node->link != NULL)
	{
		current_node = current_node->link;

		if (!check_entry(current_node, start_date, end_date, station_id, station_name)) { continue; }
		if (current_node->snwd < 0) { continue; }

		precipitation_snow_depth += current_node->snwd;
		i++;
	}

	precipitation_snow_depth /= i;
	return precipitation_snow_depth;
}
float precipitation_snow_amount(station_data* root_node, string start_date, string end_date, string station_id, string station_name)
{
	float precipitation_snow_amount = 0.0;
	station_data* current_node;
	current_node = root_node;

	int i = 0;
	while (current_node->link != NULL)
	{
		current_node = current_node->link;

		if (!check_entry(current_node, start_date, end_date, station_id, station_name)) { continue; }
		if (current_node->snow < 0) { continue; }

		precipitation_snow_amount += current_node->snow;
		i++;
	}

	precipitation_snow_amount /= i;
	return precipitation_snow_amount;
}

// Wind procedures
float wind_average(station_data* root_node, string start_date, string end_date, string station_id, string station_name)
{
	float wind_average = 0.0;
	station_data* current_node;
	current_node = root_node;

	int i = 0;
	while (current_node->link != NULL)
	{
		current_node = current_node->link;

		if (!check_entry(current_node, start_date, end_date, station_id, station_name)) { continue; }
		if (current_node->awnd < 0) { continue; }


		wind_average += current_node->awnd;
		i++;
	}

	wind_average /= i;
	return wind_average;
}
float wind_two_minute(station_data* root_node, string start_date, string end_date, string station_id, string station_name, char type)
{
	float wind_two_minute = 0.0;
	station_data* current_node = root_node;

	int i = 0;
	while (current_node->link != NULL)
	{
		current_node = current_node->link;

		if (!check_entry(current_node, start_date, end_date, station_id, station_name)) { continue; }
		if (current_node->wsf2 < 0) { continue; }

		i++;

		if (type == 'A') // If type requested is wind speed average
		{
			wind_two_minute += current_node->wsf2;
		}

		if (type == 'B') // If type requested is max wind speed
		{
			if (current_node->wsf2 > wind_two_minute)
			{
				wind_two_minute = current_node->wsf2;
			}
		}


	}

	// Calculate avg if type requested is avg
	if (type == 'A') { wind_two_minute /= i; }

	return wind_two_minute;
}
float wind_five_second(station_data* root_node, string start_date, string end_date, string station_id, string station_name, char type)
{
	float wind_five_second = 0.0;
	station_data* current_node = root_node;

	int i = 0;
	while (current_node->link != NULL)
	{
		current_node = current_node->link;

		if (!check_entry(current_node, start_date, end_date, station_id, station_name)) { continue; }
		if (current_node->wsf5 < 0) { continue; }

		i++;

		if (type == 'A') // If type requested is wind speed average
		{
			wind_five_second += current_node->wsf5;
		}

		if (type == 'B') // If type requested is max wind speed
		{
			if (current_node->wsf5 > wind_five_second)
			{
				wind_five_second = current_node->wsf5;
			}
		}


	}

	// Calculate avg if type requested is avg
	if (type == 'A') { wind_five_second /= i; }

	return wind_five_second;
}
