#include "../include/UserInterface.hpp"

/*  user_interface()
 *  Displays a simple user interface.
 */
void user_interface() {
    // Greetings messages
    std::cout << "Bem vindo ao Sudokunator-2000!" << std::endl;
    std::cout << "Este programa soluciona jogos de sudoku e gera jogos solucionaveis" << std::endl;

    int input = -1;

    while (input != 0) {
        // Prints a menu onscreen
        std::cout << "Escolha uma opcao:" << std::endl;
        std::cout << "\t1. Rodar jogos de demonstracao;" << std::endl;
        std::cout << "\t2. Gerar um jogo com solucao;" << std::endl;
        std::cout << "\t0. Sair." << std::endl;

        // Receives user input
        std::cin >> input;

        // Tests validness of user input
        if (std::cin.fail()) {
            // If it's a bad input, clears it
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            input = -1;

            // Prints invalid input message
            print_invalid();
            continue;
        }
        // Grabs only valid input
        else {
            std::cin.ignore(32767, '\n');
        }

        // User chose option 1
        if (input == 1) {
            precoded_games();
            system("clear");
        }
        // User chose option 2
        else if (input == 2) {
            Sudoku s;
            system("clear");
            s.generate();
        }
        // User chose option 0
        else if (input == 0) break;

        // User chose any other number
        else
            print_invalid();

    }

    // Goodbye message
    std::cout << "Obrigado por usar o programa, volte sempre!" << std::endl;
}

/*  precoded_games()
 *  Runs pre-coded demonstration games
 */
void precoded_games() {
    int input = -1;

    while (input != 0) {
        // Prints menu
        std::cout << "Escolha uma opcao: " << std::endl;
        std::cout << "\t1. Jogo 1;" << std::endl;
        std::cout << "\t2. Jogo 2;" << std::endl;
        std::cout << "\t3. Jogo 3;" << std::endl;
        std::cout << "\t0. Voltar ao menu anterior." << std::endl;

        // Receives user input
        std::cin >> input;

        // Tests validness of user input
        if (std::cin.fail()) {
            // If it's a bad input, clears it
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            input = -1;

            // Prints invalid input message
            print_invalid();
            continue;
        }
        // Grabs only valid input
        else {
            std::cin.ignore(32767, '\n');
        }

        // User chose games 1-3
        if (0 < input && input < 4) {
            Sudoku s;
            s.games(input);
            s.solve(true);
        }
        // User chose option 0
        else if (input == 0) break;

        // User chose any other number
        else
            print_invalid();
    }
}

/*  print_invalid()
 *  Prints a message when a user input is invalid
 */
void print_invalid() {
    std::cout << "Entrada invalida. Por favor, tente novamente." << std::endl;
}