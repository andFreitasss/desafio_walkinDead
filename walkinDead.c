#include <stdio.h>

// Função para obter o número de humanos vizinhos
int obterNumHumanosVizinhos(int matriz[][50], int linha, int coluna, int m,
                            int n) {
  int nHumanos = 0, i, j;
  int row, col;

  // Verificar as células vizinhas, considerando as bordas da matriz
  for (i = linha - 1; i <= linha + 1; i++) {
    for (j = coluna - 1; j <= coluna + 1; j++) {
      // Ignorar a própria célula e considerar as bordas
      row = (i + m) % m;
      col = (j + n) % n;

      // Verificar se a célula é um humano
      if (matriz[row][col] == 1) {
        nHumanos++;
      }
    }
  }

  // Subtrair 1 se a célula atual for um humano
  if (matriz[linha][coluna] == 1) {
    nHumanos--;
  }

  return nHumanos;
}

// Função para atualizar o estado do planeta após um dia
void atualizarEstado(int matriz[][50], int m, int n) {
  int novoEstado[50][50], i, j;
  int nHumanosVizinhos;

  // Atualizar o estado para cada célula da matriz
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      nHumanosVizinhos = obterNumHumanosVizinhos(matriz, i, j, m, n);

      if (matriz[i][j] == 1) {
        // Se o indivíduo atual for um humano
        if (nHumanosVizinhos >= 1) {
          // Será infectado e se tornará um zumbi
          novoEstado[i][j] = 2;
        } else {
          // Continua sendo um humano
          novoEstado[i][j] = 1;
        }
      } else if (matriz[i][j] == 2) {
        // Se o indivíduo atual for um zumbi
        if (nHumanosVizinhos >= 2) {
          // É caçado e morto pelos humanos
          novoEstado[i][j] = 0;
        } else if (nHumanosVizinhos == 0) {
          // Morre de fome e fica vazio
          novoEstado[i][j] = 0;
        } else {
          // Continua sendo um zumbi
          novoEstado[i][j] = 2;
        }
      } else if (matriz[i][j] == 0) {
        // Se a célula atual estiver vazia
        if (nHumanosVizinhos == 2) {
          // Nasce um novo humano
          novoEstado[i][j] = 1;
        } else {
          // Continua vazia
          novoEstado[i][j] = 0;
        }
      }
    }
  }

  // Atualizar a matriz original com o novo estado
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      matriz[i][j] = novoEstado[i][j];
    }
  }
}

int main() {
  // Leitura do tamanho da matriz e número de dias a simular
  int m, n, nDias, matriz[50][50];
  int valor;

  printf("Tamanho da matriz (linha e coluna) :\n");
  scanf("%d %d", &m, &n);

  printf("\nNumero de dias:\n");
  scanf("%d", &nDias);

  printf("\nInforme estado atual do planeta, sendo 0 vazio, 1 representa um "
         "humano e 2 um zumbi:\n\n");

  // Leitura do estado inicial do planeta
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &valor);

      // Verificar se o valor inserido é válido (0, 1 ou 2)
      if (valor == 0 || valor == 1 || valor == 2) {
        matriz[i][j] = valor;
      } else {
        printf("Valor inválido. Insira novamente: ");
        j--;
        // Precisamos decrementar j para repetir a leitura do valor inválido
      }
    }
  }

  // Imprimir o estado inicial da população
  printf("iteracao 0:\n");
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", matriz[i][j]);
    }
    printf("\n");
  }

  // Simular os dias transcorridos
  for (int dia = 1; dia <= nDias; dia++) {
    atualizarEstado(matriz, m, n);

    // Imprimir o estado atual da população
    printf("iteracao %d:\n", dia);
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        printf("%d ", matriz[i][j]);
      }
      printf("\n");
    }
  }

  return 0;
}
