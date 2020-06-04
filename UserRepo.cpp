#include "UserRepo.h"

UserRepo::UserRepo() = default;

void UserRepo::create_csv(string l1, string l2){
	fstream fout;

	fout.open("UserRepo.txt", ios::out | ios::app);

	fout << l1 << '\n';
	fout << l2 << '\n';
}

void UserRepo::read_csv(){
	fstream fin;
	vector<string> lines;
	string line;
	fin.open("UserRepo.txt", ios::in);

	while (getline(fin, line))
		lines.push_back(line);

	for (size_t i = 0; i < lines.size(); ++i)
		cout << lines[i] << '\n';

	fin.close();
}

void UserRepo::open_csv(){
	system("notepad.exe UserRepo.txt");
}

void UserRepo::update_csv(string title){
	fstream fin, fout;
	int i, pos, index = 0, intLike;
	string line, update_line, link_line, strLike;
	vector<string> row;

	//citire si scriere txt/csv
	fin.open("AdminRepo.txt", ios::in);
	fout.open("AdminRepoCopy.txt", ios::out);

	row.clear();

	while (getline(fin, line)){
		if (!line.find(title)){
			update_line = line;
			getline(fin, line);
			link_line = line;
		}
	}

	for (i = 0; i < 3; i++){
		pos = update_line.find(',');
		row.push_back(update_line.substr(0, pos));
		update_line.erase(0, pos + 2);
	}

	//update atribut
	row.push_back(update_line);
	//update link
	row.push_back(link_line);


	strLike = row[3];
	stringstream geek(strLike);
	intLike = 0;
	geek >> intLike;

	intLike++;
	strLike = to_string(intLike);
	row[3] = strLike;

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

int UserRepo::delete_csv(){
	fstream finUser, foutUser;
	string title, line, blank;
	int pos, like;
	vector<string> row;
	bool exista;

	//deschidere txt/csv
	finUser.open("UserRepo.txt", ios::in);
	foutUser.open("UserRepo.txt", ios::out);

	cout << "Title: ";
	getline(cin, blank);
	getline(cin, title);

	exista = false;
	while (!finUser.eof()){
		getline(finUser, line);
		pos = line.find(title);
		if (pos != string::npos){
			exista = true;
		}
	}

	finUser.close();

	if (!exista){
		cout << "Not found!" << endl;
		return 1;
	}

	cout << "Like?" << endl;
	cout << "1->YES    2->NO" << endl;
	cin >> like;

	if (like == 1){
		update_csv(title);
	}

	finUser.open("UserRepo.txt", ios::in);

	while (!finUser.eof()){
		getline(finUser, line);
		if (line.find(title)){
			row.push_back(line);
			getline(finUser, line);
			row.push_back(line);
		}
		else
			getline(finUser, line);
	}

	finUser.close();

	for (int i = 0; i < row.size(); i++){
		foutUser << row[i] << "\n";
	}

	foutUser.close();

	remove("UserRepo.txt");
	rename("UserRepoCopy.txt", "UserRepo.txt");

	return 0;
}