#include <pistache/endpoint.h>
#include "WebHandler.h"

using namespace Pistache;

int main() {
    Http::listenAndServe<WebHandler>(Pistache::Address("0.0.0.0", Pistache::Port(9080)));
    return 0;
}
