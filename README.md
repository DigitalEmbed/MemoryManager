# Data Structures

## English

### Preface

On some occasions, we need to allocate infinite memory or vectors for any given data at runtime. In C we have available functions for memory allocation, such as **malloc** and **calloc**. There are no problems when the software runs over a memory manager (MMU) or operating system, such as Windows and Linux. The problem is when we do not have this feature available: There can be several problems, such as allocation accidents, memory fragmentation, among others. In embedded systems there is one more problem: Allocations do not have a pre-set execution time.

In more modern programming languages (Java, for example) there are several mechanisms that allow memory allocation to be simple and secure.

The set of libraries was made in C in order to reach the majority of embedded programmers. The advantage of using the C library is the speed of execution and memory economy, since classes generate a lot of memory garbage.

### Bits

With this library it is possible from the manipulation of bits in a variable to the creation of bit vectors. They are ideal for programs that have many binary variables because they have a large memory economy, and are handled faster by the processor/microcontroller.

### MemoryPool

Memory Pools are fixed-size blocks of allocation. This library manages these memory blocks, allowing dynamic allocation and deallocation of memory comparable to C malloc or C++ new operator. This concept was widely used in older video games because of its speed of execution. JAVA also uses this concept for its allocations.

Because native C/C ++ memory allocation implementations suffer fragmentation due to variable block sizes, it is not recommended to use them in a real-time system because of performance. The idea here is to pre-allocate multiple memory blocks of the same size: The manager can allocate, access, and release these pre-allocated blocks. There are several benefits to this approach, including:

- Memory pools allow memory allocation with constant runtime. The memory release is also much faster than the free/delete implementation, native to C and C++ respectively.

- Memory pools can be grouped into hierarchical tree structures, which is suitable for special programming structures such as loops and recursions.

- Fixed-size block memory sets do not need to store allocation metadata for each allocation, describing characteristics such as the size of the allocated block. Particularly for small allocations, this provides substantial space savings.

- It allows the deterministic behavior in real-time systems, avoiding errors of lack of memory.

In this manager, allocation, release and memory checking functions were implemented. See the examples before implementing it in your firmware.

### DataBank

A Memory Pools manager for the C primitives (8-bit, 16-bit, 32-bit, and 64-bit variables) has been implemented in this library, **as long as their size does not exceed 64-bits**. The idea is to provide the user with automated dynamic allocation functions, always allocating pre-allocated Memory Pools in this library, similar to a database. This type of management is similar to a hierarchical tree, where each variable is directed to a specific Memory Pool according to its size.

Control, allocation, and deallocation functions are present in this library. See the examples before implementing it in your firmware.

### LinkedList

Two types of linked lists were implemented in this library, one typed and the other untyped. Even with Memory Pools, a major
Dynamic allocations are memory fragmentation. An advantage of threaded lists is that they can solve this problem completely if implemented in conjunction with Memory Pools. Another great advantage is that you do not have to enter the maximum size of these lists: Just add data while there is free memory space in your Memory Pool.

Typed lists are those where the elements of it will be of only a single type, which is informed in the creation of the list. Untyped ones can have elements of any type, provided the size of each die is informed at the time of memory allocation.

A major disadvantage of this approach is the increase in memory consumption over simple static or dynamic allocation. To calculate the space required to store a set of data, we have the following equations:

For typed threaded lists:
		
	Bytes = sum (sizeof (YourVariables)) + numerOfVariables * sizeof (uelem_t) + sizeof (list_t)

For untyped threaded lists:
		
	Bytes = sum (sizeof (YourVariables)) + numberOfVariables * sizeof (telem_t) + sizeof (list_t)

At where:
		
	sizeof (uelem_t) = 2 * sizeof (void *)
	sizeof (telem_t) = 2 * sizeof (void *) + sizeof (uint8_t)
	sizeof (list_t) = sizeof (uint8_t) + sizeof (uint16_t) + 2 * sizeof (void *)

Each processor sets a size for the pointers. In an Arduino UNO (ATMega328p), for example, to save a variable in a typed list, we have to reserve:

	Bytes = 10 + 1 + sizeof (YourVariable)
	Bytes = 11 + sizeof (YourVariable)

As you can see, storing any data requires 11 bytes more than direct storage in memory: A char, for example, would consume 12 bytes of memory if allocated in a typed chained list and 1 byte if allocated statically or dynamically. One should then use this artifice with caution. See the examples before implementing them in your firmware. **The linked lists of this solution support storing non-primitive C types as long as the size of this type does not exceed 64-bits**.

### Buffer

A buffer manager has been implemented in this library. With this manager, you can handle **circular**, **stack** or **queue** type buffers. The operation of this buffer consists of the static or dynamic allocation of the memory pools, aiming at a greater simplification of the tool. The advantages of this endless vector in relation to the threaded list implementation of this set of libraries are:

- Lower cost of memory;
- Increased speed of access and data recording.

A major disadvantage is overwriting data if the buffer reaches its limiting amount of data.

### How to use this library in C ++?

To use it in C ++ written code, simply change the file extensions of that library from .c to .cpp.

