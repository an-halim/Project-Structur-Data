#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <string.h>
#include <queue>

using namespace std;
/*
implementasi array -> done
implementasi struct -> done
implementasi pointer
implementasi search -> done
implementasi sorting -> done
implementasi queue

*/
struct guest {
	string nama;
	char nik[17]{};
	string address;
	int umur{};
} person[100];// Implementasi array of struct

int jumlah = -1; // public

bool login();
bool auth(string username, string password);
void loading();
void mainMenu(queue<string> g);
bool regist();
void quisioner(queue<string> g);
void rapid(queue<string> q);
int cari(char nik[]);
void sorting(int sortMode);
void cetakHasil(string data);
string saveToTxt(string name, string addres, char nik[], int umur, string data);
void exitConfirm();
void showq(queue<string> g);


int main() {
	SetConsoleTitle(TEXT("Hospital Helper"));
	bool isLogin;
	queue<string> antri;
	do
	{
		system("cls");
		isLogin = login();
		if (isLogin)
		{
			cout << "Login berhasil!";
			Sleep(1200);
			loading();
			mainMenu(antri);
		}
	} while (!isLogin);

	return 0;
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

bool auth(string username, string password) {
	string db[5][3] = {
		{"anhalim", "admin", "ahmad nur halim"},
		{"indra", "indraadmin077", "full name"},
		{"Wibisono", "wibiganteng", "full name"},
		{"admin", "admin", "full name" }
	};// Implementasi array 2D
	int i = 0;

	do
	{
		if (username == db[i][0] && password == db[i][1]) {
			return true;
		}
		i++;
	} while (i < 5);

	cout << "Password atau username salah!" << endl;
	Sleep(1000);
	return false;
}

void loading() {
	string s = " ";
	for (int i = 0; i < 100; i++) {
		system("cls");
		cout << "\n\n\n\n\n\t\t\t\t\t\t\tLoading " << i << "% ";
		s += "=";
		cout << endl;
		cout << "\t" << s;
	}
}

void mainMenu(queue<string> g) {
	string uname, pass;
	char nik[17];
	int pilihan, hasil;
	char pilih;
	bool isRegistered;
	awal:

	system("cls");
	cout << "Menu" << endl;
	cout << "--------------------------" << endl;
	cout << "1. Registrasi pasien" << endl;
	cout << "2. Screening Covid-19" << endl;
	cout << "3. Rapid test" << endl;// implementasi queue
	cout << "4. Cari data pasien" << endl; // implementasi searching
	cout << "5. Tampilkan data pasien" << endl; // implementasi sorting
	cout << "6. keluar" << endl;

	cout << "Masukan pilihan kamu => ";
	cin >> pilihan;
	switch (pilihan)
	{
	case 1:
		isRegistered = regist();
		if (isRegistered)
		{
			system("cls");
			cout << "Registrasi berhasil!" << endl;
		}
		break;
	case 2:
		cout << "Apakah pasien sebelumnya sudah terdaftar? [Y/n] -> ";
		cin >> pilih;
		if (pilih == 'Y' || pilih == 'y')
		{
			cout << "Silahkan masukan NIK anda : ";
			cin >> nik;
			hasil = cari(nik);
			if (hasil != -1)
			{
				quisioner(g);
			}
		}
		else
		{
			isRegistered = regist();
			if (isRegistered)
			{
				system("cls");
				cout << "Registrasi berhasil!" << endl;
			}
		}
		break;
	case 3:
		rapid(g);
		break;
	case 4:
		system("cls");
		cout << "Masukan NIK pasien: ";
		cin >> nik;
		hasil = cari(nik);
		if (hasil != -1)
		{
			cout << "Nama: " << person[hasil].nama << endl;
			cout << "Umur: " << person[hasil].umur << endl;
			cout << "NIK: " << person[hasil].nik << endl;
			cout << "Alamat: " << person[hasil].address << endl;
		}
		break;
	case 5:
		system("cls");
		cout << "Pilih tipe pengurutan data" << endl;
		cout << "1. ascending(menaik)" << endl;
		cout << "2. descending(menurun)" << endl;
		cout << "Masukan pilihan -> ";
		int k;
		cin >> k;
		sorting(k);
		break;
	case 6:
		exitConfirm();
		break;
	default:
		cout << "Pilihan menu tidak tersedia!" << endl;
		break;
	}
	cout << "\nKembali ke menu utama? [Y/n] -> ";
	cin >> pilih;
	if (pilih == 'Y' || pilih =='y')
		goto awal;
	else
		exitConfirm();
}

bool regist() {
	char pilihan;
	system("cls");
	cout << "Sebelum melanjutkan apakah data diri pasien bersedia tersimpan dalam database? [Y/n] -> ";
	cin >> pilihan;
	
	if (pilihan == 'y' || pilihan == 'Y') {
		jumlah++;
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
		return true;
	}
	else
	{
		cout << "Registrasi gagal!" << endl;
		Sleep(1000);
		return false;
	}
}

void quisioner(queue<string> g) {
	system("cls");
	string pilihan, hasil;
	int yes = 0;
	string question[5] = {
		"Apakah pasien demam?",
		"Apakah pasien batuk/pilek?",
		"Apakah Anda pernah kontak dengan pasien positif COVID-19 atau berada satu ruangan yang sama atau kontak dalam 1 meter pada 14 hari terakhir ?",
		"Apakah Anda pernah berkunjung atau tinggal ke negara atau daerah endemis COVID-19 dalam 14 hari Terakhir?",
		"Apakah Anda mengalami Diare pada 14 hari terakhir ?"
	};

	string answer[3] = {
		"Lakukan perawatan mandiri di rumah dengan beristirahat jika seminggu tidak ada perubahan segera datang ke klinik terdekta",
		"Kondisi anda kurang fit, segera periksa dokter terdekat!",
		"Segera lakukan rapid test di Fasilitas Kesehatan terdekat atau Hubungi segera layanan 119 Ext 9."
	};

	cout << "Silahkan isi quisioner berikut\n" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << question[i] << endl;
		cout << "ya/tidak?\n->";
		cin >> pilihan;
		if (pilihan == "ya" || pilihan == "Ya" || pilihan == "YA" || pilihan == "Y" || pilihan == "y")
			yes++;
	}

	if (yes <= 2) {
		hasil = answer[0];
		cetakHasil(hasil);
	}
	else if (yes == 3) {
		hasil = answer[1];
		cetakHasil(hasil);
	}
	else {
		hasil = answer[2];
		cetakHasil(hasil);
	}
	
	cout << "Simpan hasil tes kedalam file? [Y/n] -> ";
	cin >> pilihan;
	if (pilihan == "ya" || pilihan == "YA" || pilihan == "y" || pilihan == "Y") {
		string save = saveToTxt(person[jumlah].nama, person[jumlah].address, person[jumlah].nik, person[jumlah].umur, hasil);
		cout << "\nFile tersimpan dalam " << save << endl;
	}

	cout << "Apakah anda ingin melakukan rapid test? [Y/n] -> ";
	cin >> pilihan;
	if (pilihan == "ya" || pilihan == "YA" || pilihan == "y" || pilihan == "Y")
		rapid(g);
	else
		mainMenu(g);
}

