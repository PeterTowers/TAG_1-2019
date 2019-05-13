# Project 2 - Topological sort and critical path in a DAG
This project constructs a weighted digraph using '/data/materias.txt' file, utilizing adjacency list. We implemented the
following features to the digraph:
1. Topological sorting;
2. Critical path; and
3. Print the digraph on a `.dot` file in order to create an image of it.

## Critical path
The critical path is calculated as the sum of each course's credits (including the last one on the path). If there's a
tie, it'll select the path with most nodes.

## Printing the graph as an image
This program creates `.dot` files of:
1. The digraph (`/data/adjacency_list.dot`);
2. The digraph topologically ordered (`/data/topological_order.dot`);
3. It's critical path (`/data/critical_path.dot`).
In order to create each image, it's necessary to use [Graphviz](http://www.graphviz.org/). You can create the images
on Graphviz's pocket guide [website](https://graphs.grevian.org/graph) or using their software. In order to do so with
their software, you need to run the following line on your terminal:

```bash
dot -T<output file format> <path to .dot file> -o <desired output file name>
```

We recommend `.svg` file format (`-Tsvg`). If you don't want to bother with an output file name, it's possible to use
`-O` (capital `O`) flag instead of '-o'.

# Projeto 2 - Ordernacão topológica e caminho crítico em um DAG
Este programa utiliza o arquivo './data/materias.txt' para montar um dígrafo com peso, utilizando lista de
adjacência. Implementamos as seguintes funções sobre o dígrafo:
1. Ordenação topológica;
2. Caminho crítico; e
3. Impressão do dígrafo em um arquivo com terminação `.dot` para criar uma imagem do grafo.

## Caminho crítico
O camihnho crítico é calculado como a soma dos créditos de cada matéria no caminho (incluindo a última). Caso haja um
empate, o algoritmo irá escolher o caminho com maior número de nós.

## Impressão do dígrafo como uma imagem
Este programa cria arquivos `.dot` do:
1. Dígrafo (`/data/adjacency_list.dot`);
2. A ordenação topológica do dígrafo (`/data/topological_order.dot`);
3. Caminho crítico do dígrafo (`/data/critical_path.dot`).

Para criar cada imagen, é necessário utilizar o [Graphviz](http://www.graphviz.org/). É possível criar as imagens
utilizando o site do [guia de bolso do Graphviz](https://graphs.grevian.org/graph) ou o software. Nesse último caso é
preciso executar o seguinte comando no terminal:

```bash
dot -T<formato do arquivo de saída> <caminho para o arquivo .dot> -o <nome desejado do arquivo de saída>
```

Nós recomendamos o formato `.svg` (`-Tsvg`). Caso deseje nomear o arquivo de saída de forma automática, basta substituir
a _flag_ `-o` por `-O` (`O` maiúsculo).