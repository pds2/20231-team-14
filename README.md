# Trabalho prático - Jogo de cartas no estilo UNO - Grupo 14

## Dependências

O projeto possui a depêndencia da instalação do framework cocos2d-x. Para instala-lo, siga os procedimentos da pasta cocos do repositório

```
$ https://github.com/pds2/20231-team-14/tree/main/cocos2d
```

## Como Executar

Para compilar no Linux o código, deve-se utilizar o seguinte comando:

```
$ cocos compile -s ./ -p linux -m release -o ./bin
```

Enquanto isso, para executar o código no Linux deve-se utilizar o seguinte comando:

```
$ cocos run -s ./ -p linux
```

Para facilitar foi criado um arquivo shellscript para executar o código, assim pode-se executar utilizando

```
$ ./compileLinux.sh
```

## Funcionamento do programa

O programa é semelhante ao jogo de baralho Uno, sendo assim um jogo de cartas jogado entre 4 jogadores. O objetivo principal do jogo é ser o primeiro jogador a descartar todas as suas cartas. O jogo possui um baralho composto por 108 cartas, divididas em quatro cores (vermelho, amarelo, verde e azul), além de cartas especiais. A partida começa com cada jogador recebendo sete cartas aleatórias. O restante das cartas é colocado virado para baixo, formando a pilha de compra, enquanto a primeira carta é virada e colocada no centro da tela, formando o monte de cartas jogadas.

Os jogadores jogam por turnos, no sentido horário, e o objetivo é combinar a carta que possuem com a carta do topo do monte de descarte, seguindo algumas regras. As cartas são combinadas de acordo com a cor ou número. Por exemplo, se a carta do topo do monte de cartas jogadas é um 7 verde, o jogador pode descartar qualquer carta verde ou qualquer 7, independentemente da cor. O jogador descarta cartas clicando na carta desejada presente em sua mão, sendo descartada se for possível jogar a carta selecionada. No entanto, o jogo possui cartas especiais que adicionam elementos estratégicos e imprevisíveis. Essas cartas incluem:
* Cartas de Ação: Estas cartas têm um ícone especial e podem ser usadas para interromper o turno do próximo jogador ou impor penalidades a outros jogadores. As cartas de ação incluem "Inverter" (muda a direção do jogo), "Bloquear" (o próximo jogador é impedido de jogar) e "Mais 2" (o próximo jogador compra duas cartas e perde seu turno).
* Cartas de Curinga: As cartas de Curinga podem ser jogadas a qualquer momento e permitem que o jogador escolha uma nova cor para continuar o jogo, aparecendo no centro da tela as 4 cores possíveis para que jogador selecione uma das cores clicando nela. Existem duas variantes de cartas de Curinga: "Curinga Normal" (permite que o jogador escolha a próxima cor) e "Curinga +4" (permite que o jogador escolha a próxima cor e obriga o próximo jogador a comprar quatro cartas e perder seu turno).

Se um jogador desejar comprar cartas durante o seu turno, ele pode comprar uma carta do monte de compra clicando no baralho no canto superior esquerdo. Se a carta comprada não puder ser jogada, o jogador pode comprar cartas até conseguir uma carta que puder ser jogada. O jogador passará o turno quando selecionar uma carta da mão para jogada-la

O jogo continua até que um jogador descarte todas as suas cartas, assim finalizando o jogo com o vencedor sendo o jogador que descartou todas as cartas.

## User Stories

* Como jogador, quero ter a opção de selecionar quantos bots irão participar da partida, para que eu possa escolher entre até 8 participantes no total;
* Como jogador, quero que as cartas sejam apresentadas como elementos visuais na tela, para que eu consiga visualizar a minha mão e o número de cartas dos oponentes; 
* Como jogador, quero ter a possibilidade de escolher entre uma das cartas em minha mão, para que eu possa realizar minha jogada;
* Como jogador, quero ter a possibilidade de comprar cartas para realizar uma jogada (nos casos em que não tenho nenhuma carta válida na mão);
* Como jogador, quero que os participantes controlados pela máquina sejam capazes de decidir se é necessário comprar cartas do baralho para completar a sua mão atual ou se já podem realizar a jogada, para que o jogo flua de forma automatizada;
* Como jogador, quero que o participante, quando em uma situação de somente uma carta em mãos (ou seja, a uma jogada da vitória), seja obrigado a declarar "UNO!", para que o jogo se torne mais dinâmico. Caso não o faça, será punido e precisará adicionar ao menos uma carta do baralho à sua mão. Gostaria que tal regra também fosse aplicada aos bots, de forma que existiria uma chance dos mesmos se "esquecerem" de tal obrigação e serem punidos da mesma forma;
* Como jogador, quero que, antes do início de cada partida, eu tenha acesso a um menu de opções, para que eu tenha liberdade de escolher entre um modo de jogo padrão, personalizado ou sair do progama;
* Como jogador, quero que as cartas jogadas anteriormente pelos participantes sejam embaralhadas e devolvidas para o baralho uma vez que não existam mais cartas para serem compradas, para que tal monte seja automaticamente restituído.
