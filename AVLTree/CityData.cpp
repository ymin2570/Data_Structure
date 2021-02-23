#include "CityData.h"

CityData::CityData()		//Constructor
{
	LocationId = 0;
	name = new char[50];
	country = new char[50];
}

CityData::~CityData()
{
}

int CityData::GetLocationId()//Return Id
{
	return LocationId;
}

char * CityData::Getname()//Return name
{
	return name;
}

char * CityData::Getcountry()//Return country
{
	return country;
}

void CityData::SetLocationId(int LocationId)//Change Id
{
	CityData::LocationId = LocationId;
}

void CityData::Setname(char * name)//Change name
{
	strcpy(this->name, name);
}

void CityData::Setcountry(char * country)//Change country
{
	strcpy(this->country, country);
}
