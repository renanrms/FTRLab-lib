# Biblioteca FTRLab - Sistema Embarcado

Esta é uma biblioteca para programação de dispositivos de aquisição de dados para o software FTRLab. Por enquanto o código está estruturado em pastas como um projeto de firmware do [PlatformIO](https://platformio.org/) e não como um projeto de biblioteca, pois está sendo desenvolvido em conjunto com um exemplo da biblioteca, mas em breve o projeto será estruturado como uma biblioteca e o exemplo disponibilizado na pasta de exemplos.

## Como usar

### Criaçao do dispositivo FTRLab

Quando a biblioteca for tranformada para a estrutura de Lib e publicada no PlatformIO, serão dadas informações mais detalhadas. Por enquanto, para criar um dispositivo FTRLab é necessário copiar este projeto e modificar o código da pasta `/src`, criando os sensores desejados e adicionando-os ao objeto `board`.

Com um código finalizado, fazer a compilação e o upload do firmware para um ESP32, depois conectá-lo ao conjunto de sensores projetados.

### Compilação e upload do firmware

O projeto foi desenvolvido usando o ambiente de desenvolvimento integrado PlatformIO, como extensão do VScode. A maneira recomendada de alterar, compilar, ou fazer upload do firmware é usar esta mesma ferramenta. Para mais informações ver a [documentação do PlatformIO](https://docs.platformio.org/en/latest/integration/ide/vscode.html#ide-vscode).

### Limpeza da memória flash

Um dispositivo com firmware do FTRLab utiliza a memória flash do microcontrolador para armazenar alguns dados de forma persistente, como credenciais de redes conectadas previamente. Estes dados permanecem na memória mesmo após fazer upload de um novo firmware, o que em geral não causa nenhum problema. Mas se for necessário apagar os dados por garantia ou por alguma alteração no formato dos dados salvos, é necessário apagar a memória flash (e o firmware consequentemente).

Para isso são usadas as ferramentas da expressif. Para instalá-las, certifique-se de ter python e pip instalados e depois use os comandos:

```shell
pip install esptool
pip install setuptools
```

Depois, para zerar a memória efetivamente, pressione continuamente o botão BOOT da placa e rode o comando:

```shell
python -m esptool --chip esp32 erase_flash
```

