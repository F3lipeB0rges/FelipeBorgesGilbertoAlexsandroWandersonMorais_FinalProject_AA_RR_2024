# Projeto Final de Análise de Algoritmos

### Projeto desenvolvido por Felipe Rubens de Sousa Borges, Gilberto Alexsandro Almeida Pessoa e Wanderson Morais de Sousa

A codificação Huffman é um dos algoritmos mais simples para compactar dados. Embora, seja
muito antigo e simples, ainda é amplamente utilizado (por exemplo: em alguns estágios de JPEG,
MPEG, etc.). Neste projeto, foi implementado a codificação e decodificação huffman. 
- O sistema recebe como entrada um arquivo contendo uma página html (exemplo,
um artigo da Wikipedia) e forma uma árvore binária (huffman) para o mesmo; 
- Durante a construção da huffman tree, foi utilizada uma fila de prioridade para selecionar nós com
menores frequências; 
- Depois de construir a árvore, foi percorrida a árvore e criado um dicionário de palavras de código
(letra para código); 
- Dadas quaisquer novas frases, o sistema mostra como a sentença é convertida em
código de huffman e depois decodificada de volta para a sentença original; 
- Foi utilizada a biblioteca externa GraphViz para exibir árvore huffman criada para cada página.
