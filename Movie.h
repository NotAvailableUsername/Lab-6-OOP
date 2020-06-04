#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Movie{
private:

	string title, genre, year, likes, link;

public:

	Movie();

	Movie(string title, string genre, string year, string likes, string link);

	string getTitle();

	void setTitle(string title);

	string getGenre();

	void setGenre(string genre);

	string getYear();

	void setYear(int year);

	string getLikes();

	void setLikes(int likes);

	string getTrailer();

	void setTrailer(string link);
};