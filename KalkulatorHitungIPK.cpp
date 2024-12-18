#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <iomanip>

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;

vector<string> dataNamaMatkul;
vector<string> indexPrestasiMatkul;
vector<float> dataNilaiMatkul;
vector<int> dataSKSmatkul;

string IndeksPrestasi[12] = { "A", "A-", "B+", "B", "B-", "C+", "C-", "C", "D+", "D-", "D", "E" };

const int MIDDLE = 55;
int totalSemester;
int totalMatkulPerSemester;
int SKS;
int totalSKSselamaKuliah;
float IPK;
float totalNilaiMatkulSelamaKuliah;

string nilai;
string namaMatkul;

bool isRunning = true;
bool sedangInputNamaMatkul = true;
bool sedangInputNilaiMatkul = false;
bool sedangInputSKSMatkul = false;
bool inputSalah = true;
bool selesaiInput = false;

void PrintWithNewLine(string text);
void PrintWithNoNewLine(string text);
float KonversiNilaiMatkul(string IndexNilai);

int main()
{
	PrintWithNewLine(string(MIDDLE, ' ') + "KALKULATOR IPS");
	PrintWithNewLine("Input berapa semester yang mau dihitung\n");

	cout << ">";
	cin >> totalSemester;

	for (int iterasi = 1; iterasi <= totalSemester; iterasi++)
	{
		system("cls");
		PrintWithNewLine("SEMESTER " + std::to_string(iterasi));
		PrintWithNewLine("\nBerapa matkul di semester " + std::to_string(iterasi));

		cout << ">";
		cin >> totalMatkulPerSemester;

		for (int iterasiMatkul = 1; iterasiMatkul <= totalMatkulPerSemester;)
		{
			if (sedangInputNamaMatkul) {

				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				PrintWithNoNewLine("\nMasukan nama matkul " + std::to_string(iterasiMatkul) + " (Pastikan Huruf Besarnya Kecilnya!): ");
				std::getline(cin, namaMatkul);

				dataNamaMatkul.push_back(namaMatkul);
				sedangInputNamaMatkul = false;
				sedangInputNilaiMatkul = true;
			}

			if (sedangInputNilaiMatkul) {

				PrintWithNoNewLine("Masukan nilai matkul " + namaMatkul + " (A,A-,B+,B-,B,C+,C-,C,D+,D,D-,E): ");
				std::getline(cin, nilai);

				std::transform(nilai.begin(), nilai.end(), nilai.begin(), ::toupper);
				for (int iterasiNilai = 0; iterasiNilai < std::size(IndeksPrestasi); iterasiNilai++)
				{
					if (nilai.compare(IndeksPrestasi[iterasiNilai]) == 0) {

						inputSalah = false;
						indexPrestasiMatkul.push_back(nilai);
						dataNilaiMatkul.push_back(KonversiNilaiMatkul(nilai));
						break;
					}
				}

				if (inputSalah) {

					PrintWithNewLine("Input Salah! (Pastikan input sesuai dengan indeksnya A sampai E, dan pastikan input huruf besar)\n");
				}
				else {

					PrintWithNewLine("Berhasil\n");
					sedangInputSKSMatkul = true;
					sedangInputNilaiMatkul = false;
				}
			}

			if (sedangInputSKSMatkul) {
				PrintWithNoNewLine("Masukan SKS matkul " + namaMatkul + ": ");
				cin >> SKS;
				dataSKSmatkul.push_back(SKS);

				sedangInputSKSMatkul = false;
				selesaiInput = true;
			}

			if (selesaiInput) {
				totalNilaiMatkulSelamaKuliah += KonversiNilaiMatkul(nilai) * SKS;
				totalSKSselamaKuliah += SKS;

				sedangInputNamaMatkul = true;
				iterasiMatkul++;
			}
		}
	}

	IPK = totalNilaiMatkulSelamaKuliah / totalSKSselamaKuliah;
	system("cls");

	PrintWithNewLine("Mata Kuliah  IndeksNilai  Nilai  SKS\n");
	for (int iterasi = 0; iterasi < std::size(dataNamaMatkul); iterasi++)
	{
		PrintWithNewLine(dataNamaMatkul[iterasi] + " " + indexPrestasiMatkul[iterasi] + " " + std::to_string(dataNilaiMatkul[iterasi]) + " " + std::to_string(dataSKSmatkul[iterasi]));
	}
	cout << "\nIPK Kamu: " << std::setprecision(2) << std::fixed << IPK << endl;;
	// this where we reveal
}

void PrintWithNewLine(string text)
{
	cout << text << endl;
}

void PrintWithNoNewLine(string text)
{
	cout << text;
}

float KonversiNilaiMatkul(string IndexNilai)
{
	std::unordered_map<string, float> nilai;

	nilai["A"] = 4.00f;
	nilai["A-"] = 3.67f;
	nilai["B+"] = 3.33f;
	nilai["B"] = 3.00f;
	nilai["B-"] = 2.67f;
	nilai["C+"] = 2.33f;
	nilai["C"] = 2.00f;
	nilai["C-"] = 1.67f;
	nilai["D+"] = 1.33f;
	nilai["D"] = 1.00f;
	nilai["D-"] = 0.67f;
	nilai["E"] = 0.00f;

	return nilai[IndexNilai];
}
