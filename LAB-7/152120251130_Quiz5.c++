#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Sensor {
	int sensor_id;
	float sicaklik;
};

int main() {
	long long studentId;
	cout << "Student ID giriniz: ";
	cin >> studentId;

	int N = studentId % 50;
	int E = studentId % 100;

	fstream sensorFile("sensors.bin", ios::in | ios::out | ios::binary);
	if (!sensorFile.is_open()) {
		cout << "Hata: sensors.bin dosyasi acilamadi." << endl;
		return 1;
	}

	Sensor record;
	streamoff offset = static_cast<streamoff>(N) * sizeof(Sensor);

	sensorFile.seekg(offset, ios::beg);
	if (!sensorFile.read(reinterpret_cast<char*>(&record), sizeof(Sensor))) {
		cout << "Hata: N'inci kayit okunamadi." << endl;
		sensorFile.close();
		return 1;
	}

	float firstTemperature = record.sicaklik;
	record.sicaklik += static_cast<float>(E);

	sensorFile.seekp(offset, ios::beg);
	if (!sensorFile.write(reinterpret_cast<const char*>(&record), sizeof(Sensor))) {
		cout << "Hata: N'inci kayit guncellenemedi." << endl;
		sensorFile.close();
		return 1;
	}

	sensorFile.close();

	string reportFileName = to_string(studentId) + "_Quiz5.txt";
	ofstream reportFile(reportFileName.c_str(), ios::out);
	if (!reportFile.is_open()) {
		cout << "Hata: rapor dosyasi olusturulamadi." << endl;
		return 1;
	}

	reportFile << "Number: " << studentId << '\n';
	reportFile << "Sensor Index Used in the Process: " << N << '\n';
	reportFile << "First Temperature: " << firstTemperature
			   << " -> New Temperature: " << record.sicaklik << '\n';

	reportFile.close();

	cout << "Islem tamamlandi. Rapor: " << reportFileName << endl;

}