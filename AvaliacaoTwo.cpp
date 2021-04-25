//Vou importar a iostream para mostrar a lista.
#include <iostream> 
//A stdlib para alocar memória na heep
#include <stdlib.h> 
#include <time.h> 
#include <unistd.h> //E estas duas ultimas para gerar números aleatorios para a lista

using namespace std;

//Vou criar a estrutura de nó para a lista ja definindo como um tipo
typedef struct nolista
{
    struct nolista *ant, *prox; //criando os dois ponteiros para os nós ligados
    int dado;
} NoLista; //E vou dar o nome dessa estrutura de NoLista

//Vou criar tambem a estrutura para a lista em sí
typedef struct lista 
{
    NoLista *cabeca, *rabo; //Ela vai ter um ponteiro para o inicio dela e o fim
    int tamanho;           //E vai ter tambem seu tamanho referenciado nela
} Lista; //E vou dar o nome do tipo de Lista mesmo

//Vou criar uma função que já inicia um nó na heep
NoLista* criarNo(int dado, NoLista* ant, NoLista* prox)
{
    NoLista* no = (NoLista*)malloc(sizeof(NoLista)); //Primeiro eu aloco o nó com malloc
    no->dado = dado; //depois eu estancio os dados que passei na função
    no->ant = NULL; //Por segurança vou começar os nos como nulos.
    no->prox = NULL;

    //e so vou colocar algo neles se realmente passar algo válido para a função
    if (ant)
    {
        no->ant = ant;
    }
    if (prox)
    {
        no->prox = prox;
    }

    return no; //no fim eu só retorno o nó
}

//Eu crio uma fução que retorna uma lista.
Lista* criarLista()
{
    Lista* lista = (Lista*)malloc(sizeof(Lista)); //Ela aloca a lista na heep com malloc
    lista->cabeca = criarNo(0, NULL, NULL); //E estancia os dois nós de referencia com 0;
    lista->rabo = criarNo(0, NULL, NULL);
    lista->tamanho = 0; //Alem do tamanho tambem começar com 0

    return lista;
}

//Crio uma função que adiciona novos nós no fim da lista
void add_no(int dado, Lista* lista)
{
    NoLista* no = criarNo(dado, NULL, NULL);
   

    if (lista->cabeca->prox == NULL) //Se a lista estiver vazia ele liga o novo nó nos nós de referencia
    {
        lista->cabeca->prox = no;
        lista->rabo->ant = no;
        no->prox = lista->rabo;
        no->ant = lista->cabeca;

    }else{  //Se tiver algo ele liga no ultimo e no nó do fim da lista
        NoLista* noant = lista->rabo->ant; 
        no->prox = lista->rabo;
        no->ant = noant;
        noant->prox = no;
        lista->rabo->ant = no;
    }   
    lista->tamanho++; //E no final esse soma mais um ao tamanho da lista
}

//Agora vem a parte principal do programa, vou criar uma função que divide uma lista em duas
//como C++ não tem uma forma oficial de retornar mutiplos valores, eu vou passar tanto a
//lista que vai ser dividida quanto as listas que vão receber as partes da primeira como
//ponteiros nos argumentos da função
void dividirLista(Lista* lista, Lista* lista1, Lista* lista2)
{
    //Vou começar ligando o começo da lista 1 no começo da lista original
    lista1->cabeca->prox = lista->cabeca->prox;
    //Vou ligar o fim da lista 2 no fim da lista original
    lista2->rabo->ant = lista->rabo->ant;
    //E por fim vou ligar estes nós de volta no inicio da lista 1 e no fim da lista 2
    //Eu preciso fazer isso por que é uma lista duplamente ligada
    lista->rabo->ant->prox = lista2->rabo; //Então o ultimo nó da lista original se liga no fim da lista 1
    lista->cabeca->prox->ant = lista1->cabeca; //E o primeiro nó da lista original se liga no inicio da lista 2
    //Tambem vou criar um nó indice, que vai ser o nó onde eu vou dividir a lista
    NoLista* noindice = lista->cabeca->prox;
    //Agora vou considerar os dois casos, se a lista for par, o c++ vai dividir o tamanho da lista precisamente pra mim
    //e se for impar ele vai ignorar as casas decimais, o que é o mesmo que arredondar para baixo
    //então vou começar com um bloco if-else para o caso do tamanho da lista ser par
    if (lista->tamanho %2 == 0) //Para verificar se é par basta verificar que o resto da divisão por dois é zero
    {
        //Agora vou fazer o nó indice percorrer a lista até a metade do tamanho dela,
        //como eu ja coloquei o nó indice no primeiro termo, eu vou fazer um for, de 1 até metade da lista
        for (size_t i = 1; i < lista->tamanho / 2; i++)
        {
            //dentro do for eu simplesmente coloco que o nó indice vai ser igual ao proximo até terminar
            noindice = noindice->prox;
        }
        //Pronto, nesse ponto o nó indice está no meio da lista, no caso no nó anterior do meio ja que é par
        //Agora eu ja posso atualizar o tamanho das duas outras listas
        lista1->tamanho = lista->tamanho / 2;
        lista2->tamanho = lista->tamanho / 2;
        //Como eu vou atualizar os ponteiros tanto para o caso par quanto pro impar da mesma forma, vou deixar
        //para fazer no fim fora do bloco if-else
    } else {
        //No else só o que muda pe que vou fazer um for de 1 até precisamente a metáde da lista,
        //ou seja, vou parar exatamente no nó da metade, então vai ser de 1 até o tamanho dividido por 2 + 1
        //ja que o c++ vai arredondar sempre para baixo
        for (size_t i = 1; i < (lista->tamanho / 2) + 1; i++)
        {
            noindice = noindice->prox; //Dentro do for eu faço o mesmo que no outro
            
        }
        //E atualizo denovo o tamanho da lista, mas nesse caso muda que a lista 1 vai ter 1 nó a mais que a 2
        lista1->tamanho = (lista->tamanho / 2) + 1;
        //A dois vai ser igual a do if
        lista2->tamanho = lista->tamanho / 2;
    }
    //Pronto, agora que a gente tem o ponteiro de indice apontando para o luar certo não importa
    //se é impar ou par, a gente pode mudar os ponteiros do meio da lista original para ser o começo
    //da lista 2 e o fim da lista 1:
    //Eu começo criando uma variavel que aponta para o proximo do nó do indice:
    NoLista* proximo = noindice->prox;
    //E vou fazer o seguinte, o nó do indice será o fim da lista 1, e o proximo a ele o começo da 2
    //então vou começar ligarndo o fim da lista 1 com o nó do indice:
    lista1->rabo->ant = noindice;
    //Vou ligar o proximo do indice de volta com o fim da lista 1.
    noindice->prox = lista1->rabo;
    //Vou ligar o começo da lista 2 com o proximo ao indice
    lista2->cabeca->prox = proximo;
    //E por fim ligar o proximo ao indice de volta com o começp da lista 2
    proximo->ant = lista2->cabeca;
    //Nesse momento a gente tem todos os ponteiros apontando para o lugar certo
    //No total são 8 ponteiros mudados, pois são 4 nós a serem ligados uns nos
    //outros, e cada um tem um próximo e um anterior sendo referenciado.
    
    //Como a lista ja foi dividida para as outras duas, eu ja posso pegar o inicio e o
    //fim da lista original e dizer que seus ponteiros não estão ligados a mais nada
    lista->cabeca->prox = NULL;
    lista->rabo->ant = NULL;
    //Vou atualizar também o tamanho da lista original para zero
    lista->tamanho = 0;
}

