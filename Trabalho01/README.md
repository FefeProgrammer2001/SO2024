# Projeto da escada rolante
### Fellipe Jardanovski e Felipe Jiao

## Explicação do projeto

O projeto consiste basicamente em calcular o último momento
em que a última pessoa saiu da escada. Considerando alguns
aspectos essenciais como a direção desejada pela pessoa, o
tempo de cada um (chegada e saída), e considerar que duas
pessoas ou mais podem acessar a escada rolante desde que 
esteja na mesma direção de ambas as pessoas. Isso porque a escada
é larga, cabem inúmeras pessoas nessa escada, e para cada pessoa
que acessa a escada, ela leva 10 segundos para ir de uma ponta a outra.
Esses tempos serão somados com o tempo final para calcular o momento
em que a última pessoa saiu da escada.

## Abordagem utilizada

Tentamos inúmeras abordagens para resolver esse problema. Tivemos
que pensar bastante em como iriamos resolver esse problema. A aborgadem
que mais funcionou foi utilizar a estrutura de dados fila para poder
organizar as pessoas em filas para cada direção, isto é, se a escada
está indo para a direção 0, as pessoas que desejam ir para a direção
1 vão formar uma fila nessa estrutura para que, quando a escada trocar
de direção, essa fila será zerada, criando uma nova fila. Porém, não
utilizamos a fila de maneira explicita. Nesse caso, utilizamos vetores
para simular as filas 0 e 1.
### Uso do semáforo
Além do uso da estrutura fila, também foi utilizado o semáforo e mutex, para
realizar o controle e garantir que, enquanto a escada estiver indo na direção
0, as pessoas que querem ir para a direção 1 sejam impedidas, até que a escada
mude a direção. Isto é possível com o uso do mutex ou semáforos. Somente quando a
escada inverter que o semáforo irá liberar e zerar a outra fila que estava aguardando

## Vantagens de usar pthread para resolver esse problema

Algumas vantagems de resolver esse problema com pthread são:
* Uso eficiente de recursos e memória
* Sincronização simplificada
* Desempenho e Escalabilidade
* Facilidade de Manutenção

Isso ocorre principalmente devido a principal propriedade das threads
de que duas ou mais podem compartilhar o mesmo espaço na memória, facilitando
a manutenção, e principalmente, um código mais rápido e otimizado com o uso
de memória e recursos. Ao utilizar processos no caso, cada processo será
uma pessoa. O processo necessitará de mais recursos e mais espaço na memória, já que os procesos filhos criados pelo processos pai através do fork() não conseguem compartilhar
o mesmo espaço na memória, e pra cada processos criado, o espaço na memória é duplicado.

