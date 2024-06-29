#include <iostream>
#include <pistache/endpoint.h>
#include <nlohmann/json.hpp>
#include "RBT.h"

using namespace Pistache;
using json = nlohmann::json;

class WebHandler : public Http::Handler {
public:
    HTTP_PROTOTYPE(WebHandler)

    void onRequest(const Http::Request& request, Http::ResponseWriter response) override {
        if (request.method() == Http::Method::Get && request.resource() == "/insert") {
            handleInsert(request, response);
        } else if (request.method() == Http::Method::Get && request.resource() == "/delete") {
            handleDelete(request, response);
        } else if (request.method() == Http::Method::Get && request.resource() == "/treeData") {
            handleTreeData(request, response);
        } else if (request.method() == Http::Method::Get && request.resource() == "/clear") {
            handleClear(request, response);
        } else if (request.method() == Http::Method::Get && request.resource() == "/find") {
            handleFind(request, response);
        } else {
            response.send(Http::Code::Not_Found, "Ruta no encontrada.");
        }
    }

private:
    static RBT<int> tree; // Árbol Red-Black estático

    void handleInsert(const Http::Request& request, Http::ResponseWriter& response) {
        if (!request.query().has("value")) {
            response.send(Http::Code::Bad_Request, "Se requiere un valor para insertar en el árbol.");
            return;
        }

        int value = std::stoi(request.query().get("value").value());

        // Insertar el valor en el árbol
        tree.insert(value);
        response.send(Http::Code::Ok, "Nodo insertado exitosamente.");
    }

    void handleDelete(const Http::Request& request, Http::ResponseWriter& response) {
        if (!request.query().has("value")) {
            response.send(Http::Code::Bad_Request, "Se requiere un valor para eliminar del árbol.");
            return;
        }

        int value = std::stoi(request.query().get("value").value());

        // Eliminar el valor del árbol
        bool result = tree.deleteNode(value);
        if (result) {
            response.send(Http::Code::Ok, "Nodo eliminado exitosamente.");
        } else {
            response.send(Http::Code::Not_Found, "Nodo no encontrado.");
        }
    }

    void handleTreeData(const Http::Request& request, Http::ResponseWriter& response) {
        json treeDataJson = generateTreeData();
        response.send(Http::Code::Ok, treeDataJson.dump());
    }

    void handleClear(const Http::Request& request, Http::ResponseWriter& response) {
        tree.clear();
        response.send(Http::Code::Ok, "Árbol limpiado exitosamente.");
    }

    void handleFind(const Http::Request& request, Http::ResponseWriter& response) {
        if (!request.query().has("value")) {
            response.send(Http::Code::Bad_Request, "Se requiere un valor para buscar en el árbol.");
            return;
        }

        int value = std::stoi(request.query().get("value").value());

        // Buscar el valor en el árbol
        bool found = tree.search(value);
        json result;
        result["found"] = found;

        if (found) {
            response.send(Http::Code::Ok, result.dump());
        } else {
            response.send(Http::Code::Not_Found, result.dump());
        }
    }

    json generateTreeData() {
        if (tree.getRoot() == nullptr) {
            return json::object();
        }
        return generateChildren(tree.getRoot());
    }

    json generateChildren(Node<int>* node) {
        if (node == nullptr) {
            return json::object();
        }

        json currentNode;
        currentNode["name"] = std::to_string(node->data);
        currentNode["color"] = node->color == 'R' ? "red" : "black";

        json children = json::array();
        children.push_back(generateChildren(node->left));
        children.push_back(generateChildren(node->right));

        currentNode["children"] = children;

        return currentNode;
    }
};

// Inicialización de la variable estática `tree`
RBT<int> WebHandler::tree;

int main() {
    Port port(9080);

    Address addr(Ipv4::any(), port);

    auto opts = Http::Endpoint::options().threads(1);

    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(Http::make_handler<WebHandler>());
    server.serve();

    return 0;
}
