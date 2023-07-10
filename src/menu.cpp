#include "../include/menu.hpp"

void Menu::abrir_menu(){
    bool opcao_fechar = false; /*!< Verifica se o jogador digitou uma opcao valida para o menu fechar.*/
    bool qntd_alterada = false;
    _quantidade_de_jogadores = 4;
    _quantidade_de_cartas_iniciais = 7;
    while(!opcao_fechar){
        unsigned int opcao; 
         /*!< Verifica se o jogador alterou a quantidade de jogadores e cartas iniciais.*/
        std::cout << "\n------------------/// UNO ///------------------\n";
        std::cout << "\n\n\nOPCOES:\n";
        std::cout << "1 - Iniciar uma partida\n";
        std::cout << "2 - Alterar regras\n";
        std::cout << "3 - Fechar o programa\n";
        std::cout << "\n\n\n Digite a opção desejada: ";
        std::cin >> opcao;
        switch(opcao){
            case 1:
            {
                if(!qntd_alterada){
                    std::cout << "\nAviso: Caso não seja alterado nas regras, o programa considera que serão 4 jogadores e 7 cartas iniciais.\n";
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                }
                
                Sistema* s = new Sistema(_quantidade_de_jogadores, _quantidade_de_cartas_iniciais);
                s->nova_partida();
                delete s;
                std::this_thread::sleep_for(std::chrono::seconds(5));
                opcao_fechar = true;
                break;
            }
                
            case 2:
            {
                bool sair_menu = false;
                while(!sair_menu){
                    unsigned int regra_desejada;
                    std::cout << "\nRegras do jogo: \n";
                    std::cout << "\n1 - Alterar quantidade de jogadores(" << _quantidade_de_jogadores << ") e de cartas iniciais(" << _quantidade_de_cartas_iniciais << ")" <<  std::endl;
                    std::cout << "\n2 - Voltar\n";
                    std::cout << "\n\n\n Digite a regra pra ser alterada: ";
                    std::cin >> regra_desejada;
                    switch (regra_desejada){  
                        case 1: 
                        {
                            std::cout << "\nDigite a quantidade de jogadores da partida (atual = " << _quantidade_de_jogadores << "): ";
                            std::cin >> _quantidade_de_jogadores;
                            std::cout << "\nDigite a quantidade de cartas iniciais da partida (atual = " << _quantidade_de_cartas_iniciais << "): ";
                            std::cin >> _quantidade_de_cartas_iniciais;
                            qntd_alterada = true;
                            break;
                        }
                            
                        case 2: 
                        {
                            std::cout << "\nVoltando...\n\n";
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                            sair_menu = true;
                            break;
                        }
                            
                        default:
                        {
                            break;
                        }    
                    }  
                }
                break;
            }
                
            case 3:
            {
                std::cout << "\n\n Fechando o programa...\n";
                opcao_fechar = true;
                break;
            }
                
        }
    }
}