### License

#### GNU Lesser General Public License v3.0

Permissions of this copyleft license are conditioned on making available complete source code of licensed works and modifications under the same license or the GNU GPLv3. Copyright and license notices must be preserved. Contributors provide an express grant of patent rights. However, a larger work using the licensed work through interfaces provided by the licensed work may be distributed under different terms and without source code for the larger work.

Permissions:

- Commercial use;
- Modification;
- Distribuition;
- Patent Use;
- Private Use;

Limitations:

- Liability;
- Warranty;

Conditions:

- License and copyright notice;
- Disclose source;
- State changes;
- Same license (library);

For more informations, check the _LICENSE_ document. If you want to use a commercial product without having to provide the source code, send an email to jorge_henrique_123@hotmail.com to talk.

### How can I contribute?

You can contribute to this project in several ways:

- Improving the algorithm;
- Fixing bugs;
- Improving documentation;
- Testing the algorithms and reporting errors;
- Solving problems of any kind using this library and sharing the solution to the community;

**Caution:** _Codes follow the **MISRA** pattern. Codes that do not follow this pattern **will not** enter the solution._

The exception is the use of dynamic memory allocation, but only in the latter case.

### Author

This system was developed by ** orge Henrique Moreira Santana**:
   - Electronic Technician by SENAI
   - Electrical Engineer with emphasis in Automation and Control by the Federal University of Uberlândia

## Português

### Introdução

Em algumas ocasiões, precisamos alocar memória ou vetores infinitos para um dado qualquer em tempo de execução. Em C temos disponível funções para alocação de memória, como **malloc** e **calloc**. Não existem problemas quando o software é executado por cima de um gerenciador de memória (MMU) ou sistema operacional, como Windows e Linux. O problema é quando não temos esse recurso disponível: 

Podem ocorrer vários problemas, como acidentes de alocação, fragmentação de memória, dentre outros. Em sistemas embarcados ainda há mais um problema: As alocações não possuem um tempo de execução pré-estabelecido.

Em linguagens de programação mais modernas (Java, por exemplo) existem diversos mecanismos que permitem que a alocação de memória seja simples e segura.

O conjunto de bibliotecas foi feito em C visando atingir a maior parte de programadores embarcados. A vantagem de se utilizar a biblioteca em C é a velocidade de execução e a economia de memória , já que classes geram muito lixo de memória.

### Bits

Com essa biblioteca é possível desde a manipulação de bits em uma variável até a criação de vetores de bits. São ideais em programas que possuam muitas variáveis binárias por ter uma grande economia de memória, além de ser manipulada mais rapidamente pelo processador/microcontrolador.

### MemoryPool

Memory Pools são blocos de tamanho fixo de alocação. Essa biblioteca gerencia esses blocos de memória, permitindo alocação e desalocação dinâmica de memória comparável a malloc do C ou ao operador new, do C++. Esse conceito era muito usado em video-games mais antigos, devido a sua velocidade de execução. O JAVA também utiliza esse conceito para as suas alocações.

Como as implementações de alocação de memória nativas do C/C++ sofrem fragmentação devido aos tamanhos de blocos variáveis, não é recomendável usá-las em um sistema de tempo real devido ao desempenho. A idéia aqui é a pré-alocação de vários blocos de memória com o mesmo tamanho: O gerenciador pode alocar, acessar e liberar esses blocos pré-alocados. Existem vários benefícios com essa abordagem, dentre elas:

 - Os pools de memória permitem a alocação de memória com tempo de execução constante. A liberação de memória também é muito mais rápida do que a implementação free/delete, nativas do C e do C++ respectivamente.

 - Os pools de memória podem ser agrupados em estruturas de árvore hierárquicas, o que é adequado para estruturas de programação especiais, como loops e recursões.

 - Os conjuntos de memória de bloco de tamanho fixo não precisam armazenar metadados de alocação para cada alocação, descrevendo características como o tamanho do bloco alocado. Particularmente para pequenas alocações, isso proporciona economia substancial de espaço.

 - Permite o comportamento determinístico em sistemas em tempo real, evitando erros de falta de memória.

Nesse gerenciador, foram implementadas funções de alocação, liberação e checagem de memória. Consulte os exemplos antes de implementá-la em seu firmware.

### DataBank

Foi implementado nessa biblioteca um gerenciador de Memory Pools para os tipos primitivos do C (variáveis de 8-btis, 16-bits, 32-bits e 64-bits) e não primitivos, **desde que o tamanho destes não ultrapassem 64-bits**. A idéia é proporcionar ao usuário funções de alocação dinâmicas automatizadas, sempre alocando dos Memory Pools pré-alocados nessa bilbioteca, semelhante a um banco de dados. Esse tipo de gerenciamento é semelhante a uma arvore hierárquica, onde cada variável é direcionada para um Memory Pool específico de acordo com o seu tamanho. 

Funções de controle, alocação e desalocação estão presentes nessa biblioteca. Consulte os exemplos antes de implementá-la em seu firmware.

### LinkedList

