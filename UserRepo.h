#pragma once

#include "Movie.h"

class UserRepo{
public:

	UserRepo();
	//creeaza fisier txt/csv
	void create_csv(string l1, string l2);

	void read_csv();
	//deschide fisier txt/csv
	void open_csv();
	
	void update_csv(string title);

	//sterge din fisier txt/csv
	int delete_csv();
};