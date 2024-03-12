O funcionamento desse programa consiste basicamente na criação entre dois processos pai e filho
utilizando os comandos fork() e pipe(), e utilizando uma tubulação, a mensagem é trocada entre
os dois processos por uma espécie de tubo criado entre eles. Quando os processos pai e filho são
criados com a função fork(), ambos possuem uma cópia do mesmo endereço de memória, porém, com
identificadores de processos diferentes.
