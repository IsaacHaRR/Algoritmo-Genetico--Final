#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main() {
    //Declaração de variaveis
    int max_geracoes;
    int tam_populacao;
    int melhor_individuo;
    int geracao = 0;
    double taxa_mutacao;
    double a, b, c, d, e, f;
    
    srand(time(0));


    //Inicialização das variaveis
    
    do {
        printf("Informe o tamanho da populacao inicial: ");
        scanf("%d", &tam_populacao);
            //Condição para população inicial ser maior que 1
        if(tam_populacao < 1) {
            printf("\nErro! Necessario informar um numero positivo.\n\n");
        }
    } while(tam_populacao < 1);

    do {
        printf("\n\nInforme a taxa de mutacao: ");
        scanf("%lf", &taxa_mutacao);
            //Condição para taxa de mutação estar entre 0 e 1 
        if((taxa_mutacao <= 0) || (taxa_mutacao > 1)) {
            printf("\nErro! Necessario informar um numero entre 0 e 1, incluindo o 1.");
        }
    } while((taxa_mutacao <= 0) || (taxa_mutacao > 1));

    do {
        printf("\n\nInforme o numero maximo de geracoes: ");
        scanf("%d", &max_geracoes);
            //Condição para maximo de gerações ser maior que 1
        if(max_geracoes < 1) {
            printf("\nErro! Necessario informar um numero positivo.");
        }
    } while(max_geracoes < 1);

    do {
        printf("\n\nInforme os 6 coeficientes da equacao de quinto grau, com a diferente de 0: ");
        scanf("%lf %lf %lf %lf %lf  %lf", &a, &b, &c, &d, &e, &f);
            //Condição para o coeficiente "a" ser diferente de 0
        if(a == 0) {
            printf("Erro! Informe um 'a' diferente de 0.");
        }
    } while(a == 0);

    int populacao[tam_populacao];


    //Gerar aleatoriamente a populacao inicial
    for(int i = 0; i < tam_populacao; i++) {
        populacao[i] = (rand() % (255 * 2)) - 255;
    }
    

    //Laco das geracoes:
    for(int i = 0; i < max_geracoes; i++) {
        long long int resultado;
        long long int diferencas[tam_populacao];
        long long int melhor_diferenca;
        long long int pior_diferenca;

        geracao++;


        //Avaliar populacao para o seu problema e Armazenar o melhor individuo ate o momento:

        //Testa o resultado com o primeiro individuo da populacao:
        resultado = a*pow(populacao[0], 5) + b*pow(populacao[0], 4) + c*pow(populacao[0], 3) + d*pow(populacao[0], 2) + e*populacao[0] + f;
        diferencas[0] = llabs(resultado);
        if(i == 0 || diferencas[0] < melhor_diferenca) {
            melhor_diferenca = diferencas[0];
            melhor_individuo = populacao[0];
        }
        pior_diferenca = diferencas[0];
        
        //resolvendo equação com números sorteados e pegando melhor individuo
        for(int j = 1; j < tam_populacao; j++) {
            resultado = a*pow(populacao[j], 5) + b*pow(populacao[j], 4) + c*pow(populacao[j], 3) + d*pow(populacao[j], 2) + e*populacao[j] + f;
            diferencas[j] = llabs(resultado);

            if(diferencas[j] < melhor_diferenca) {
                melhor_individuo = populacao[j];
                melhor_diferenca = diferencas[j];
            }
            else if(diferencas[j] > pior_diferenca) {
                pior_diferenca = diferencas[j];
            }
        }


        //Verificar se a solucao esta aceitavel(se sim, encerrar laco)
        if(melhor_diferenca <= 3) {
            printf("Solucao aceitavel: \n");
            break;
        }


        //Selecionar os melhores individuos:
        int melhores[tam_populacao / 2];
        int cont = 0;
        int m = 0;

        while(cont < (tam_populacao/2)) {
            for(int j = 0; j < tam_populacao; j++) {
                int chance = (rand() % (pior_diferenca - melhor_diferenca)) + melhor_diferenca;

                if(chance > populacao[m]) {
                    melhores[cont] = populacao[m];
                    cont++;
                }

                m++;
            }

            m = 0;
        }


        //Criando variaveis para cruzamento
        int x = 0;
        int mascara_bits_direita = 15;
        int mascara_bits_esquerda = mascara_bits_direita << 4;
        
        //Aplicar cruzamento dos individuos:
        for(int j = 0; j < tam_populacao/2; j++) {
            int individuo1, individuo2;

            do {
                individuo1 = melhores[rand() % (tam_populacao/2)];
                individuo2 = melhores[rand() % (tam_populacao/2)];  

                int temp_direita1 = individuo1 & mascara_bits_direita;
                int temp_direita2 = individuo2 & mascara_bits_direita;

                int temp_esquerda1 = individuo2 & mascara_bits_esquerda;
                int temp_esquerda2 = individuo1 & mascara_bits_esquerda;

                populacao[x] = temp_direita1 | temp_esquerda1;
                populacao[x+1] = temp_direita2 | temp_esquerda2; 

            } while((abs(populacao[x]) > 255) || (abs(populacao[x+1]) > 255));

            x = x + 2;
        }
        
        // melhor individuo
        populacao[0] = melhor_individuo;

        
        //Aplicar mutacao:
        int mascara_mutacao = 0b1;

        for(int j = 0; j < tam_populacao; j++) {
            double chance = (rand() % 100) / (double)100;
            int bit;

            if(chance < taxa_mutacao) {
                int mutacao = rand() % 7;

                bit = mascara_mutacao << mutacao;

                populacao[j] = populacao[j] ^ bit;
            }
        }
    } 


    //Imprimir a melhor solucao
    printf("Resultado: %d, da geracao %d", melhor_individuo, geracao);

    return 0; 
}
