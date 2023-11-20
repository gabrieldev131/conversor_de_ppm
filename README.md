# conversor_de_imagem_ppm

Este programa foi produzido para um trabalho universitário da disciplina Estrutura de Dados, sob tutoria do Prof. Thiago M. Paixão, no IFES CAMPUS SERRA, juntamente com meu colega Davi de Assis.
Ele é um conversor de imagem ppm (portable pix map), do qual converte imagens coloridas (tipo P3) em imagens em nivel de cinza (tipo P2). Em seu programa principal, há um menu do qual lhe dará opções, desde converter de rgb para niveis de cinza, á nomear o arquivo.

Como usar:
Coloque todos os arquivos na mesma pasta, depois use os comandos "make all" e "./main" no prompt de comando (shell), nesta ordem, que o arquivo executavel será gerado e o programa será executado, respectivamente.

O que será feito:

O primeiro menu sempre será exibido no inicio e após cada conversão, até que seja pedido para sair

O segundo menu diz respeito a qual arquivo deve ser convertido, caso não seja escolhido, uma imagem padrão será convertida como exemplo

O terceiro menu diz respeito ao nome para criação do arquivo, caso não seja escolhido, a imagem convertida receberá o nome "arquivo.ppm"

Caso tudo ocorra como esperado, o programa voltará ao menu inicial

Caso as opções mostradas no display não sejam escolhidas, é retornada uma mensagem de erro e o programa retorna ao inicio

Informações sobre a implementação:
A struct usada (Image), foi implementada pensando nos dados de cabeçalho (tipo, dimensões e valor máximo dos pixels), dessa forma, é evidente que as notas de cabeçalho deve estar na estrutura, quanto a aos dados do pixels, diversas formas foram pensadas, desde usar uma struct adicional para cada tipo, até fazer ponteiro para funções dentro da struct, mas nenhuma dessas foi usada, visto que o uso de memória e processamento de dados seria muito ampliado e existia uma maneira mais simples de se fazer: matrizes. Como o universo das imagens PPMs é diverso, com diferentes dimensões, tais matrizes deveriam ser dinâmicas e se adaptar ao tamanho de cada imagem e ao seu tipo. Pensando nisso, foi se usado um ponteiro para ponteiros (ponteiro duplo).
Essa estratégia foi muito útil e bem mais simples que as anteriores, alem de ser mais econômica. Com isso, a função create() pode ser pensada como uma alocação dinâmica de matrizes, onde a única mudança entre o tipo P3 e P2 é que o tipo P3 possui uma multiplicação por 3 nas colunas (alocar o RGB), já o tipo P2, tem apenas uma simples alocação das dimensões dadas (linha x coluna), usando menos memória que se utiliza-se um mesmo tipo de alocação para ambos os tipos.
Na função load_from_ppm() tive algumas dificulcades, visto que era nescessário alocar memória para a variável que armazenaria os dados do tipo Image do arquivo a ser convertido, algumas horas foram perdidas, mas o mesmo erro não mais ocorreu novamente (aprendi com os erros hehe). 
As funções write_to_ppm() e rgb_to_gray foram bem simples e não representam problemas, chegaram até serem triviais ao código, visto que a parte mais dificl eram alocar memória
e extrair dados do arquivo.
O arquivo main.c foi a parte que mais demandou tempo visto que para implementar o TAD haviam muitos pontos, como o menu, que deveria voltar ao inicio ao fim de cada conversão. Foram boas horas olhando a tela sem entender o motivo de não funcionar e no fim, eram alguns erros de código (lixos não apagados nas funções em image.c), dos quais foram corrigidos. No fim, vejo que foi bem mais simples que eu imaginei que seria, pricipalmente visto que o uso de ferramentas para meu auxilio (chatGPT, stackoverflow, github...) não foram tão usadas, ao menos não para o trabalho como um todo, mas sim como auxiliares para afagar-me no desespero (basicamente usei estas ferramentas para mostrar algumas funções das bibliotecas padrões e foram muito úteis para o aprendizado), mas afirmo que este programa foi feito com minhas próprias mãos.