//Vou criar uma função rapidinho so para mostrar a lista
void mostrar(Lista *lista)
{
    if (lista->tamanho == 0)
    {
        cout << endl; //Se a lista estiver vazia ele so pula uma linha
        return;
    }

    //Se não tiver ele vai ter que percorrer ele inteira para mostrar nó por nó
    NoLista* interador = lista->cabeca->prox;

    //Vai mostrar o primeiro entre chaves
    cout << endl
         << "\033[35m" //Com a cor roxa.
         << "[" << interador->dado
         << "]";

    //E em seguida vai printar todos os outros com uma setinha no começo
    while (interador->prox != lista->rabo)
    {
        interador = interador->prox;
        cout << " -> [" << interador->dado
             << "]";
    }
    cout << "\033[0m" //Volto para a cor padrão do terminal
         << endl
         << endl; //E dou duas quebras de linha pra finalizar
}

int main()
{
    //Primeiro eu vou dar uma seed para a função rand, vai ser a função time que importei la em cima
    srand(time(NULL));
    //Depois vou criar duas listas vazias, uma que vai ter um numero par de elementos e a outra impar
    Lista* lista1 = criarLista();
    Lista* lista2 = criarLista();
    //Agora vou popular as listas, ambas inicialmente com 6 numeros de 0 a 99
    //vou fazer um for de 0 a 5
    for (size_t i = 0; i <= 5; i++)
    {
        //dentro do for vou usar a função de adicionar para colocar numeros na lista
        add_no(rand() % 100, lista1); //Em ambas eu vou passar o resto da função rand dividido por 100
        usleep(1); //Antes de adicionar na segunda vou dar um sleep de 1 milisegundo so para garantir que os números aleatorios sejam diferentes
        add_no(rand() % 100, lista2); //E ai sim vou fazer o mesmo na segunda lista
    }
    add_no(rand() % 100, lista2); //Vou adicionar um número randomico a mais na segunda lista para ficar com 7 de tamanho
   
    //Vou mostrar a lista 1 coma função de mostrar que criei:
    cout << "Lista 1:"; //Vou adicionar uma legenda so pra saber qual é qual
    mostrar(lista1);

    //Vou criar duas listas vazias para serem o resultado da divisão da primeira
    Lista* lista1_divisao1 = criarLista();
    Lista* lista1_divisao2 = criarLista();
    //Vou dividir a lista com a função que criei
    dividirLista(lista1, lista1_divisao1, lista1_divisao2);
    //E mostrar as duas novas listas:
    cout << "Lista 1, parte 1:";
    mostrar(lista1_divisao1);
    cout << "Lista 1, parte 2:";
    mostrar(lista1_divisao2);

    //Agora vou mostrar a lista 2:
    cout << "Lista 2:";
    mostrar(lista2);

    //Criar outras duas listas para serem a divisão da lista 2:
    Lista* lista2_divisao1 = criarLista();
    Lista* lista2_divisao2 = criarLista();
    //Divido a lista dois nessas duas:
    dividirLista(lista2, lista2_divisao1, lista2_divisao2);
    //E vou mostrar as listas divididas:
    cout << "Lista 2, parte 1:";
    mostrar(lista2_divisao1);
    cout << "Lista 2, parte 2:";
    mostrar(lista2_divisao2);
}
