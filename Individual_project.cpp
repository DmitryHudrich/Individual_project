#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>

struct ClientInfo {
  std::string full_name;        // Фамилия
  std::string phone_number;     // Телефонный номер
  std::string date_conclusion;  // Дата начала договора
  std::string date_termination; // Дата конца договора
  int amount_debt;              // Задолжность
  int acceptable_credit;        // Допустимый кредит
};

struct ServiceInfo {
  std::string name_service;     // Название услуги
  std::string numb_service;     // Номер услуги
  int cost;                     // Цена
  int quantity;                 // Кол-во
  std::string unit_measurement; // Еденица измерения
};

struct ClientServiceInfo {
  std::string phone_number;  // Телефонный номер
  std::string numb_service;  // Номер услуги
  std::string date_time_use; // Дата и время использования
  int time_of_use;           // Кол-во времени пользования услугой
};

struct ReportStruct {
  std::string clients;  // Фио клиента
  std::string services; // Название услуги
  std::string month;    // Месяц
};

// Считываем Param.ini
void readParam(std::string &paramName) {
  std::ifstream in; // окрываем файл для чтения
  in.open(paramName);
  if (in.is_open()) {
    while (in) {
      std::getline(in, paramName);
    }
  in.close();
  } else {
    std::cout << "Не удалось открыть файл. <<Param.ini>>" << std::endl;
  }
}

void readAndWriteToVectorInfoClient(std::vector<ClientInfo> &clients) {

  std::ifstream inputFile("Info_client.txt");

  if (!inputFile.is_open()) {
    std::cerr << "Не удалось открыть файл." << std::endl;
    return;
  }

  std::string line;
  while (std::getline(inputFile, line)) {
    std::istringstream iss(line);
    ClientInfo client;

    // Считывание данных из строки
    getline(iss, client.full_name, ',');
    iss >> client.phone_number;

    // Добавление структуры в вектор
    clients.push_back(client);
  }
}

void readAndWriteToVectorInfoService(std::vector<ServiceInfo> &services) {
  std::ifstream inputFile("Info_service.txt"); // Имя вашего файла

  if (!inputFile.is_open()) {
    std::cerr << "Не удалось открыть файл." << std::endl;
    return;
  }

  std::string line;
  while (std::getline(inputFile, line)) {
    std::istringstream iss(line);
    ServiceInfo service;

    // Считывание данных из строки
    std::getline(iss, service.name_service, ',');
    iss >> service.numb_service;

    // Добавление структуры в вектор
    services.push_back(service);
  }
}

void readAndWriteToVectorInfoClientService(std::vector<ClientServiceInfo> &clients_services) // Считываем Info_client_service.txt и записываем его в масси
{
  std::ifstream in("Info_client_service.txt"); // Окрываем файл для чтения

  if (!in.is_open()) {
    std::cerr << "Ошибка открытия файла "
              << "Info_client_service.txt" << std::endl;
    return;
  }

  ClientServiceInfo ClientService;

  std::string line;
  while (std::getline(in, line)) {
    std::istringstream iss(line);

    // Считывание данных из строки
    iss >> ClientService.phone_number;
    iss.ignore(); // Пропускаем запятую после phoneNumber
    iss >> ClientService.numb_service;
    iss.ignore(); // Пропускаем запятую после value1
    getline(iss, ClientService.date_time_use, ',');

    // Добавление структуры в вектор
    clients_services.push_back(ClientService);
  }
  in.close(); // Закрытие потока для чтения Info_client_service.txt
}

void reporter(std::vector<ClientInfo> &clients, std::vector<ServiceInfo> &services,
              std::vector<ClientServiceInfo> &clients_services, std::vector<ReportStruct> &report_struct_arr,
              std::string &param, std::string service_id, std::string phone_number) {
  std::string a;
  std::string month;
      std::map<std::string, std::vector<std::string>> write_buffer;
  for (int i = 0; i < clients_services.size(); i++) {
    a = clients_services[i].date_time_use;
    month = a[3];
    month = month + a[4];
    if (month == param) {
      service_id = clients_services[i].numb_service;
      phone_number = clients_services[i].phone_number;

      if (phone_number == clients[i].phone_number) {
        for (int j = 0; j < services.size(); j++) {
          if (service_id == services[j].numb_service) {
            write_buffer[clients[i].full_name].push_back(services[j].name_service);
          }
        }
      }
    }
  }
  std::ofstream outputFile("Report.txt");

  // Перебор элементов и запись в файл
  for (const auto &entry : write_buffer) {
    std::ostringstream oss;
    for (const auto &element : entry.second) {
      oss << element << " ";
    }

    // Получаем строку из std::ostringstream
    std::string result = oss.str();
    outputFile << "Key: " << entry.first << ", Value: " << oss.str() << std::endl;
  }

  // Закрываем файловый поток
  outputFile.close();
}

struct InfoBuffer {
  std::vector<ClientInfo> clients;
  std::vector<ServiceInfo> services;
  std::vector<ClientServiceInfo> clients_services;

  InfoBuffer(std::vector<ClientInfo> clients,
             std::vector<ServiceInfo> services,
             std::vector<ClientServiceInfo> clients_services) {
    this->clients = clients;
    this->services = services;
    this->clients_services = clients_services;
  }
};

int main() {
  std::string paramName = "Param.ini";
  std::string numCerv;
  std::string numPhone;
  std::vector<ClientInfo> clients;
  std::vector<ServiceInfo> services;
  std::vector<ClientServiceInfo> clients_services;
  std::vector<ReportStruct> report_struct_arr;
  readParam(paramName);                                    // Считываем Param.ini
  readAndWriteToVectorInfoClient(clients);                 // Считываем Info_client.txt и записываем его в массив
  readAndWriteToVectorInfoService(services);               // Считываем Info_service.txt и записываем его в массив
  readAndWriteToVectorInfoClientService(clients_services); // Считываем Info_client_service.txt и записываем его в массив

  reporter(clients, services, clients_services, report_struct_arr, paramName, numCerv, numPhone);

  return 0;
}