void rapid(queue<string> q) {//implementasi queue
	char pilih;
	int pilihan;
	char nik[17];
	int hasil, i = 0;

		cout << "Apakah pasien sebelumnya sudah terdaftar? [Y/n] -> ";
		cin >> pilih;
		if (pilih == 'Y' || pilih == 'y')
		{
			cout << "Silahkan masukan NIK anda : ";
			cin >> nik;
			hasil = cari(nik);
			if (hasil != -1)
			{
				showq(q);
				cout << "RAPID TEST" << endl;
				cout << "1. Ambil antrian" << endl;
				cout << "2. Panggil antrian" << endl;
				cout << "Silahkan masukan antrian yang akan diambil -> ";
				cin >> pilihan;
				if (pilihan == 1 )
				{
					q.push(person[hasil].nama);
				}
				else if (pilihan == 2)
				{
					if (q.empty())
						cout << "Antrian kosong!" << endl;
					else
						q.pop();
				}

			}
		}
		else
		{
			regist();
		}

}

int cari(char nik[]) { //implementasi squential search
	int posisi = -1;
	for (int i = 0; i < 100; i++)
	{
		if (strcmp(nik, person[i].nik) == 0) {
			posisi = i;
			cout << "Data ditemukan!!" << endl;
		}
	}
	
	if (posisi == -1)
	{
		cout << "Data tidak ditemukan!!" << endl;
	}
	return posisi;
}

