#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;
/*
implementasi array -> done
implementasi struct -> done
implementasi pointer
implementasi search
implementasi sorting
implementasi queue

*/
struct guest {
	string nama;
	int nik;
	string address;
	int umur;
} person[100];// Implementasi array of struct

int jumlah = 0;

void mainMenu();
void quisioner();
bool regist();
bool auth(string username, string password);
bool login();

int main() {
	SetConsoleTitle(TEXT("Hospital Helper"));
	if (login())
	{
		mainMenu();
	}
	

	return 0;
}


void mainMenu() {
	string uname, pass;
	int pilihan;
	system("cls");
	cout << "Menu" << endl;
	cout << "--------------------------" << endl;
	cout << "1. Screening Covid-19" << endl;
	cout << "2. Rapid test" << endl;// implementasi queue
	cout << "3. Cek data vaksinasi" << endl;
	cout << "4. Pengajuan vaksinasi" << endl;
	cout << "e. keluar" << endl;

	cout << "Masukan pilihan kamu => ";
	cin >> pilihan;
	switch (pilihan)
	{
	case 1:
		if (regist())
			quisioner();
		break;
	case 5:
		break;
	default:
		cout << "Terimakasih" << endl;
		exit(0);
		break;
	}
}

bool regist() {
	char pilihan;
	system("cls");
	cout << "Sebelum melanjutkan apakah data diri pasien bersedia tersimpan dalam database?" << endl;
	cout << "Y/n? -> ";
	cin >> pilihan;
	
	if (pilihan == 'y' || pilihan == 'Y') {
		cout << "Data diri pasien" << endl;
		cout << "Nama : ";
		cin.ignore();
		getline(cin, person[jumlah].nama);
		cout << "Umur : ";
		cin >> person[jumlah].umur;
		cout << "NIK  : ";
		cin >> person[jumlah].nik;
		cout << "Alamat : ";
		cin.ignore();
		getline(cin, person[jumlah].address);
		jumlah++;
		return true;
	}
	else
	{
		cout << "Mohon maaf kamu tidak dapat melakukan deteksi mandiri." << endl;
		return false;
	}
		

	
}

void quisioner() {
	string pilihan;
	int yes = 0;
	string question[5] = {
		"Apakah pasien demam?",
		"Apakah pasien batuk/pilek?",
		"Apakah Anda pernah kontak dengan pasien positif COVID-19 atau berada satu ruangan yang sama atau kontak dalam 1 meter pada 14 hari terakhir ?",
		"Apakah Anda pernah berkunjung atau tinggal ke negara atau daerah endemis COVID-19 dalam 14 hari Terakhir?",
		"Apakah Anda mengalami Diare pada 14 hari terakhir ?"
	};

	for (int i = 0; i < 5; i++)
	{
		cout << question[i] << endl;
		cout << "ya/tidak?\n->";
		cin >> pilihan;
		if (pilihan == "ya" || pilihan == "Ya")
			yes++;
	}

	if (yes <= 2) {
		cout << "Lakukan perawatan mandiri di rumah dengan beristirahat jika seminggu tidak ada perubahan segera datang ke klinik terdekta" << endl;
	}
	else if (yes == 3)
	{
		cout << "Kondisi anda kurang fit, segera periksa dokter terdekat!" << endl;
	}
	else {
		cout << "Segera lakukan rapid test, Datang ke Fasilitas Kesehatan terdekat atau Hubungi segera layanan 119 Ext 9." << endl;
	}
}

bool auth(string username, string password) {
	string db[5][2] = {
		{"anhalim", "admin"},
		{"indra", "indraadmin077"},
		{"Wibisono", "wibiganteng"},
		{"admin", "admin"}
	};// Implementasi array 2D
	int i = 0;

	do
	{
		if (username == db[i][i] && password == db[i][i + 1])
			return true;
		i++;
	} while (i<5);

	cout << "Password atau username salah!" << endl;
	return false;
}

bool login() {
	string username, password;
	cout << "LOGIN" << endl;
	cout << "Username : "; cin >> username;
	cout << "Passsword : "; cin >> password;
	if (auth(username, password))
		return true;
	else
		return false;

}


void rapid() {//implementasi queue
	char pilih;
	int nik, i = 0;
	cout << "Apakah pasien sebelumnya sudah terdaftar? Y/n : ";
	cin >> pilih;
	if (pilih == 'Y' || pilih == 'y')
	{
		cout << "Silahkan masukan NIK anda : ";
		cin >> nik;
		while (i == jumlah)
		{
			if (person[i].nik == nik)
			{

			}
			i++;
		}
	}

}