Foram implementadas nesta biblioteca dois tipos de listas encadeadas, sendo uma tipada e a outra não tipada. Mesmo com Memory Pools, um grande problema das alocações dinâmicas é a fragmentação de memória. Uma vantagem das listas encadeadas é que elas conseguem resolver esse problema por completo se implementadas juntamente com Memory Pools. Uma outra grande vantagem é que não é preciso informar o tamanho máximo dessas listas: Basta ir adicionando dados enquanto houver espaço de memória livre no seu Memory Pool.

Listas tipadas são aquelas onde os elementos dela serão de apenas um único tipo, que é informado na criação da lista. Já as não tipadas podem ter elementos de qualquer tipo, desde que seja informado o tamanho de cada dado no momento da alocação de memória.

Uma grande desvantagem dessa abordagem é do aumento do consumo de memória em relação a alocação estática ou dinâmica simples. Para calcular o espaço necessário para armazenar um conjunto de dados, temos as equações abaixo:

Para listas encadeadas tipadas:
      
	Bytes = somatório(sizeof(SuasVariaveis)) + numeroDeVariaveis*sizeof(uelem_t) + sizeof(list_t)

Para listas encadeadas não-tipadas:
      
	Bytes = somatório(sizeof(SuasVariaveis)) + numeroDeVariaveis*sizeof(telem_t) + sizeof(list_t)

Onde:

	sizeof(uelem_t) = 2*sizeof(void*)
	sizeof(telem_t) = 2*sizeof(void*) + sizeof(uint8_t)
	sizeof(list_t) = sizeof(uint8_t) + sizeof(uint16_t) + 2*sizeof(void*)

Cada processador define um tamanho para os ponteiros. Em um Arduino UNO (ATMega328p), por exemplo, para guardar uma variável em uma lista tipada, teremos que reservar:

	Bytes = 10 + 1 + sizeof(SuaVariavel)
	Bytes = 11 + sizeof(SuaVariavel)

Como pode-se notar, o armazenamento de qualquer dado requer 11 bytes a mais que o armazenamento direto na memória: Um char, por exemplo, consumiria 12 bytes de memória se alocado em uma lista encadeada tipada e 1 byte se alocado estaticamente ou dinamicamente. Deve-se então utilizar esse artifício com cautela. Consulte os exemplos antes de implementá-las em seu firmware. **As listas encadeadas desta solução suportam armazenamentos de tipos nao-primitivos do C desde que o tamanho deste tipo nao ultrapasse 64-bits**.

### Buffer

Um gerenciador de buffers foi implementado nesta biblioteca. Com esse gerenciador, você pode manipular buffers do tipo **circular**, **pilha** ou **fila**. O funcionamento deste buffer consiste na alocação estatica ou dinâmica dos memory pools, visando uma maior simplificação da ferramenta. As vantagens deste vetor sem fim em relação a implementação de lista encadeada desse conjunto de bibliotecas são:

- Menor custo de memória;
- Maior velocidade de acesso e gravação dos dados.

Uma grande desvantagem é a sobrescrição de dados caso o buffer atinja sua quantidade limite de dados.

### Como utilizar essa bilbioteca em C++?

Para usá-la em códigos escritos em C++, basta mudar as extensões dos arquivos dessa biblioteca de .c para .cpp.

### Licença

### GNU Lesser General Public License v3.0

As permissões desta licença de copyleft estão condicionadas a disponibilizar o código fonte completo de trabalhos licenciados e modificações sob a mesma licença ou a GNU GPLv3. Direitos autorais e avisos de licença devem ser preservados. Os colaboradores fornecem uma concessão expressa de direitos de patente. No entanto, um trabalho maior usando o trabalho licenciado por meio de interfaces fornecidas pelo trabalho licenciado pode ser distribuído sob termos diferentes e sem código-fonte para o trabalho maior.

Permissões:

- Uso comercial;
- Modificações;
- Distribuição;
- Uso em patentes;
- Uso privado;

Limitações:

- Responsabilidade;
- Garantia;

Condições:

- Licença e aviso de direitos autorais;
- Divulgação do código fonte;
- Mudanças de estado;
- Compatibilidade de licenças (para bibliotecas);

Para maiores detalhes, checar o documento _LICENSE_. Caso queira utilizar em um produto comercial sem a disponibilização do código fonte, envie um e-mail para jorge_henrique_123@hotmail.com para conversarmos.

### Como posso ajudar?

Você pode contribuir para este projeto de várias maneiras:

- Melhorando o algoritmo;
- Corrigindo bugs;
- Melhorando a documentação;
- Testando os algoritmos e reportando erros;
- Resolvendo problemas de qualquer natureza utilizando essa biblioteca e compartilhando a solução para a comunidade;

**Atenção:** _Os códigos seguem o padrão **MISRA**. Códigos que não seguem esse padrão **não** entrarão na solução._

### Autor

Este sistema foi desenvolvido por **Jorge Henrique Moreira Santana**:
  - Técnico em Eletrônica pelo SENAI
  - Engenheiro Eletricista com ênfase em Automação e Controle pela Universidade Federal de Uberlândia
