#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>

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