void sorting(int sortMode) { //implemetasi bubble sort
	bool tukar;
	int tempUmur, j, i;
	char tempNIK[17];
	string tempAdd, tempNama;
	int total = jumlah + 1;

	system("cls");
	if (jumlah == -1) {
		cout << "Data pasien kosong!" << endl;
		return;
	} 
	else if (sortMode == 1)// ascending
	{
		i = 0;
		tukar = true;
		while ((i <= total - 2) && (tukar))
		{
			tukar = false;
			for (j = total - 1; j >= i + 1; j--)
			{
				if (person[j].umur < person[j - 1].umur)
				{
					{
						tempUmur = person[j].umur;
						person[j].umur = person[j - 1].umur;
						person[j - 1].umur = tempUmur;

						for (int i = 0; i < 17; i++) {
							tempNIK[i] = person[j].nik[i];
							person[j].nik[i] = person[j - 1].nik[i];
							person[j - 1].nik[i] = tempNIK[i];
						}

						tempNama = person[j].nama;
						person[j].nama = person[j - 1].nama;
						person[j - 1].nama = tempNama;

						tempAdd = person[j].address;
						person[j].address = person[j - 1].address;
						person[j - 1].address = tempAdd;
						tukar = true;
					}
				}
				i++;
			}
		}
	}
	else if(sortMode == 2)// descending
	{
		i = 0;
		tukar = true;
		while ((i <= total - 2) && (tukar))
		{
			tukar = false;
			for (j = total - 1; j >= i + 1; j--)
			{
				if (person[j].umur > person[j - 1].umur)
				{
					tempUmur = person[j].umur;
					person[j].umur = person[j - 1].umur;
					person[j - 1].umur = tempUmur;

					for (int i = 0; i < 17; i++) {
						tempNIK[i] = person[j].nik[i];
						person[j].nik[i] = person[j - 1].nik[i];
						person[j - 1].nik[i] = tempNIK[i];
					}

					tempNama = person[j].nama;
					person[j].nama = person[j - 1].nama;
					person[j - 1].nama = tempNama;

					tempAdd = person[j].address;
					person[j].address = person[j - 1].address;
					person[j - 1].address = tempAdd;
					tukar = true;
				}
			}
			i++;
		}
	}
	else {
		cout << "Maaf sepertinya menu nomor " << sortMode << " tidak tersedia!" << endl;
		Sleep(2000);
		return;
	}

	if (sortMode == 1)
		cout << "Data pasien berdasarkan umur termuda" << endl;
	else
		cout << "Data pasien berdasarkan umur tertua" << endl;

	for (i = 0; i <= jumlah; i++) {
		int no = i + 1;
		cout <<
			no << ".\tNama : " << person[i].nama
			<< "\n\tUmur : " << person[i].umur
			<< "\n\tNIK  : " << person[i].nik
			<< "\n\tAlamat : " << person[i].address << endl;
	}
		
}

void cetakHasil(string data) {
	system("cls");
	cout << "===========Hasil periksa============" << endl;
	cout << "Nama: " << person[jumlah].nama << endl;
	cout << "Umur: " << person[jumlah].umur << endl;
	cout << "NIK: " << person[jumlah].nik << endl;
	cout << "Alamat: " << person[jumlah].address << endl;
	cout << "Hasil: " << data << endl;
	cout << "====================================" << endl;
}

string saveToTxt(string name, string addres, char nik[], int umur, string data) {
	string fileName = name + "_HASILSCREENING.txt";
	ofstream myfile(fileName);
	if (myfile.is_open())
	{
		myfile << "===========Hasil periksa============" << endl;
		myfile << "Nama: " << person[jumlah].nama << endl;
		myfile << "Umur: " << person[jumlah].umur << endl;
		myfile << "NIK: " << person[jumlah].nik << endl;
		myfile << "Alamat: " << person[jumlah].address << endl;
		myfile << "Hasil: " << data << endl;
		myfile << "===================================" << endl;
		myfile.close();
		return "Hasil tersimpan dalam " + fileName;
	}
	else
	{
		return "Gagal menyimpan file!";
	}
}

void exitConfirm() {
	string konfir, username, password;
	system("cls");
	cout << "Semua data pasien yang tersimpan akan terhapus!" << endl;
	cout << "Apakah anda yakin keluar? [Y/n] -> ";
	cin >> konfir;
	if (konfir == "Y" || konfir == "y")
	{
		cout << endl;
		cout << "Sebagai konfirmasi akhir silahkan masukan username dan password anda" << endl;
		cout << "Username : ";
		cin >> username;
		cout << "Password : ";
		cin >> password;
		if (auth(username, password))
		{
			exit(0);
		}
	}
}

void showq(queue<string> g)
{
	while (!g.empty()) {
		cout << '\t' << g.front();
		g.pop();
	}
	cout << '\n';
}
