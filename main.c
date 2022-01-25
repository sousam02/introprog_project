#include<stdio.h>
#include<string.h>
#include<stdlib.h>
 
void read_archive()
{
 FILE *arq;
 char Linha[100];
 char *result;
 int i;
 
 arq = fopen("resultados.txt", "rt");
 if (arq == NULL)
 {
   printf("Problemas na abertura do arquivo\n");
   return;
 }
 i = 1;
 while (!feof(arq))
 {
   result = fgets(Linha, 100, arq);
   if (result)
    printf("%s",Linha);
   i++;
 }
 fclose(arq);
}
 
typedef struct tabela {
 char times[30];
 int pontos;
 int gols_pro;
 int gols_contra;
 int saldo;
} TABELA;
typedef struct confronto{
 char times[30];
 int resultados;
} CONFRONTO;
 
void ExibeTimes(int quantidade_de_times, TABELA campeonato[quantidade_de_times]) {
 printf("\n------Times na disputa:------\n");
 for(int i = 0;i < quantidade_de_times; i++){
   printf("%dº - %s \n",i + 1, campeonato[i].times);
 }
}
 
TABELA InsereTimes(
 int quantidade_de_times,
 TABELA campeonato[quantidade_de_times]
) {
 int i = 0;
 
 while(i < quantidade_de_times){
   printf("Escolha um time: ");
   fflush(stdin);
 
   fgets(campeonato[i].times, sizeof campeonato[i].times, stdin);
   size_t len = strlen(campeonato[i].times);
   if (len <= 2) {
     printf("\nTime deve ter no mínimo 3 caracteres!\n");
     i--;
   };
 
   i++;
 }
 
 return campeonato[quantidade_de_times];
}
 
CONFRONTO AdicionarConfrontos(
 int quantidade_de_times,
 int incremento,
 int numero_do_jogo,
 int indice_partidas,
 TABELA campeonato[],
 CONFRONTO partidas[]
) {
 printf("\n------Jogos que acontecerão------\n");
 
 numero_do_jogo = 1;
 
 for(int i = 0;i < quantidade_de_times;i++){
   for(int j = 0;j < quantidade_de_times;j++){
     if(i != j){
       printf("Jogo %d\n%s%s\n\n", numero_do_jogo, campeonato[i].times, campeonato[j].times);
 
       strcpy(partidas[incremento].times, campeonato[i].times);
       incremento++;
 
       strcpy(partidas[incremento].times, campeonato[j].times);
       incremento++;
       numero_do_jogo++;
     }
   }
 }
 return partidas[indice_partidas];
}
 
