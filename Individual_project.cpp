#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <algorithm>

struct ClientInfo {
    std::string full_name; //Фамилия
    std::string phone_number;//Телефонный номер
    std::string date_conclusion;//Дата начала договора
    std::string date_termination;//Дата конца договора
    int amount_debt;//Задолжность
    int acceptable_credit;//Допустимый кредит
};

struct ServiceInfo
{
    std::string name_service;//Название услуги
    std::string numb_service;//Номер услуги
    int cost;//Цена
    int quantity;//Кол-во
    std::string unit_measurement;//Еденица измерения
};

struct ClientServiceInfo
{
    std::string phone_number;//Телефонный номер
    std::string numb_service;//Номер услуги
    std::string date_time_use;//Дата и время использования
    int time_of_use;//Кол-во времени пользования услугой
};

struct ReportStruct
{
    std::string clients;//Фио клиента
    std::string service;//Название услуги
    std::string month;//Месяц
};

auto readParam(std::string& param)//Считываем Param.ini
{
    std::ifstream in("Param.ini"); // окрываем файл для чтения
    if (in.is_open())
    {
        while (in) 
        {
            std::getline(in, param);
         
        }
    }
    else
    {
        std::cout << "Не удалось открыть файл. <<Param.ini>>" << std::endl;
    }
    in.close();
}

void readAndWriteToVectorInfoClient(std::vector<ClientInfo>& clients_struct_arr)
{

    std::ifstream inputFile("Info_client.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Не удалось открыть файл." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        ClientInfo
     clients;

        // Считывание данных из строки
        getline(iss, clients.full_name, ',');
        iss >> clients.phone_number;

        // Добавление структуры в вектор
        clients_struct_arr.push_back(clients);
    }
}

void readAndWriteToVectorInfoService(std::vector<ServiceInfo>& clients_service_arr)
{
S  std::ifstream inputFile("Info_service.txt"); // Имя вашего файла

        if (!inputFile.is_open()) {
            std::cerr << "Не удалось открыть файл." << std::endl;
            return;
        }

        std::string line;
        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            ServiceInfo
         services;

            // Считывание данных из строки
            std::getline(iss, services.name_service, ',');
            iss >> services.numb_service;

            // Добавление структуры в вектор
            clients_service_arr.push_back(services);
        }
}

void readAndWriteToVectorInfoClient_service(std::vector<ClientServiceInfo>& client_service_arr)//Считываем Info_client_service.txt и записываем его в масси
{
    std::ifstream in("Info_client_service.txt");//Окрываем файл для чтения

    if (!in.is_open()) {
        std::cerr << "Ошибка открытия файла " << "Info_client_service.txt" << std::endl;
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
            client_service_arr.push_back(ClientService);
        }
    in.close();//Закрытие потока для чтения Info_client_service.txt
}

void reporter(std::vector<ClientInfo>& clients_struct_arr, std::vector<ServiceInfo>& clients_service_arr, 
    std::vector<ClientServiceInfo>& client_service_arr, std::vector<ReportStruct>& report_struct_arr, 
    std::string& param, std::string numCerv, std::string numPhone)
{
    std::string a;
    std::string b;
    for (int i = 0; i < client_service_arr.size(); i++)
    {
        a = client_service_arr[i].date_time_use;
        b = a[3];
        b = b + a[4];
        if ( b == param)
        {
            numCerv = client_service_arr[i].numb_service;
            numPhone = client_service_arr[i].phone_number;
            
            for (int ic = 0; ic < clients_service_arr.size(); ic++)
            {
                std::vector<std::string> write_buffer;

                if (numPhone == clients_struct_arr[ic].phone_number)
                {
                    write_buffer.push_back(clients_struct_arr[ic].full_name);
                }
                if (numCerv == clients_service_arr[ic].numb_service)
                {
                    write_buffer.push_back(clients_service_arr[ic].name_service);
                }
            }
            for (int ib = 0; ib < clients_struct_arr.size; ib++)
            {
                std::vector<std::string> write_buffer2;

                if (numPhone == clients_struct_arr[ib].phone_number)
                {
                    write_buffer2.push_back(clients_struct_arr[ib].full_name);
                }
            }
        }
    }
}

struct InfoBuffer {
    std::vector<ClientInfo
> clients_struct_arr;
    std::vector<ServiceInfo
> clients_service_arr;
    std::vector<ClientServiceInfo> client_service_arr;

    InfoBuffer() {

    }

}

int main() {
    std::string param;
    std::string numCerv;
    std::string numPhone;
    std::vector<ClientInfo
>clients_struct_arr;
    std::vector<ServiceInfo
>clients_service_arr;
    std::vector<ClientServiceInfo>client_service_arr;
    std::vector<ReportStruct>report_struct_arr;
    readParam(param); //Считываем Param.ini
    readAndWriteToVectorInfoClient(clients_struct_arr);//Считываем Info_client.txt и записываем его в массив
    readAndWriteToVectorInfoService(clients_service_arr);//Считываем Info_service.txt и записываем его в массив
    readAndWriteToVectorInfoClientService(client_service_arr);//Считываем Info_client_service.txt и записываем его в массив

    reporter(clients_struct_arr, clients_service_arr, client_service_arr, report_struct_arr, param, numCerv, numPhone);

    return 0;
}                                                  