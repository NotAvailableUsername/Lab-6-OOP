#include "AdminRepo.h"

AdminRepo::AdminRepo() = default;

void AdminRepo::create_csv(Movie m){
	fstream fout;

	fout.open("AdminRepo.txt", ios::out | ios::app);

	fout << m.getTitle() << ", "
		<< m.getGenre() << ", "
		<< m.getYear() << ", "
		<< m.getLikes() << "\n";

	fout << m.getTrailer() << "\n";
}

void AdminRepo::read_csv(){
	fstream fin;
	vector<string> lines;
	fin.open("AdminRepo.txt", ios::in);

	string line;
	while (getline(fin, line))
		lines.push_back(line);

	for (size_t i = 0; i < lines.size(); ++i)
		cout << lines[i] << '\n';

	fin.close();
}

void AdminRepo::open_csv(){
	system("notepad.exe AdminRepo.txt");
}

void AdminRepo::update_csv(){
	fstream fin, fout;
	char atr;
	int i, pos, index = 0;
	string title, new_atr, line, update_line, link_line, str, blank;
	vector<string> row;
	bool exista;

	//citire si scriere in txt/csv
	fin.open("AdminRepo.txt", ios::in);
	fout.open("AdminRepoCopy.txt", ios::out);

	//update Title
	cout << "Title: ";
	getline(cin, blank);
	getline(cin, title);

	row.clear();
	exista = false;
	while (getline(fin, line)){
		if (!line.find(title)){
			update_line = line;
			getline(fin, line);
			link_line = line;
			exista = true;
		}
	}

	//daca nu exista filmul
	if (!exista){
		cout << "Not found!";
		exit(0);
	}

	//atributul care trebuie sa fie actualizat 
	cout << "T = titlu,  G = gen,  Y = An,  L = Numar Like, H = Adresa URL" << endl;
	cout << "Alegeti ce doriti sa actualizati: ";
	cin >> atr;

	if (atr == 't' || atr == 'T')
		index = 0;
	else if (atr == 'g' || atr == 'G')
		index = 1;
	else if (atr == 'y' || atr == 'Y')
		index = 2;
	else if (atr == 'l' || atr == 'L')
		index = 3;
	else if (atr == 'h' || atr == 'H')
		index = 4;
	else{
		cout << "Invalid. Try again!\n";
		exit(0);
	}

	cout << "New: ";
	getline(cin, blank);
	getline(cin, new_atr);

	for (i = 0; i < 3; i++){
		pos = update_line.find(',');
		row.push_back(update_line.substr(0, pos));
		update_line.erase(0, pos + 2);
	}

	row.push_back(update_line);
	row.push_back(link_line);

	row[index] = new_atr;

	//copiez in fisierul nou 
	fout << row[0] << ", " << row[1] << ", " << row[2] << ", " << row[3] << "\n";
	fout << row[4] << "\n";

	fin.close();
	fin.open("AdminRepo.txt", ios::in);

	while (!fin.eof()){
		getline(fin, line);
		if (line.find(title)){
			fout << line << endl;
			getline(fin, line);
			fout << line << endl;
		}
		else
			getline(fin, line);
	}

	fin.close();
	fout.close();

	remove("AdminRepo.txt");
	rename("AdminRepoCopy.txt", "AdminRepo.txt");
}

void AdminRepo::delete_csv(){
	fstream fin, fout;
	string title, line, blank;
	vector<string> row;
	bool exista;

	//deschid fisierele txt/csv
	fin.open("AdminRepo.txt", ios::in);
	fout.open("AdminRepoCopy.txt", ios::out);

	cout << "Title: ";
	getline(cin, blank);
	getline(cin, title);

	//verific daca exista fimul in AdminRepo.txt
	exista = false;
	while (!fin.eof()){
		getline(fin, line);
		if (!line.find(title))
			exista = true;
	}

	fin.close();

	while (!exista){
		cout << "Not found!" << endl;
		break;
	}

	fin.open("AdminRepo.txt", ios::in);

	while (!fin.eof()){
		getline(fin, line);
		if (line.find(title)){
			row.push_back(line);
			getline(fin, line);
			row.push_back(line);
		}
		else
			getline(fin, line);
	}

	fin.close();

	for (int i = 0; i < row.size(); i++){
		fout << row[i] << "\n";
	}

	fout.close();

	remove("AdminRepo.txt");
	rename("AdminRepoCopy.txt", "AdminRepo.txt");
}

int AdminRepo::search_genre(string genre){
	fstream fin;
	string line;
	vector<string> row;
	size_t pos;

	fin.open("AdminRepo.txt", ios::in);

	while (!fin.eof()){
		getline(fin, line);
		pos = line.find(genre);
		if (pos != string::npos){
			row.push_back(line);
			getline(fin, line);
			row.push_back(line);
		}
	}

	if (row.size() == 0){
		cout << "Not found!" << endl;
		return 0;
	}
	else{
		cout << "Film after genre: " << endl;
		for (int i = 0; i < row.size(); i++){
			cout << row[i] << endl;
		}
		return 1;
	}
}

string AdminRepo::getLink(string title){
	fstream fin;
	string line;
	size_t pos;

	fin.open("AdminRepo.txt", ios::in);

	while (!fin.eof()){
		getline(fin, line);
		pos = line.find(title);
		if (pos != string::npos){
			getline(fin, line);
			return line;
		}
	}
}