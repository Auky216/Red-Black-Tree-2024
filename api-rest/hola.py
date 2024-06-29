def promedio(lista):
    promedio = sum(lista) / len(lista)

    return promedio


cant = int(input("cantidad: "))

lista1 = []
for i in range(1,cant+1):
    numero = int(input("numero"))
    lista1.append(numero)

print(promedio(lista1))
