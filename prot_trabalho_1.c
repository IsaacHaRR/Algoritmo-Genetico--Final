#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main() {
    //Declaração de variaveis
    int max_geracoes;
    int tam_populacao;
    int melhor_individuo;
    double taxa_mutacao;
    double a, b, c, d, e, f;

    srand(time(0));


    //Inicialização das variaveis
    do {
        printf("Informe o tamanho da populacao inicial: ");
        scanf("%d", &tam_populacao);
        if(tam_populacao < 1) {
            printf("\nErro! Necessario informar um numero positivo.\n\n");
        }
    } while(tam_populacao < 1);

    do {
        printf("\n\nInforme a taxa de mutacao: ");
        scanf("%lf", &taxa_mutacao);
        if((taxa_mutacao <= 0) || (taxa_mutacao > 1)) {
            printf("\nErro! Necessario informar um numero entre 0 e 1, incluindo o 1.");
        }
    } while((taxa_mutacao <= 0) || (taxa_mutacao > 1));

    do {
        printf("\n\nInforme o numero maximo de geracoes: ");
        scanf("%d", &max_geracoes);
        if(max_geracoes < 1) {
            printf("\nErro! Necessario informar um numero positivo.");
        }
    } while(max_geracoes < 1);

    do {
        printf("\n\nInforme os 6 coeficientes da equacao de quinto grau, com a diferente de 0: ");
        scanf("%lf %lf %lf %lf %lf  %lf", &a, &b, &c, &d, &e, &f);
        if(a == 0) {
            printf("Erro! Informe um 'a' diferente de 0.");
        }
    } while(a == 0);

    int populacao[tam_populacao];



    //Gerar aleatoriamente a populacao inicial
    for(int i = 0; i < tam_populacao; i++) {
        populacao[i] = rand() % 100;
        printf("%d ", populacao[i]);
    } //---------------------------------------------?

    printf("\n\n\n");
    

    //Laco das geracoes:
    for(int i = 0; i < max_geracoes; i++) {
        long long int resultado;
        long long int diferencas[tam_populacao];
        double melhor_diferenca;


        //Avaliar populacao para o seu problema e Armazenar o melhor individuo ate o momento
        resultado = a*pow(populacao[0], 5) + b*pow(populacao[0], 4) + c*pow(populacao[0], 3) + d*pow(populacao[0], 2) + e*populacao[0] + f;
        diferencas[0] = abs(resultado);
        melhor_diferenca = diferencas[0];
        melhor_individuo = populacao[0];

        //printf("%lli ", diferencas[0]);

        for(int j = 1; j < tam_populacao; j++) {
            resultado = a*pow(populacao[j], 5) + b*pow(populacao[j], 4) + c*pow(populacao[j], 3) + d*pow(populacao[j], 2) + e*populacao[j] + f;
            diferencas[j] = abs(resultado);

            if(diferencas[j] < melhor_diferenca) {
                melhor_individuo = populacao[j];
                melhor_diferenca = diferencas[j];
            }
        }


        //Verificar se a solucao esta aceitavel(se cim, encerrar laco)
        if(melhor_diferenca <= 10) {
            break;
        }


        //Selecionar os melhores individuos:
        int troca;

        do {
            troca = 0;

            for(int x = 1; x < tam_populacao; x++) {
                int k = x - 1;

                if(diferencas[k] > diferencas[x]) {
                    int aux = populacao[x];
                    populacao[x] = populacao[k];
                    populacao[k] = aux;

                    aux = diferencas[x];
                    diferencas[x] = diferencas[k];
                    diferencas[k] = aux;

                    troca = 1;
                }
            }
        } while(troca != 0); 

        int melhores[tam_populacao / 2];

        for(int j = 0; j < tam_populacao / 2; j++) {
            melhores[j] = populacao[j];
            printf("%d ", melhores[j]);
        }

        //Aplicar cruzamento: ------------------------------------
        int x = 0;
        printf("\n\n");
        for(int j = 0; j < (tam_populacao / 2) - 1; j++) {
            for(int k = j+1; k < tam_populacao / 2; k++) {
                populacao[x] = melhores[j] & melhores[k];
                printf("%d ", x);
                x++;
            }
        }
        
        printf("\n\n\n\npopulacao nova: ");
        for(int j = 0; j < tam_populacao; j++) {
            printf("%d ", populacao[j]);
        }

        //Aplicar mutacao:

    } 

    //Imprimir a melhor solucao
    printf("resultado: %d", melhor_individuo);


    return 0; 
}