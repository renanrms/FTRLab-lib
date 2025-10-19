<a href="https://registry.platformio.org/libraries/renanrms/FTRLab"><img src="https://badges.registry.platformio.org/packages/renanrms/library/FTRLab.svg" alt="PlatformIO Registry" /></a>

# Biblioteca FTRLab

Biblioteca para programação de dispositivos de aquisição de dados em experimentos didáticos que se integram à aplicação [FTRLab desktop](https://github.com/renanrms/FTRLab-desktop). O propósito da Lib é cuidar das tarefas envolvidas por debaixo dos panos, para que o utilizador desenvolva apenas o código específico de medição de cada sensor, ou inclua um sensor previamente implementado.

Habilita comunicação por Wi-Fi, sincronização de tempo, descoberta do dispositivo em uma rede, perfilamento e envio de medições, geração de mensagens de log, e outras funcionalidades automaticamente.

Atualmente funcional para o microcontrolador ESP32.

## Primeiros passos

### Construção de um dispositivo FTRLab

Para criar um dispositivo será necessário montar um protótipo com ESP32 e algum sensor de interesse, e programar um firmware simples para leitura dos sensores importando a biblioteca. Ver [exemplos](#exemplos).

Recomendamos fortemente utilizar a [PlatformIO IDE](#plataformio), como extensão do VScode, para desenvolvimento, compilação e upload do firmware para o dispositivo.

### Exemplos

Veja a [pasta de exemplos](https://github.com/renanrms/FTRLab-lib/tree/main/examples). Cada subpasta contém um exemplo diferente, com um arquivo `platformio.ini`, que torna o diretório um projeto de firmware PlatformIO. Assim você pode abrir a pasta no VScode e utilizar os botões da interface para fazer upload e visualização da saída no serial monitor, ou utilizar a ferramenta CLI.

Perceba que em cada exemplo, a biblioteca é incluída sem especificar uma versão no arquivo `platformio.ini`. Para programar um firmware prefira indicar a versão da lib como recomendado na [seção sobre instalação](https://registry.platformio.org/libraries/renanrms/FTRLab/installation).

## PlatformIO

### Informações gerais

Para utilizar PlatformIO como extensão do VSCode veja a [documentação do PlatformIO](https://docs.platformio.org/en/latest/integration/ide/vscode.html#installation). Ela mostra passo a passo como instalar e utilizar a interface para fazer o upload do firmware. Após a instalação do [PlatformIO Core (CLI)](https://docs.platformio.org/en/latest/core/index.html#piocore), para ser capaz de fazer upload dos exemplos para as placas, verifique ainda a página [udev-rules](https://docs.platformio.org/en/latest/core/installation/udev-rules.html).

Também será útil [instalar os comandos Shell](https://docs.platformio.org/en/latest/core/installation/shell-commands.html), para facilitar build e upload via linha de comando. Feito isto, navegue até uma pasta que contém um projeto de firmware PlatformIO (como um dos exemplos) e execute o comando:

```shell
pio run --target upload
```

## Limpeza da memória flash

Um dispositivo com firmware do FTRLab utiliza a memória flash do microcontrolador para armazenar alguns dados de forma persistente, como credenciais de redes conectadas previamente. Estes dados permanecem na memória mesmo após fazer upload de um novo firmware, o que em geral não causa nenhum problema. Mas se for necessário apagar os dados por garantia ou por alguma alteração no formato dos dados salvos, é necessário apagar a memória flash (e o firmware consequentemente).

Para isso são usadas as ferramentas da espressif. Para instalá-las, certifique-se de ter python e pip instalados e depois use os comandos:

```shell
pip install esptool
pip install setuptools
```

Depois, para zerar a memória efetivamente, pressione continuamente o botão BOOT da placa e rode o comando:

```shell
python -m esptool --chip esp32 erase_flash
```

## Desenvolvimento da Lib

As recomendações para desenvolvimento da lib são muito semelhantes às de utilização. É necessário fazer a compilação e upload de um firmware que utilize a biblioteca para verificar seu funcionamento enquanto a lib é editada, o que pode ser feito com um dos exemplos. Neste caso a instalação da CLI do Platformio será essencial.

Para se utilizar a lib na versão local sendo editada, ao invés de baixar a versão publicada, utilize um caminho local na propriedade `lib_deps` do `platformio.ini`. Além disso, pode ser feito o build com modo de debug para ver erros de execução com mensagens mais completas. Nos exemplos da pasta examples, ficaria assim:

```
[env:esp32dev]
...
monitor_filters = esp32_exception_decoder
lib_deps = ../../
build_type = debug
```

Também é muito útil ter endereços decodificados para linhas quando ocorre um erro e o dispositivo imprime um stack trace. Para isso `esp32_exception_decoder` deve estar listado na propriedade `monitor_filters`, como indicado acima. O serial monitor deve ser chamado na pasta que contém este platformio.ini com o filtro, o que pode ser feito navegando até o diretório e usando o comando:

```shell
pio device monitor
```

Além disso, quando a lib já estiver instalada, é necessário a desinstalar antes de cada upload para forçar a reinstalação e posteriormente o build com a versão local mais recente.

```shell
pio pkg uninstall -l FTRLab
```