int main(){
FILE *games;
int quantidade_de_times = -1;
int incremento = 1;
int buscar_jogo;
int numero_do_jogo = 1;
//INSERE OS TIMES QUE VÃO PARTICIPAR DO CAMPEONATO
printf("\n------REGRAS------\n------Insira a quantidade times participantes par e diferente de zero------\n\n\nQuantidade de times: ");
scanf("%d", &quantidade_de_times);
getchar(); //Limpa o buffer "\n" deixado pelo scanf
/*Verifica se a inserção tá correta*/
while(quantidade_de_times % 2 != 0 || quantidade_de_times <= 0) {
 printf("\nPar, maior e diferente de zero!\n");
 scanf("%d", &quantidade_de_times);
 getchar();
}
/*Talvez possa ser usado como indice dos jnogos*/
int numero_jogo[quantidade_de_times * (quantidade_de_times - 1)];
printf("Quantidade de jogos: %d\n\n\n", quantidade_de_times * (quantidade_de_times - 1));
int quantidade_de_jogos = quantidade_de_times * (quantidade_de_times - 1);
int indice = 2 * quantidade_de_jogos;
CONFRONTO partidas[indice + 1];
TABELA campeonato[quantidade_de_times];
campeonato[quantidade_de_times] = InsereTimes(quantidade_de_times, campeonato);
ExibeTimes(quantidade_de_times, campeonato);
 
//MOSTRA OS CONFRONTOS E OS COLOCAM NA STRUCT CONFRONTO
partidas[indice + 1] = AdicionarConfrontos(
 quantidade_de_times,
 numero_do_jogo,
 indice + 1,
 incremento,
 campeonato,
 partidas
);
//INPUT DOS JOGOS E RESULTADOS
printf("------Informe qual jogo acontecerá e os gols das equipes------\n\n\n");
for(int i = 0;i < quantidade_de_times * (quantidade_de_times - 1); i++){
  printf("Informe o numero do jogo: ");
  scanf("%d", &buscar_jogo);
 
  if(buscar_jogo == 0) {
    printf("\nExistem apenas 2 jogos, ida e volta.");
    i--;
  } 
  else {
    printf("%s",partidas[(buscar_jogo * 2) -1].times);
    scanf("%d", &partidas[(buscar_jogo * 2) -1].resultados);
    printf("%s", partidas[(buscar_jogo * 2)].times);
    scanf("%d", &partidas[(buscar_jogo * 2)].resultados);
    printf("\n\n");
  }
}
//COLOCANDO OS RESULTADOS DOS JOGOS NA STRUCT TABELA
//FUNÇÃO PARA LIMPAR A STRUCT TABELA
for(int i=0;i<=4;i++){
  campeonato[i].gols_pro=0;
  campeonato[i].gols_contra=0;
  campeonato[i].pontos=0;
}
incremento=1;
for(int i=0;i<quantidade_de_times;i++){
  for(int j=0;j<quantidade_de_times;j++){
    if(i!=j){
      //ATRIBUINDO GOLS FEITOS E SOFRIDOS AOS TIMES
      campeonato[i].gols_pro+=partidas[incremento].resultados;
      campeonato[j].gols_contra+=partidas[incremento].resultados;
      incremento++;
      campeonato[j].gols_pro+=partidas[incremento].resultados;
      campeonato[i].gols_contra+=partidas[incremento].resultados;
      //ATRIBUINDO PONTOS AOS TIMES
      if(partidas[incremento].resultados<partidas[incremento-1].resultados){
        campeonato[i].pontos+=3;
      }
      else if(partidas[incremento].resultados>partidas[incremento-1].resultados){
        campeonato[j].pontos+=3;
      }
      else{
        campeonato[i].pontos+=1;
        campeonato[j].pontos+=1;
      }
      incremento++;
    }
  }
}
//CALCULANDO O SALDO DE GOLS(GOLS FEITOS - GOLS SOFRIDOS)
for(int i=0;i<quantidade_de_times;i++){
  campeonato[i].saldo = campeonato[i].gols_pro - campeonato[i].gols_contra;
}
//GERAR O ARQUIVO.TXT COM OS RESULTADOS
games=fopen("resultados.txt","w");
fprintf(games,"------Resultado Final------\n\n");
for(int i=0;i<quantidade_de_times;i++){
  fprintf(games,"Time: %sGols feitos: %d\nGols Sofridos: %d\nSaldo de gols: %d\nPontos: %d\n\n\n", campeonato[i].times, campeonato[i].gols_pro, campeonato[i].gols_contra, campeonato[i].saldo, campeonato[i].pontos);
}
fclose(games);
//CRIAÇÃO DA TABELA USANDO MATRIZES E PONTEIROS PARA PONTEIROS
printf("------Tabela com os resultados respectivamente de:------\n");
for(int i = 0;i < quantidade_de_times; i++){
  printf("%s", campeonato[i].times);
}
//CRIAÇÃO DA MATRIZ UTILIZANDO PONTEIROS
int**classificacao;
classificacao = (int**)malloc(quantidade_de_times*sizeof(int));
for(int i=0;i<quantidade_de_times;i++){
  classificacao[i] = (int*)malloc(4*sizeof(int));
}
//PREENCHENDO A MATRIZ COM DADOS DA STRUCT TABELA
for(int coluna = 0;coluna < 4;coluna++){
  for(int linha = 0; linha < quantidade_de_times; linha++){
    if(coluna==0){
     classificacao[linha][coluna] = campeonato[linha].pontos;
    }
    else if(coluna==1){
      classificacao[linha][coluna] = campeonato[linha].gols_pro;
    }
    else if(coluna==2){
      classificacao[linha][coluna] = campeonato[linha].gols_contra;
    }
    else if(coluna==3){
      classificacao[linha][coluna] = campeonato[linha].saldo;
    }
  }
}
//IMPRESSÃO DA TABELA
printf("\n\nP GP GC S\n");
for(int linha = 0; linha < quantidade_de_times; linha++){
  for(int coluna = 0;coluna < 4;coluna++){
    printf("%d ",classificacao[linha][coluna]);
  }
  printf("\n");
}

 
read_archive();
printf("O Resultado Final dos times foi separado em um arquivo.txt\n\n");
return 0;
}
