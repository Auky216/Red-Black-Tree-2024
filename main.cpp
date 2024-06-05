#include "RBT.h"
#include <chrono>
#include <iostream>
#include <random>
#include <pistache/endpoint.h>
#include <nlohmann/json.hpp>

using namespace std;
using namespace Pistache;
using json = nlohmann::json;

class HelloHandler : public Http::Handler {
private:
    static RBT<int> tree; // Declarar el árbol como una variable estática privada en la clase

public:
    HTTP_PROTOTYPE(HelloHandler)

    void onRequest(const Http::Request& request, Http::ResponseWriter response) override {
        if (request.method() == Http::Method::Get && request.resource() == "/add") {
            auto queryParams = request.query();
            auto elementStrOpt = queryParams.get("element");
            if (elementStrOpt.has_value()) {
                auto elementStr = elementStrOpt.value();
                try {
                    int elementToAdd = std::stoi(elementStr);

                    auto inicio = std::chrono::high_resolution_clock::now();
                    tree.insert(elementToAdd);
                    auto fin = std::chrono::high_resolution_clock::now();

                    std::chrono::duration<double> tiempo_total = fin - inicio;

                    json responseData;
                    responseData["message"] = "Elemento agregado correctamente.";
                    responseData["time"] = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count(); // Se muestra en segundos

                    std::string jsonResponse = responseData.dump();

                    response.headers().add<Http::Header::ContentType>(MIME(Application, Json));
                    response.send(Http::Code::Ok, jsonResponse);
                } catch (const std::invalid_argument& e) {
                    response.send(Http::Code::Bad_Request, "El parámetro 'element' debe ser un número entero válido.");
                }
            } else {
                response.send(Http::Code::Bad_Request, "Parámetro 'element' faltante en la URL.");
            }
        } else if (request.method() == Http::Method::Get && request.resource() == "/add_random") {
            auto queryParams = request.query();
            auto countStrOpt = queryParams.get("count");
            if (countStrOpt.has_value()) {
                auto countStr = countStrOpt.value();
                try {
                    int count = std::stoi(countStr);

                    auto inicio = std::chrono::high_resolution_clock::now();
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> dis(1, 1000000); // Generar valores del 1 al 1 millón

                    for (int i = 0; i < count; ++i) {
                        tree.insert(dis(gen));
                    }

                    auto fin = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> tiempo_total = fin - inicio;

                    json responseData;
                    responseData["message"] = "Elementos agregados correctamente.";
                    responseData["count"] = count;
                    responseData["time"] = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count(); // Se muestra en segundos // Se muestra en segundos

                    std::string jsonResponse = responseData.dump();

                    response.headers().add<Http::Header::ContentType>(MIME(Application, Json));
                    response.send(Http::Code::Ok, jsonResponse);
                } catch (const std::invalid_argument& e) {
                    response.send(Http::Code::Bad_Request, "El parámetro 'count' debe ser un número entero válido.");
                }
            } else {
                response.send(Http::Code::Bad_Request, "Parámetro 'count' faltante en la URL.");
            }
        } else if (request.method() == Http::Method::Get && request.resource() == "/returnvalues") {
            // Obtener los valores del árbol en orden utilizando la función printInOrder
            std::string values = tree.printInOrder();

            // Crear un objeto JSON para la respuesta
            json responseData;
            responseData["message"] = "Valores del árbol en orden.";
            responseData["values"] = values;
            responseData["time"] = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count(); // Se muestra en segundos // Se muestra en segundos

            // Convertir el JSON a una cadena de texto
            std::string jsonResponse = responseData.dump();

            // Establecer el tipo de contenido de la respuesta como application/json
            response.headers().add<Http::Header::ContentType>(MIME(Application, Json));

            // Enviar la respuesta
            response.send(Http::Code::Ok, jsonResponse);
        } else {
            response.send(Http::Code::Not_Found);
        }
    }
};

// Inicializar la variable estática del árbol
RBT<int> HelloHandler::tree;

int main() {
    Address addr(Ipv4::any(), Port(9080));

    auto opts = Http::Endpoint::options().threads(1);
    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(Http::make_handler<HelloHandler>());
    server.serve();
}
