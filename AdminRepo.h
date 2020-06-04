#pragma once

#include "Movie.h"

class AdminRepo{
public:
 
	AdminRepo();
	//creeaza un fisier txt/csv
	void create_csv(Movie m);
	//fisier txt/csv
	void read_csv();
	//deschide fisierul txt/csv
	void open_csv();
	//face update la un atribut al filmului
	void update_csv();
	//sterge un film din txt/csv
	void delete_csv();
	//cauta un film dupa dupa gen
	int search_genre(string genre);
	//returneaza link-ul filmului
	string getLink(string title);
};