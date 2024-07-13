#include "database.h"
#include "operations.h"
#include <iostream>
#include <string>

void mostrarMenu()
{
    std::cout << "\n===== Menú =====\n";
    std::cout << "1. Agregar Usuario\n";
    std::cout << "2. Agregar Juego\n";
    std::cout << "3. Eliminar Usuario\n";
    std::cout << "4. Eliminar Juego\n";
    std::cout << "5. Actualizar Usuario\n";
    std::cout << "6. Actualizar Juego\n";
    std::cout << "7. Listar Usuarios\n";
    std::cout << "8. Listar Juegos\n";
    std::cout << "9. Buscar Usuario\n";
    std::cout << "10. Buscar Juego\n";
    std::cout << "11. Agregar juego a usuario\n";
    std::cout << "12. Listar Compras\n";
    std::cout << "0. Salir\n";
    std::cout << "================\n";
    std::cout << "Ingrese su opción: ";
}

void printOperationResult(bool success, const std::string &operation)
{
    if (success)
    {
        std::cout << operation << " correctamente." << std::endl;
    }
    else
    {
        std::cout << "Error al " << operation << "." << std::endl;
    }
}

int main()
{
    Database db("games_users.db");

    // Crear tablas al inicio del programa
    db.createTables();

    int opcion;
    do
    {
        mostrarMenu();
        std::cin >> opcion;
        std::cin.ignore(); // Limpiar el carácter de nueva línea del búfer de entrada

        switch (opcion)
        {
        case 1:
        {
            std::string nombre, email;
            std::cout << "Ingrese el nombre del usuario: ";
            std::getline(std::cin, nombre);
            std::cout << "Ingrese el email: ";
            std::getline(std::cin, email);
            addUser(db, nombre, email);
            printOperationResult(true, "Usuario agregado");
            break;
        }
        case 2:
        {
            std::string nombre, genero;
            std::cout << "Ingrese el nombre del juego: ";
            std::getline(std::cin, nombre);
            std::cout << "Ingrese el género: ";
            std::getline(std::cin, genero);
            addGame(db, nombre, genero);
            printOperationResult(true, "Juego agregado");
            break;
        }
        case 3:
        {
            int idUsuario;
            std::cout << "Ingrese el ID del usuario a eliminar: ";
            std::cin >> idUsuario;
            deleteUser(db, idUsuario);
            printOperationResult(true, "Usuario eliminado");
            break;
        }
        case 4:
        {
            int idJuego;
            std::cout << "Ingrese el ID del juego a eliminar: ";
            std::cin >> idJuego;
            deleteGame(db, idJuego);
            printOperationResult(true, "Juego eliminado");
            break;
        }
        case 5:
        {
            int idUsuario;
            std::string nuevoNombre, nuevoEmail;
            std::cout << "Ingrese el ID del usuario a actualizar: ";
            std::cin >> idUsuario;
            std::cin.ignore(); // Limpiar el carácter de nueva línea del búfer de entrada
            std::cout << "Ingrese el nuevo nombre: ";
            std::getline(std::cin, nuevoNombre);
            std::cout << "Ingrese el nuevo email: ";
            std::getline(std::cin, nuevoEmail);
            updateUser(db, idUsuario, nuevoNombre, nuevoEmail);
            printOperationResult(true, "Usuario modificado");
            break;
        }
        case 6:
        {
            int idJuego;
            std::string nuevoNombre, nuevoGenero;
            std::cout << "Ingrese el ID del juego a actualizar: ";
            std::cin >> idJuego;
            std::cin.ignore(); // Limpiar el carácter de nueva línea del búfer de entrada
            std::cout << "Ingrese el nuevo nombre: ";
            std::getline(std::cin, nuevoNombre);
            std::cout << "Ingrese el nuevo género: ";
            std::getline(std::cin, nuevoGenero);
            updateGame(db, idJuego, nuevoNombre, nuevoGenero);
            printOperationResult(true, "Juego modificado");
            break;
        }
        case 7:
            listUsers(db);
            break;
        case 8:
            listGames(db);
            break;
        case 9:
        {
            std::string email;
            std::cout << "Ingrese el email del usuario a buscar: ";
            std::getline(std::cin, email);
            searchUser(db, email);
            break;
        }
        case 10:
        {
            std::string nombre;
            std::cout << "Ingrese el nombre del juego a buscar: ";
            std::getline(std::cin, nombre);
            searchGame(db, nombre);
            break;
        }
        case 11:
        {
            int idUsuario, idJuego;
            std::cout << "Ingrese el ID del usuario: ";
            std::cin >> idUsuario;
            std::cout << "Ingrese el ID del juego: ";
            std::cin >> idJuego;
            purchaseGame(db, idUsuario, idJuego);
            printOperationResult(true, "Compra registrada");
            break;
        }
        case 12:
            showPurchases(db);
            break;
        case 0:
            std::cout << "Saliendo del programa.\n";
            break;
        default:
            std::cout << "Opción inválida. Por favor, intente nuevamente.\n";
            break;
        }

    } while (opcion != 0);

    return 0;
}
