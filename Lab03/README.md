# Troca de contexto entre processo pai e thread
## Fellipe Jardanovski e Felipe Jiao

Nesse programa, basicamente ocorre a troca de contexto entre o processo pai e a thread filha criada.
Ele é semelhante ao programa que faz a troca de contexto entre um processo pai e o processo filho,
porém, ao invés de utilizar fork() para criar um processo filho, é utilizado a clone() para a chamada
de sistema. A troca de contexto ocorre usando um argumento do tipo inteiro, definindo sua estrutura
em ThreadArgs, onde será passado o argumento para a thread. A função threadFunction será executada
pela thread, onde ela receberá um argumento do tipo void e converte para o argumento ThreadArgs*.
Na main, a thread é alocada em uma stack, passando a função threadFunction, além das flags, argumento
e o endereço da stack. É utilizado o comando waitpid para garantir que não terá interrupção da thread.
Ao final, a Stack é liberada pela thread.

A thread pode ser utilizada para compartilhamento de memória, já que, por exemplo, duas threads criadas
pelo mesmo processo, podem compartilhar a mesma memória, permitindo a alteração de variáveis globais por
exemplo. Além disso, as threads são mais leves, já que não precisa necessariamente cada thread possuir um
espaço na memória.
